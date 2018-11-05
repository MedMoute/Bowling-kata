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
    for (i=0; i<10; i++)
    {
        processFrame(i);
    }
    if(*cur !='\0')//input has too much data
    {
        return -1;
    }
    else
    {
        int res=0; //Assuming the line is an empty sheet
        for (i=0; i<10; i++)
        {
            std::cout<<*cur <<" "<<frames[i]<<std::endl;
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
}

void Bowling::processFrame(int i)
{

    switch (*cur)
    {
    case 'X': //strike
        if (prevPrevWasStrike)
            frames[i-2]+=10;
        if (prevWasStrike)
            frames[i-1]+=10;
        if (prevWasSpare)
            frames[i-1]+=10;
        frames[i]+=10;
        //Setup flags
        if(prevWasStrike)
            prevPrevWasStrike=true;
        else
            prevPrevWasStrike=false;
        prevWasStrike=true;
        prevWasSpare=false;
        //move iterator
        ++cur;
        if(i==9)//strike on 10th frame -> 2 more throws
        {
            prevPrevWasStrike=false;
            switch (*cur)
            {
            case 'X':
                if (prevPrevWasStrike)
                    frames[i-2]+=10;
                if (prevWasStrike)
                    frames[i-1]+=10;
                if (prevWasSpare)
                    frames[i-1]+=10;
                frames[i]+=10;

                break;
            default:
                if (isdigit(*cur))  //1st char should be a number, or else the frame is invalid
                {
                    if (prevPrevWasStrike)
                        frames[i-2]+=(*cur-'0');
                    if (prevWasStrike)
                        frames[i-1]+=(*cur-'0');
                    if (prevWasSpare)
                        frames[i-1]+=(*cur-'0');
                    frames[i]+=(*cur-'0');
                }
                else
                {
                    frames[i]=-1;
                }

                break;
            }

       prevWasStrike=false;
            ++cur;

            switch (*cur)
            {
            case 'X':
                if (prevPrevWasStrike)
                    frames[i-2]+=10;
                if (prevWasStrike)
                    frames[i-1]+=10;
                if (prevWasSpare)
                    frames[i-1]+=10;
                frames[i]+=10;
                break;
            default:
                if (isdigit(*cur))  //1st char should be a number, or else the frame is invalid
                {
                    if (prevPrevWasStrike)
                        frames[i-2]+=(*cur-'0');
                    if (prevWasStrike)
                        frames[i-1]+=(*cur-'0');
                    if (prevWasSpare)
                        frames[i-1]+=(*cur-'0');
                    frames[i]+=(*cur-'0');
                }
                else
                {
                    frames[i]=-1;
                }

                break;
            }
            ++cur;

        }
        break;
    case '\0': //end of array -usually wrong input
        frames[i]=-1;
        break;
    default : //This is not a strike, there are 2 throws in this frame. The only case where there will be 3 throws is if i==10 and we do a spare or a strike
        if (isdigit(*cur))  //1st char should be a number, or else the frame is invalid
        {
            if (prevPrevWasStrike)
                frames[i-2]+=(*cur-'0');
            if (prevWasStrike)
                frames[i-1]+=(*cur-'0');
            if (prevWasSpare)
                frames[i-1]+=(*cur-'0');
            frames[i]+=(*cur-'0');
        }
        else
        {
            std::cout<<"pb at "<<i<<" : n'est pas un digit"<<std::endl;
            frames[i]=-1;
        }
        ++cur;//move iterator

        //update flags
        if(prevWasStrike)
        {
            prevPrevWasStrike=true;
            prevWasStrike=false;
        }
        if(prevPrevWasStrike)
            prevPrevWasStrike=false;

        // Processing the second throw
        switch (*cur)
        {
        case '/': //spare
            if (prevPrevWasStrike)
                frames[i-2]+=(*cur-'0');
            frames[i]+=(*cur-'0');
            prevWasSpare=true;
            prevWasStrike=false;
            ++cur;//move iterator
            if(i==9)//strike on 10th frame -> 1 more throw
            {
                switch (*cur)
                {
                case 'X':
                    if (prevPrevWasStrike)
                        frames[i-2]+=10;
                    if (prevWasStrike)
                        frames[i-1]+=10;
                    if (prevWasSpare)
                        frames[i-1]+=10;
                    frames[i]+=10;
                    break;
                default:
                    if (isdigit(*cur))  //1st char should be a number, or else the frame is invalid
                    {
                        if (prevPrevWasStrike)
                            frames[i-2]+=(*cur-'0');
                        if (prevWasStrike)
                            frames[i-1]+=(*cur-'0');
                        if (prevWasSpare)
                            frames[i-1]+=(*cur-'0');
                        frames[i]+=(*cur-'0');
                    }
                    else
                    {
                        frames[i]=-1;
                    }

                    break;
                }
            }
            break;
        default:
            if (isdigit(*cur))  //2nd char should be a number or /, or else the frame is invalid
            {
                if (prevPrevWasStrike)
                {
                   frames[i-2]+=(*cur-'0');
                    prevPrevWasStrike=false;
                }
                frames[i]+=(*cur-'0');

            }
            else
            {
                std::cout<<"pb at "<<i<<" : n'est pas un digit"<<std::endl;
                frames[i]=-1;
            }
            ++cur;//move iterator
            break;
        }
        break;
    }
}
