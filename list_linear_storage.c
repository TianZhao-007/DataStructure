#include "stdio.h"    
#include "stdlib.h"   
#include "math.h"  
#include "time.h"

#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0

#define MAXSIZE 20 /* 存储空间初始分配量 */

typedef int Status;          /* Status是函数的类型,其值是函数结果状态代码，如OK等 */
typedef int ElemType;        /* ElemType类型根据实际情况而定，这里假设为int */

Status visit(ElemType c)
{
    printf("%d ",c);
    return OK;
}

typedef struct
{
	ElemType data[MAXSIZE];        /* 数组，存储数据元素 */
	int length;                                /* 线性表当前长度 */
}SqList;


// initilise list
Status InitList(SqList *L)
{
    L->length = 0;
    return 0;
}

Status ListEmpty(SqList L)
{
    if(L.length == 0) 
        return TRUE;
    else 
        return FALSE;
}

//clear the list
Status ClearList(SqList *L)
{
    L ->length = 0;
    return OK;
}

int ListLength(SqList L)
{
    return L.length;
}

// initial condition: List L has existed, 1<= i <= listlength(L)
//i-th element of List L returns to e
Status GetElem(SqList L,int i,ElemType *e)
// e is a pointer here
{
    if(i<1 || i>L.length || L.length ==0)
        return ERROR;
    *e = L.data[i-1];

    return OK;
}

Status LocateElem(SqList L,ElemType e)
{
    int i;
    if(L.length == 0) return 0;      //consider when list is empty

    for(i = 0; i<= L.length; i++)
    {
        if(L.data[i]==e) return i+1;
        break;
    }
    if(i>L.length) return 0;

    return i+1;
}

/* 初始条件：顺序线性表L已存在,1≤i≤ListLength(L)， */
/* 操作结果：在L中第i个位置之前插入新的数据元素e，L的长度加1 */

Status ListInsert(SqList *L,int i,ElemType e)
{   
    int j;

    if(i<1 || i>L->length + 1 || L->length == MAXSIZE)
        return ERROR;
    
    if(L->length >= MAXSIZE)
        return ERROR;
    
    if(i<=L->length)
    {
         for(j=L->length-1; j>i-1; j--)
            {
                 L->data[j+1] = L->data[j];
            }
    }

    L->data[i-1] = e;
    L->length ++;

    return OK;

}

/* 初始条件：顺序线性表L已存在，1≤i≤ListLength(L) */
/* 操作结果：删除L的第i个数据元素，并用e返回其值，L的长度减1 */

Status ListDelete(SqList *L,int i,ElemType *e)
{
    int j;
    if(i<1 || i>L->length || L->length ==0) 
        return ERROR;
    
    *e = L->data[i-1];
    if(L->length > i)
    {
        for(j = i; j <L->length; j++)
        {
            L->data[j-1] =L->data[j];
        }
    }
    L->length--;
    return OK;
}

/* 初始条件：顺序线性表L已存在 */
/* 操作结果：依次对L的每个数据元素输出 */
Status ListTraverse(SqList L)
{
	int i;
    for(i=0;i<L.length;i++)
            visit(L.data[i]);
    printf("\n");
    return OK;
}


void unionL(SqList *La,SqList Lb)
{
	int La_len,Lb_len,i;
	ElemType e;
	La_len=ListLength(*La);
	Lb_len=ListLength(Lb);
	for (i=1;i<=Lb_len;i++)
	{
		GetElem(Lb,i,&e);
		if (!LocateElem(*La,e))
			ListInsert(La,++La_len,e);
	}
}




int main()
{
    SqList L;
	SqList Lb;

    ElemType e;
    Status i;
    int j,k;
    i=InitList(&L);
    printf("初始化L后：L.length=%d\n",L.length);
    for(j=1;j<=5;j++)
            i=ListInsert(&L,1,j);
    printf("在L的表头依次插入1～5后：L.data=");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    i=ClearList(&L);
    printf("清空L后：L.length=%d\n",L.length);
    i=ListEmpty(L);
    printf("L是否空：i=%d(1:是 0:否)\n",i);

    for(j=1;j<=10;j++)
            ListInsert(&L,j,j);
    printf("在L的表尾依次插入1～10后：L.data=");
    ListTraverse(L); 

    printf("L.length=%d \n",L.length);

    ListInsert(&L,1,0);
    printf("在L的表头插入0后：L.data=");
    ListTraverse(L); 
    printf("L.length=%d \n",L.length);

    GetElem(L,5,&e);
    printf("第5个元素的值为：%d\n",e);
    for(j=3;j<=4;j++)
    {
            k=LocateElem(L,j);
            if(k)
                    printf("第%d个元素的值为%d\n",k,j);
            else
                    printf("没有值为%d的元素\n",j);
    }


    k=ListLength(L); /* k为表长 */
    for(j=k+1;j>=k;j--)
    {
            i=ListDelete(&L,j,&e); /* 删除第j个数据 */
            if(i==ERROR)
                    printf("删除第%d个数据失败\n",j);
            else
                    printf("删除第%d个的元素值为：%d\n",j,e);
    }
    printf("依次输出L的元素：");
    ListTraverse(L); 

    j=5;
    ListDelete(&L,j,&e); /* 删除第5个数据 */
    printf("删除第%d个的元素值为：%d\n",j,e);

    printf("依次输出L的元素：");
    ListTraverse(L); 

	//构造一个有10个数的Lb
	i=InitList(&Lb);
    for(j=6;j<=15;j++)
            i=ListInsert(&Lb,1,j);

	unionL(&L,Lb);

	printf("依次输出合并了Lb的L的元素：");
    ListTraverse(L); 

    return 0;
}


