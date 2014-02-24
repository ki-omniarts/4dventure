// {{{ LICENSE
/*
 * filesystem.cpp
 * This file is part of 4dventure
 *
 * Copyright (C) 2014 - KiNauiz
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
#include "filesystem.hpp"

#include <stdexcept>
#include <cstring>
// }}} Includes

using namespace fs;

Filesystem Filesystem::instance_{};

Filesystem::Filesystem()
{}

Filesystem::~Filesystem() noexcept
{
    if (PHYSFS_isInit())
        PHYSFS_deinit();
}

Filesystem* Filesystem::fs()
{
    return instance_;
}

// {{{ Filesystem::init()
void Filesystem::init(char* arg0)
{
    if (!PHYSFS_isInit() && !PHYSFS_init(arg0))
        throw std::runtime_error("Could not initialize PhysicsFS!");
}
// }}} Filesystem::init()

// {{{ Filesystem::setSource()
bool Filesystem::setSource(const std::string& source)
{
    if (!PHYSFS_isInit())
        return false;

    if (!gameSrc_.empty())
        return false;

    if (!PHYSFS_addToSearchPath(source,1))
        return false;

    gameSrc_ = source;

    return true;
}
// }}} Filesystem::setSource()

// {{{ Filesystem::mount()
bool Filesystem::mount(const char* archive,const char* mountpoint,bool append)
{
    if (!PHYSFS_isInit() || !archive)
        return false;

    if (std::strlen(archive)==0 || std::strstr(archive,"..") 
            || std::strcmp(archive,"/") == 0)
        return false;

    std::string realPath;
    {
        const char* realDir = PHYSFS_getRealDir(archive);
        if (!realDir)
            return false;
        realPath = realDir;
    }


    if (realPath.find(gameSrc_) == 0)
        return false;

    realPath += '/';
    realPath += archive;

    return PHYSFS_mount(realPath.c_str(),mountpoint,append);
}
// }}} Filesystem::mount()

// {{{ Filesystem::umount()
bool Filesystem::umount(const char* archive)
{
    if (!PHYSFS_isInit() || !archive)
        return false;

    if (std::strlen(archive)==0 || std::strstr(archive,"..") 
            || std::strcmp(archive,"/") == 0)
        return false;

    std::string realPath;
    {
        const char* realDir = PHYSFS_getRealDir(archive);
        if (!realDir)
            return false;
        realPath = realDir;
    }

    realPath += '/';
    realPath += archive;

    {
        const char *mountpoint = PHYSFS_getMountPoint(realPath.c_str());
        if (!mountpoint)
            return false;
    }

    return PHYSFS_removeFromSearchPath(realPath.c_str());
}
// }}} Filesystem::umount()

// {{{ Filesystem::newFile()
std::shared_ptr<File> Filesystem::newFile()
{
    return std::shared_ptr<File>(new File(filename));
}
// }}} Filesystem::newFile()

// {{{ Filesystem::newFileData()
std::shared_ptr<File::Data> Filesystem::newFileData(void* data,size_t size,
    const char* filename) const
{
    std::shared_ptr<File::Data> fd{new File::Data(size,filename)};

    std::memcpy(fd->getData(),data,size);

    return fd;
}
// }}} Filesystem::newFileData()

// {{{ Filesystem::getSourceBaseDir()
std::string Filesystem::getSourceBaseDir() const
{
    if (gameSrc_.empty())
        return "";

    // FIXME: doesn't care about '.' or '..'
    auto base_end_pos = gameSrc_.find_last_of('/',gameSrc_.length() - 2);

    if (base_end_pos == std::string::npos)
        return "";

    // Allow "/"
    if (base_end_pos == 0)
        base_end_pos = 1;

    return gameSrc_.substr(0,base_end_pos);
}
// }}} Filesystem::getSourceBaseDir()

// {{{ Filesystem::mkdir()
bool Filesystem::mkdir(const char* dirname)
{
    if (PHYSFS_getWriteDir() == 0 /* && !setupWrightDirectory */)
        return false;

    return PHYSFS_mkdir(dirname);
}
// }}} Filesystem::mkdir()

// {{{ Filesystem::rm()
bool Filesystem::rm(const char* filename)
{
    if (PHYSFS_getWriteDir() == 0 /* && !setupWrightDirectory */)
        return false;

    return PHYSFS_delete(filename);
}
// }}} Filesystem::rm()

// {{{ Filesystem::read()
std::shared_ptr<File::Data> Filesystem::read(const char* filename,
    File::size_type size) const
{
    File file{filename};

    file.open(File::READ);

    return file.read(size);
}
// }}} Filesystem::read()

// {{{ Filesystem::write()
void Filesystem::write(const char *filename, const void *data,
        File::size_type size) const
{
    File file{filename};

    file.open(File::WRITE);

    if(!file.write(data,size))
        throw std::runtime_error("Data could not be written!");
}
// }}} Filesystem::write()

// {{{ Filesystem::append()
void Filesystem::append(const char *filename, const void *data,
        File::size_type size) const
{
    File file{filename};

    file.open(File::APPEND);

    if(!file.write(data,size))
        throw std::runtime_error("Data could not be written!");
}
// }}} Filesystem::append()

// {{{ Filesystem::getDirectoryItems
int Filesystem::getDirectoryItems(lua_State *L)
{
    const char *dir = luaL_checkstring(L, 1);

    std::shared_ptr<char* rc>{PHYSFS_enumerateFiles(dir),PHYSFS_freeList};
    int index = 1;

    lua_newtable(L);

    for (char** i=rc.get();*i!=0;++i)
    {
        lua_pushstring(L,*i);
        lua_setrawi(L,-2,index++);
    }

    return 1;
}
// }}} Filesystem::getDirectoryItems

// {{{ Filesystem::getLastModified
File::size_type Filesystem::getLastModified(const char* filename) const
{
    PHYSFS_sint64 time = PHYSFS_getLastModTime(filename);

    if (time == -1)
        throw std::runtime_error("Could not determine file modification date.");

    return time;
}
// }}} Filesystem::getLastModified

// {{{ Filesystem::getSize
File::size_type Filesystem::getSize(const char* filename) const
{
    File file{filename};
    File::size_type size{file.getSize()};
    return size;
}
// }}} Filesystem::getSize
