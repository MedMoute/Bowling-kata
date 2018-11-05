#ifndef __BOWLING_H__
#define __BOWLING_H__

class Bowling //an instance of the bowling class correspond to a Line
{
public:
    Bowling(char* _data);
    ~Bowling();
    int process();
private:
    char* data;
};

#endif
