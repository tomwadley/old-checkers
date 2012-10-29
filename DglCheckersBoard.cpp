// DglCheckersBoard.cpp

#include "DglCheckersBoard.h"

CDglCheckersBoard::CDglCheckersBoard()
{
    ClearBoard();
}    

CDglCheckersBoard::~CDglCheckersBoard()
{
    // nothing to do yet
}    

Cell CDglCheckersBoard::GetCell(int t1, int t2)
{
    return cellBoard[t1][t2];
}    

void CDglCheckersBoard::SetCell(int t1, int t2, Cell cell)
{
    cellBoard[t1][t2] = cell;
}

void CDglCheckersBoard::ResetBoard()
{
    int t1, t2;
    Cell* pcellPeice = 0; // NULL
    
    Cell cellEmpty, cellWhite, cellBlack;
    cellEmpty.bEmpty = true;
    cellWhite.bEmpty = false;
    cellBlack.bEmpty = false;
    cellWhite.cOwner = WHITE;
    cellBlack.cOwner = BLACK;
    cellWhite.bKing = false;
    cellBlack.bKing = false;
    
    t1 = 0; t2 = 0;
    bool bEvenRow = false;
    while (t2 <=7)
    {
        if (t2 >= 3)
        {
            if (t2 <= 4)
            {
                pcellPeice = &cellEmpty;
            }
            else
            {
                pcellPeice = &cellBlack;
            }    
        }
        else
        {
            pcellPeice = &cellWhite;
        }     
            
        if (bEvenRow)
        {
            while (t1 <= 7)
            {
                SetCell(t1, t2, cellEmpty);
                t1 ++;
                SetCell(t1, t2, *pcellPeice);
                t1 ++;
            }
        }
        else
        {
            while (t1 <= 7)
            {
                SetCell(t1, t2, *pcellPeice);
                t1 ++;
                SetCell(t1, t2, cellEmpty);
                t1 ++;
            }
        }
        bEvenRow = !bEvenRow;    
        t1 = 0;
        t2 ++; 
    }

}

void CDglCheckersBoard::ClearBoard()
{
    Cell cellEmpty = {true};
    for (int t2 = 0; t2 <= 7; t2 ++)
    {
        for (int t1 = 0; t1 <= 7; t1 ++)
        {
            SetCell(t1, t2, cellEmpty);
        }
    }
}            

void CDglCheckersBoard::Move(int f1, int f2, int t1, int t2)
{
    Cell cellEmpty = {true};
    SetCell(t1, t2, GetCell(f1, f2));
    SetCell(f1, f2, cellEmpty);
}

void CDglCheckersBoard::King(int t1, int t2)
{
    Cell cell = GetCell(t1, t2);
    cell.bKing = true;
    SetCell(t1, t2, cell);
}

void CDglCheckersBoard::Capture(int t1, int t2)
{
    Cell cellEmpty = {true};
    SetCell(t1, t2, cellEmpty);
}
    
