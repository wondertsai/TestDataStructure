
#include <stdio.h>
#include <stdlib.h>
#include "three_dimension_reader.h"
#include "aStack.h"
#include "aStack_int.h"

#define LEN_ARRAY_DECL 32
static char strArrayDecl[LEN_ARRAY_DECL];
#define LEN_ARRAY_NAME 256
static char strArrayName[LEN_ARRAY_NAME];
int iArrayDim[3]={0, 0, 0};
//#define LEN_ONE_DIM 256
//int data_3d[LEN_ONE_DIM][LEN_ONE_DIM][LEN_ONE_DIM];
int *pData_3d=0;



typedef enum _STAGES {
    STAGE_ARRAY_DECL=0,
    STAGE_ARRAY_NAME,
    STAGE_3D_DECL,
    STAGE_DECL_EQUAL,
    STAGE_3D_DATA
}STAGES;

static unsigned int is_legal_letter(char c)
{
    return ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || (c >= '0' && c <= '9') || (c == '_')) ? 1 : 0;
}

static unsigned int is_num(char c)
{
    return (c >= '0' && c <= '9') ? 1 : 0;
}

static int get_ten_to_power_of(int ipwr)
{
    int iRet=1;

    for (int i=0; i<ipwr; i++)
    {
        iRet *= 10;
    }

    return iRet;
}

static void get_num_in_dim(int idx_dim)
{
    int idx=0;
    char cPop;
    int iTen_part=1;

    iArrayDim[idx_dim]=0;
    while (stack_pop(&cPop)==STACK_RET_OK)
    {
        if (cPop == '[')
        {
            break;
        } else
        {
            if (is_num(cPop))
            {
                //printf("before: idx_dim: %d, iArrayDim[]:%d, cPop:%c\n", idx_dim, iArrayDim[idx_dim], cPop);
                iTen_part=get_ten_to_power_of(idx);
                iArrayDim[idx_dim] += (int)((unsigned char)cPop-(unsigned char)('0'))*iTen_part;
                idx++;
                //printf("after: idx_dim: %d, iArrayDim[]:%d, cPop:%c, idx:%d\n", idx_dim, iArrayDim[idx_dim], cPop, idx);
            } else
            {
                //not allowed ascii code in the number for dimension
            }
        }
    }
}

//static iCnt_debug=0;
//return : 0: no data, 1: data in pone_dim
static int get_all_num_in_one_dim(int *pdata, int size_of_dim, int *pone_dim)
{

    int idx=0;
    char cPop;
    unsigned int bEnd=0;
    int iVal=0;
    int idx_in_dim=0;
    int iTen_part=1;
    int bData=0;

    idx_in_dim=size_of_dim-1;
    while (stack_pop(&cPop)==STACK_RET_OK)
    {
//        if (cPop == '{')
//        {
//            break;
//        } else
//        {
//
//        }
//        if (iCnt_debug <20)
//        {
//            printf("%d: get_all_num_in_one_dim: cPop: %c\n", iCnt_debug, cPop);
//            iCnt_debug++;
//        }
        switch (cPop)
        {
        case '{':
            bEnd=1;

            if (idx_in_dim >=0)//it should be 0
            {
                pone_dim[idx_in_dim]=iVal;
                idx_in_dim--;//no need
            }

            iVal=0;
            idx=0;
            break;
        case ',':
            if (idx_in_dim >=0)
            {
                pone_dim[idx_in_dim]=iVal;
                idx_in_dim--;
            }

            iVal=0;
            idx=0;
            break;
        default:
            if (is_num(cPop))
            {
                bData=1;

                iTen_part=get_ten_to_power_of(idx);
                iVal += (int)((unsigned char)cPop-(unsigned char)('0'))*iTen_part;
                idx++;
            } else
            {
                //not allowed ascii code in the number for dimension
            }
            break;
        }

        if (bEnd)
        {
            break;
        }
    }

    //printf("bData:%d\n", bData);
    if (bData)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void init_three_dim_reader(void)
{
    memset(strArrayDecl, 0, LEN_ARRAY_DECL);
    memset(strArrayName, 0, LEN_ARRAY_NAME);
}

void three_dim_reader_run(char *pfile)
{
    FILE *fp;
    char c;
    STAGES cur_stage=STAGE_ARRAY_DECL;
    int idx_array_decl=0;
    int idx_array_name=0;
    int iCnt_dim=0;
    int *pCur_data=0;
    int *pOne_dim=0;
    int i;
    int bGetData=0;


    fp=fopen(pfile, "r");

    while ((c=fgetc(fp)) != EOF )
    {
        switch (cur_stage)
        {
        case STAGE_ARRAY_DECL:
            if (is_legal_letter(c))
            {
                strArrayDecl[idx_array_decl]=c;
                idx_array_decl++;
            } else if (c == ' ')
            {
                if (idx_array_decl != 0)
                {
                    strArrayDecl[idx_array_decl]='\0';
                    cur_stage=STAGE_ARRAY_NAME;
                }
            } else
            {
                //not allowed ascii code
            }
            break;
        case STAGE_ARRAY_NAME:
            if (is_legal_letter(c))
            {
                strArrayName[idx_array_name]=c;
                idx_array_name++;
            } else if (c == ' ')
            {

            } else if (c == '[')
            {
                if (idx_array_name != 0)
                {
                    strArrayName[idx_array_name]='\0';
                    cur_stage=STAGE_3D_DECL;
                    stack_init();
                    stack_push(c);
                } else
                {
                    //not allowed ascii code, there is '[' in array name
                }
            }
            else
            {
                //not allowed ascii code
            }
            break;
        case STAGE_3D_DECL:
            switch (c)
            {
            case '[':
                stack_init();
                stack_push(c);
                break;
            case ']':
                get_num_in_dim(iCnt_dim);
                iCnt_dim++;
                break;
            case '=':
                if (iCnt_dim == 3)
                {
                    cur_stage=STAGE_3D_DATA;
                    if (pData_3d==0)//not allocate memory yet
                    {
                        pData_3d=(int *)malloc(iArrayDim[0]*iArrayDim[1]*iArrayDim[2]*sizeof(int));
                        pCur_data=pData_3d;
                        pOne_dim=(int *)malloc(iArrayDim[2]*sizeof(int));
                    }
                    stack_init();//stack_int_init();
                }
                else
                {
                    //not allowed ascii code, not a 3d array, less than 3 dimensions.
                }
                break;
            default:
                if (is_num(c))
                {
                    stack_push(c);
                } else
                {
                    //not allowed ascii code
                }
                break;
            }
            break;
        case STAGE_3D_DATA:
            switch (c)
            {
            case '{':
                //stack_int_push(9998);//!!! using 9998 to replace '{', and using 9999 to replace '}' in the stack_int
                stack_push(c);
                break;
            case '}':
                bGetData=get_all_num_in_one_dim(pCur_data, iArrayDim[2], pOne_dim);
                //printf("bGetData:%d\n", bGetData);
                if (bGetData)
                {
                    //printf("pOne_dim:%d, %d, %d\n", pOne_dim[0], pOne_dim[1], pOne_dim[2]);
                    for (i=0; i< iArrayDim[2]; i++)
                    {
                        *pCur_data = pOne_dim[i];
                        pCur_data++;
                    }
                    //pCur_data += iArrayDim[2];
                }
                break;
            case ';':
                break;
            default:
                stack_push(c);
                break;
            }

            break;
        }
    }

    //print data out
    printf("----------------------\n");
    printf("strArrayDecl: %s\n", strArrayDecl);
    printf("strArrayName: %s\n", strArrayName);
    printf("iArrayDim[0]: %d\n", iArrayDim[0]);
    printf("iArrayDim[1]: %d\n", iArrayDim[1]);
    printf("iArrayDim[2]: %d\n", iArrayDim[2]);
    printf("----------------------\n");
    for (i=0; i<(iArrayDim[0]*iArrayDim[1]*iArrayDim[2]); i++)
    {
        printf("%d: %d\n", i, pData_3d[i]);
    }
    printf("done");


    if (pData_3d)
    {
        free(pData_3d);
    }
    if (pOne_dim)
    {
        free(pOne_dim);
    }
    fclose(fp);
}
