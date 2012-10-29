// DglCheckers3d.h

#define WHITE 0
#define BLACK 1
#define TARGET 2

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BOARD_ROTATION_SPEED 100
#define PEICE_MOVEMENT_SPEED 4

#define DIAGONAL_CELL_LENGTH 1.412 // sqrt(2)
#define PEICE_JUMP_HEIGHT 3

#define WIN_LOGO_WIDTH 160
#define WIN_LOGO_HEIGHT 80

#define MOUSE_HEIGHT 16
#define MOUSE_WIDTH 16

#include "DglOpenGl.h"
#include "DglCheckersBoard.h"
#include "DglKeyboard.h"
//#include "DglCamera.h"
#include "DglGameMenu.h"
#include "DglTexture.h"

struct MoveInfo
{
    bool bValid;
    bool bCapture;
    int iCapture1, iCapture2;
    bool bKing;
    bool bEndsTurn;
    bool bWinsGame;
    bool bMoved;
    float fProgress;
};

struct AiMove
{
    int iPeiceX;
    int iPeiceY;
    int iTargetX;
    int iTargetY;
    bool bCapture;
    int iScore;
};    

class CDglCheckers3d
{
public:
    CDglCheckers3d();
    ~CDglCheckers3d();
    
    int GameLoop();
    
private:
    void Draw(bool bTestingMouse);
    void Update();
    
    void DrawBoard();
    void DrawMovingPeice();
    void DrawPeices();
    void DrawSelectors();
    void DrawOrthoStuff();
    
    void Ai();
    bool bAiFinished;
    
    void Construct(); //call this after window creation
    
    void SelectionUpdate();
    MoveInfo CalcMoveInfo();
    int GetMouseSelectionId(int x, int y);
    
    CDglOpenGl openglWindow;
    CDglCheckersBoard checkersBoard;
    CDglKeyboard keyboardWatch;
    //CDglCamera cameraBoard;
    CDglGameMenu gameMenu;
    bool bDisplayMenu;
    bool bGameInProgress;
    char cTurn; // WHITE | BLACK
    int aiSelect[3][2]; // [WHITE | BLACK | TARGET][0 | 1]
    //float afCamera[2][3];; // [WHITE | BLACK][0(x) | 1(y) | 2(z)]
    float fRotation;
    bool bWhiteIsLocalHuman;
    bool bBlackIsLocalHuman;
    bool bWinner;
    char cWinner;
    
    bool bMousePressed;
    long lMouseX, lMouseY;
    
    CDglTexture dgltextureWhiteWin;
    CDglTexture dgltextureBlackWin;
    CDglTexture dgltextureMaskWhiteWin;
    CDglTexture dgltextureMaskBlackWin;
    CDglTexture dgltextureMaskMouse;
    CDglTexture dgltextureMouse;
    
    CDglTexture dgltextureGreenSquare;
    CDglTexture dgltextureBuffSquare;
    CDglTexture dgltextureRedPeice;
    CDglTexture dgltextureBlackPeice;
    CDglTexture dgltextureRedKing;
    CDglTexture dgltextureBlackKing;
    
    float fLastFrameTime;
    float fTimeSinceLastFrame;
    
    int iUpKey, iDownKey, iLeftKey, iRightKey, iSelectKey, iBackKey, iMenuKey;
    
    bool bPeiceSelected;
    bool bTargetSelected;
    MoveInfo moveinfoCurrent;
};

