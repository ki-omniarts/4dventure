#include "point.h"

Point::Point(unsigned int x, unsigned int y, char tile)
    : x_(x), y_(y), tile_(tile)
{}

Point::Point()
    : Point(0,0)
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

Point::~Point()
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
    
