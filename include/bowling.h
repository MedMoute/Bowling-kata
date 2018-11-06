#ifndef __BOWLING_H__
#define __BOWLING_H__

#include <string>

class Bowling //an instance of the bowling class correspond to a Line
{
public:
    Bowling(const char* _data);
    ~Bowling();
    int processLine();
    void processFrame(int);
private:
    //Private methods
    bool updateFrames(int,int,bool&,bool&);
    void updateFlags(int,int,bool,bool);
    int getCurrentSpareValue();
    //Members
    std::string data;
    int frames[10];
    bool prevWasStrike; // Flag upped if a strike happened in last frame
    bool prevPrevWasStrike;  // Flag upped if a strike happened in frame before the last one
    bool prevWasSpare; //Flag upped is the was frame was a spare
    std::string::const_iterator cur;
};

#endif
