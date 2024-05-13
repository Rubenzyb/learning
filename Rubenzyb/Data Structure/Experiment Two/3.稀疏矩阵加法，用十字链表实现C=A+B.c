/*
��������
ϡ�����ӷ�����ʮ������ʵ��C=A+B��
��������ϡ��������������ӵĽ����
��֪�����������Ϊrow������Ϊcolumn��
�����ΧΪ���ӵ�0������row�У��ӵ�0������column�С�

����˵��
����˵����
��һ�������ĸ����������ֱ��������������m����n����һ������ķ���Ԫ�صĸ��� t1 �͵ڶ�������ķ���Ԫ�صĸ��� t2 ��
�������� t1+t2 ������Ԫ�飬�ֱ��ǵ�һ����������ݺ͵ڶ�����������ݡ�
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

/*---ϡ��������Ԫ��ʮ������洢�ṹ---*/

#define MATRIX_UNIT_SIZE 1		 // ϡ�����洢�ռ�ĵ�λ������
#define ElemType int			 // �Զ���ϡ����������Ԫ������
#define EmptySet 0				 // �Զ���ϡ���������Ԫ�������
#define print(x) printf("%d", x) // �Զ�������Ԫ�ص����뺯��
#define scan(x) scanf("%d", x)	 // �Զ�������Ԫ�ص��������
// ���ϲ��ֿɸ�����������޸�

typedef struct Triple
{
	int rwnum, clnum;				  // �÷���Ԫ�����ڵ��кţ�rwnum�����кţ�clnum��
	ElemType data;					  // ����Ԫ�صľ�����ֵ������ΪElemType
	struct Triple *rowlink, *collink; // ָ��ͬһ�л�ͬһ������һ������Ԫ�ص�ָ�룬�γ���ʽ�洢�ṹ

} Triple;

typedef struct
{
	Triple *rowheader, *colheader; // �ֱ�ָ�����ÿһ�к�ÿһ�з���Ԫ������ı�ͷָ��
	int row, column;			   // �����������row����������column��
	int elnum;					   // �����з���Ԫ�ص�������elnum��

} TriSMatrix;

// �Զ��庯��
void InsertNode(Triple *, Triple *, int, int, ElemType);   // ����ڵ�
void AllocSMatrix(TriSMatrix *, int, int, int);			   // Ϊϡ��������ò���������ռ�
void InitSMatrix(TriSMatrix *);							   // ��ʼ��ϡ�����
void DestroySMatrix(TriSMatrix *);						   // ����ϡ�����
void PrintSMatrix(TriSMatrix *);						   // ���ϡ�����
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

	// �ͷų���ռ�õĴ�p���ռ䲢�˳�
	DestroySMatrix(&MatrixA);
	DestroySMatrix(&MatrixB);
	DestroySMatrix(&MatrixC);

	return OK;
}

// ���½ڵ�new_node���뵽Ŀ��ڵ�����������ʵ�λ��
void InsertNode(Triple *rowp, Triple *colp, int rwnum, int clnum, ElemType data)
{
	// �жϴ����ָ���Ƿ�Ϊ��
	if (rowp == NULL || colp == NULL)
	{
		printf("The incoming pointers are  null pointers!\n");
		exit(ERROR);
	}

	// �����µĽڵ�洢����Ԫ�أ��������ڴ�
	Triple *new_node = (Triple *)malloc(MATRIX_UNIT_SIZE * sizeof(Triple));

	// ����ڴ�����Ƿ�ɹ�������ʼ���½ڵ������
	if (new_node != NULL)
	{
		new_node->rwnum = rwnum;
		new_node->clnum = clnum;
		new_node->data = data;
	}

	else
	{
		printf("Memory allocation failed to create a new node to store non-zero elements!\n");
		exit(ERROR);
	}

	// ����ͷ�������ͷ�����в��Һ��ʵ�λ�ò����½ڵ�
	while ((rowp->rowlink != NULL) && (rowp->rowlink->clnum < clnum))
		rowp = rowp->rowlink;
	while ((colp->collink != NULL) && (colp->collink->rwnum < rwnum))
		colp = colp->collink;

	new_node->rowlink = rowp->rowlink;
	rowp->rowlink = new_node;

	new_node->collink = colp->collink;
	colp->collink = new_node;
}

// ���ݸ���������(row)������(column)�Լ�����Ԫ�ظ���(M->elnum)����̬����ͳ�ʼ��ϡ�����M
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

	// ��ʼ��ϡ�����ṹ���еĳ�Ա���������������������ͷ���Ԫ�ظ���
	M->row = row;
	M->column = column;
	M->elnum = elnum;

	// ��ʼ��ϡ��������ͷ���飬Ϊÿ��Ԫ�ط����ڴ沢��ʼ��
	int i;
	M->rowheader = (Triple *)malloc((M->row + MATRIX_UNIT_SIZE) * sizeof(Triple));
	if (M->rowheader != NULL)
	{
		for (i = 0; i <= M->row; i++)
		{
			M->rowheader[i].rwnum = -1;
			M->rowheader[i].clnum = -1;
			M->rowheader[i].data = EmptySet;
			M->rowheader[i].rowlink = NULL;
			M->rowheader[i].collink = NULL;
		}
	}

	else
	{
		printf("Memory allocation for row header array failed!\n");
		exit(ERROR);
	}

	// ��ʼ��ϡ��������ͷ���飬Ϊÿ��Ԫ�ط����ڴ沢��ʼ��
	M->colheader = (Triple *)malloc((M->column + MATRIX_UNIT_SIZE) * sizeof(Triple));
	if (M->colheader != NULL)
	{
		for (i = 0; i <= M->column; i++)
		{
			M->colheader[i].rwnum = -1;
			M->colheader[i].clnum = -1;
			M->colheader[i].data = EmptySet;
			M->colheader[i].rowlink = NULL;
			M->colheader[i].collink = NULL;
		}
	}

	else
	{
		printf("Memory allocation for column header array failed!\n");
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

	// �����������ʱ�洢��ȡ�����кš��кż�����Ԫ��ֵ
	int rwnum, clnum;
	ElemType data;

	// ����Ҫ��ȡ�����з���Ԫ��
	int count;
	for (count = 0; count < M->elnum; count++)
	{

		// ��ȡһ������Ԫ�ص��кš��кź�����ֵ
		scanf("%d %d", &rwnum, &clnum);
		scan(&data);
		if (rwnum > M->row || clnum > M->column || data == EmptySet)
		{
			printf("Errors in row number, column number and data value for non-zero elements!\n");
			exit(ERROR);
		}
		InsertNode(&M->rowheader[rwnum], &M->colheader[clnum], rwnum, clnum, data);
	}
}

// ����ϡ������ͷ���ռ�õ��ڴ���Դ
void DestroySMatrix(TriSMatrix *M)
{

	// ��鴫��ľ���ָ��M�Ƿ�Ϊ��
	if (M == NULL)
	{
		printf("Passing a matrix pointer as an argument to the function fails!\n");
		exit(ERROR);
	}

	// ����ϡ�����ÿһ�еķ���Ԫ��
	int i;
	for (i = 0; i <= M->row; i++)
	{

		// ��ȡ��ǰ�еĵ�һ������Ԫ��ָ��
		Triple *p1 = M->rowheader[i].rowlink;

		// ѭ���������е����з���Ԫ�أ������ͷ�����ռ�õ��ڴ�
		while (p1 != NULL)
		{
			Triple *p2 = p1->rowlink;
			free(p1);
			p1 = p2;
		}
	}

	// �ͷ���ͷ�������ͷ����ռ�õ��ڴ�
	free(M->rowheader);
	free(M->colheader);

	// ���������ͷ�������ͷ����ָ����ΪNULL����ֹ����ָ��
	M->rowheader = NULL;
	M->colheader = NULL;
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
	// ����ϡ������ÿһ��
	for (count = 0; count <= M->row; count++)
	{
		Triple *p = M->rowheader[count].rowlink;
		// ������ǰ�е����з���Ԫ��
		while (p != NULL)
		{
			printf("%d %d ", p->rwnum, p->clnum);
			print(p->data);
			printf("\n");
			p = p->rowlink;
		}
	}
}

// �ϲ�����ϡ�����A��B��Ԫ�ص�C�У����A��B����ͬλ����Ԫ�أ�����ӣ�����ֱ����ӵ�C��
void SumSMatrix(TriSMatrix *A, TriSMatrix *B, TriSMatrix *C)
{
	// ��������ϡ�����ָ���Ƿ���Ч����һΪ�������������Ϣ���˳�
	if (A == NULL || B == NULL || C == NULL)
	{
		printf("Passing  matrix pointers as arguments to the function fails!\n");
		exit(ERROR);
	}

	// ������������Ƿ������ͬ����������������ͬ���޷���ӣ����������Ϣ���˳�
	if (A->row != B->row || A->column != B->column)
	{
		printf("The two sparse matrices cannot be added together!\n");
		exit(ERROR);
	}

	int count = 0, i;
	for (i = 0; i <= A->row; i++)
	{

		// ��ʼ��ָ�����������Ӧ��ͷ��ָ��
		Triple *pA = A->rowheader[i].rowlink, *pB = B->rowheader[i].rowlink, *pC = &C->rowheader[i];

		// ����������ͬһ���ڵķ���Ԫ�أ��ϲ���C��
		while ((pA != NULL) && (pB != NULL))
		{

			// ��A���б��С��B����A��Ԫ�ز��뵽C��
			if (pA->clnum < pB->clnum)
			{
				InsertNode(pC, &C->colheader[pA->clnum], pA->rwnum, pA->clnum, pA->data);
				pA = pA->rowlink;
				count++;
			}

			// ��A���б�Ŵ���B����B��Ԫ�ز��뵽C��
			else if (pA->clnum > pB->clnum)
			{
				InsertNode(pC, &C->colheader[pB->clnum], pB->rwnum, pB->clnum, pB->data);
				pB = pB->rowlink;
				count++;
			}

			// ��A��B��ͬһ��λ�ã�������֮�ͣ����㣩���뵽C��
			else if (pA->clnum == pB->clnum)
			{
				if (pA->data + pB->data != 0)
				{
					InsertNode(pC, &C->colheader[pB->clnum], pA->rwnum, pA->clnum, pA->data + pB->data);
					pA = pA->rowlink;
					pB = pB->rowlink;
					count++;
				}
				// ����Ϊ�㣬�������������뵽C��
				else
				{
					pA = pA->rowlink;
					pB = pB->rowlink;
				}
			}
		}

		// ��A����ʣ��Ԫ�أ�ֱ�Ӳ��뵽C��
		while (pA != NULL)
		{
			InsertNode(pC, &C->colheader[pA->clnum], pA->rwnum, pA->clnum, pA->data);
			pA = pA->rowlink;
			count++;
		}

		// ��B����ʣ��Ԫ�أ�ֱ�Ӳ��뵽C��
		while (pB != NULL)
		{
			InsertNode(pC, &C->colheader[pB->clnum], pB->rwnum, pB->clnum, pB->data);
			pB = pB->rowlink;
			count++;
		}
	}

	// ����ʵ����ӵ�C�ķ���Ԫ������������C�ķ���Ԫ������
	C->elnum = count;
}