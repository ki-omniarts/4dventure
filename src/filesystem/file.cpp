// {{{ LICENSE
/*
 * file.cpp
 * This file is part of 4dventure
 *
 * Copyright (C) 2014 - KiNaudiz
 *
 * 4dventure is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 * 4dventure is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with 4dventure If not, see <http://www.gnu.org/licenses/>.
 *
 * This file is inspired by Löve
 * <https://bitbucket.org/rude/love/src/c44b99f7e020/src/modules/filesystem/?at=default>
 */
// }}} LICENSE

// {{{ Includes
#include "file.hpp"

#include <stdexcept>
#include <cstring>
// }}} Includes

using namespace fs;

// std::unordered_map<char,MODE> File::modeMap_
// { 
//     { 'c' , File::CLOSED },
//     { 'r' , File::READ   },
//     { 'w' , File::WRITE  },
//     { 'a' , File::APPEND }
// }
//
// std::unordered_map<std::string,MODE> File::bufferModeMap_
// { 
//     { "none" , File::BUFFER_NONE },
//     { "line" , File::BUFFER_LINE },
//     { "full" , File::BUFFER_FULL },
// }

File::File(const std::string& filename)
    : filename_(filename)
    , file_(nullptr)
    , mode_(CLOSED)
    , bufferMode_(BUFFER_NONE)
    , bufferSize_(0)
{}

File::~File() noexcept
{
    try {
        if (mode_ != CLOSED)
            close();
    } catch (const std::exception& e) {}
}

// {{{ File::Data
File::Data::Data(File::size_type size,const std::string& filename)
    : data_(new char[static_cast<size_t>(size)])
    , size_(size)
    , filename_(filename)
{}

File::Data::Data() noexcept
{
    delete(nowthrow)[] data_;
}
// }}} File::Data

// {{{ File::open()
bool File::open(Mode mode)
{
    if (mode == CLOSED)
        return true;

    if (mode == READ && !PHYSFS_exists(filename_.c_str()))
    {
        std::string tmp{"File "};
        tmp += filename;
        tmp += " does not exist!";
        throw std::runtime_error(tmp);
    }

    if ((mode == APPEND || mode == WRITE) && PHYSFS_getWriteDir() == 0)
        throw std::runtime_error("Could not set write directory!");

    if (file_ != nullptr)
        return false;

    mode_ = mode;

    switch (mode_)
    {
        case READ:
            file_ = PHYSFS_openRead(filename_.c_str());
            break;
        case APPEND:
            file_ = PHYSFS_openAppend(filename_.c_str());
            break;
        case WRITE:
            file_ = PHYSFS_openWrite(filename_.c_str());
            break;
        case default:
            break;
    }
    
    if (file_ && !setBuffer(bufferMode_,bufferSize_))
    {
        bufferMode_ = BUFFER_NONE;
        bufferSize_ = 0;
    }

    return static_cast<bool>(file_);
}
// }}} File::open()

// {{{ File::close()
bool File::close()
{
    if (!PHYSFS_close(file_))
        return false;
    mode_ = CLOSED;
    file_ = nullptr;
    return true;
}
// }}} File::close()

// {{{ File::isOpen()
bool File::isOpen() const
{
    return mode_ != CLOSED && file_ != 0;
}
// }}} File::isOpen()

// {{{ File::size()
File::size_type File::getSize()
{
    if (file_ == nullptr)
    {
        open(READ);
        auto size = static_cast<File::size_type>(PHYSFS_fileLength(file_));
        cloase();
        return size;
    }

    return static_cast<File::size_type>(PHYSFS_fileLength(file_));
}
// }}} File::size()

// {{{ Data* File::read()
std::shared_ptr<File::Data> File::read(File::size_type size)
{
    bool isOpen = !file_;

    if (!file_ && !open(READ))
    {
        std::string tmp{"Could not open file "};
        tmp += filename_;
        tmp += ".";
        throw std::runtime_error(tmp);
    }

    auto max = getSize();
    size = (size==ALL)?max:size;
    auto cur = tell();

    if (size < 0)
        throw std::logic_error("Invalid read size!");
    
    if (cur < 0)
        cur = 0;
    else if (cur > max)
        cur = max;

    if (cur+size > max)
        size = max - cur;

    std::shared_ptr<Data> data{new Data(size,getFilename())};
    File::size_type bytesRead = read(data->getData(),size);

    if (bytesRead < 0 || ( bytesRead == 0 && bytesRead != size))
        throw std::runtime_error("Could not read from file.");
    if (bytesRead < size)
    {
        std::shared_ptr<Data> tmp{new Data(bytesRead,getFilename())};
        std::memcpy(tmp->getData(),data->getData(),
                static_cast<size_t>(bytesRead););
        data = tmp;
    }

    if (isOpen)
        close();

    return data;
}
// }}} Data* File::read()

// {{{ File::size_type File::read()
File::size_type File::read(char* buf,File::size_type size)
{
    if (!file_ || mode_ != READ)
        throw std::runtime_error("File is not opened!");

    {
        auto max = getSize();
        size = (size==ALL)  ? max : size;
        size = (size > max) ? max : size;
    }

    if (size < 0)
        throw std::logic_error("Invalid read size!");

    return static_cast<File::size_type>(PHYSFS_read(file_,buf,1,
                static_cast<PHYSFS_uint64>(size)));
}
// }}} File::size_type File::read()

// {{{ bool File::write()
bool File::write(const char* buf,File::size_type size)
{
    if (!file_ || (mode_ != WRITE && mode_ != APPEND))
        throw std::runtime_error("File is not opened for writing.");

    if (size < 0)
        throw std::logic_error("Invalid write size!");

    auto written = static_cast<File::size_type>(PHYSFS_write(file_,buf,1
                static_cast<PHYSFS_uint64>(size)));

    if (written != size)
        return false;

    if (bufferMode_ == BUFFER_LINE && bufferSize_ > size)
        if (std::memchr(buf,'\n',static_cast<size_t>(size)))
            flush();

    return true;
}
// {{{ bool File::write()

// {{{ Data* File::write()
Data* File::write(const Data* data,File::size_type size)
{
    return write(data->getData(), (size == ALL) ? data_->getSize() : size);
}
// }}} Data* File::write()

// {{{ File::flush()
bool File::flush()
{
    if (!file_ || (mode_ == WRITE && mode_ == APPEND))
        throw std::runtime_error("File not opened for writing.");

    return PHYSFS_flush(file_);
}
// }}} File::flush()

// {{{ File::eof()
bool File::eof()
{
    if (!file_ || PHYSFS_eof(file_))
        return true;
    return false;
}
// }}} File::eof()

// {{{ File::tell()
File::size_type File::tell()
{
    if (!file_)
        return -1;
    
    return static_cast<File::size_type>(PHYSFS_tell(file_));
}
// }}} File::tell()

// {{{ File::seek()
bool File::seek(File::size_type pos)
{
    if (!file_)
        return false;

    if (!PHYSFS_seek(file_,static_cast<PHYSFS_uint64>(pos)))
        return false;
    return true;
}
// }}} File::seek()

// {{{ File::setBuffer()
bool File::setBuffer(BufferMode bufferMode,File::size_type size)
{
    if (size < 0)
        return false;

    if (!file_ || mode_ == CLOSED)
    {
        bufferMode_ = bufferMode;
        bufferSize_ = size;
        return true;
    }

    int ret = 1;

    switch (bufferMode)
    {
        case BUFFER_NONE:
        default:
            ret = PHYSFS_setBuffer(file_,0);
            break;
        case BUFFER_LINE:
        case BUFFER_FULL:
            ret = PHYSFS_setBuffer(file_,size);
    }

    if (ret == 0)
        return false;

    bufferMode_ = bufferMode;
    bufferSize_ = size;

    return true;
}
// }}} File::setBuffer()

// {{{ File::getBuffer()
File::BufferMode File::getBuffer(File::size_type& size) const
{
    size = bufferSize_;
    return bufferMode_;
}
// }}} File::getBuffer()
