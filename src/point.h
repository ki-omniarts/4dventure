#ifndef ADVENTURE_POINT_H
#define ADVENTURE_POINT_H

#include <utility>

class Point
{
    unsigned int x_ = 0;
    unsigned int y_ = 0;

    public:
        Point();
        Point(unsigned int x, unsigned int y);
        Point(const Point& other);
        Point(Point&& other);
        Point& operator=(const Point& other);
        Point& operator=(Point&& other);
        virtual ~Point();

        const unsigned int x() const { return x_; }
        const unsigned int y() const { return y_; }
};

#endif
