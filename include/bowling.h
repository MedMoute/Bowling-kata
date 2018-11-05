#ifndef __BOWLING_H__
#define __BOWLING_H__

#include <string>

class Bowling //an instance of the bowling class correspond to a Line
{
public:
    Bowling(char* _data);
    ~Bowling();
    int processLine();
    void processFrame(int);
private:
    std::string data;
    unsigned int frames[10];
    bool prevWasStrike; // Flag upped if a strike happened in last frame
    bool prevPrevWasStrike;  // Flag upped if a strike happened in frame before the last one
    bool prevWasSpare; //Flag upped is the was frame was a spare
    std::string::const_iterator cur;
};

#endif
