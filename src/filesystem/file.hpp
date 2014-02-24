// {{{ LICENSE
/*
 * file.hpp
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

// {{{ Include Guards
#ifndef ADVENTURE_FS_FILE_HPP
#define ADVENTURE_FS_FILE_HP
// }}} Include Guards

// {{{ Includes
#include <string>

extern "C"
{
    #include "physfs.h"
}
// }}} Includes

// {{{ namespace
namespace fs 
{
// }}} namespace

// {{{ File
class File 
{
    // {{{ Public Constants
    public:
        using size_type = long long int;

        enum Mode
        {
            CLOSED,
            READ,
            WRITE,
            APPEND,
            MODE_MAX_ENUM
        };

        enum BufferMode
        {
            BUFFER_NONE,
            BUFFER_LINE,
            BUFFER_FULL,
            BUFFER_MAX_ENUM
        };

        static constexpr size_type ALL = -1;

        // {{{ File::Data
        class Data
        {
            public:
                enum Decoder
                {
                    FILE,
                    BASE64,
                    DECODE_MAX_ENUM
                };

            private:
                char* data_;
                File::size_type size_;
                std::string filename_;

            public:
                Data(File::size_type size, const std::string& filename);
                virtual ~Data() noexcept;

                char *getData() const
                { return data_; }
                File::size_type getSize() const
                { return size_; }
                std::string getFilename() const
                { return filename_; }
        };
        // }}} File::Data
    // }}} Public Constants

    private:
        std::string filename_;
        PHYSFS_File* file_;

        Mode mode_;
        BufferMode bufferMode_;
        size_type bufferSize_;

        // static std::unordered_map<char,Mode> modeMap_;
        // static std::unordered_map<std::string,Mode> bufferModeMap_;
        
        File(const File&) = delete;
        File& operator=(const File&) = delete;
    
    public:
        File(const std::string& filename);
        virtual ~File() noexcept;

        bool open(Mode mode);
        bool close();

        bool isOpen() const;
        size_type getSize();

        Data* read(size_type size = ALL);
        size_type read(char* buf,File::size_type size);
        bool write(const char* buf,size_type size);
        bool write(const Data* data,size_type size = ALL);
        bool flush();
        bool eof();
        bool tell();
        bool seek(size_type pos);

        bool setBuffer(BufferMode bufferMode,size_type size);
        bool getBuffer(size_type& size) const;

        Mode getMode() const
        { return mode_; }
        std::string getFilename() const
        { return filename_;}
};
// }}} File

// {{{ namespace
} // namespace: fs
// }}} namespace

// {{{ Include Guards
#endif // ADVENTURE_FS_FILE_HPP
// }}} Include Guards
