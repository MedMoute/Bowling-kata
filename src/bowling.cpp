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

void Bowling::updateFlags(bool _isstrike,bool _isspare)
{
    if(prevWasStrike)
        prevPrevWasStrike=true;
    else
        prevPrevWasStrike=false;
    if(_isspare)
        prevWasSpare=true;
    else
        prevWasSpare=false;
    if(_isstrike)
        prevWasStrike=true;
    else
        prevWasStrike=false;

}

//Method updating the Frames array
//returns true if the frame is ending on this throw
//false if not
bool Bowling::updateFrames(const int i,const int counter,bool& _isstrike, bool& _isspare)
{
    switch (*cur)
    {
    case 'X': //strike
    {
        if(counter==0 || i==9)//A valid spare can only be a first throw OR happening during the last frame
        {
            if (prevPrevWasStrike)
                frames[i-2]+=10;
            if (prevWasStrike)
                frames[i-1]+=10;
            if (prevWasSpare)
                frames[i-1]+=10;
            frames[i]+=10;
            //
            _isstrike=true;
            _isspare=false;
            //
            if(i==9 && counter<2)//only case where the frame doesn't end after a strike
                return false;
            else
                return true;
    }
    else//invalid strike entry
    {
        _isstrike=false;
        _isspare=false;
        frames[i]=-1;
        return true;
    }
    }
    break;
case '/': //spare
    if(counter==1)//A valid spare can ONLY be a second throw
    {
            if (prevPrevWasStrike)
                frames[i-2]+=this->getCurrentSpareValue();
            if (prevWasStrike)
                frames[i-1]+=this->getCurrentSpareValue();
            if (prevWasSpare)
                frames[i-1]+=this->getCurrentSpareValue();
            frames[i]+=this->getCurrentSpareValue();
                        //
            _isstrike=false;
            _isspare=true;
            //
        if(i==9 && counter<2)//only case where the frame doesn't end after a spare
            return false;
        else
            return true;
    }
    else//invalid spare entry
    {
        _isstrike=false;
        _isspare=false;
        frames[i]=-1;
        return true;
    }
case '\0': //Unexpected end of array
    _isstrike=false;
    _isspare=false;
    frames[i]=-1;
    return true;
    break;
default:
    if (isdigit(*cur))  //char should be a number, or else the frame is invalid
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
    return false;
    break;
}
}

void Bowling::processFrame(int i)
{
    int counter=0;
    bool framestop=false;
    while (!framestop)
    {
        bool isspare=false;
        bool isstrike=false;
        framestop = this->updateFrames(i,counter,isstrike,isspare);
        this->updateFlags(isstrike,isspare);
        ++cur;
        counter++;
    }
}

//This method return the value of a throw that happened on a Spare
int Bowling::getCurrentSpareValue()
{
    int res;
    cur--; //move iterator back to previous throw
    if((*cur-'0')<=9 && (*cur-'0')>=0)
     res= 10-(*cur-'0');
    else
        res=-1; //the previous throw could not lead to a spare : ERROR
    cur++; //move iterator back to current throw
    return res;
}
