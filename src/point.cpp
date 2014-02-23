// {{{ License
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
// }}} License

// {{{ Includes
#include "point.hpp"
// }}} Includes

// {{{ Point *ctors + Assign
// {{{ Point Constructors
// {{{ Point::Point(uint,uint,tile_id_t)
Point::Point(unsigned int x, unsigned int y, tile_id_t tile)
    : data_{new pImpl{x,y,tile}}
{}
// }}} Point::Point(uint,uint,tile_id_t)

// {{{ Point::Point()
Point::Point()
    : Point{0,0}
{}
// }}} Point::Point()

// {{{ Point::Point(Point)
Point::Point(const Point& other)
    : data_{new pImpl{*other.data_}}
{}
// }}} Point::Point(Point)

// {{{ Point::Point(Point&&)
Point::Point(Point&& other)
    : data_{nullptr}
{
    swap(*this,other);
}
// }}} Point::Point(Point&&)
// }}} Point Constructors

// {{{ Point::~Point()
Point::~Point() noexcept
{}
// }}} Point::~Point()

// {{{ Point assign
// {{{ Point::operator=(Point)
Point& Point::operator=(const Point& other)
{
    auto tmp = other;
    swap(*this,tmp);
    return *this;
}
// }}} Point::operator=(Point)

// {{{ Point::operator=(Point&&)
Point& Point::operator=(Point&& other)
{
    swap(*this,other);
    return *this;
}
// }}} Point::operator=(Point&&)
// }}} Point assign
// }}} Point *ctors + Assign
    
// {{{ Point::pImpl Constructor
Point::pImpl::pImpl(unsigned int xx,unsigned int yy,tile_id_t tt)
    : x(xx),y(yy),tile(tt)
{}
// }}} Point::pImpl Constructor
