#include "map.h"

const std::vector<char> Map::reservedSymbols_   = {'$'};

Map::~Map() {}

Map::Map(const std::string& mapstring)
{
    generateTiles_(mapstring);
}

Map::Map(const Map& other)
    : tiles_(other.tiles_)
    , symbols_(other.symbols_)
{}

Map& Map::operator=(const Map& other)
{
    if ( this == &other ) return *this;
    tiles_ = other.tiles_;
    symbols_ = other.symbols_;
    return *this;
}

Map::Map(Map&& other)
    : tiles_(std::move(other.tiles_))
    , symbols_(std::move(other.symbols_))
{}

Map& Map::operator=(Map&& other)
{
    if ( this == &other ) return *this;
    tiles_ = std::move(other.tiles_);
    symbols_ = std::move(other.symbols_);
    return *this;
}

void Map::generateTiles_(const std::string& mapstring)
{
    Map::Tiles tiles;
    std::vector<char> symbols = {};
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
                if ( mapstring[i] == reservedSymbols_[s] )
                    return;
            }
            tiles[current_line].push_back
                    (Point(current_col,current_line,mapstring[i]));
            // add the char to the list of symbols
            {
                bool not_found = true;
                for (size_t s = 0; s != symbols.size(); s++)
                {
                    if ( mapstring[i] == symbols[s] )
                    {
                        not_found = false;
                        break;
                    }
                }
                if (not_found)
                    symbols.push_back(mapstring[i]);
            }
        }
        if ( mapstring[i] != '\n' )
            current_col++;
    }
    tiles_      = std::move(tiles);
    symbols_    = std::move(symbols);
    valid_      = true;
}

const Point Map::startpoint()
{
    Point p = Point(0,0);

    for(auto y : tiles_)
        for(auto x : y)
        {
            if ( ( x.tile() == 'S' ) && ( p == Point(0,0) ) )
                p = x;
        }
    return p;
}

bool Map::exists(const Point& p)
{
    return ( ( p.y() < tiles_.size() ) && ( p.x() < tiles_[p.y()].size() ) );
}
