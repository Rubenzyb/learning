/*
��������
��������ϡ��������������ӵĽ����
��֪�����������Ϊrow������Ϊcolumn��
�����ΧΪ���ӵ�0������row�У��ӵ�0������column�С� 

����˵��
����˵����
��һ�������ĸ����������ֱ��������������m����n����һ������ķ���Ԫ�صĸ���t1�͵ڶ�������ķ���Ԫ�صĸ���t2��
��������t1+t2������Ԫ�飬�ֱ��ǵ�һ����������ݺ͵ڶ�����������ݡ�
��Ԫ��ĵ�һ��Ԫ�ر�ʾ�кţ��ڶ���Ԫ�ر�ʾ�кţ�������Ԫ���Ǹ����ֵ��

���˵����
�����Ӻ�ľ�����Ԫ�顣
*/

// ���������ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>

// �������״̬����
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR 1
#define INFEASIBLE -1
#define OVERFLOW -2

/*---ϡ��������Ԫ��˳���洢�ṹ---*/

#define MATRIX_UNIT_SIZE 1       // ϡ�����洢�ռ�ĵ�λ������
#define ElemType int             // �Զ���ϡ����������Ԫ������
#define EmptySet 0               // �Զ���ϡ���������Ԫ�������
#define print(x) printf("%d", x) // �Զ�������Ԫ�ص����뺯��
#define scan(x) scanf("%d", x)   // �Զ�������Ԫ�ص��������
// ���ϲ��ֿɸ�����������޸�

typedef struct
{

  int rwnum, clnum; // ����Ԫ�ص��кź��к�
  ElemType data;

} Triple;

typedef struct
{

  Triple *element;        // ��element[1]��ʼ�洢���ݵ���Ԫ���
  int row, column, elnum; // ���������,���������Ԫ�ظ���

} TriSMatrix;

// �Զ��庯��
void AllocSMatrix(TriSMatrix *, int, int, int);            // Ϊϡ��������ò���������ռ�
void InitSMatrix(TriSMatrix *);                            // ��ʼ��ϡ�����
void DestroySMatrix(TriSMatrix *);                         // ����ϡ�����
void PrintSMatrix(TriSMatrix *);                           // ���ϡ�����
void SumSMatrix(TriSMatrix *, TriSMatrix *, TriSMatrix *); // ������ϡ��������

int main()
{

  // ���ն˽����ĸ�������m��n��t1��t2���ֱ��ʾ����������������������������ķ���Ԫ�ظ���
  int m, n, t1, t2;
  scanf("%d %d %d %d", &m, &n, &t1, &t2);

  // ��������ʼ������ϡ�����MatrixA��MatrixB��MatrixC��ǰ���ߴ洢����ľ��󣬺��ߴ洢��Ӻ�ľ���
  TriSMatrix MatrixA, MatrixB, MatrixC;
  AllocSMatrix(&MatrixA, m, n, t1);
  AllocSMatrix(&MatrixB, m, n, t2);
  AllocSMatrix(&MatrixC, m, n, t1 + t2);
  InitSMatrix(&MatrixA);
  InitSMatrix(&MatrixB);

  // ����ӵõ��ľ��󴢴���MatrixC�в����
  SumSMatrix(&MatrixA, &MatrixB, &MatrixC);
  PrintSMatrix(&MatrixC);

  // �ͷų���ռ�õĴ洢�ռ䲢�˳�
  DestroySMatrix(&MatrixA);
  DestroySMatrix(&MatrixB);
  DestroySMatrix(&MatrixC);

  return OK;
}

// ���ݸ���������(row)������(column)�Լ�����Ԫ�ظ���(M->elnum)��Ϊϡ�����M��̬����ͳ�ʼ������Ľṹ�ռ�
void AllocSMatrix(TriSMatrix *M, int row, int column, int elnum)
{

  // ��鴫���ָ��M�Ƿ�Ϊ��
  if (M == NULL)
  {
    printf("Passing a matrix pointer as an argument to the function fails!\n");
    exit(ERROR);
  }

  // ��鴫���ϡ�����Ĳ����Ƿ�Ϸ�
  if (row == 0 || column == 0)
  {
    printf("The parameters of the sparse matrix read in were incorrect!\n");
    exit(ERROR);
  }

  // ����ϡ�����������������ͷ���Ԫ�ظ���
  M->row = row;
  M->column = column;
  M->elnum = elnum;

  // ʹ��malloc�������䣨M->elnum+MATRIX_UNIT_SIZE����Triple�ṹ���С�������ڴ�ռ�
  M->element = (Triple *)malloc((M->elnum + MATRIX_UNIT_SIZE) * sizeof(Triple));

  // ���malloc�����Ƿ�ɹ��������ڴ�
  if (M->element == NULL)
  {
    printf("Memory allocation failed for the sparse matrix elements.\n");
    exit(ERROR);
  }
}

// ��ʼ��ϡ����󣬴ӱ�׼�����ȡϡ�����ķ���Ԫ�ص�����
void InitSMatrix(TriSMatrix *M)
{

  // ��鴫���ָ��M�Ƿ�Ϊ��
  if (M == NULL)
  {
    printf("Passing a matrix pointer as an argument to the function fails!\n");
    exit(ERROR);
  }

  // ��������洢��ȡ�����кš��кż�����Ԫ��ֵ
  int rwnum, clnum;
  ElemType data;

  // ���ݾ���Ķ���Ԥ��Ϊ����Ԫ�ط����㹻����ڴ�ռ�
  int matrixsize = M->row * M->column;

  Triple *temp = (Triple *)realloc(M->element, (matrixsize + MATRIX_UNIT_SIZE) * sizeof(Triple));
  // ������·���ʧ�ܣ��ͷ�ԭ�ڴ沢�˳�����
  if (temp == NULL)
  {
    printf("Failed to reallocate sparse matrix memory space!\n");
    free(M->element);
    exit(ERROR);
  }
  else
    M->element = temp; // �������M��elementָ��

  int count = 1;
  do
  {

    // ��ȡһ������Ԫ�ص��кš��кź�����ֵ
    scanf("%d %d", &rwnum, &clnum);
    scan(&data);

    // ����ǰ��ȡ���ķ���Ԫ�������ϡ�����ṹ����,����element[1]��ʼ�洢����Ԫ�ص����ݣ�element[0]δʹ��
    if (data != EmptySet)
    {

      M->element[count].rwnum = rwnum;
      M->element[count].clnum = clnum;
      M->element[count].data = data;
      count++;
    }

  } while ((M->elnum != 0) ^ (data != EmptySet) ^ (count <= M->elnum));

  // ѭ�������󣬸���ʵ��ʹ��������ͷŶ����ڴ�
  M->elnum = count - 1;

  if (M->elnum < matrixsize)
  {

    Triple *temp = (Triple *)realloc(M->element, (M->elnum + MATRIX_UNIT_SIZE) * sizeof(Triple));
    // �������ʧ���ͷ�ԭ�ڴ沢�˳�����
    if (temp == NULL)
    {
      printf("Failed to shrink memory for the sparse matrix elements.\n");
      free(M->element);
      exit(ERROR);
    }
    else
      M->element = temp;
  }
}

// ���������ϡ�����M��ʹ�䴦��һ����֪�ĳ�ʼ״̬
void DestroySMatrix(TriSMatrix *M)
{

  // ��鴫���ָ��M�Ƿ�Ϊ��
  if (M == NULL)
  {
    printf("Passing a matrix pointer as an argument to the function fails!\n");
    exit(ERROR);
  }

  // �ͷŷ���Ԫ��������ڴ�
  free(M->element);

  // ��elementָ���ÿգ���ֹҰָ��
  M->element = NULL;

  // ������������������ͷ���Ԫ�ظ�������Ϊ��
  M->row = 0;
  M->column = 0;
  M->elnum = 0;
}

// ��ӡ������ϡ�����M������
void PrintSMatrix(TriSMatrix *M)
{

  // ��鴫���ָ��M�Ƿ�Ϊ��
  if (M == NULL)
  {
    printf("Passing a matrix pointer as an argument to the function fails!\n");
    exit(ERROR);
  }

  // ���ϡ�����ķ���Ԫ�ظ����Ƿ����
  if (M->elnum < 1)
  {
    printf("Incorrect number of non-zero elements of a sparse matrix!\n");
    exit(ERROR);
  }

  // ����ϡ���������з���Ԫ��
  int count;
  printf("\n");
  for (count = 1; count <= M->elnum; count++)
  {
    // ��ӡ��ǰ����Ԫ�ص��кţ��кź����ݴ�С������
    printf("%d %d ", M->element[count].rwnum, M->element[count].clnum);
    print(M->element[count].data);
    printf("\n");
  }
}

// �ϲ�����ϡ�����A��B��Ԫ�ص�C�У����A��B����ͬλ����Ԫ�أ�����ӣ�����ֱ����ӵ�C��
void SumSMatrix(TriSMatrix *A, TriSMatrix *B, TriSMatrix *C)
{
  // ��������ϡ�����ָ���Ƿ���Ч����һΪ���򱨴��˳�
  if (A == NULL || B == NULL || C == NULL)
  {
    printf("Passing  matrix pointers as arguments to the function fails!\n");
    exit(ERROR);
  }

  // ������������Ƿ���ͬ�;���
  if (A->row != B->row || A->column != B->column)
  {
    printf("The two sparse matrices cannot be added together!\n");
    exit(ERROR);
  }

  // ��ʼ��ָ����������Ԫ�ص�ָ��
  Triple *pA = &A->element[1], *pB = &B->element[1], *pC = &C->element[1];

  // ���ָ���ʼ���Ƿ�ɹ�
  if (pA == NULL || pB == NULL || pC == NULL)
  {
    printf("The initialisation of the pointers generated errors!\n");
    exit(ERROR);
  }

  // ��ʼ��������������׷���Ѻϲ���Ԫ������
  int count = 0;

  // ������������ķ���Ԫ��
  while (pA <= &A->element[A->elnum] && pB <= &B->element[B->elnum])
  {
    // �Ƚ��кź��кţ�������ϲ�Ԫ�ص�C��

    /* ����A���к�С��B����� */
    if (pA->rwnum < pB->rwnum)
    {

      pC->rwnum = pA->rwnum;
      pC->clnum = pA->clnum;
      pC->data = pA->data;
      pC++;
      pA++;
      count++;
    }

    /* ����A���кŴ���B����� */
    else if (pA->rwnum > pB->rwnum)
    {

      pC->rwnum = pB->rwnum;
      pC->clnum = pB->clnum;
      pC->data = pB->data;
      pC++;
      pB++;
      count++;
    }

    /* �к���ͬ���ٱȽ��кţ����кϲ������ */
    else if (pA->rwnum == pB->rwnum)
    {

      if (pA->clnum < pB->clnum)
      {

        pC->rwnum = pA->rwnum;
        pC->clnum = pA->clnum;
        pC->data = pA->data;
        pC++;
        pA++;
        count++;
      }

      else if (pA->clnum > pB->clnum)
      {

        pC->rwnum = pB->rwnum;
        pC->clnum = pB->clnum;
        pC->data = pB->data;
        pC++;
        pB++;
        count++;
      }

      else if (pA->clnum == pB->clnum)
      {

        if (pA->data + pB->data != 0)
        {
          pC->rwnum = pA->rwnum;
          pC->clnum = pA->clnum;
          pC->data = pA->data + pB->data;
          pC++;
          pA++;
          pB++;
          count++;
        }
      }
    }
  }

  // ��A��ʣ��Ԫ�أ�ֱ��׷�ӵ�C��
  while (pA <= &A->element[A->elnum])
  {
    pC->rwnum = pA->rwnum;
    pC->clnum = pA->clnum;
    pC->data = pA->data;
    pC++;
    pA++;
    count++;
  }

  // ��B��ʣ��Ԫ�أ�ֱ��׷�ӵ�C��
  while (pB <= &B->element[B->elnum])
  {
    pC->rwnum = pB->rwnum;
    pC->clnum = pB->clnum;
    pC->data = pB->data;
    pC++;
    pB++;
    count++;
  }

  // ����ʵ��ʹ���������C���ڴ��С���ͷ�δʹ�õ��ڴ�
  if (count < C->elnum)
  {
    C->elnum = count; // ����C�ķ���Ԫ������

    // ʹ��realloc������СC���ڴ�ռ��
    Triple *temp = (Triple *)realloc(C->element, (C->elnum + MATRIX_UNIT_SIZE) * sizeof(Triple));
    // ����ڴ�����ʧ�ܣ����ͷ�ԭ�ڴ沢�����˳�
    if (temp == NULL)
    {
      printf("Failed to shrink memory for the sparse matrix elements.\n");
      free(C->element);
      exit(ERROR);
    }
    else
      C->element = temp; // �������C��elementָ��
  }
}
