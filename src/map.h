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
    static const std::vector<char> necessarySymbols_; 
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
    

};

#endif
