// DglKeyboard.cpp

#include <windows.h>
#include "DglLL.h"

#include "DglKeyboard.h"

CDglKeyboard::CDglKeyboard()
{}

CDglKeyboard::~CDglKeyboard()
{}

void CDglKeyboard::WatchKey(int iKey)
{
    KeyWatch* pkeywatchNew = llKeyWatchList.InsertFirst();
    pkeywatchNew->iKey = iKey;
    pkeywatchNew->bKeyWasDown = false;
}

bool CDglKeyboard::KeyBeenPressed(int iKey)
{
    llKeyWatchList.MoveFirst();
    while (llKeyWatchList.GetData() != NULL)
    {
        if (llKeyWatchList.GetData()->iKey == iKey)
        {
            if (GetKeyState(iKey) & 0x80)
            {
                if (!llKeyWatchList.GetData()->bKeyWasDown)
                {
                    llKeyWatchList.GetData()->bKeyWasDown = true;
                    return true;
                }
                else
                {
                    return false;
                }
            }
            else
            {
                llKeyWatchList.GetData()->bKeyWasDown = false;
                return false;
            }            
        }
        llKeyWatchList.MoveNext();
    }
    return false;
}

bool CDglKeyboard::KeyDown(int iKey)
{
    return (GetKeyState(iKey) & 0x80);
}
                
