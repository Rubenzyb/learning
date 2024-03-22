/*
任务描述
给定两个按照升序排列的有序数组，请把它们合成一个升序数组并输出。

编程要求
根据提示，在右侧编辑器补充代码，完成合并有序数组。

测试说明
输入说明：
第一行为第一个有序数组的长度，正整数 n，n<=20 ；
第二行为第一个有序数组的 n 个数字，用空格隔开；
第三行为第二个有序数组的长度，正整数m，m<=20；
第四行为第二个有序数组的 m 个数字，用空格隔开。

输出说明：
输出合并后的数组，每个数字占一行。
*/

//程序包含的头文件 
#include <stdio.h>
#include <stdlib.h>

//函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR 1
#define INFEASIBLE - 1
#define OVERFLOW - 2

/*-----线性表的动态分配顺序存储结构-----*/
#define LIST_INIT_SIZE 100 //线性表存储空间的初始分配量 
#define LISTINCREMENT 10 // 线性表存储空间的分配增量
//以下部分可根据需求进行修改 
#define ElemType int //自定义顺序表的数据元素类型
#define print(x) printf("%d", x) //自定义输入函数 
#define scan(x) scanf("%d", x) //自定义输出函数 

struct SqList {
  ElemType * elem; //存储空间基址 
  int length; //当前长度 
  int listsize; //当前分配存储容量（以sizeof(ElemType)为单位） 
};

//程序定义的函数
void InitList(struct SqList * );
void Modlistsize(struct SqList * , ElemType);
void ModAlelem(struct SqList * );
void MergeList(struct SqList * , struct SqList * , struct SqList * );
void PrintList(struct SqList);

int main() {

  //定义三个线性表，前两者用于存储给定的线性表，最后一个用于存储合并后的线性表 
  struct SqList LA, LB, LC;
  InitList( & LA);
  InitList( & LB);
  InitList( & LC);

  //读取线性表的长度并将据此修改存储容量,再读入数据元素
  ElemType LA_length;
  scan( & LA_length);
  Modlistsize( & LA, LA_length);
  ModAlelem( & LA);

  ElemType LB_length;
  scan( & LB_length);
  Modlistsize( & LB, LB_length);
  ModAlelem( & LB);

  ElemType LC_length = LA_length + LB_length;
  Modlistsize( & LC, LC_length);

  //合并线性表并输出 
  MergeList( & LA, & LB, & LC);
  PrintList(LC);

  //释放内存并结束程序	
  free(LA.elem);
  free(LB.elem);
  free(LC.elem);
  LA.elem = NULL;
  LB.elem = NULL;
  LC.elem = NULL;

  return OK;

}

//构造一个L.listsize=LIST_INIT_SIZE的空表L 
void InitList(struct SqList * L) {

  L -> elem = calloc(LIST_INIT_SIZE, sizeof(ElemType));
  if (L -> elem == NULL) exit(OVERFLOW); //分配内存失败 
  L -> length = 0; //空表长度为零 
  L -> listsize = LIST_INIT_SIZE; //初始存储容量 

}

//根据L_length修改线性表L的listsize 
void Modlistsize(struct SqList * L, ElemType L_length) {

  ElemType * newelem = realloc(L -> elem, L_length * sizeof(ElemType));

  if (newelem != NULL) {
    L -> elem = newelem;
    L -> length = L_length;
    L -> listsize = L_length;
  } //内存重新分配成功 
  else exit(OVERFLOW); //内存重新分配失败 

}

//依据输入顺序依次再读入数据元素到线性表中 
void ModAlelem(struct SqList * L) {

  ElemType * point = L -> elem;
  ElemType * L_last = L -> elem + L -> length;
  while (point < L_last) {
    scan(point);
    point++;
  }

}

//将LA和LB的数据元素合并到LC中 
void MergeList(struct SqList * LA, struct SqList * LB, struct SqList * LC) {

  //用指针扫描LA和LB中的每个数据元素，按照大小顺序存储到LC中 
  ElemType * pA = LA -> elem, * pB = LB -> elem, * pC = LC -> elem;
  ElemType * LA_last = LA -> elem + LA -> length, LB_last = LB -> elem + LB -> length;
  ElemType LC_newlength = 0;
  while (pA < LA_last && pB < LB_last) {

    if ( * pA <= * pB) {
      * pC = * pA;
      pA++;
      pC++;
      LC_newlength++;
    } else if ( * pA > * pB) {
      * pC = * pB;
      pB++;
      pC++;
      LC_newlength++;
    }
  }

  //若LA或LB还有剩余的元素，直接合并到LC的末尾 
  while (pA < LA_last) {
    * pC = * pA;
    pA++;
    pC++;
    LC_newlength++;
  }

  while (pB < LB_last) {
    * pC = * pB;
    pB++;
    pC++;
    LC_newlength++;
  }
  //修改LC的存储容量 
  Modlistsize(LC, LC_newlength);
}

//输出合并后的新表LC
void PrintList(struct SqList L) {

  ElemType * point = L.elem;
  ElemType * L_last = L.elem + L.length;
  while (point < L_last) {
    print( * point);
    printf("\n");
    point++;
  }

}
