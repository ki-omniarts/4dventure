/*
 * map.h
 * This file is part of 4dventure
 *
 * Copyright (C) 2012 - KiNaudiz
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
 * along with 4dventure. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "point.h"

#include <memory>
#include <string>
#include <vector>

class Map 
{
    typedef std::vector<std::vector<Point>> Tiles;
    bool valid_ = false; // TODO: exception?

    struct pImpl
    {
        Tiles tiles = {};
        std::vector<tile_id_t> symbols = {};
    };

    std::unique_ptr<pImpl> data_;

    // Symbols
    static const std::vector<tile_id_t> reservedSymbols_; 

    // Functions
    void generateTiles_(const std::string& mapstring);

    public:
        Map();
        Map(const std::string& mapstring);
        Map(const Map& other);
        Map& operator=(const Map& other);
        Map(Map&& other);
        Map& operator=(Map&& other);
        virtual ~Map() noexcept;

        // Getter
        bool valid() { return valid_; }
        const Point startpoint();
        bool exists(const Point& p);
        tile_id_t symbol(const Point& p) 
            { return data_->tiles[p.y()][p.x()].tile(); }

        friend void swap(Map& lhs,Map& rhs)
        {
            std::swap(lhs.data_,rhs.data_);
        }
};

#endif
