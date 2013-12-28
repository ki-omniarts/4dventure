/*
 * point.h
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

#ifndef ADVENTURE_POINT_H
#define ADVENTURE_POINT_H

#include <utility>

typedef unsigned int tile_id_t;

class Point
{
    unsigned int x_     = 0;
    unsigned int y_     = 0;
    // tile id
    tile_id_t tile_     = '$';

    public:
        explicit Point();
        explicit Point(unsigned int x, unsigned int y, tile_id_t tile = '$');
        Point(const Point& other);
        Point(Point&& other);
        Point& operator=(const Point& other);
        Point& operator=(Point&& other);
        virtual ~Point() noexcept;

        unsigned int x() const { return x_; }
        unsigned int y() const { return y_; }
        tile_id_t tile() const { return tile_; } 
};

inline bool operator==(const Point& lhs, const Point& rhs)
{
    if ( lhs.x() == rhs.x() && lhs.y() == rhs.y()
        && lhs.tile() == rhs.tile() ) // XXX remove tile comparason?
        return true;
    return false;
}

inline bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs==rhs);
}

#endif
