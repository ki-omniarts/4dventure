/*
 * point.cpp
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

#include "point.h"

Point::Point(unsigned int x, unsigned int y, tile_id_t tile)
    : x_{x}, y_{y}, tile_{tile}
{}

Point::Point()
    : Point{0,0}
{}

Point::Point(const Point& other)
    : x_(other.x_)
    , y_(other.y_)
    , tile_(other.tile_)
{}

Point::Point(Point&& other)
    : x_(std::move(other.x_))
    , y_(std::move(other.y_))
    , tile_(std::move(other.tile_))
{}

Point::~Point() noexcept
{}

Point& Point::operator=(const Point& other)
{
    if ( this == &other ) return *this;
    x_ = other.x_;
    y_ = other.y_;
    tile_ = other.tile_;
    return *this;
}

Point& Point::operator=(Point&& other)
{
    if ( this == &other ) return *this;
    x_ = std::move(other.x_);
    y_ = std::move(other.y_);
    tile_ = std::move(other.tile_);
    return *this;
}
    
