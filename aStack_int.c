/*
 * aStack.c
 *
 *  Created on: 2020¦~6¤ë18¤é
 *      Author: qwerw
 */
#include "aStack_int.h"

#define MAX_STACK_INT_ITEM_NUM 16
typedef struct stSTACK_INT
{
    int item[MAX_STACK_INT_ITEM_NUM];
    int top;
}STACK_INT;




#define STACK_INT_RET_YES       1
#define STACK_INT_RET_NO        0

STACK_INT S_int;

void stack_int_init(void)
{
    S_int.top=-1;
}

void stack_int_clear(void)
{
    stack_int_init();
}

static unsigned int isFull(void)
{
    if (S_int.top >= (MAX_STACK_INT_ITEM_NUM-1))
        return STACK_INT_RET_YES;
    else
        return STACK_INT_RET_NO;
}

static unsigned int isEmpty(void)
{
    if (S_int.top == -1)
        return STACK_INT_RET_YES;
    else
        return STACK_INT_RET_NO;
}

unsigned int stack_int_push(int val)
{
    if (isFull()==STACK_INT_RET_YES)
        return STACK_INT_RET_FAILED;

    S_int.top++;
    S_int.item[S_int.top]=val;

    return STACK_INT_RET_OK;
}

unsigned int stack_int_pop(int *pItem)
{
    if (isEmpty()==STACK_INT_RET_YES)
        return STACK_INT_RET_FAILED;

    *pItem=S_int.item[S_int.top];
    S_int.top--;

    return STACK_INT_RET_OK;
}

#if (STACK_INT_EXTEND_FUNCTION_SUPPORT == 1)

unsigned int stack_int_isFull(void)
{
    return isFull();
}

unsigned int stack_int_isEmpty(void)
{
    return isEmpty();
}

//just peek the data instead of popping it.
unsigned int stack_int_peek(int *pItem)
{
    if (isEmpty()==STACK_INT_RET_YES)
        return STACK_INT_RET_FAILED;

    *pItem=S_int.item[S_int.top];

    return STACK_INT_RET_OK;
}

#endif
