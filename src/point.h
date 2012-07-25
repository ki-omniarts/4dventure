#ifndef ADVENTURE_POINT_H
#define ADVENTURE_POINT_H

#include <utility>

class Point
{
    unsigned int x_     = 0;
    unsigned int y_     = 0;
    char      tile_     = '$';

    public:
        Point();
        Point(unsigned int x, unsigned int y, char tile = '$');
        Point(const Point& other);
        Point(Point&& other);
        Point& operator=(const Point& other);
        Point& operator=(Point&& other);
        virtual ~Point();

        unsigned int x()  const { return x_; }
        unsigned int y()  const { return y_; }
        char tile()       const { return tile_; } 
};

inline bool operator==(const Point& lhs, const Point& rhs)
{
    if ( lhs.x() == rhs.x() && lhs.y() == rhs.y()
        && lhs.tile() == rhs.tile() )
        return true;
    return false;
}

inline bool operator!=(const Point& lhs, const Point& rhs)
{
    return !(lhs==rhs);
}

#endif
