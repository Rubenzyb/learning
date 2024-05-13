/*
任务描述
稀疏矩阵加法，用十字链表实现C=A+B。
输入两个稀疏矩阵，输出它们相加的结果。
已知若矩阵的行数为row，列数为column，
则矩阵范围为：从第0行至第row行，从第0列至第column列。

测试说明
输入说明：
第一行输入四个正整数，分别是两个矩阵的行m、列n、第一个矩阵的非零元素的个数 t1 和第二个矩阵的非零元素的个数 t2 。
接下来的 t1+t2 行是三元组，分别是第一个矩阵的数据和第二个矩阵的数据。
三元组的第一个元素表示行号，第二个元素表示列号，第三个元素是该项的值。

输出说明：
输出相加后的矩阵三元组。
*/

// 程序包含的头文件
#include <stdio.h>
#include <stdlib.h>

// 函数结果状态代码
#define TRUE 1
#define FALSE 0
#define OK 0
#define ERROR 1
#define INFEASIBLE -1
#define OVERFLOW -2

/*---稀疏矩阵的三元组十字链表存储结构---*/

#define MATRIX_UNIT_SIZE 1		 // 稀疏矩阵存储空间的单位分配量
#define ElemType int			 // 自定义稀疏矩阵的数据元素类型
#define EmptySet 0				 // 自定义稀疏矩阵数据元素零符号
#define print(x) printf("%d", x) // 自定义数据元素的输入函数
#define scan(x) scanf("%d", x)	 // 自定义数据元素的输出函数
// 以上部分可根据需求进行修改

typedef struct Triple
{
	int rwnum, clnum;				  // 该非零元素所在的行号（rwnum）和列号（clnum）
	ElemType data;					  // 非零元素的具体数值，类型为ElemType
	struct Triple *rowlink, *collink; // 指向同一行或同一列中下一个非零元素的指针，形成链式存储结构

} Triple;

typedef struct
{
	Triple *rowheader, *colheader; // 分别指向矩阵每一行和每一列非零元素链表的表头指针
	int row, column;			   // 矩阵的行数（row）和列数（column）
	int elnum;					   // 矩阵中非零元素的总数（elnum）

} TriSMatrix;

// 自定义函数
void InsertNode(Triple *, Triple *, int, int, ElemType);   // 插入节点
void AllocSMatrix(TriSMatrix *, int, int, int);			   // 为稀疏矩阵设置参数并分配空间
void InitSMatrix(TriSMatrix *);							   // 初始化稀疏矩阵
void DestroySMatrix(TriSMatrix *);						   // 销毁稀疏矩阵
void PrintSMatrix(TriSMatrix *);						   // 输出稀疏矩阵
void SumSMatrix(TriSMatrix *, TriSMatrix *, TriSMatrix *); // 将两个稀疏矩阵相加

int main()
{

	// 从终端接收四个正整数m、n、t1和t2，分别表示输入矩阵的行数和列数、两个矩阵的非零元素个数
	int m, n, t1, t2;
	scanf("%d %d %d %d", &m, &n, &t1, &t2);

	// 创建并初始化三个稀疏矩阵MatrixA、MatrixB和MatrixC，前两者存储输入的矩阵，后者存储相加后的矩阵
	TriSMatrix MatrixA, MatrixB, MatrixC;
	AllocSMatrix(&MatrixA, m, n, t1);
	AllocSMatrix(&MatrixB, m, n, t2);
	AllocSMatrix(&MatrixC, m, n, t1 + t2);
	InitSMatrix(&MatrixA);
	InitSMatrix(&MatrixB);

	// 将相加得到的矩阵储存在MatrixC中并输出
	SumSMatrix(&MatrixA, &MatrixB, &MatrixC);
	PrintSMatrix(&MatrixC);

	// 释放程序占用的存p储空间并退出
	DestroySMatrix(&MatrixA);
	DestroySMatrix(&MatrixB);
	DestroySMatrix(&MatrixC);

	return OK;
}

// 将新节点new_node插入到目标节点所在链表的适当位置
void InsertNode(Triple *rowp, Triple *colp, int rwnum, int clnum, ElemType data)
{
	// 判断传入的指针是否为空
	if (rowp == NULL || colp == NULL)
	{
		printf("The incoming pointers are  null pointers!\n");
		exit(ERROR);
	}

	// 创建新的节点存储非零元素，并分配内存
	Triple *new_node = (Triple *)malloc(MATRIX_UNIT_SIZE * sizeof(Triple));

	// 检查内存分配是否成功，并初始化新节点的内容
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

	// 在行头链表和列头链表中查找合适的位置插入新节点
	while ((rowp->rowlink != NULL) && (rowp->rowlink->clnum < clnum))
		rowp = rowp->rowlink;
	while ((colp->collink != NULL) && (colp->collink->rwnum < rwnum))
		colp = colp->collink;

	new_node->rowlink = rowp->rowlink;
	rowp->rowlink = new_node;

	new_node->collink = colp->collink;
	colp->collink = new_node;
}

// 根据给定的行数(row)、列数(column)以及非零元素个数(M->elnum)，动态分配和初始化稀疏矩阵M
void AllocSMatrix(TriSMatrix *M, int row, int column, int elnum)
{

	// 检查传入的指针M是否为空
	if (M == NULL)
	{
		printf("Passing a matrix pointer as an argument to the function fails!\n");
		exit(ERROR);
	}

	// 检查传入的稀疏矩阵的参数是否合法
	if (row == 0 || column == 0)
	{
		printf("The parameters of the sparse matrix read in were incorrect!\n");
		exit(ERROR);
	}

	// 初始化稀疏矩阵结构体中的成员变量，包括行数、列数和非零元素个数
	M->row = row;
	M->column = column;
	M->elnum = elnum;

	// 初始化稀疏矩阵的行头数组，为每个元素分配内存并初始化
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

	// 初始化稀疏矩阵的列头数组，为每个元素分配内存并初始化
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

// 初始化稀疏矩阵，从标准输入读取稀疏矩阵的非零元素的数据
void InitSMatrix(TriSMatrix *M)
{

	// 检查传入的指针M是否为空
	if (M == NULL)
	{
		printf("Passing a matrix pointer as an argument to the function fails!\n");
		exit(ERROR);
	}

	// 定义变量来临时存储读取到的行号、列号及非零元素值
	int rwnum, clnum;
	ElemType data;

	// 遍历要读取的所有非零元素
	int count;
	for (count = 0; count < M->elnum; count++)
	{

		// 读取一个非零元素的行号、列号和数据值
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

// 销毁稀疏矩阵，释放其占用的内存资源
void DestroySMatrix(TriSMatrix *M)
{

	// 检查传入的矩阵指针M是否为空
	if (M == NULL)
	{
		printf("Passing a matrix pointer as an argument to the function fails!\n");
		exit(ERROR);
	}

	// 遍历稀疏矩阵每一行的非零元素
	int i;
	for (i = 0; i <= M->row; i++)
	{

		// 获取当前行的第一个非零元素指针
		Triple *p1 = M->rowheader[i].rowlink;

		// 循环遍历该行的所有非零元素，依次释放它们占用的内存
		while (p1 != NULL)
		{
			Triple *p2 = p1->rowlink;
			free(p1);
			p1 = p2;
		}
	}

	// 释放行头数组和列头数组占用的内存
	free(M->rowheader);
	free(M->colheader);

	// 将矩阵的行头数组和列头数组指针置为NULL，防止悬挂指针
	M->rowheader = NULL;
	M->colheader = NULL;
}

// 打印给定的稀疏矩阵M的内容
void PrintSMatrix(TriSMatrix *M)
{
	// 检查传入的指针M是否为空
	if (M == NULL)
	{
		printf("Passing a matrix pointer as an argument to the function fails!\n");
		exit(ERROR);
	}

	// 检查稀疏矩阵的非零元素个数是否合理
	if (M->elnum < 1)
	{
		printf("Incorrect number of non-zero elements of a sparse matrix!\n");
		exit(ERROR);
	}

	// 遍历稀疏矩阵的所有非零元素
	int count;
	printf("\n");
	// 遍历稀疏矩阵的每一行
	for (count = 0; count <= M->row; count++)
	{
		Triple *p = M->rowheader[count].rowlink;
		// 遍历当前行的所有非零元素
		while (p != NULL)
		{
			printf("%d %d ", p->rwnum, p->clnum);
			print(p->data);
			printf("\n");
			p = p->rowlink;
		}
	}
}

// 合并两个稀疏矩阵A和B的元素到C中，如果A和B在相同位置有元素，则相加；否则，直接添加到C中
void SumSMatrix(TriSMatrix *A, TriSMatrix *B, TriSMatrix *C)
{
	// 检查输入的稀疏矩阵指针是否有效，任一为空则输出错误信息并退出
	if (A == NULL || B == NULL || C == NULL)
	{
		printf("Passing  matrix pointers as arguments to the function fails!\n");
		exit(ERROR);
	}

	// 检查两个矩阵是否具有相同的行数和列数，不同则无法相加，输出错误信息并退出
	if (A->row != B->row || A->column != B->column)
	{
		printf("The two sparse matrices cannot be added together!\n");
		exit(ERROR);
	}

	int count = 0, i;
	for (i = 0; i <= A->row; i++)
	{

		// 初始化指向三个矩阵对应行头的指针
		Triple *pA = A->rowheader[i].rowlink, *pB = B->rowheader[i].rowlink, *pC = &C->rowheader[i];

		// 对于两矩阵同一行内的非零元素，合并到C中
		while ((pA != NULL) && (pB != NULL))
		{

			// 若A的列编号小于B，将A的元素插入到C中
			if (pA->clnum < pB->clnum)
			{
				InsertNode(pC, &C->colheader[pA->clnum], pA->rwnum, pA->clnum, pA->data);
				pA = pA->rowlink;
				count++;
			}

			// 若A的列编号大于B，将B的元素插入到C中
			else if (pA->clnum > pB->clnum)
			{
				InsertNode(pC, &C->colheader[pB->clnum], pB->rwnum, pB->clnum, pB->data);
				pB = pB->rowlink;
				count++;
			}

			// 若A和B在同一列位置，将二者之和（非零）插入到C中
			else if (pA->clnum == pB->clnum)
			{
				if (pA->data + pB->data != 0)
				{
					InsertNode(pC, &C->colheader[pB->clnum], pA->rwnum, pA->clnum, pA->data + pB->data);
					pA = pA->rowlink;
					pB = pB->rowlink;
					count++;
				}
				// 若和为零，则跳过，不插入到C中
				else
				{
					pA = pA->rowlink;
					pB = pB->rowlink;
				}
			}
		}

		// 若A还有剩余元素，直接插入到C中
		while (pA != NULL)
		{
			InsertNode(pC, &C->colheader[pA->clnum], pA->rwnum, pA->clnum, pA->data);
			pA = pA->rowlink;
			count++;
		}

		// 若B还有剩余元素，直接插入到C中
		while (pB != NULL)
		{
			InsertNode(pC, &C->colheader[pB->clnum], pB->rwnum, pB->clnum, pB->data);
			pB = pB->rowlink;
			count++;
		}
	}

	// 根据实际添加到C的非零元素数量，更新C的非零元素总数
	C->elnum = count;
}