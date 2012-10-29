// DglCheckers3d.cpp

#include <windows.h>

#include "DglOpenGl.h"
#include "DglCheckersBoard.h"
#include "DglKeyboard.h"
#include "DglGameMenu.h"

#include "DglCheckers3d.h"

bool g_bLMouseDown = false;

LRESULT CALLBACK wndproc(	HWND	hWnd,			// Handle For This Window
							UINT	uMsg,			// Message For This Window
							WPARAM	wParam,			// Additional Message Information
							LPARAM	lParam)			// Additional Message Information
{
	switch (uMsg)									// Check For Windows Messages
	{
		case WM_CLOSE:								// Did We Receive A Close Message?
		{
			PostQuitMessage(0);						// Send A Quit Message
			return 0;								// Jump Back
		}
		case WM_SIZE:
		{
			//glwindow.SizeScene(LOWORD(lParam),HIWORD(lParam));
			return 0;
		}
		case WM_KEYDOWN:
		{
			switch(wParam)
			{
				//case VK_ESCAPE:
				//{
				//	PostQuitMessage(0);
				//}
			}
			return 0;
		}
		case WM_LBUTTONDOWN:
        {
		    g_bLMouseDown = true;
		    return 0;  
        }    
        case WM_LBUTTONUP:
        {
		    g_bLMouseDown = false;
		    return 0;  
        }   

	}

	// Pass All Unhandled Messages To DefWindowProc
	return DefWindowProc(hWnd,uMsg,wParam,lParam);
}



CDglCheckers3d::CDglCheckers3d()
{
    /*
    Cell redcell;
    Cell blackcell;
    redcell.bEmpty = false;
    redcell.bKing = false;
    redcell.cOwner = WHITE;
    blackcell.bEmpty = false;
    blackcell.bKing = false;
    blackcell.cOwner = BLACK;
    
    checkersBoard.ClearBoard();
    checkersBoard.SetCell(3,3,blackcell);
    checkersBoard.SetCell(4,4,redcell);
    checkersBoard.SetCell(2,4,redcell);
    checkersBoard.SetCell(5,5,redcell);
    checkersBoard.SetCell(1,5,redcell);
    checkersBoard.SetCell(1,1,redcell);
    checkersBoard.SetCell(5,1,redcell);
    checkersBoard.SetCell(2,2,redcell);
    checkersBoard.SetCell(4,2,redcell);
    checkersBoard.SetCell(0,0,redcell);
    checkersBoard.SetCell(7,7,redcell);
    
    cTurn = WHITE;
    */
    
}

CDglCheckers3d::~CDglCheckers3d()
{
}   

void CDglCheckers3d::Construct()
{
    bDisplayMenu = true;
    bMousePressed = false;
    
    gameMenu.SetItemDimensions(260,130);
    gameMenu.SetScreenDimensions(SCREEN_WIDTH,SCREEN_HEIGHT);
    gameMenu.CreateItemList(3);
    gameMenu.GetItem(0)->bVisible = true;
    gameMenu.GetItem(0)->bSelectable = true;
    gameMenu.GetItem(1)->bVisible = true;
    gameMenu.GetItem(1)->bSelectable = true;
    gameMenu.GetItem(2)->bVisible = true;
    gameMenu.GetItem(2)->bSelectable = true;
    if (!gameMenu.GetItem(0)->dgltexturePic.LoadTexture("playervsplayerlocal.bmp"))
    {
        MessageBox(NULL,"cant load playervsplayerlocal.bmp","error",0);
    }    
    if (!gameMenu.GetItem(0)->dgltextureMaskPic.LoadTexture("maskplayervsplayerlocal.bmp"))
    {
        MessageBox(NULL,"cand load maskplayervsplayerlocal.bmp","error",0);
    }
    if (!gameMenu.GetItem(1)->dgltexturePic.LoadTexture("playervscpu.bmp"))
    {
        MessageBox(NULL,"cant load playervscpu.bmp","error",0);
    }    
    if (!gameMenu.GetItem(1)->dgltextureMaskPic.LoadTexture("maskplayervscpu.bmp"))
    {
        MessageBox(NULL,"cand load maskplayervscpu.bmp","error",0);
    }
    if (!gameMenu.GetItem(2)->dgltexturePic.LoadTexture("quit.bmp"))
    {
        MessageBox(NULL,"cant load quit.bmp","error",0);
    }    
    if (!gameMenu.GetItem(2)->dgltextureMaskPic.LoadTexture("maskquit.bmp"))
    {
        MessageBox(NULL,"cand load maskquit.bmp","error",0);
    }
    gameMenu.GetSelectPic()->LoadTexture("selectpic.bmp");
    gameMenu.GetMaskSelectPic()->LoadTexture("maskselectpic.bmp");
    
    dgltextureWhiteWin.LoadTexture("whitewin.bmp");
    dgltextureBlackWin.LoadTexture("blackwin.bmp");
    dgltextureMaskWhiteWin.LoadTexture("maskwhitewin.bmp");
    dgltextureMaskBlackWin.LoadTexture("maskblackwin.bmp");
    
    dgltextureMaskMouse.LoadTexture("maskmouse.bmp");
    dgltextureMouse.LoadTexture("mouse.bmp");
    
    if (!dgltextureGreenSquare.LoadTexture("greensquare.bmp"))
    {
        MessageBox(NULL,"cand load greensquare.bmp","error",0);
    }    
    if (!dgltextureBuffSquare.LoadTexture("buffsquare.bmp"))
    {
        MessageBox(NULL,"cand load buffsquare.bmp","error",0);
    }    
    if (!dgltextureRedPeice.LoadTexture("redpeice.bmp"))
    {
         MessageBox(NULL,"cand load redpeice.bmp","error",0);
    }    
    dgltextureBlackPeice.LoadTexture("blackpeice.bmp");
    dgltextureRedKing.LoadTexture("redking.bmp");
    dgltextureBlackKing.LoadTexture("blackking.bmp");
    
    bGameInProgress = false;
    bWinner = false;
    
    checkersBoard.ClearBoard();
    cTurn = WHITE;
    aiSelect[WHITE][0] = aiSelect[WHITE][1] = 0;
    aiSelect[BLACK][0] = aiSelect[BLACK][1] = 7;
    bPeiceSelected = false;
    bTargetSelected = false;
    
    fLastFrameTime = timeGetTime() * 0.001f;
    
    iUpKey = VK_UP;
    iDownKey = VK_DOWN;
    iLeftKey = VK_LEFT;
    iRightKey = VK_RIGHT;
    iSelectKey = VK_SPACE;
    iBackKey = VK_BACK;
    iMenuKey = VK_ESCAPE;
    
    keyboardWatch.WatchKey(VK_LEFT);
    keyboardWatch.WatchKey(VK_RIGHT);
    keyboardWatch.WatchKey(VK_UP);
    keyboardWatch.WatchKey(VK_DOWN);
    keyboardWatch.WatchKey(VK_SPACE);
    keyboardWatch.WatchKey(VK_BACK);
    keyboardWatch.WatchKey(VK_ESCAPE);
    
    fRotation = 180;
}     

int CDglCheckers3d::GameLoop()
{
    if (!openglWindow.CreateOpenGlWindow("Checkers 3D", SCREEN_WIDTH, SCREEN_HEIGHT, 16, true, wndproc))
    {
        MessageBox(NULL, "Could not init OpenGl!", "Checkers 3D", 0);
        return 0;
    }
    Construct();
    MSG msg;
	bool done = false;
	while(!done)
	{
		if (PeekMessage(&msg,NULL,0,0,PM_REMOVE))
		{
			if (msg.message==WM_QUIT)	
			{
				done=TRUE;		
			}
			else									
			{
				TranslateMessage(&msg);	
				DispatchMessage(&msg);	
			}
		}
		else			
		{
		    Update();
			Draw(false);
		}
	}
	return 1;
}    


void CDglCheckers3d::Update()
{ 
    float fCurrentTime = timeGetTime() * 0.001f;
	fTimeSinceLastFrame = fCurrentTime - fLastFrameTime;
    fLastFrameTime = fCurrentTime;                 
    
    float currentMovementSpeed = 0;	
	if (bGameInProgress)
	{
        currentMovementSpeed = BOARD_ROTATION_SPEED * fTimeSinceLastFrame;
    }
    else
    {
        currentMovementSpeed = (BOARD_ROTATION_SPEED / 4) * fTimeSinceLastFrame;
        fRotation += currentMovementSpeed;
    }        
	// modify fRotation
	if (bGameInProgress)
	{
    	if (cTurn == WHITE & bWhiteIsLocalHuman)
    	{
    	    if (fRotation > 0)
    	    {
    	        fRotation += currentMovementSpeed;
    	        if (fRotation > 360)
    	        {
    	            fRotation = 0;
    	        }    
    	    }
        }
        else 
        {
            if (bBlackIsLocalHuman)
            {
                if (fRotation < 180)
                {
                    fRotation += currentMovementSpeed;
                    if (fRotation > 180)
                    {
                        fRotation = 180;
                    }    
                }
            }    
        }
    }       
    if (fRotation >= 360)
    {
        fRotation = 0;
    }         
    
    if (bTargetSelected)
    {
        if (!moveinfoCurrent.bMoved)
        {
            if (!moveinfoCurrent.bCapture)
            {
                moveinfoCurrent.fProgress += (PEICE_MOVEMENT_SPEED * fTimeSinceLastFrame);
                if (moveinfoCurrent.fProgress >= DIAGONAL_CELL_LENGTH)
                {
                    moveinfoCurrent.fProgress = 0;
                    checkersBoard.Move(aiSelect[cTurn][0], aiSelect[cTurn][1], aiSelect[TARGET][0], aiSelect[TARGET][1]);
                    moveinfoCurrent.bMoved = true;
                }  
            }
            else
            {
                moveinfoCurrent.fProgress += (PEICE_MOVEMENT_SPEED * fTimeSinceLastFrame)/2;
                if (moveinfoCurrent.fProgress >= 2)
                {
                    moveinfoCurrent.fProgress = 0;
                    checkersBoard.Move(aiSelect[cTurn][0], aiSelect[cTurn][1], aiSelect[TARGET][0], aiSelect[TARGET][1]);
                    moveinfoCurrent.bMoved = true;
                }  
            }          
        }
        else
        {
            if (moveinfoCurrent.bCapture)
            {
                checkersBoard.Capture(moveinfoCurrent.iCapture1, moveinfoCurrent.iCapture2);
                moveinfoCurrent.bCapture = false; 
            }
            else
            {
                if (moveinfoCurrent.bKing)
                {
                    checkersBoard.King(aiSelect[TARGET][0], aiSelect[TARGET][1]);
                    moveinfoCurrent.bKing = false;
                }
                else
                {
                    if (moveinfoCurrent.bWinsGame)
                    {
                        // player wins
                        bWinner = true;
                        cWinner = cTurn;
                        bGameInProgress = false;
                    }
                    else
                    {
                        bAiFinished = false;
                        if (moveinfoCurrent.bEndsTurn)
                        {
                            if (cTurn == WHITE)
                            {
                                cTurn = BLACK;
                                if (bBlackIsLocalHuman)
                                {
                                    iUpKey = VK_DOWN;
                                    iDownKey = VK_UP;
                                    iLeftKey = VK_RIGHT;
                                    iRightKey = VK_LEFT;
                                }
                                else
                                {
                                    //run ai
                                }        
                                //cameraBoard.PinLocation(&afCamera[BLACK][0], &afCamera[BLACK][1], &afCamera[BLACK][1]);
                            }
                            else
                            {
                                cTurn = WHITE;
                                if (bWhiteIsLocalHuman)
                                {
                                    iUpKey = VK_UP;
                                    iDownKey = VK_DOWN;
                                    iLeftKey = VK_LEFT;
                                    iRightKey = VK_RIGHT;
                                }
                                else
                                {
                                    //run ai
                                }        
                                //cameraBoard.PinLocation(&afCamera[WHITE][0], &afCamera[WHITE][1], &afCamera[WHITE][1]);
                            }
                            fLastFrameTime = timeGetTime() * 0.001f;
                        }
                        bTargetSelected = false;
                        bPeiceSelected = false;            
                    }        
                }        
            }        
        }        
    }

    SelectionUpdate();

}    

void CDglCheckers3d::SelectionUpdate()
{
    //check ai   
    if (bGameInProgress & (((cTurn == WHITE) & !bWhiteIsLocalHuman) | ((cTurn == BLACK) & !bBlackIsLocalHuman)))
    {
        if (!bAiFinished)
        {
            Ai();
            if (bAiFinished)
            {
                moveinfoCurrent = CalcMoveInfo();
                if (moveinfoCurrent.bValid)
                {
                    bPeiceSelected = true;
                    bTargetSelected = true;
                }       
            }    
        }
    }                     
    
    //mouse code begins here
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(openglWindow.GetHWND(), &point);
    lMouseX = point.x;
    lMouseY = point.y;
    
    if (bDisplayMenu)
    {
        gameMenu.ModifySelectionFromMouse(lMouseX, lMouseY);
        if (keyboardWatch.KeyBeenPressed(iMenuKey))
        {
            bDisplayMenu = false;
        }
    } 
    else
    {
        if (keyboardWatch.KeyBeenPressed(iMenuKey))
        {
            bDisplayMenu = true;
        }
    }    
    
    if (!bMousePressed)
    {
        if (g_bLMouseDown)
        {
            bMousePressed = true;
            
            if (bDisplayMenu)
            {
                if (gameMenu.ItemSelected())
                {
                    switch (gameMenu.GetSelectedItem())
                    {
                        case 0:
                            bGameInProgress = true;
                            checkersBoard.ResetBoard();
                            cTurn = WHITE;
                            aiSelect[WHITE][0] = aiSelect[WHITE][1] = 0;
                            aiSelect[BLACK][0] = aiSelect[BLACK][1] = 7;
                            bPeiceSelected = false;
                            bTargetSelected = false;
                            iUpKey = VK_UP;   
                            iDownKey = VK_DOWN;
                            iLeftKey = VK_LEFT;
                            iRightKey = VK_RIGHT;
                            bWhiteIsLocalHuman = true;
                            bBlackIsLocalHuman = true;
                            bWinner = false;
                            
                            bDisplayMenu = false;
                            break;
                        case 1:
                            bGameInProgress = true;
                            checkersBoard.ResetBoard();
                            cTurn = WHITE;
                            aiSelect[WHITE][0] = aiSelect[WHITE][1] = 0;
                            aiSelect[BLACK][0] = aiSelect[BLACK][1] = 7;
                            bPeiceSelected = false;
                            bTargetSelected = false;
                            iUpKey = VK_UP;   
                            iDownKey = VK_DOWN;
                            iLeftKey = VK_LEFT;
                            iRightKey = VK_RIGHT;
                            bWhiteIsLocalHuman = true;
                            bBlackIsLocalHuman = false;
                            bWinner = false;
                            
                            bDisplayMenu = false;
                            break;
                        case 2:
                            PostQuitMessage(0);
                            bDisplayMenu = false;
                            break;
                    }    
                }  
                
            }
            else //no menu
            {
                int iSelectionId = 0;
                if (!bTargetSelected)
                {
                    if ((fRotation == 0) | (fRotation == 180))
                    {
                        iSelectionId = GetMouseSelectionId((int)lMouseX,(int)lMouseY);
                        //for (int i =0; i < 100; i ++)
                        //{
                        //   Draw(true);
                        //}    
                    }    
                }    
                if (iSelectionId != 0)
                {
                    int iSelectionX = iSelectionId % 10;
                    int iSelectionY = (int)(iSelectionId / 10) % 10;
                    //MessageBox(NULL,"you clicked something!","checkers3d",0);
                    //g_bLMouseDown = false; //debug line
                    if (!bTargetSelected & ((cTurn == WHITE & bWhiteIsLocalHuman == true) | (cTurn == BLACK & bBlackIsLocalHuman == true)) )
                    {
                        if (!bPeiceSelected)
                        {
                            if (!checkersBoard.GetCell(iSelectionX, iSelectionY).bEmpty)
                            {
                                if (checkersBoard.GetCell(iSelectionX, iSelectionY).cOwner == cTurn)
                                {
                                    aiSelect[cTurn][0] = iSelectionX;
                                    aiSelect[cTurn][1] = iSelectionY;
                                    bPeiceSelected = true;
                                }
                            }     
                        }
                        else
                        {
                            if ((iSelectionX != aiSelect[cTurn][0]) | (iSelectionY != aiSelect[cTurn][1]))
                            {
                                if (checkersBoard.GetCell(iSelectionX, iSelectionY).cOwner == cTurn & !checkersBoard.GetCell(iSelectionX, iSelectionY).bEmpty)
                                {
                                    aiSelect[cTurn][0] = iSelectionX;
                                    aiSelect[cTurn][1] = iSelectionY;
                                }
                                else
                                {    
                                    aiSelect[TARGET][0] = iSelectionX;
                                    aiSelect[TARGET][1] = iSelectionY;
                                    moveinfoCurrent = CalcMoveInfo();
                                    if (moveinfoCurrent.bValid)
                                    {
                                        bTargetSelected = true;
                                    }
                                }    
                            }
                            else
                            {
                                bPeiceSelected = false;
                            }        
                        }    
                    }       
                }
                else
                {
                    //MessageBox(NULL,"no","checkers3d",0);
                } 
                    
            }    
                
        }
    }
    else
    {
        if (!g_bLMouseDown)  
        {
            bMousePressed = false;
        }
    } 
    //mouse code ends here
    
    //keyobard code begins here 
    /*
    if (bDisplayMenu)
    {
        if (keyboardWatch.KeyBeenPressed(VK_UP))
        {
            gameMenu.ModifySelectionUpOrDown(true); 
        } 
        if (keyboardWatch.KeyBeenPressed(VK_DOWN))
        {
            gameMenu.ModifySelectionUpOrDown(false);
        }
        if (keyboardWatch.KeyBeenPressed(iSelectKey))
        {
            if (gameMenu.ItemSelected())
            {
                switch (gameMenu.GetSelectedItem())
                {
                    case 0:
                        bGameInProgress = true;
                        checkersBoard.ResetBoard();
                        cTurn = WHITE;
                        aiSelect[WHITE][0] = aiSelect[WHITE][1] = 0;
                        aiSelect[BLACK][0] = aiSelect[BLACK][1] = 7;
                        bPeiceSelected = false;
                        bTargetSelected = false;
                        iUpKey = VK_UP;   
                        iDownKey = VK_DOWN;
                        iLeftKey = VK_LEFT;
                        iRightKey = VK_RIGHT;
                        bWhiteIsLocalHuman = true;
                        bBlackIsLocalHuman = true;
                        bWinner = false;
                        
                        bDisplayMenu = false;
                        break;
                    case 1:
                        bGameInProgress = true;
                        checkersBoard.ResetBoard();
                        cTurn = WHITE;
                        aiSelect[WHITE][0] = aiSelect[WHITE][1] = 0;
                        aiSelect[BLACK][0] = aiSelect[BLACK][1] = 7;
                        bPeiceSelected = false;
                        bTargetSelected = false;
                        iUpKey = VK_UP;   
                        iDownKey = VK_DOWN;
                        iLeftKey = VK_LEFT;
                        iRightKey = VK_RIGHT;
                        bWhiteIsLocalHuman = true;
                        bBlackIsLocalHuman = false;
                        bWinner = false;
                        
                        bDisplayMenu = false;
                        break;
                    case 2:
                        PostQuitMessage(0);
                        bDisplayMenu = false;
                        break;
                }    
            }    
                        
        }   
        if (keyboardWatch.KeyBeenPressed(iMenuKey))
        {
            bDisplayMenu = false;
        }     
    }
    else
    {   
        if (keyboardWatch.KeyBeenPressed(iMenuKey))
        {
            bDisplayMenu = true;
        }    
        if (!bTargetSelected)
        {
            if (!bPeiceSelected)
            {
                if (keyboardWatch.KeyBeenPressed(iRightKey))
                {
                    if (aiSelect[cTurn][0] < 7)
                    {
                        aiSelect[cTurn][0] ++;
                    }    
                }
                if (keyboardWatch.KeyBeenPressed(iLeftKey))
                {
                    if (aiSelect[cTurn][0] > 0)
                    {
                        aiSelect[cTurn][0] --;
                    }    
                } 
                if (keyboardWatch.KeyBeenPressed(iUpKey))
                {
                    if (aiSelect[cTurn][1] < 7)
                    {
                        aiSelect[cTurn][1] ++;
                    }    
                } 
                if (keyboardWatch.KeyBeenPressed(iDownKey))
                {
                    if (aiSelect[cTurn][1] > 0)
                    {
                        aiSelect[cTurn][1] --;
                    }    
                } 
                if (keyboardWatch.KeyBeenPressed(iSelectKey))
                {           
                    if (!checkersBoard.GetCell(aiSelect[cTurn][0], aiSelect[cTurn][1]).bEmpty)
                    {
                        if (checkersBoard.GetCell(aiSelect[cTurn][0], aiSelect[cTurn][1]).cOwner == cTurn)
                        {
                            bPeiceSelected = true;
                            aiSelect[TARGET][0] = aiSelect[cTurn][0];
                            aiSelect[TARGET][1] = aiSelect[cTurn][1];
                        }
                    }        
                }        
            }
            else
            {
                if (!bTargetSelected)
                {
                    if (keyboardWatch.KeyBeenPressed(iRightKey))
                    {
                        if (aiSelect[TARGET][0] < 7)
                        {
                            aiSelect[TARGET][0] ++;
                        }    
                    }
                    if (keyboardWatch.KeyBeenPressed(iLeftKey))
                    {
                        if (aiSelect[TARGET][0] > 0)
                        {
                            aiSelect[TARGET][0] --;
                        }    
                    } 
                    if (keyboardWatch.KeyBeenPressed(iUpKey))
                    {
                        if (aiSelect[TARGET][1] < 7)
                        {
                            aiSelect[TARGET][1] ++;
                        }    
                    } 
                    if (keyboardWatch.KeyBeenPressed(iDownKey))
                    {
                        if (aiSelect[TARGET][1] > 0)
                        {
                            aiSelect[TARGET][1] --;
                        }    
                    } 
                    if (keyboardWatch.KeyBeenPressed(iBackKey))
                    {
                        bPeiceSelected = false;
                    }    
                    if (keyboardWatch.KeyBeenPressed(iSelectKey))
                    {
                        moveinfoCurrent = CalcMoveInfo();
                        if (moveinfoCurrent.bValid)
                        {
                            bTargetSelected = true;
                        }    
                    }    
                }    
            }
        }
    } 
    //keyboard code ends here  
    */           
}

MoveInfo CDglCheckers3d::CalcMoveInfo()
{
    //MoveInfo moveinfo;
    //moveinfo.bValid = true;
    //return moveinfo;
    
    // some constants to make life easier
    int aiEnemyRow[2];
    aiEnemyRow[WHITE] = 7;
    aiEnemyRow[BLACK] = 0;
    
    // i use these twice
    int x = 0;
    int y = 0;
    
    //this will be returned
    MoveInfo moveinfo;
    moveinfo.fProgress = 0;
    moveinfo.bMoved = false;
    moveinfo.bEndsTurn = true;
    bool bPlayerMustCapture = false;
    
    
    moveinfo.bValid = true;
    // must move onto vacent cell
    if (!checkersBoard.GetCell(aiSelect[TARGET][0], aiSelect[TARGET][1]).bEmpty)
    {
        moveinfo.bValid = false;
        return moveinfo;
    }
    // must move in correct direction unless king 
    if (!checkersBoard.GetCell(aiSelect[cTurn][0], aiSelect[cTurn][1]).bKing)
    {
        if (abs(aiEnemyRow[cTurn] - aiSelect[cTurn][1]) < abs(aiEnemyRow[cTurn] - aiSelect[TARGET][1]))
        {
            moveinfo.bValid = false;
            return moveinfo;
        }      
    }
    // cant move more than 2 rows in either direction      
    int rowDifference = abs(aiSelect[TARGET][1] - aiSelect[cTurn][1]);
    int colDifference = abs(aiSelect[TARGET][0] - aiSelect[cTurn][0]);
    if (rowDifference <= 2)
    {
        // cant move 0 rows
        if (rowDifference == 0)
        {
            moveinfo.bValid = false;
            return moveinfo;
        }
        // check if a player must capture this turn
        for (y = 0; y <= 7; y++)
        {
            for (x = 0; x <= 7; x++)
            {
                if (!checkersBoard.GetCell(x,y).bEmpty)
                {
                    if (checkersBoard.GetCell(x,y).cOwner == cTurn)
                    {
                        if ( ((checkersBoard.GetCell(x,y).cOwner == WHITE) | (checkersBoard.GetCell(x,y).bKing)) & (y < 6) )
                        {
                            if (x > 1)
                            {
                                if (!checkersBoard.GetCell(x - 1, y + 1).bEmpty)
                                {
                                    if (checkersBoard.GetCell(x - 1, y + 1).cOwner != cTurn)
                                    {
                                        if (checkersBoard.GetCell(x - 2, y + 2).bEmpty)
                                        {
                                            bPlayerMustCapture = true;
                                        }
                                    }    
                                }      
                            }
                            if (x < 6)
                            {    
                                if (!checkersBoard.GetCell(x + 1, y + 1).bEmpty)
                                {
                                    if (checkersBoard.GetCell(x + 1, y + 1).cOwner != cTurn)
                                    {
                                        if (checkersBoard.GetCell(x + 2, y + 2).bEmpty)
                                        {
                                            bPlayerMustCapture = true;
                                        }
                                    }    
                                }
                            }    
                        }
                        if ( ((checkersBoard.GetCell(x,y).cOwner == BLACK) | (checkersBoard.GetCell(x,y).bKing)) & (y > 1) )
                        {
                            if (x > 1)
                            {
                                if (!checkersBoard.GetCell(x - 1, y - 1).bEmpty)
                                {
                                    if (checkersBoard.GetCell(x - 1, y - 1).cOwner != cTurn)
                                    {
                                        if (checkersBoard.GetCell(x - 2, y - 2).bEmpty)
                                        {
                                            bPlayerMustCapture = true;
                                        }
                                    }    
                                }      
                            }
                            if (x < 6)
                            {    
                                if (!checkersBoard.GetCell(x + 1, y - 1).bEmpty)
                                {
                                    if (checkersBoard.GetCell(x + 1, y - 1).cOwner != cTurn)
                                    {
                                        if (checkersBoard.GetCell(x + 2, y - 2).bEmpty)
                                        {
                                            bPlayerMustCapture = true;
                                        }
                                    }    
                                }
                            }    
                        }
                    }
                }
            }
        }
        // can move 1 row (no capture)
        if (rowDifference == 1)
        {
            if (bPlayerMustCapture)
            {
                moveinfo.bValid = false;
                return moveinfo;
            }    
            if (colDifference != 1)
            {
                moveinfo.bValid = false;
                return moveinfo; 
            }
            moveinfo.bCapture = false;
            moveinfo.bEndsTurn = true;
            moveinfo.bWinsGame = false;    
        }       
        // can move 2 rows (capture)
        if (rowDifference == 2)
        {
            if (colDifference != 2)
            {
                moveinfo.bValid = false;
                return moveinfo; 
            }
            if (aiSelect[TARGET][0] > aiSelect[cTurn][0])
            {
                moveinfo.iCapture1 = aiSelect[cTurn][0] + 1;
            }
            else
            {
                moveinfo.iCapture1 = aiSelect[cTurn][0] - 1;      
            } 
            if (aiSelect[TARGET][1] > aiSelect[cTurn][1])
            {
                moveinfo.iCapture2 = aiSelect[cTurn][1] + 1;
            }
            else
            {
                moveinfo.iCapture2 = aiSelect[cTurn][1] - 1;      
            }
            if (checkersBoard.GetCell(moveinfo.iCapture1, moveinfo.iCapture2).bEmpty)
            {
                moveinfo.bValid = false;
                return moveinfo; 
            }
            if (checkersBoard.GetCell(moveinfo.iCapture1, moveinfo.iCapture2).cOwner == cTurn)
            {
                moveinfo.bValid = false;
                return moveinfo; 
            }      
            moveinfo.bCapture = true;
            
            x = aiSelect[TARGET][0];
            y = aiSelect[TARGET][1];
            if ( ((checkersBoard.GetCell(aiSelect[cTurn][0],aiSelect[cTurn][1]).cOwner == WHITE) | (checkersBoard.GetCell(aiSelect[cTurn][0],aiSelect[cTurn][1]).bKing)) & (y < 6) )
            {
                if (x > 1)
                {
                    if (!checkersBoard.GetCell(x - 1, y + 1).bEmpty)
                    {
                        if (checkersBoard.GetCell(x - 1, y + 1).cOwner != cTurn)
                        {
                            if (checkersBoard.GetCell(x - 2, y + 2).bEmpty)
                            {
                                moveinfo.bEndsTurn = false;
                            }
                        }    
                    }      
                }
                if (x < 6)
                {    
                    if (!checkersBoard.GetCell(x + 1, y + 1).bEmpty)
                    {
                        if (checkersBoard.GetCell(x + 1, y + 1).cOwner != cTurn)
                        {
                            if (checkersBoard.GetCell(x + 2, y + 2).bEmpty)
                            {
                                moveinfo.bEndsTurn = false;
                            }
                        }    
                    }
                }    
            }
            if ( ((checkersBoard.GetCell(aiSelect[cTurn][0],aiSelect[cTurn][1]).cOwner == BLACK) | (checkersBoard.GetCell(aiSelect[cTurn][0],aiSelect[cTurn][1]).bKing)) & (y > 1) )
            {
                if (x > 1)
                {
                    if (!checkersBoard.GetCell(x - 1, y - 1).bEmpty)
                    {
                        if (checkersBoard.GetCell(x - 1, y - 1).cOwner != cTurn)
                        {
                            if (checkersBoard.GetCell(x - 2, y - 2).bEmpty)
                            {
                                moveinfo.bEndsTurn = false;
                            }
                        }    
                    }      
                }
                if (x < 6)
                {    
                    if (!checkersBoard.GetCell(x + 1, y - 1).bEmpty)
                    {
                        if (checkersBoard.GetCell(x + 1, y - 1).cOwner != cTurn)
                        {
                            if (checkersBoard.GetCell(x + 2, y - 2).bEmpty)
                            {
                                moveinfo.bEndsTurn = false;
                            }
                        }    
                    }
                }    
            }
            
            moveinfo.bWinsGame = true;
            bool bEnemyPeiceFound = false;
            for (y = 0; y <= 7; y ++)
            {
                for (x = 0; x <= 7; x ++)
                {
                    if (!checkersBoard.GetCell(x, y).bEmpty)
                    {
                        if (checkersBoard.GetCell(x, y).cOwner != cTurn)
                        {
                            if (bEnemyPeiceFound)
                            {
                                moveinfo.bWinsGame = false;
                            }
                            bEnemyPeiceFound = true;    
                        }
                    }
                }
            }
                                
        }    
    }
    else
    {
        moveinfo.bValid = false;
        return moveinfo;
    }    
    
    // check if peice becomes king
    moveinfo.bKing = false;
    if (aiSelect[TARGET][1] == aiEnemyRow[cTurn])
    {
        if (!checkersBoard.GetCell(aiSelect[cTurn][0], aiSelect[cTurn][1]).bKing)
        {
            moveinfo.bKing = true;
            moveinfo.bEndsTurn = true; //a peice that gets kinged cant jump again on same turn
        }    
    }
    
    if (moveinfo.bEndsTurn)
    {
        //Cell cellTemp;
        bool bEnemyColour;
        if (cTurn == WHITE)
        {
            bEnemyColour = BLACK;
        }
        else
        {
            bEnemyColour = WHITE;
        }        
        bool bNoMovesForEnemy = true;
        for (y = 0; y <= 7; y ++)
        {
            for (x = 0; x <= 7; x ++)
            {
                if ( !checkersBoard.GetCell(x,y).bEmpty & (checkersBoard.GetCell(x,y).cOwner == bEnemyColour) & !(moveinfo.bCapture & (moveinfo.iCapture1 == x) & (moveinfo.iCapture2 == y)) )
                {
                    //y -1
                    if (  ((abs(aiEnemyRow[bEnemyColour] - y) > abs(aiEnemyRow[bEnemyColour] - (y - 1))) | checkersBoard.GetCell(x,y).bKing) & (y > 0) )
                    {
                        //x -1
                        if ( (((checkersBoard.GetCell(x-1,y-1).bEmpty) & !((aiSelect[TARGET][0] == (x-1)) & (aiSelect[TARGET][1] == (y-1)))) | ((aiSelect[cTurn][0] == (x-1)) & (aiSelect[cTurn][1] == (y-1)))) & (x > 0))
                        {
                            bNoMovesForEnemy = false;
                        }    
                        //x +1
                        if ( (((checkersBoard.GetCell(x+1,y-1).bEmpty) & !((aiSelect[TARGET][0] == (x+1)) & (aiSelect[TARGET][1] == (y-1)))) | ((aiSelect[cTurn][0] == (x+1)) & (aiSelect[cTurn][1] == (y-1)))) & (x < 7))
                        {
                            bNoMovesForEnemy = false;
                        }    
                    }
                    //y +1
                    if (  ((abs(aiEnemyRow[bEnemyColour] - y) > abs(aiEnemyRow[bEnemyColour] - (y + 1))) | checkersBoard.GetCell(x,y).bKing) & (y < 7) )
                    {
                        //x -1
                        if ( (((checkersBoard.GetCell(x-1,y+1).bEmpty) & !((aiSelect[TARGET][0] == (x-1)) & (aiSelect[TARGET][1] == (y+1)))) | ((aiSelect[cTurn][0] == (x-1)) & (aiSelect[cTurn][1] == (y+1)))) & (x > 0))
                        {
                            bNoMovesForEnemy = false;
                        }    
                        //x +1
                        if ( (((checkersBoard.GetCell(x+1,y+1).bEmpty) & !((aiSelect[TARGET][0] == (x+1)) & (aiSelect[TARGET][1] == (y+1)))) | ((aiSelect[cTurn][0] == (x+1)) & (aiSelect[cTurn][1] == (y+1)))) & (x < 7))
                        {
                            bNoMovesForEnemy = false;
                        }    
                    }
                    //y -2
                    if (  ((abs(aiEnemyRow[bEnemyColour] - y) > abs(aiEnemyRow[bEnemyColour] - (y - 2))) | checkersBoard.GetCell(x,y).bKing) & (y > 1) )
                    {
                        //x -2
                        if ( (((checkersBoard.GetCell(x-2,y-2).bEmpty) & !((aiSelect[TARGET][0] == (x-2)) & (aiSelect[TARGET][1] == (y-2)))) | ((aiSelect[cTurn][0] == (x-2)) & (aiSelect[cTurn][1] == (y-2)))) & (x > 1) &    ( (!(checkersBoard.GetCell(x-1,y-1).bEmpty) & (checkersBoard.GetCell(x-1,y-1).cOwner == cTurn)) | (aiSelect[cTurn][0] == (x-1) & aiSelect[cTurn][1] == (y-1))) )
                        {
                            bNoMovesForEnemy = false;
                        }  
                        //x +2
                        if ( (((checkersBoard.GetCell(x+2,y-2).bEmpty) & !((aiSelect[TARGET][0] == (x+2)) & (aiSelect[TARGET][1] == (y-2)))) | ((aiSelect[cTurn][0] == (x+2)) & (aiSelect[cTurn][1] == (y-2)))) & (x < 6) &    ( (!(checkersBoard.GetCell(x+1,y-1).bEmpty) & (checkersBoard.GetCell(x+1,y-1).cOwner == cTurn)) | (aiSelect[cTurn][0] == (x+1) & aiSelect[cTurn][1] == (y-1))) )
                        {
                            bNoMovesForEnemy = false;
                        } 
                    } 
                    //y +2
                    if (  ((abs(aiEnemyRow[bEnemyColour] - y) > abs(aiEnemyRow[bEnemyColour] - (y + 2))) | checkersBoard.GetCell(x,y).bKing) & (y < 6) )
                    {
                        //x -2
                        if ( (((checkersBoard.GetCell(x-2,y+2).bEmpty) & !((aiSelect[TARGET][0] == (x-2)) & (aiSelect[TARGET][1] == (y+2)))) | ((aiSelect[cTurn][0] == (x-2)) & (aiSelect[cTurn][1] == (y+2)))) & (x > 1) &    ( (!(checkersBoard.GetCell(x-1,y+1).bEmpty) & (checkersBoard.GetCell(x-1,y+1).cOwner == cTurn)) | (aiSelect[cTurn][0] == (x-1) & aiSelect[cTurn][1] == (y+1))) )
                        {
                            bNoMovesForEnemy = false;
                        }  
                        //x +2
                        if ( (((checkersBoard.GetCell(x+2,y+2).bEmpty) & !((aiSelect[TARGET][0] == (x+2)) & (aiSelect[TARGET][1] == (y+2)))) | ((aiSelect[cTurn][0] == (x+2)) & (aiSelect[cTurn][1] == (y+2)))) & (x < 6) &    ( (!(checkersBoard.GetCell(x-1,y+1).bEmpty) & (checkersBoard.GetCell(x-1,y+1).cOwner == cTurn)) | (aiSelect[cTurn][0] == (x-1) & aiSelect[cTurn][1] == (y+1))) )
                        {
                            bNoMovesForEnemy = false;
                        } 
                    }     
                }
            }
        } 
        if (bNoMovesForEnemy)
        {
            moveinfo.bWinsGame = true;
        }    
    }                   
    
    
    return moveinfo;
}

void CDglCheckers3d::Ai()
{
    AiMove moves[48];
    int iNumberOfMoves = 0;
    int x = 0;
    int y = 0;
    while (1)
    {
        if (!checkersBoard.GetCell(x,y).bEmpty)
        {
            if (checkersBoard.GetCell(x,y).cOwner == cTurn)
            {
                //check it
                if ((cTurn == WHITE) | checkersBoard.GetCell(x,y).bKing)
                {
                    if (y < 7)
                    {
                        if (x > 0)
                        {
                            if (checkersBoard.GetCell(x-1,y+1).bEmpty)
                            {
                                //move found
                                iNumberOfMoves ++;
                                moves[iNumberOfMoves - 1].iPeiceX = x;
                                moves[iNumberOfMoves - 1].iPeiceY = y;
                                moves[iNumberOfMoves - 1].iTargetX = x-1;
                                moves[iNumberOfMoves - 1].iTargetY = y+1;
                                moves[iNumberOfMoves - 1].bCapture = false;
                                moves[iNumberOfMoves - 1].iScore = 0;
                            }
                        }
                        if (x < 7)
                        {
                            if (checkersBoard.GetCell(x+1,y+1).bEmpty)
                            {
                                //move found
                                iNumberOfMoves ++;
                                moves[iNumberOfMoves - 1].iPeiceX = x;
                                moves[iNumberOfMoves - 1].iPeiceY = y;
                                moves[iNumberOfMoves - 1].iTargetX = x+1;
                                moves[iNumberOfMoves - 1].iTargetY = y+1;
                                moves[iNumberOfMoves - 1].bCapture = false;
                                moves[iNumberOfMoves - 1].iScore = 0;
                            }
                        }
                        if (y < 6)
                        {
                            if (x > 1)
                            {
                                if (!checkersBoard.GetCell(x-1,y+1).bEmpty)
                                {
                                    if (checkersBoard.GetCell(x-1,y+1).cOwner != cTurn)
                                    {
                                        if (checkersBoard.GetCell(x-2,y+2).bEmpty)
                                        {
                                            //move found
                                            iNumberOfMoves ++;
                                            moves[iNumberOfMoves - 1].iPeiceX = x;
                                            moves[iNumberOfMoves - 1].iPeiceY = y;
                                            moves[iNumberOfMoves - 1].iTargetX = x-2;
                                            moves[iNumberOfMoves - 1].iTargetY = y+2;
                                            moves[iNumberOfMoves - 1].bCapture = true;
                                            moves[iNumberOfMoves - 1].iScore = 1;
                                        }
                                    }        
                                }
                            }
                            if (x < 6)
                            {
                                if (!checkersBoard.GetCell(x+1,y+1).bEmpty)
                                {
                                    if (checkersBoard.GetCell(x+1,y+1).cOwner != cTurn)
                                    {
                                        if (checkersBoard.GetCell(x+2,y+2).bEmpty)
                                        {
                                            //move found
                                            iNumberOfMoves ++;
                                            moves[iNumberOfMoves - 1].iPeiceX = x;
                                            moves[iNumberOfMoves - 1].iPeiceY = y;
                                            moves[iNumberOfMoves - 1].iTargetX = x+2;
                                            moves[iNumberOfMoves - 1].iTargetY = y+2;
                                            moves[iNumberOfMoves - 1].bCapture = true;
                                            moves[iNumberOfMoves - 1].iScore = 1;
                                        }
                                    }        
                                }
                            }
                        }
                    }
                }
                if ((cTurn == BLACK) | checkersBoard.GetCell(x,y).bKing)
                {
                    if (y > 0)
                    {
                        if (x > 0)
                        {
                            if (checkersBoard.GetCell(x-1,y-1).bEmpty)
                            {
                                //move found
                                iNumberOfMoves ++;
                                moves[iNumberOfMoves - 1].iPeiceX = x;
                                moves[iNumberOfMoves - 1].iPeiceY = y;
                                moves[iNumberOfMoves - 1].iTargetX = x-1;
                                moves[iNumberOfMoves - 1].iTargetY = y-1;
                                moves[iNumberOfMoves - 1].bCapture = false;
                                moves[iNumberOfMoves - 1].iScore = 0;
                            }
                        }
                        if (x < 7)
                        {
                            if (checkersBoard.GetCell(x+1,y-1).bEmpty)
                            {
                                //move found
                                iNumberOfMoves ++;
                                moves[iNumberOfMoves - 1].iPeiceX = x;
                                moves[iNumberOfMoves - 1].iPeiceY = y;
                                moves[iNumberOfMoves - 1].iTargetX = x+1;
                                moves[iNumberOfMoves - 1].iTargetY = y-1;
                                moves[iNumberOfMoves - 1].bCapture = false;
                                moves[iNumberOfMoves - 1].iScore = 0;
                            }
                        }
                        if (y > 1)
                        {
                            if (x > 1)
                            {
                                if (!checkersBoard.GetCell(x-1,y-1).bEmpty)
                                {
                                    if (checkersBoard.GetCell(x-1,y-1).cOwner != cTurn)
                                    {
                                        if (checkersBoard.GetCell(x-2,y-2).bEmpty)
                                        {
                                            //move found
                                            iNumberOfMoves ++;
                                            moves[iNumberOfMoves - 1].iPeiceX = x;
                                            moves[iNumberOfMoves - 1].iPeiceY = y;
                                            moves[iNumberOfMoves - 1].iTargetX = x-2;
                                            moves[iNumberOfMoves - 1].iTargetY = y-2;
                                            moves[iNumberOfMoves - 1].bCapture = true;
                                            moves[iNumberOfMoves - 1].iScore = 1;
                                        }
                                    }        
                                }
                            }
                            if (x < 6)
                            {
                                if (!checkersBoard.GetCell(x+1,y-1).bEmpty)
                                {
                                    if (checkersBoard.GetCell(x+1,y-1).cOwner != cTurn)
                                    {
                                        if (checkersBoard.GetCell(x+2,y-2).bEmpty)
                                        {
                                            //move found
                                            iNumberOfMoves ++;
                                            moves[iNumberOfMoves - 1].iPeiceX = x;
                                            moves[iNumberOfMoves - 1].iPeiceY = y;
                                            moves[iNumberOfMoves - 1].iTargetX = x+2;
                                            moves[iNumberOfMoves - 1].iTargetY = y-2;
                                            moves[iNumberOfMoves - 1].bCapture = true;
                                            moves[iNumberOfMoves - 1].iScore = 1;
                                        }
                                    }        
                                }
                            }
                        }
                    }
                }             
            }
        }        
        
        x ++;
        if (x > 7)
        {
            y ++;
            x = 0;
        }
        if (y > 7)
        {
            if (iNumberOfMoves == 0)
            {
                MessageBox(NULL, "The Ai reckons there arnt any moves", "error",0);
                break; //no valid moves? this shouldn't happen
            }
            break;
        }
    }    
    
    // decide whiche move to make
    bool bMustCapture = false;
    int iHighestCaptureScore = -10;
    int iHighestScore = -10;
    for (int i = 0; i < iNumberOfMoves; i++)
    {
        if (moves[i].iScore > iHighestScore)
        {
            iHighestScore = moves[i].iScore;
        }
        if (moves[i].bCapture)
        {
            bMustCapture = true;
            if (moves[i].iScore > iHighestCaptureScore)
            {
                iHighestCaptureScore = moves[i].iScore;
            }    
        }
    }
    for (int i = 0; i < iNumberOfMoves; i++)
    {
        if (bMustCapture)
        {
            if (moves[i].bCapture)
            {
                if (moves[i].iScore == iHighestCaptureScore)
                {
                    //use this move
                    aiSelect[cTurn][0] = moves[i].iPeiceX;
                    aiSelect[cTurn][1] = moves[i].iPeiceY;
                    aiSelect[TARGET][0] = moves[i].iTargetX;
                    aiSelect[TARGET][1] = moves[i].iTargetY;
                }
            }
        }
        else
        {
            if (moves[i].iScore == iHighestScore)
            {
                // use this move
                aiSelect[cTurn][0] = moves[i].iPeiceX;
                aiSelect[cTurn][1] = moves[i].iPeiceY;
                aiSelect[TARGET][0] = moves[i].iTargetX;
                aiSelect[TARGET][1] = moves[i].iTargetY;
            }
        }
    }                    
    
    bAiFinished = true;
}    

int CDglCheckers3d::GetMouseSelectionId(int x, int y)
{
	int objectsFound = 0;								// This will hold the amount of objects clicked
	int	viewportCoords[4] = {0};						// We need an array to hold our view port coordinates

	// This will hold the ID's of the objects we click on.
	// We make it an arbitrary number of 32 because openGL also stores other information
	// that we don't care about.  There is about 4 slots of info for every object ID taken up.
	unsigned int selectBuffer[32] = {0};				
														
	// glSelectBuffer is what we register our selection buffer with.  The first parameter
	// is the size of our array.  The next parameter is the buffer to store the information found.
	// More information on the information that will be stored in selectBuffer is further below.

	glSelectBuffer(32, selectBuffer);					// Setup our selection buffer to accept object ID's

	// This function returns information about many things in OpenGL.  We pass in GL_VIEWPORT
	// to get the view port coordinates.  It saves it like a RECT with {top, left, bottom, right}

	glGetIntegerv(GL_VIEWPORT, viewportCoords);			// Get the current view port coordinates

	// Now we want to get out of our GL_MODELVIEW matrix and start effecting our
	// GL_PROJECTION matrix.  This allows us to check our X and Y coords against 3D space.

	glMatrixMode(GL_PROJECTION);						// We want to now effect our projection matrix
	
	glPushMatrix();										// We push on a new matrix so we don't effect our 3D projection

		// This makes it so it doesn't change the frame buffer if we render into it, instead, 
		// a record of the names of primitives that would have been drawn if the render mode was
		// GL_RENDER are now stored in the selection array (selectBuffer).

		glRenderMode(GL_SELECT);						// Allows us to render the objects, but not change the frame buffer

		glLoadIdentity();								// Reset our projection matrix

		// gluPickMatrix allows us to create a projection matrix that is around our
		// cursor.  This basically only allows rendering in the region that we specify.
		// If an object is rendered into that region, then it saves that objects ID for us (The magic).
		// The first 2 parameters are the X and Y position to start from, then the next 2
		// are the width and height of the region from the starting point.  The last parameter is
		// of course our view port coordinates.  You will notice we subtract "y" from the
		// BOTTOM view port coordinate.  We do this to flip the Y coordinates around.  The 0 y
		// coordinate starts from the bottom, which is opposite to window's coordinates.
		// We also give a 2 by 2 region to look for an object in.  This can be changed to preference.

		gluPickMatrix(x, viewportCoords[3] - y, 2, 2, viewportCoords);

		// Next, we just call our normal gluPerspective() function, exactly as we did on startup.
		// This is to multiply the perspective matrix by the pick matrix we created up above. 

		gluPerspective(45.0f,(float)SCREEN_WIDTH/(float)SCREEN_HEIGHT,0.1f,150.0f);
		
		glMatrixMode(GL_MODELVIEW);						// Go back into our model view matrix
	
		Draw(true);									// Now we render into our selective mode to pinpoint clicked objects

		// If we return to our normal render mode from select mode, glRenderMode returns
		// the number of objects that were found in our specified region (specified in gluPickMatrix())

		objectsFound = glRenderMode(GL_RENDER);			// Return to render mode and get the number of objects found
		//MessageBox(NULL,"bodge","bodge",0);
		glMatrixMode(GL_PROJECTION);					// Put our projection matrix back to normal.
	glPopMatrix();										// Stop effecting our projection matrix

	glMatrixMode(GL_MODELVIEW);							// Go back to our normal model view matrix

	// PHEW!  That was some stuff confusing stuff.  Now we are out of the clear and should have
	// an ID of the object we clicked on.  objectsFound should be at least 1 if we found an object.

	if (objectsFound > 0)
	{		
		// If we found more than one object, we need to check the depth values
		// of all the objects found.  The object with the LEAST depth value is
		// the closest object that we clicked on.  Depending on what you are doing,
		// you might want ALL the objects that you clicked on (if some objects were
		// behind the closest one), but for this tutorial we just care about the one
		// in front.  So, how do we get the depth value?  Well, The selectionBuffer
		// holds it.  For every object there is 4 values.  The first value is
		// "the number of names in the name stack at the time of the event, followed 
		// by the minimum and maximum depth values of all vertices that hit since the 
		// previous event, then followed by the name stack contents, bottom name first." - MSDN
		// The only ones we care about are the minimum depth value (the second value) and
		// the object ID that was passed into glLoadName() (This is the fourth value).
		// So, [0 - 3] is the first object's data, [4 - 7] is the second object's data, etc...
		// Be carefull though, because if you are displaying 2D text in front, it will
		// always find that as the lowest object.  So make sure you disable text when
		// rendering the screen for the object test.  I use a flag for RenderScene().
		// So, lets get the object with the lowest depth!		

		// Set the lowest depth to the first object to start it off.
		// 1 is the first object's minimum Z value.
		// We use an unsigned int so we don't get a warning with selectBuffer below.
		unsigned int lowestDepth = selectBuffer[1];

		// Set the selected object to the first object to start it off.
		// 3 is the first object's object ID we passed into glLoadName().
		int selectedObject = selectBuffer[3];

		// Go through all of the objects found, but start at the second one
		for(int i = 1; i < objectsFound; i++)
		{
			// Check if the current objects depth is lower than the current lowest
			// Notice we times i by 4 (4 values for each object) and add 1 for the depth.
			if(selectBuffer[(i * 4) + 1] < lowestDepth)
			{
				// Set the current lowest depth
				lowestDepth = selectBuffer[(i * 4) + 1];

				// Set the current object ID
				selectedObject = selectBuffer[(i * 4) + 3];
			}
		}
		
		// Return the selected object
		return selectedObject;
		//return selectBuffer[6]; //i dont know why but this works, and the crap above doesn't..
	}

	// We didn't click on any objects so return 0
	return 0;											
}


// known bugs
// - board will stop mid rotation if u play too fast (fixed by disallowing fats play)
// - it claimed once that black had won even though red still had 1 movable
//   peice (red also had 1 trapped peice) a black king had just completed a
//   triple jump
// - it claimed that red had won even though blak had a king on the red starting row.
//   had it not been a king it ould have been trapped
// todo
// - player turn indicator
// - menu button
// - fps counter (make a toggle key)
// - load 3d models
// - ai
// - network play? prob not

