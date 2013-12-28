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

#include "map.hpp"

const std::vector<tile_id_t> Map::reservedSymbols_   = {'$'};

Map::~Map() noexcept {}

Map::Map()
    : data_{new pImpl{}}
{}

Map::Map(const std::string& mapstring)
    : data_{new pImpl{}}
{
    generateTiles_(mapstring);
}

Map::Map(const Map& other)
    : data_{new pImpl{*other.data_}}
{}

Map& Map::operator=(const Map& other)
{
    auto tmp = other;
    swap(*this,tmp);
    return *this;
}

Map::Map(Map&& other)
    : data_{nullptr}
{
    swap(*this,other);
}

Map& Map::operator=(Map&& other)
{
    swap(*this,other);
    return *this;
}

void Map::generateTiles_(const std::string& mapstring)
{
    Map::Tiles tiles;
    std::vector<tile_id_t> symbols = {};
    size_t current_line = 0;
    size_t current_col  = 0;
    tiles.push_back(std::vector<Point>());

    // go through each char
    for (size_t i = 0; i != mapstring.size(); i++)
    {
        // begin a new vector when a new line starts
        if ( mapstring[i] == '\n' )
        {
            current_line++;
            current_col = 0;
            tiles.push_back(std::vector<Point>());
        } else {
            // is there a reserved char?
            for (size_t s = 0; s != reservedSymbols_.size(); s++)
            {
                if  (
                        static_cast<tile_id_t>(mapstring[i]) 
                        == reservedSymbols_[s] 
                    )
                    return;
            }
            tiles[current_line].push_back
                (Point(current_col,current_line,
                    static_cast<tile_id_t>(mapstring[i])));
            // add the char to the list of symbols
            {
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
        }
        if ( mapstring[i] != '\n' )
            current_col++;
    }
    data_->tiles    = std::move(tiles);
    data_->symbols  = std::move(symbols);
}

const Point Map::startpoint() const
{
    Point p = Point(0,0);

    for(auto y : data_->tiles)
        for(auto x : y)
        {
            if ( ( x.tile() == 'S' ) && ( p == Point(0,0) ) )
                p = x;
        }
    return p;
}

bool Map::exists(const Point& p) const
{
    return (  ( p.y() < data_->tiles.size() ) 
           && ( p.x() < data_->tiles[p.y()].size() ) );
}
