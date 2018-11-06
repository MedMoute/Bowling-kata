#include <bowling.h>

#include <iostream>
#include <stdlib.h>
#include <ctype.h>

Bowling::Bowling(const char* _data): frames{},prevWasStrike(false),prevPrevWasStrike(false),prevWasSpare(false)
{
    data=std::string(_data);
    cur = data.begin();
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
        if(*cur=='\0')//input is too short
        {
            return -1;
        }
        else
        {
            processFrame(i);
        }
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
            //Debug line
            //   std::cout<<"Frames : ("<<i<< ") -> "<< frames[i]<<std::endl;
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

//Updates the boolean flags to fit the current situation
void Bowling::updateFlags(const int i,const int counter,bool _isstrike,bool _isspare)
{
    if(i<9)
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
    else
    {
        if(prevWasStrike)
            prevPrevWasStrike=true;
        else
            prevPrevWasStrike=false;
        prevWasSpare=false;
        prevWasStrike=false;
    }

}

//Method updating the Frames array
//returns true if the frame is ending on this throw
//false if not
bool Bowling::updateFrames(const int i,const int counter,bool& _isstrike, bool& _isspare)
{

//Debug line
//  std::cout<<"Processing current throw : "<<*cur<< " ("<<counter <<"th throw in the" <<i<< "th frame)"<<std::endl;
    switch (*cur)
    {
    case 'X': //strike
    {
        if(counter==0 || i==9)//A valid strike can only be a first throw OR happening during the last frame
        {
            if (prevPrevWasStrike)
                frames[this->getFrameOfPrevPrevThrow(i,counter)]+=10;
            if (prevWasStrike)
                frames[this->getFrameOfPrevThrow(i,counter)]+=10;
            if (prevWasSpare)
                frames[this->getFrameOfPrevThrow(i,counter)]+=10;
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
        break;
    }
    case '/': //spare
    {
        if(counter>0)//A valid spare can ONLY be a second or third throw
        {
            if (prevPrevWasStrike)
                frames[this->getFrameOfPrevPrevThrow(i,counter)]+=this->getCurrentSpareValue();
            if (prevWasStrike)
                frames[this->getFrameOfPrevThrow(i,counter)]+=this->getCurrentSpareValue();
            if (prevWasSpare)
                frames[this->getFrameOfPrevThrow(i,counter)]+=this->getCurrentSpareValue();
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
        break;
    }
    case '\0': //Unexpected end of array
    {
        _isstrike=false;
        _isspare=false;
        frames[i]=-1;
        return true;
        break;
    }
    default:
    {
        if (((*cur-'0')<=9 && (*cur-'0')>0 )|| *cur=='-')  //char should be a number or a miss, or else the frame is invalid
        {
            if((*cur-'0')<=9 && (*cur-'0')>0 ) //if we hit some pins, we have to make sure there was still enough pins before
            {
                if(this->getRemainingPins()<=*cur-'0') //we hit more pins than the actual number of pins : ERROR
                {
                    frames[i]=-1;
                    return true;
                    break;
                }
            }
            if (prevPrevWasStrike)
                *cur=='-' ? frames[this->getFrameOfPrevPrevThrow(i,counter)] : frames[this->getFrameOfPrevPrevThrow(i,counter)]+=(*cur-'0');
            if (prevWasStrike)
                *cur=='-' ? frames[this->getFrameOfPrevThrow(i,counter)] : frames[this->getFrameOfPrevThrow(i,counter)]+=(*cur-'0');
            if (prevWasSpare)
                *cur=='-' ? frames[this->getFrameOfPrevThrow(i,counter)] : frames[this->getFrameOfPrevThrow(i,counter)]+=(*cur-'0');

            *cur=='-' ? frames[i] : frames[i]+=(*cur-'0');
            //
            _isstrike=false;
            _isspare=false;
            //
            if(counter==0 || ((i==9)&&(counter==1)&&(prevPrevWasStrike)))
                return false;
            else
                return true;
        }
        else
        {
            _isstrike=false;
            _isspare=false;
            frames[i]=-1;
            return true;
        }

        break;
    }
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
        this->updateFlags(i,counter,isstrike,isspare);
        ++cur;
        counter++;
    }
}
//This method return the number of pins that were present at the current throw
int Bowling::getRemainingPins()
{
    int res;
    cur--; //move iterator back to previous throw
    if(*cur=='X'||*cur=='/') //Previous throw was a strike or a pair
        res= 10; //10 pins up
    else
    {
        if(((*cur-'0')<=9 && (*cur-'0')>0)
                || *cur=='-')
        {
            *cur=='-' ? res = 10 :res=10-(*cur-'0') ;
        }
    }
    cur++; //move iterator back to current throw
    return res;
}

//This method return the value of a throw that happened to be a Spare
int Bowling::getCurrentSpareValue()
{
    int res;
    cur--; //move iterator back to previous throw
    if((*cur-'0')<=9 && (*cur-'0')>0)
        res= 10-(*cur-'0');
    else
    {
        if(*cur=='-')
            res=10;
        else
            res=-1; //the previous throw could not lead to a spare : ERROR
    }
    cur++; //move iterator back to current throw
    return res;
}

int Bowling::getFrameOfPrevThrow(const int i,const int counter)
{
    if (counter>0)
        return i;
    else
        return i-1;
}

int Bowling::getFrameOfPrevPrevThrow(int i,int counter)
{
    if (counter>1)
        return i;
    else
    {
        if(counter==1)
        {
            return i-1;
        }
        else
        {
            if(prevWasStrike)
                return i-2;
            else
                return i-1;
        }
    }

}
