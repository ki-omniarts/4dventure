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
    bool valid_ = false;

    Tiles tiles_ = {};

    // Symbols
    std::vector<char> symbols_  = {};
    static const std::vector<char> reservedSymbols_; 

    // Functions
    void generateTiles_(const std::string& mapstring);

    public:
        Map() = default;
        Map(const std::string& mapstring);
        Map(const Map& other);
        Map& operator=(const Map& other);
        Map(Map&& other);
        Map& operator=(Map&& other);
        virtual ~Map();

        // Getter
        bool valid() { return valid_; }
        const Point startpoint();
        bool exists(const Point& p);
        char symbol(const Point& p) { return tiles_[p.y()][p.x()].tile(); }
};

#endif
