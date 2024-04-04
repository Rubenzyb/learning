/*
任务描述
限制使用双向链表作存储结构，
请根据用户输入的一个整数（该整数表示精确到小数点后的位数，可能要求精确到小数点后 500 位），
高精度计算PI值。可以利用反三角函数幂级展开式来进行计算。
测试说明
输入说明：输入的一个正整数n。
输出说明：输出PI的值，精确到小数点后n位，最后输出一个回车。
*/

//程序包含的头文件
#include <stdio.h>

#include <stdlib.h>

//函数结果状态代码
#define OK 0
#define ERROR 1
#define INFEASIBLE - 1
#define OVERFLOW - 2

/*-----线性表的双向链表存储结构-----*/
typedef struct DuLNode {
  int data;
  struct DuLNode * prior;
  struct DuLNode * next;
}
DuLNode, * DuLinkList;

void InitDuLinkList(DuLinkList * );
void InsertAtHead(DuLinkList * , int);
void SearchList(DuLinkList * , DuLNode ** );
void PrintList(DuLinkList * , DuLNode ** , int);
void FreeList(DuLinkList * );

void Largenumber_Addition(DuLinkList * , DuLinkList * );
void Largenumber_Multiplication(DuLinkList * , int);
void Largenumber_Division(DuLinkList * , int);

int main() {

  DuLinkList Curterm, Sum;
  InitDuLinkList( & Curterm);
  InitDuLinkList( & Sum);

  int i, figure;
  scanf("%d", & figure);
  InsertAtHead( & Curterm, 1);
  InsertAtHead( & Sum, 1);

  for (i = 1; i <= 3 * figure; i++) {
    InsertAtHead( & Curterm, 0);
    InsertAtHead( & Sum, 0);
  }

  for (i = 1; i <= 6 * figure; i++) {

    Largenumber_Multiplication( & Curterm, i);
    Largenumber_Division( & Curterm, 2 * i + 1);
    Largenumber_Addition( & Sum, & Curterm);

  }

  Largenumber_Addition( & Sum, & Sum);

  DuLNode * Sum_tail;
  SearchList( & Sum, & Sum_tail);
  PrintList( & Sum, & Sum_tail, figure);

  FreeList( & Curterm);
  FreeList( & Sum);
  return OK;

}

// 创建并初始化一个空双向链表
void InitDuLinkList(DuLinkList * L) {

  * L = (DuLNode * ) malloc(sizeof(DuLNode));

  if ( * L == NULL) {
    exit(OVERFLOW);
  }

  ( * L) -> data = 0;
  ( * L) -> prior = NULL;
  ( * L) -> next = NULL;

}

// 向双向链表头部插入一个新节点
void InsertAtHead(DuLinkList * L, int data) {

  DuLNode * new_node = (DuLNode * ) malloc(sizeof(DuLNode));

  if (new_node == NULL) {
    exit(OVERFLOW);
  }

  new_node -> data = data;
  new_node -> next = ( * L) -> next;
  new_node -> prior = * L;

  if (( * L) -> next != NULL) {
    ( * L) -> next -> prior = new_node;
  }
  ( * L) -> next = new_node;

}
// 查找并返回链表的尾节点
void SearchList(DuLinkList * L, DuLNode ** p) {

  if (( * L) == NULL) exit(ERROR);

  DuLNode * current = * L;

  while (current -> next != NULL) {
    current = current -> next;
  }

  * p = current;
}

// 逆序输出链表至指定位数，处理小数点位置，并在末尾添加换行符
void PrintList(DuLinkList * L, DuLNode ** p, int i) {

  if ( * p == NULL) exit(ERROR);

  DuLNode * current = * p;

  while (current -> data == 0 && current -> prior != NULL) {
    current = current -> prior;
  }

  if (current -> data == 0) exit(ERROR);

  int count = 0;
  printf("%d", current -> data);
  current = current -> prior;

  if (current != NULL) printf(".");

  while (count < i && current != NULL) {
    printf("%d", current -> data);
    count++;
    current = current -> prior;
  }

  printf("\n");

  if (count <= i) exit(ERROR);

}

// 释放链表占用的内存
void FreeList(DuLinkList * L) {

  if (( * L) == NULL) exit(ERROR);

  DuLNode * current = * L;

  while (current -> next != NULL) {
    DuLNode * agency = current -> next;
    free(current);
    current = agency;
  }

}

//大数加法实现,结果放置于A链表中
void Largenumber_Addition(DuLinkList * A, DuLinkList * B) {

  DuLNode * pA = * A, * pB = * B;
  DuLNode * tail_A = * A; // 记录A链表的当前末尾节点
  int up = 0;

  while (pA != NULL && pB != NULL) {

    pA -> data = pA -> data + pB -> data + up;
    up = pA -> data / 10;
    pA -> data %= 10;

    tail_A = pA; // 更新A链表的末尾节点
    pA = pA -> next;
    pB = pB -> next;
  }

  // 将未遍历完的链表（如果有）接到A链表末尾，并处理剩余节点和进位
  DuLinkList longer_list = (pA == NULL) ? B : A;
  DuLNode * remaining_node = (pA == NULL) ? pB : pA;

  while (remaining_node != NULL) {

    remaining_node -> data += up;
    up = remaining_node -> data / 10;
    remaining_node -> data %= 10;

    tail_A -> next = remaining_node;
    tail_A -> next -> prior = tail_A;
    tail_A = tail_A -> next;
    remaining_node = remaining_node -> next;

  }

  // 如果最后仍有进位，需在A链表末尾添加新节点存储进位值
  if (up > 0) {

    DuLNode * new_node = (DuLNode * ) malloc(sizeof(DuLNode));

    if (new_node == NULL) {
      exit(OVERFLOW);
    }

    new_node -> data = up;
    new_node -> prior = tail_A;
    new_node -> next = NULL;
    tail_A -> next = new_node;

  }

}

//大数乘法实现,结果放置于A链表中
void Largenumber_Multiplication(DuLinkList * L, int num) {

  if (( * L) == NULL) exit(ERROR);

  DuLNode * current = * L;

  while (current -> next != NULL) {

    current -> data = current -> data * num;
    current = current -> next;

  }

  int up = 0;
  current = * L;

  while (current -> next != NULL) {

    current -> data += up;
    up = current -> data / 10;
    current -> data %= 10;
    current = current -> next;
  }

  while (up > 0) {
    DuLNode * new_node = (DuLNode * ) malloc(sizeof(DuLNode));

    if (new_node == NULL) {
      exit(OVERFLOW);
    }

    new_node -> data = up % 10;
    new_node -> prior = current;
    new_node -> next = NULL;
    current -> next = new_node;
    up /= 10;
    current = new_node;

  }

}

//大数除法实现,结果放置于A链表中
void Largenumber_Division(DuLinkList * L, int num) {

  if (( * L) == NULL) exit(ERROR);

  DuLNode * current;
  SearchList(L, & current);

  if (current == NULL) exit(ERROR);

  while (current -> data == 0 && current -> prior != NULL) {
    current = current -> prior;
  }

  if (current -> data == 0) exit(ERROR);

  int temp = 0;

  while (current -> prior != NULL) {

    int agency = current -> data + temp;
    temp = (agency % num) * 10;
    current -> data = agency / num;
    current = current -> prior;

  }

}