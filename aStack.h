/*
 * aStack.h
 *
 *  Created on: 2020¦~6¤ë18¤é
 *      Author: qwerw
 */

#ifndef ASTACK_H_
#define ASTACK_H_

#define STACK_EXTEND_FUNCTION_SUPPORT   1

#define STACK_RET_OK        1
#define STACK_RET_FAILED    0

void stack_init(void);
void stack_clear(void);
//return STACK_RET_OK or STACK_RET_FAILED
unsigned int stack_push(char val);
//return STACK_RET_OK or STACK_RET_FAILED
unsigned int stack_pop(char *pItem);


#if (STACK_EXTEND_FUNCTION_SUPPORT == 1)
extern unsigned int stack_isFull(void);
extern unsigned int stack_isEmpty(void);
//just peek the data instead of popping it.
extern unsigned int stack_peek(char *pItem);
#endif

#endif /* ASTACK_H_ */
