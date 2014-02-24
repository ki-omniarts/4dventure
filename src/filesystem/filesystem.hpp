// {{{ LICENSE
/*
 * filesystem.hpp
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

// {{{ Include Guard
#ifndef ADVENTURE_FS_FILESYSTEM_HPP
#define ADVENTURE_FS_FILESYSTEM_HPP
// }}} Include Guard

// {{{ Includes
#include "file.hpp"
#include <memory>

extern "C"
{
    #include "lua.h"
}
// }}} Includes

namespace fs 
{

class Filesystem
{
    private:
        std::string cwd_;
        std::string gameSrc_;

        // Singleton
        Filesystem();
        virtual ~Filesystem() noexcept;

        Filesystem(const Filesystem&) = delete;
        Filesystem& operator=(const Filesystem&) = delete;
        Filesystem(Filesystem&&) = delete;
        Filesystem& operator=(Filesystem&&) = delete;

        static Filesystem instance_;

    public:
        static Filesystem& fs();

        void init(char* arg0);

        bool setSource(const std::string& source);
        std::string getSource() const
        { return gameSrc_; }

        bool mount(const char* archive,const char* mountpoint,bool append);
        bool umount(const char* archive);

        std::shared_ptr<File> newFile(const char* filename);
        std::shared_ptr<File::Data> newFileData(void* data,size_t size,
                const char* filename) const;
        // std::shared_ptr<File::Data> newFileData(const char* b64,
        //         const char* filename) const; // TODO

        const char* cwd(); // TODO
        const char* getUserDir()
        { return PHYSFS_getUserDir(); }
        std::string getSourceBaseDir() const;

        bool exists(const char* filename)
        { return PHYSFS_exists(filename); }
        bool isDir(const char* dirname)
        { return PHYSFS_isDirectory(dirname); }
        bool isFile(const char* filename)
        { return exists(filename) && !isDir(filename); }

        bool mkdir(const char* dirname);
        bool rm(const char* filename);

        std::shared_ptr<File::Data> read(const char* filename,
                File::size_type size) const;
        void write(const char *filename, const void *data,
                File::size_type size) const;
        void append(const char *filename, const void *data,
                File::size_type size) const;

        int getDirectoryItems(lua_State *L);

        File::size_type getLastModified(const char* filename) const;
        File::size_type getSize(const char* filename) const;


        // TODO
        // https://bitbucket.org/rude/love/src/c44b99f7e020ea4e26124308af10a4f09cca92c2/src/modules/filesystem/physfs/Filesystem.cpp?at=default
};

} // namespace: fs

// {{{ Include Guard
#endif /* end of include guard: ADVENTURE_FS_FILESYSTEM_HPP */
// }}} Include Guard
