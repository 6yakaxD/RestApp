#include <iostream>

#include "Server.h"
#include "Data.h"


int main()
{
    g_data.INIT();
        

    io_context ioContext;
    Server server(ioContext, 43990);
    ioContext.run();

    

    return 0;
}

