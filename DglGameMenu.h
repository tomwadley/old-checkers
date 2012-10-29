// DglGameMenu.h

#ifndef DGLGAMEMENU_H
#define DGLGAMEMENU_H

#include "DglTexture.h"

struct MenuItem
{
    CDglTexture dgltexturePic;
    CDglTexture dgltextureMaskPic;
    bool bSelectable;
    bool bVisible;
};    

class CDglGameMenu
{
public:
    CDglGameMenu();
    ~CDglGameMenu(){DestroyItemList();};
    
    bool CreateItemList(int iNumItems);
    void DestroyItemList();
    void DrawOgl(); //Enter Ortho mode before calling DrawOgl()
    void ModifySelectionUpOrDown(bool bUp); //true for up, false for down
    void ModifySelectionFromMouse(long lMouseX, long lMouseY);
    void SetItemDimensions(int iWidth, int iHeight);
    void SetScreenDimensions(int iWidth, int iHeight);
    void Unselect();
    void Select(int iItem);
    
    MenuItem* GetItem(int iItem){return &amenuitemItems[iItem];}
    bool ItemSelected(){return bItemSelected;}
    int GetSelectedItem(){return iSelectedItem;}
    CDglTexture* GetSelectPic(){return &dgltextureSelect;}
    CDglTexture* GetMaskSelectPic(){return &dgltextureMaskSelect;}
    
private:
    int iNumberOfItems;
    MenuItem* amenuitemItems;
    bool bItemSelected;
    int iSelectedItem;
    int iMenuItemWidth;
    int iMenuItemHeight;
    int iScreenWidth;
    int iScreenHeight;
    CDglTexture dgltextureSelect;
    CDglTexture dgltextureMaskSelect;
};    

#endif
