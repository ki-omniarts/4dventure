#include "loop.h"

int main(int argc,char* argv[])
{
    if ( argc > 1)
    {
        Loop::loop().run(argv[1]);
    }

    return 0;
}
