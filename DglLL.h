// DglLL.h

#ifndef DGLLL_H
#define DGLLL_H

template <class T>
class CDglLLNode
{
public:
    CDglLLNode();
    ~CDglLLNode();
    
    //CDglLLNode* InsertNodeBehind();
    //CDglLLNode* InsertNodeAfter();
    
    T tData;
    CDglLLNode* pNodeNext;
    CDglLLNode* pNodePrev;
};            

template <class T>
class CDglLL
{
public:
    CDglLL();
    ~CDglLL();
    
    void MoveNext();
    void MovePrev();
    void MoveFirst();
    
    T* GetData();
    T* InsertFirst();
    //t* InsertAfter();
    //t* InsertBehind();
    void DeleteNode();
    
    int GetNumNodes();
private:
    CDglLLNode<T>* pNodeFirst;
    CDglLLNode<T>* pNodeSelected;
    int iNumNodes;
};
  
template <class T>
CDglLLNode<T>::CDglLLNode()
{
    pNodeNext = pNodePrev = NULL;
}

template <class T>
CDglLLNode<T>::~CDglLLNode()
{}
/*
CDglLLNode* CDglLLNode::InsertNodeBehind()
{
    pNodePrev->pNodeNext = new CDglLLNode<t>;
    pNodePrev->pNodeNext->pNodePrev = pNodePrev;
    pNodePrev->pNodeNext->pNodeNext = this;
    pNodePrev = pNodePrev->pNodeNext;
    return pNodePrev;
}    

CDglLLNode* CDglLLNode::InsertNodeAfter()
{
    pNodeNext->pNodePrev = new CDglLLNode<t>;
    pNodeNext->pNodePrev->pNodeNext = pNodeNext;
    pNodeNext->pNodePrev->pNodePrev = this;
    pNodeNext = pNodeNext->pNodePrev;
    return pNodeNext;
}    
*/

template <class T>
CDglLL<T>::CDglLL()
{
    pNodeFirst = pNodeSelected = NULL;
    iNumNodes = 0;
}

template <class T>
CDglLL<T>::~CDglLL()
{
    MoveFirst();
    while (pNodeSelected != NULL)
    {
        DeleteNode();
    }
} 

template <class T>
void CDglLL<T>::MoveNext()
{
    if (pNodeSelected != NULL)
    {
        pNodeSelected = pNodeSelected->pNodeNext;
    }    
}    

template <class T>
void CDglLL<T>::MovePrev()
{
    if (pNodeSelected != NULL)
    {
        pNodeSelected = pNodeSelected->pNodePrev;
    }    
}    

template <class T>
void CDglLL<T>::MoveFirst()
{
    pNodeSelected = pNodeFirst;
}    
       
template <class T>
T* CDglLL<T>::GetData()
{
    if (pNodeSelected != NULL)
    {
        return &pNodeSelected->tData;
    }
    return NULL;    
}

/*
t* CDglLL::InsertAfter()
{
    if (pNodeSelected == NULL)
    {
        return NULL;
    }    
    CDglLLNode<t>* pNodeNew = new CDglLLNode<t>;
    pNodeNew->pNodePrev = pNodeSelected;
    if (pNodeSelected != NULL)
    {
        if (pNodeSelected->pNodeNext != NULL)
        {
                pNodeNew->pNodeNext = pNodeSelected->pNodeNext;
        }
        else
        {
            pNodeFirst = pNodeNew;
        }            
        pNodeSelected->pNodeNext = pNodeNew;
    }
    else
    {
        pNodeFirst = pNewNode;
    }    
    iNumNodes ++;
    return &pNodeNew->tData;
}    
    
t* CDglLL::InsertBehind()
{
    if (pNodeSelected == NULL)
    {
        return NULL;
    }    
    CDglLLNode<t>* pNodeNew = new CDglLLNode<t>;
    pNodeNew->pNodeNext = pNodeSelected;
    if (pNodeSelected != NULL)
    {
        if (pNodeSelected->pNodePrev != NULL)
        {
                pNodeNew->pNodePrev = pNodeSelected->pNodePrev;
        }
        else
        {
            pNodeFirst = pNodeNew;
        }            
        pNodeSelected->pNodePrev = pNodeNew;
    }
    else
    {
        pNodeFirst = pNodeNew;
    } 
    iNumNodes ++;
    return &pNodeNew->tData;
}  
*/

template <class T>
T* CDglLL<T>::InsertFirst()
{
    CDglLLNode<T>* pNodeNew = new CDglLLNode<T>;
    if (!pNodeNew){return NULL;}
    pNodeNew->pNodeNext = pNodeFirst;
    pNodeFirst = pNodeNew;
    return &pNodeFirst->tData;
}

template <class T>
void CDglLL<T>::DeleteNode()
{
    if (pNodeSelected == NULL)
    {
        return;
    }
    if (pNodeSelected->pNodePrev != NULL)
    {
        pNodeSelected->pNodePrev->pNodeNext = pNodeSelected->pNodeNext;
    }
    if (pNodeSelected->pNodeNext != NULL)
    {  
        pNodeSelected->pNodeNext->pNodePrev = pNodeSelected->pNodePrev;
    }    
    CDglLLNode<T>* pNodeNewSelection = pNodeSelected->pNodeNext;
    delete pNodeSelected;
    pNodeSelected = pNodeNewSelection;
}

template <class T>
int CDglLL<T>::GetNumNodes()
{
    return iNumNodes;
}

  
#endif

