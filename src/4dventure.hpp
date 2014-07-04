// {{{ License
/*
 * 4dventure.hpp
 * This file is part of 4dventure
 *
 * Copyright (C) 2013 - KiNaudiz
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
 */
// }}} License

// {{{ Include guards
#ifndef 4DVENTURE_HPP
#define 4DVENTURE_HPP
// }}} Include guards

// {{{ namespace 4dventure
namespace c4dventure
{

#include "loop.hpp"

/*! Function to run a 4dventure file from cpp */
inline void runFile(const std::string& file)
{ Loop::loop().run(file); }

}
// }}} namespace 4dventure
//
// {{{ Include guards
#endif // 4DVENTURE_HPP
// }}} Include guards
