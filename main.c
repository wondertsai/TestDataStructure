/*
 * main.c
 *
 *  Created on: 2020/5/2
 *      Author: qwerw
 */
#include <stdio.h>
#include <stdlib.h>
#include "aLinkedList.h"
#include "aStack.h"
#include "Order_postfix.h"
#include "three_dimension_reader.h"


void test_stack(void)
{
	char aList[12]={'a','b','c','d','e','f','g', 'i', 'j', 'k', 'l', 'm'};
	int i;
	char iVal='x';

	stack_init();
	printf("\n push: \n");
	for (i=0; i<12; i++)
	{
		if (stack_push(aList[i]) == STACK_RET_OK)
			printf("%c, ", aList[i]);
		else
			printf("stack is full(input: %d)\n", i);
	}

	printf("\n pop: \n");
	while (stack_pop(&iVal)==STACK_RET_OK)
	{
		printf("%c, ", iVal);
	}
}

void test_order_postfix(void)
{
    unsigned int ret;
    char str[48];

    ret = order_postfix_transform("(((A+B)*C)-(D/E))", str);
    printf("%d, %s", ret, str);

}

void test_three_dimension_reader(void)
{
    init_three_dim_reader();
    three_dim_reader_run("3d_data.txt");
}

int get_ten_to_power_of(int ipwr)
{
    int iRet=1;

    for (int i=0; i<ipwr; i++)
    {
        iRet *= 10;
    }

    return iRet;
}

int main(void)
{
	//int i=3;

	//testfunc(i);
	//printf("123: %d", testfunc(i));

	//test_stack();
	//test_order_postfix();
    test_three_dimension_reader();

/*
    int i=0;
    int iRet=1;
    int iPwr=0;

    iRet=1;
    iPwr=0;
    iRet=get_ten_to_power_of(iPwr);
//    for (i=0; i<iPwr; i++)
//    {
//        iRet *=10;
//    }
    printf("iRet: %d, iPwr: %d", iRet, iPwr);


    iRet=1;
    iPwr++;
    iRet=get_ten_to_power_of(iPwr);
//    for (i=0; i<iPwr; i++)
//    {
//        iRet *=10;
//    }
    printf("iRet: %d, iPwr: %d", iRet, iPwr);

    iRet=1;
    iPwr++;
    iRet=get_ten_to_power_of(iPwr);
//    for (i=0; i<iPwr; i++)
//    {
//        iRet *=10;
//    }
    printf("iRet: %d, iPwr: %d", iRet, iPwr);

    iRet=get_ten_to_power_of(iPwr);
    */

}
