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

namespace c4dventure
{

#include "loop.hpp"

inline void runFile(const std::string& file)
{ Loop::loop().run(file); }

}
