#include <bowling.h>

#include <iostream>
#include <stdlib.h>
#include <ctype.h>

Bowling::Bowling(char* _data)
{
    data=std::string(_data);
    *frames= {};
    cur = data.begin();
     prevWasStrike=false;
     prevPrevWasStrike=false;
     prevWasSpare=false;
};

Bowling::~Bowling()
{
}
int Bowling::processLine()
//This method will process the input data and will return the score of the line (-1 if invalid)
{

    int i;
    for (i=1; i<=10; i++)
    {
        processFrame(i);
    }

    int res=0; //Assuming the line is an empty sheet
    for (i=0; i<10; i++)
    {
        if(frames[i]>=0)
            res+=frames[i];
        else //invalid data on the frame
        {
            i=10; //jump to the end
            res=-1;
        }
    }
    return res;
}

void Bowling::processFrame(int i)
{
  //  std::cout<<*cur<<std::endl;
    switch (*cur)
    {
    case 'X': //strike
//TODO Proper flag management
        //move iterator
        ++cur;
        break;
    case '\0': //end of array -usually wrong input
        frames[i]=-1;
        break;
    default : //This is not a strike, there are 2 throws in this frame. The only case where there will be 3 throws is if i==10 and we do a spare
        if (isdigit(*cur))  //1st char should be a number, or else the frame is invalid
        {

        }
        else
        {
            frames[i]=-1;
        }
        ++cur;//move iterator
        switch (*cur)
        {
        case '/': //spare
            break;
        default:
            break;
        }
        break;
    }
}
