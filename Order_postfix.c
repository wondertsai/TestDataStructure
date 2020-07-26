/*
 * Order_postfix.c
 *
 *  Created on: 2020¦~6¤ë17¤é
 *      Author: qwerw
 */

#include "aStack.h"
#include "Order_postfix.h"



unsigned int is_operand(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z')) ? 1 : 0;
}

static char list_operators[]={'+', '-', '*', '/'};
static int list_operators_priority[]={1, 1, 2, 2};
unsigned int is_operator(char c)
{
    unsigned int i;

    for (i=0; i< sizeof(list_operators); i++)
    {
        if (list_operators[i] == c)
            return 1;
    }
    return 0;
}

//return:
//  0: not found
//  >0: higher value higher priority
unsigned int get_priority(char c)
{

    for (int i=0; i< sizeof(list_operators); i++)
    {
        if (list_operators[i] == c)
        {
            return list_operators_priority[i];
        }
    }

    return 0;
}



unsigned int order_postfix_transform(char *pstr, char *pstr_post)
{
    unsigned int idx_post_str=0;
    char data=' ';

    stack_init();

    while (*pstr != '\0')
    {
        if (is_operand(*pstr))
        {
            pstr_post[idx_post_str]=*pstr;
            idx_post_str++;
        }
        else if (is_operator(*pstr))
        {
            while (stack_peek(&data)==STACK_RET_OK)
            {
                if (get_priority(*pstr) > get_priority(data))
                {
                    stack_push(*pstr);
                    break;
                } else
                {
                    stack_pop(&data);
                    pstr_post[idx_post_str]=data;
                    idx_post_str++;
                }
            }
        }
        else if (*pstr == '(')
        {
            stack_push(*pstr);
        }
        else if (*pstr == ')')
        {
            while (stack_pop(&data)==STACK_RET_OK)
            {
                if (data == '(')
                {
                    break;
                } else
                {
                    pstr_post[idx_post_str]=data;
                    idx_post_str++;
                }
            }
        }
        pstr++;
    }

    pstr_post[idx_post_str]='\0';

    stack_clear();

    return ORDER_POSTFIX_RET_OK;
}
