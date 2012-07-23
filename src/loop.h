#include "point.h"

#include <memory>
#include <vector>

class Loop
{
    typedef std::vector<std::vector<Point>> Map;
    std::unique_ptr<Map> map_ = std::unique_ptr<Map>(new Map);

    public:

};
