// {{{ License
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
// }}} License

// {{{ Include guards
#ifndef ADVENTURE_MAP_HPP
#define ADVENTURE_MAP_HPP
// }}} License

// {{{ Includes
#include "point.hpp"

#include <memory>
#include <string>
#include <vector>
// }}} Includes

// {{{ class Map
/*! Class representing a 2D game map */
class Map
{
    // {{{ Aliases
    /*!< Tiles are represented as a 2D-vector of Point objects */
    using Tiles = std::vector<std::vector<Point>>;
    // }}} Aliases

    // {{{ struct pImpl
    /*!< POD structure that holds the map's data */
    struct pImpl
    {
        Tiles tiles{};
        std::vector<tile_id_t> symbols{};
    };
    // }}} struct pImpl

    // {{{ Member variables
    /*!< the map's data as a unique ressource */
    std::unique_ptr<pImpl> data_;

    // Symbols -- XXX how about using an array? heap? (sorted container for fast
    // search)
    /*!< static list of symbols that shall not be used on a custom map */
    static const std::vector<tile_id_t> reservedSymbols_; 
    // }}} Member variables

    // {{{ Private member functions
    /*!< private function to generate a map from an ASCII string */
    void generateTiles_(const std::string& mapstring);
    // }}} Private member functions

    public:
        // {{{ *ctors
        /*!< default constructor creates an empty map */
        Map();
        /*!< constructor creates a map from an ASCII string */
        Map(const std::string& mapstring);
        /*!< copy constructor */
        Map(const Map& other);
        /*!< copy assign */
        Map& operator=(const Map& other);
        /*!< move constructor */
        Map(Map&& other);
        /*!< move assign */
        Map& operator=(Map&& other);
        /*!< destructor */
        virtual ~Map() noexcept;
        // }}} *ctors

        // {{{ Getter
        /*!< returns the player's position at the beginning of the game */
        const Point startpoint() const;
        /*!< returns true if Point p exists on map */
        bool exists(const Point& p) const;
        /*!< returns the tile id that's assigned to Point p */
        tile_id_t symbol(const Point& p) const
            { return data_->tiles[p.y()][p.x()].tile(); }
        /*!< returns true if the map is empty */
        bool empty() const // XXX: is a map with only $-tiles empty?
            { return data_->symbols.empty(); }

        // XXX: deprecated, will be removed soon
        /*!< DEPRECATED! does the same as empty() */
        bool valid() __attribute__ ((deprecated)) { return empty(); }
        // }}} Getter

        // {{{ swap
        /*!< swaps two Map objects */
        friend void swap(Map& lhs,Map& rhs)
        {
            std::swap(lhs.data_,rhs.data_);
        }
        // }}} swap
};
// }}} class Map

// {{{ License
#endif
// }}} License
