/*
��������
���ϡ������ת�þ��󡣣����о�������20��
��֪�����������Ϊrow������Ϊcolumn��
�����ΧΪ���ӵ�0������row�У��ӵ�0������column�С� 

����˵��
����˵����
��һ���������������� n �� m ,�ֱ��ʾ�����������������
Ȼ�����������Ԫ�飬
������루0 0 0����ʾ�������롣

���˵����
ת�ú�ľ���
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
void AllocSMatrix(TriSMatrix *, int, int, int);    // Ϊϡ��������ò���������ռ�
void InitSMatrix(TriSMatrix *);                    // ��ʼ��ϡ�����
void DestroySMatrix(TriSMatrix *);                 // ����ϡ�����
void PrintSMatrix(TriSMatrix *);                   // ���ϡ�����
void TransposeSMatrix(TriSMatrix *, TriSMatrix *); // ��ϡ������ת�þ���

int main()
{

  // ���ն˽�������������n��m���ֱ��ʾ����ľ��������������
  int n, m;
  scanf("%d %d", &n, &m);

  // ��������ʼ������ϡ�����SMatrix��TMatrix��ǰ�ߴ洢����ľ��󣬺��ߴ洢ת�ú�ľ���
  TriSMatrix SMatrix, TMatrix;

  AllocSMatrix(&SMatrix, n, m, 0);
  InitSMatrix(&SMatrix);
  AllocSMatrix(&TMatrix, m, n, SMatrix.elnum);

  // ��ϡ�����SMatrix��ת�þ��󴢴���TMatrix�в����
  TransposeSMatrix(&SMatrix, &TMatrix);
  PrintSMatrix(&TMatrix);

  // �ͷų���ռ�õĴ洢�ռ䲢�˳�
  DestroySMatrix(&SMatrix);
  DestroySMatrix(&TMatrix);

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

// ת��ϡ�����M����������洢��ϡ�����T�У��°棩
void TransposeSMatrix(TriSMatrix *M, TriSMatrix *T) {

	// ��������ϡ�����ָ��M��T�Ƿ�Ϊ��
	if (M == NULL || T == NULL) {
		printf("Passing  matrix pointers as arguments to the function fails!\n");
		exit(ERROR);
	}

	// ��ʼ��һ����������cpot�����ڼ�¼��λ���ϵķ���Ԫ�ظ��������鳤��ΪM������
	int count1, count2, cpot[M->column+1];

	for (count1 = 0; count1 <= M->column; count1++) {
		cpot[count1] = 0; // ÿ��Ԫ�س�ʼ����Ϊ0
	}

	// ����ת�ú�ÿ���еķ���Ԫ�����¾����е�λ��ƫ����
	for (count1 = 1; count1 <= M->elnum; count1++) {
		for (count2 = M->element[count1].clnum + 1; count2 <= M->column; count2++) {
			cpot[count2]++; // ����ÿһ�У����¶�Ӧ�еļ���
		}
	}

	// ���ݼ������λ��ƫ��������M�ķ���Ԫ��ת�õ�T��
	for (count1 = 1; count1 <= M->elnum; count1++) {

		count2 = ++cpot[M->element[count1].clnum]; // ��ȡת�ú�Ԫ�ص���λ�ã����Զ����Ӽ���

		// ת�ò�������M���кű�ΪT���кţ�M���кű�ΪT���кţ����ݱ��ֲ���
		T->element[count2].rwnum = M->element[count1].clnum;
		T->element[count2].clnum = M->element[count1].rwnum;
		T->element[count2].data = M->element[count1].data;
	}

	// �����Ƿ�ɹ�ת��������Ԫ�أ����ɹ�ת�ã���������ƥ�䣩�����ӡ������Ϣ���˳�����
	if (cpot[M->column] != T->elnum) {
		printf("The transpose of the sparse matrix is not fully realised!");
		exit(ERROR);
	}
}


//// ת��ϡ�����M����������洢��ϡ�����T�У�ԭ�棩
//void TransposeSMatrix(TriSMatrix *M, TriSMatrix *T)
//{
//
//  // ��������ϡ�����ָ��M��T�Ƿ�Ϊ��
//  if (M == NULL || T == NULL)
//  {
//    printf("Passing  matrix pointers as arguments to the function fails!\n");
//    exit(ERROR);
//  }
//
//  // ����Ŀ�����T�������Լ��Ѵ洢Ԫ������������ת�ò���
//  int mcount, tcount, order;
//  for (order = 0, tcount = 0; order <= T->row && tcount <= T->elnum; order++)
//  {
//
//    // ����ԭϡ�����M�ķ���Ԫ��
//    for (mcount = 1; mcount <= M->elnum; mcount++)
//    {
//
//      // Ѱ��M���кŵ��ڵ�ǰת�þ����кŵ�Ԫ�أ�����ת�ò���
//      if (M->element[mcount].clnum == order)
//      {
//
//        tcount++;
//        // ת�ò�������M���кű�ΪT���кţ�M���кű�ΪT���кţ����ݱ��ֲ���
//        T->element[tcount].rwnum = M->element[mcount].clnum;
//        T->element[tcount].clnum = M->element[mcount].rwnum;
//        T->element[tcount].data = M->element[mcount].data;
//      }
//    }
//  }
//
//  // �����Ƿ�ɹ�ת��������Ԫ�أ����ɹ�ת�ã���������ƥ�䣩�����ӡ������Ϣ���˳�����
//  if (tcount != T->elnum)
//  {
//    printf("The transpose of the sparse matrix is not fully realised!");
//    exit(ERROR);
//  }
//}
