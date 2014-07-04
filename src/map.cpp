// {{{ License
/*
 * map.cpp
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
#include "map.hpp"
// }}} Includes

// {{{ Map::reservecSymbols_
const std::vector<tile_id_t> Map::reservedSymbols_{EMPTY_TILE};
// }}} Map::reservecSymbols_

// {{{ Map *ctors + Assign
// {{{ Map::~Map()
Map::~Map() noexcept {}
// }}} Map::~Map()

// {{{ Map Constructors
// {{{ Map::Map()
Map::Map()
    : data_{new pImpl{}}
{}
// }}} Map::Map()

// {{{ Map::Map(string)
Map::Map(const std::string& mapstring)
    : data_{new pImpl{}}
{
    generateTiles_(mapstring);
}
// }}} Map::Map(string)

// {{{ Map::Map(Map)
Map::Map(const Map& other)
    : data_{new pImpl{*other.data_}}
{}
// }}} Map::Map(Map)

// {{{ Map::Map(Map&&)
Map::Map(Map&& other)
    : data_{nullptr}
{
    swap(*this,other);
}
// }}} Map::Map(Map&&)
// }}} Map Constructors

// {{{ Map assign
// {{{ Map::operator=(Map)
Map& Map::operator=(const Map& other)
{
    auto tmp = other;
    swap(*this,tmp);
    return *this;
}
// }}} Map::operator=(Map)

// {{{ Map::operator=(Map&&)
Map& Map::operator=(Map&& other)
{
    swap(*this,other);
    return *this;
}
// }}} Map::operator=(Map&&)
// }}} Map assign
// }}} Map *ctors + Assign

// {{{ Map::generateTiles_()
void Map::generateTiles_(const std::string& mapstring)
{
    // create a temporary Tiles object
    Map::Tiles tiles;
    // create a temporary list of symbols on the map
    std::vector<tile_id_t> symbols{};
    // current line and column, beginning with (0,0)
    size_t current_line{0};
    size_t current_col{0};
    // add first row to tiles
    tiles.push_back(std::vector<Point>());

    // go through each char in given ASCII string
    for (size_t i = 0; i != mapstring.size(); i++)
    {
        // begin a new vector when a new line starts
        if ( mapstring[i] == '\n' )
        {
            current_line++;
            current_col = 0;
            // add new line for each linebreak
            tiles.push_back(std::vector<Point>());
        } else {
            // is there a reserved char? -- if so, return without any change
            // TODO: optimize by moving this after symbols-check
            for (size_t s = 0; s != reservedSymbols_.size(); s++)
                if  (
                        static_cast<tile_id_t>(mapstring[i]) 
                        == reservedSymbols_[s] 
                    )
                    return;
            tiles[current_line].push_back
                (Point(current_col,current_line,
                    static_cast<tile_id_t>(mapstring[i])));
            // add char to the list of symbols
            {
                // first look if char already is listed in list of symbols
                // XXX: optimize search? -- use list of symbols as sorted list?
                bool not_found = true;
                for (size_t s = 0; s != symbols.size(); s++)
                {
                    if ( static_cast<tile_id_t>(mapstring[i]) == symbols[s] )
                    {
                        not_found = false;
                        break;
                    }
                }
                if (not_found)
                    symbols.push_back(static_cast<tile_id_t>(mapstring[i]));
            }
            current_col++;
        }
    }

    // move temporary objects to assign values
    data_->tiles    = std::move(tiles);
    data_->symbols  = std::move(symbols);
}
// }}} Map::generateTiles_()

// {{{ Map::startpoint()
const Point Map::startpoint() const
{
    // create temporary Point
    Point p{0,0};

    // search for startpoint symbol -- TODO: 'S' as a const, optimize search
    for(auto y : data_->tiles)
        for(auto x : y)
            if ( ( x.tile() == 'S' ) && ( p == Point(0,0) ) )
            {
                // assign found Point and return
                p = x;
                return p;
            }

    // return (0,0) on default
    return p;
}
// }}} Map::startpoint()

// {{{ Map::exists()
bool Map::exists(const Point& p) const
{
    // check for map boundaries
    return (  ( p.y() < data_->tiles.size() ) 
           && ( p.x() < data_->tiles[p.y()].size() ) );
}
// }}} Map::exists()
