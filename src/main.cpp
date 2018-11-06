#include <bowling.h>
//Standard I/O functions
#include <iostream>

int mainRun(int argc, char ** argv)
{
    int res = 0;
    if (argc==2) //The correct number of arguments was inputed
    {
        Bowling* line = new Bowling(argv[1]);
        res = line->processLine();
        if (res<0)
        {
            std::cout<<"The input line was not a valid one"<<std::endl;
        }
        else
        {
            std::cout<<"This line has a score of : "<<res<<" ."<<std::endl;
        }
        delete line;
    }
    else
    {
        std::cout<<"Wrong input set"<<std::endl;
        std::cout<<"Correct usage is bowling [data]"<<std::endl;
    }
    return 0;
}
