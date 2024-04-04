/*
��������
����ʹ��˫���������洢�ṹ��
������û������һ����������������ʾ��ȷ��С������λ��������Ҫ��ȷ��С����� 500 λ����
�߾��ȼ���PIֵ���������÷����Ǻ����ݼ�չ��ʽ�����м��㡣
����˵��
����˵���������һ��������n��
���˵�������PI��ֵ����ȷ��С�����nλ��������һ���س���
*/

//���������ͷ�ļ�
#include <stdio.h>

#include <stdlib.h>

//�������״̬����
#define OK 0
#define ERROR 1
#define INFEASIBLE - 1
#define OVERFLOW - 2

/*-----���Ա��˫������洢�ṹ-----*/
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

// ��������ʼ��һ����˫������
void InitDuLinkList(DuLinkList * L) {

  * L = (DuLNode * ) malloc(sizeof(DuLNode));

  if ( * L == NULL) {
    exit(OVERFLOW);
  }

  ( * L) -> data = 0;
  ( * L) -> prior = NULL;
  ( * L) -> next = NULL;

}

// ��˫������ͷ������һ���½ڵ�
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
// ���Ҳ����������β�ڵ�
void SearchList(DuLinkList * L, DuLNode ** p) {

  if (( * L) == NULL) exit(ERROR);

  DuLNode * current = * L;

  while (current -> next != NULL) {
    current = current -> next;
  }

  * p = current;
}

// �������������ָ��λ��������С����λ�ã�����ĩβ��ӻ��з�
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

// �ͷ�����ռ�õ��ڴ�
void FreeList(DuLinkList * L) {

  if (( * L) == NULL) exit(ERROR);

  DuLNode * current = * L;

  while (current -> next != NULL) {
    DuLNode * agency = current -> next;
    free(current);
    current = agency;
  }

}

//�����ӷ�ʵ��,���������A������
void Largenumber_Addition(DuLinkList * A, DuLinkList * B) {

  DuLNode * pA = * A, * pB = * B;
  DuLNode * tail_A = * A; // ��¼A����ĵ�ǰĩβ�ڵ�
  int up = 0;

  while (pA != NULL && pB != NULL) {

    pA -> data = pA -> data + pB -> data + up;
    up = pA -> data / 10;
    pA -> data %= 10;

    tail_A = pA; // ����A�����ĩβ�ڵ�
    pA = pA -> next;
    pB = pB -> next;
  }

  // ��δ���������������У��ӵ�A����ĩβ��������ʣ��ڵ�ͽ�λ
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

  // ���������н�λ������A����ĩβ����½ڵ�洢��λֵ
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

//�����˷�ʵ��,���������A������
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

//��������ʵ��,���������A������
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