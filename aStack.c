/*
 * aStack.c
 *
 *  Created on: 2020¦~6¤ë18¤é
 *      Author: qwerw
 */
#include "aStack.h"

#define MAX_STACK_ITEM_NUM 64
typedef struct stSTACK
{
    char item[MAX_STACK_ITEM_NUM];
    int top;
}STACK;




#define STACK_RET_YES       1
#define STACK_RET_NO        0

STACK S;

void stack_init(void)
{
    S.top=-1;
}

void stack_clear(void)
{
    stack_init();
}

static unsigned int isFull(void)
{
    if (S.top >= (MAX_STACK_ITEM_NUM-1))
        return STACK_RET_YES;
    else
        return STACK_RET_NO;
}

static unsigned int isEmpty(void)
{
    if (S.top == -1)
        return STACK_RET_YES;
    else
        return STACK_RET_NO;
}

unsigned int stack_push(char val)
{
    if (isFull()==STACK_RET_YES)
        return STACK_RET_FAILED;

    S.top++;
    S.item[S.top]=val;

    return STACK_RET_OK;
}

unsigned int stack_pop(char *pItem)
{
    if (isEmpty()==STACK_RET_YES)
        return STACK_RET_FAILED;

    *pItem=S.item[S.top];
    S.top--;

    return STACK_RET_OK;
}

#if (STACK_EXTEND_FUNCTION_SUPPORT == 1)

unsigned int stack_isFull(void)
{
    return isFull();
}

unsigned int stack_isEmpty(void)
{
    return isEmpty();
}

//just peek the data instead of popping it.
unsigned int stack_peek(char *pItem)
{
    if (isEmpty()==STACK_RET_YES)
        return STACK_RET_FAILED;

    *pItem=S.item[S.top];

    return STACK_RET_OK;
}

#endif
