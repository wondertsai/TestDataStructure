#include "aLinkedList.h"



#if (0)
typedef struct ListNode
{
	unsigned int iData;
	struct ListNode *pNext;
} NODE;

void InsertAfter(NODE* pPrevNode, unsigned int iData)
{
	NODE *pNode;

	pNode= (NODE*)malloc(sizeof(NODE));
	if(pPrevNode)
	{
		pNode->pNext=pPrevNode->pNext;
		pPrevNode->pNext=pNode;
	}
	pNode->iData=iData;
}





int testfunc(int i)
{
	return (i+1);
}

#endif
