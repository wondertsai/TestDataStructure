/*
 * aStack.h
 *
 *  Created on: 2020¦~6¤ë18¤é
 *      Author: qwerw
 */

#ifndef ASTACK_INT_H_
#define ASTACK_INT_H_

#define STACK_INT_EXTEND_FUNCTION_SUPPORT   1

#define STACK_INT_RET_OK        1
#define STACK_INT_RET_FAILED    0

void stack_int_init(void);
void stack_int_clear(void);
//return STACK_INT_RET_OK or STACK_INT_RET_FAILED
unsigned int stack_int_push(int val);
//return STACK_INT_RET_OK or STACK_INT_RET_FAILED
unsigned int stack_int_pop(int *pItem);


#if (STACK_INT_EXTEND_FUNCTION_SUPPORT == 1)
extern unsigned int stack_int_isFull(void);
extern unsigned int stack_int_isEmpty(void);
//just peek the data instead of popping it.
extern unsigned int stack_int_peek(int *pItem);
#endif

#endif /* ASTACK_INT_H_ */
