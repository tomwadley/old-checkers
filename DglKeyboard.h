// DglKeyboard.h

#ifndef DGLKEYBOARD_H
#define DGLKEYBOARD_H

#include "DglLL.h"

struct KeyWatch
{
    int iKey;
    bool bKeyWasDown;
};

class CDglKeyboard
{
public:
    CDglKeyboard();
    ~CDglKeyboard();
    
    void WatchKey(int iKey);
    bool KeyBeenPressed(int iKey);
    bool KeyDown(int iKey);
    
private:
    CDglLL<KeyWatch> llKeyWatchList;
};

#endif
