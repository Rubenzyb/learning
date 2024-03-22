/*
��������
�������������������е��������飬������Ǻϳ�һ���������鲢�����

���Ҫ��
������ʾ�����Ҳ�༭��������룬��ɺϲ��������顣

����˵��
����˵����
��һ��Ϊ��һ����������ĳ��ȣ������� n��n<=20 ��
�ڶ���Ϊ��һ����������� n �����֣��ÿո������
������Ϊ�ڶ�����������ĳ��ȣ�������m��m<=20��
������Ϊ�ڶ������������ m �����֣��ÿո������

���˵����
����ϲ�������飬ÿ������ռһ�С�
*/

//���������ͷ�ļ� 
#include <stdio.h>
#include <stdlib.h>

//�������״̬����
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR 1
#define INFEASIBLE - 1
#define OVERFLOW - 2

/*-----���Ա�Ķ�̬����˳��洢�ṹ-----*/
#define LIST_INIT_SIZE 100 //���Ա�洢�ռ�ĳ�ʼ������ 
#define LISTINCREMENT 10 // ���Ա�洢�ռ�ķ�������
//���²��ֿɸ�����������޸� 
#define ElemType int //�Զ���˳��������Ԫ������
#define print(x) printf("%d", x) //�Զ������뺯�� 
#define scan(x) scanf("%d", x) //�Զ���������� 

struct SqList {
  ElemType * elem; //�洢�ռ��ַ 
  int length; //��ǰ���� 
  int listsize; //��ǰ����洢��������sizeof(ElemType)Ϊ��λ�� 
};

//������ĺ���
void InitList(struct SqList * );
void Modlistsize(struct SqList * , ElemType);
void ModAlelem(struct SqList * );
void MergeList(struct SqList * , struct SqList * , struct SqList * );
void PrintList(struct SqList);

int main() {

  //�����������Ա�ǰ�������ڴ洢���������Ա����һ�����ڴ洢�ϲ�������Ա� 
  struct SqList LA, LB, LC;
  InitList( & LA);
  InitList( & LB);
  InitList( & LC);

  //��ȡ���Ա�ĳ��Ȳ����ݴ��޸Ĵ洢����,�ٶ�������Ԫ��
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

  //�ϲ����Ա���� 
  MergeList( & LA, & LB, & LC);
  PrintList(LC);

  //�ͷ��ڴ沢��������	
  free(LA.elem);
  free(LB.elem);
  free(LC.elem);
  LA.elem = NULL;
  LB.elem = NULL;
  LC.elem = NULL;

  return OK;

}

//����һ��L.listsize=LIST_INIT_SIZE�Ŀձ�L 
void InitList(struct SqList * L) {

  L -> elem = calloc(LIST_INIT_SIZE, sizeof(ElemType));
  if (L -> elem == NULL) exit(OVERFLOW); //�����ڴ�ʧ�� 
  L -> length = 0; //�ձ���Ϊ�� 
  L -> listsize = LIST_INIT_SIZE; //��ʼ�洢���� 

}

//����L_length�޸����Ա�L��listsize 
void Modlistsize(struct SqList * L, ElemType L_length) {

  ElemType * newelem = realloc(L -> elem, L_length * sizeof(ElemType));

  if (newelem != NULL) {
    L -> elem = newelem;
    L -> length = L_length;
    L -> listsize = L_length;
  } //�ڴ����·���ɹ� 
  else exit(OVERFLOW); //�ڴ����·���ʧ�� 

}

//��������˳�������ٶ�������Ԫ�ص����Ա��� 
void ModAlelem(struct SqList * L) {

  ElemType * point = L -> elem;
  ElemType * L_last = L -> elem + L -> length;
  while (point < L_last) {
    scan(point);
    point++;
  }

}

//��LA��LB������Ԫ�غϲ���LC�� 
void MergeList(struct SqList * LA, struct SqList * LB, struct SqList * LC) {

  //��ָ��ɨ��LA��LB�е�ÿ������Ԫ�أ����մ�С˳��洢��LC�� 
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

  //��LA��LB����ʣ���Ԫ�أ�ֱ�Ӻϲ���LC��ĩβ 
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
  //�޸�LC�Ĵ洢���� 
  Modlistsize(LC, LC_newlength);
}

//����ϲ�����±�LC
void PrintList(struct SqList L) {

  ElemType * point = L.elem;
  ElemType * L_last = L.elem + L.length;
  while (point < L_last) {
    print( * point);
    printf("\n");
    point++;
  }

}
