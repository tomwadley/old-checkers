// DglCheckersBoard.h

#ifndef DGLCHECKERS_H
#define DGLCHECKERS_H

#define WHITE 0
#define BLACK 1

struct Cell
{
    bool bEmpty;
    char cOwner; // WHITE | BALCK
    bool bKing;
};

class CDglCheckersBoard
{
public:
    CDglCheckersBoard();
    ~CDglCheckersBoard();
    
    Cell GetCell(int t1, int t2);
    void SetCell(int t1, int t2, Cell cell);
    
    void ResetBoard();
    void ClearBoard();
    void Move(int f1, int f2, int t1, int t2);
    void King(int t1, int t2);
    void Capture(int t1, int t2);
    
private:
    Cell cellBoard[8][8];
};

#endif


