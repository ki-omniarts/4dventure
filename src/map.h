#ifndef ADVENTURE_MAP_H
#define ADVENTURE_MAP_H

#include "point.h"

#include <memory>
#include <string>
#include <vector>

class Map
{
    typedef std::vector<std::vector<Point>> Tiles;

    std::shared_ptr<Tiles> tiles_ = std::shared_ptr<Tiles>(new Tiles);

    // Symbols
    std::vector<char> symbols_  = {};
    static const std::vector<char> necessarySymbols_; 
    static const std::vector<char> reservedSymbols_; 

    // Functions
    void generateTiles_(const std::string& mapstring);

    public:
        Map(const std::string& mapstring);
        Map(const Map& other);
        Map& operator=(const Map& other);
        Map(Map&& other);
        Map& operator=(Map&& other);
        virtual ~Map();
    
        // Exception
        class MapNotCreated {};

};

#endif
