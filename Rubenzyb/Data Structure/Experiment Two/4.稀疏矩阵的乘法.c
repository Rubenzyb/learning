/*
任务描述
计算两个稀疏矩阵的乘法。
已知若矩阵的行数为row，列数为column，
则矩阵范围为：从第0行至第row行，从第0列至第column列。

测试说明
输入说明：
首先输入第一个矩阵的行数和列数，再输入该矩阵的三元组形式，以0 0 0结束。
然后输入第二个矩阵的行数和列数，再输入该矩阵的三元组形式，以0 0 0结束。

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

/*---稀疏矩阵的三元组顺序表存储结构---*/

#define MATRIX_UNIT_SIZE 1		 // 稀疏矩阵存储空间的单位分配量
#define ElemType int			 // 自定义稀疏矩阵的数据元素类型
#define EmptySet 0				 // 自定义稀疏矩阵数据元素零符号
#define print(x) printf("%d", x) // 自定义数据元素的输入函数
#define scan(x) scanf("%d", x)	 // 自定义数据元素的输出函数
// 以上部分可根据需求进行修改

typedef struct
{

	int rwnum, clnum; // 非零元素的行号和列号
	ElemType data;

} Triple;

typedef struct
{

	Triple *element;		// 从element[1]开始存储数据的三元组表
	int row, column, elnum; // 矩阵的行数,列数与非零元素个数

} TriSMatrix;

// 自定义函数
void AllocSMatrix(TriSMatrix *, int, int, int);					// 为稀疏矩阵设置参数并分配空间
void InitSMatrix(TriSMatrix *);									// 初始化稀疏矩阵
void DestroySMatrix(TriSMatrix *);								// 销毁稀疏矩阵
void PrintSMatrix(TriSMatrix *);								// 输出稀疏矩阵
void TransposeSMatrix(TriSMatrix *, TriSMatrix *);				// 求稀疏矩阵的转置矩阵
void MultiplySMatrix(TriSMatrix *, TriSMatrix *, TriSMatrix *); // 将两个稀疏矩阵相乘

int main()
{

	// 从终端接收四个正整数row1和col1，row2和col2，分别表示输入的两个矩阵的行数和列数
	int row1, col1, row2, col2;

	// 创建并初始化四个稀疏矩阵AMatrix，BMatrix，CMatrix和TMatrix，
	// 前两者存储输入的矩阵，次后者存储相乘后的矩阵,最后者存储转置后的矩阵
	TriSMatrix AMatrix, BMatrix, CMatrix, TMatrix;

	scanf("%d %d", &row1, &col1);
	AllocSMatrix(&AMatrix, row1, col1, 0);
	InitSMatrix(&AMatrix);

	scanf("%d %d", &row2, &col2);
	AllocSMatrix(&BMatrix, row2, col2, 0);
	InitSMatrix(&BMatrix);

	AllocSMatrix(&TMatrix, col2, row2, BMatrix.elnum);
	AllocSMatrix(&CMatrix, row1, col2, AMatrix.row * BMatrix.column);

	// 将BMatrix的转置矩阵储存在TMatrix中，
	// 再将AMatrix与TMatrix相乘得到的矩阵存储在CMatrix中并输出
	TransposeSMatrix(&BMatrix, &TMatrix);
	MultiplySMatrix(&AMatrix, &TMatrix, &CMatrix);
	PrintSMatrix(&CMatrix);

	// 释放程序占用的存储空间并退出
	DestroySMatrix(&AMatrix);
	DestroySMatrix(&BMatrix);
	DestroySMatrix(&CMatrix);
	DestroySMatrix(&TMatrix);

	return OK;
}

// 根据给定的行数(row)、列数(column)以及非零元素个数(M->elnum)，为稀疏矩阵M动态分配和初始化所需的结构空间
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

	// 设置稀疏矩阵的行数，列数和非零元素个数
	M->row = row;
	M->column = column;
	M->elnum = elnum;

	// 使用malloc函数分配（M->elnum+MATRIX_UNIT_SIZE）个Triple结构体大小的连续内存空间
	M->element = (Triple *)malloc((M->elnum + MATRIX_UNIT_SIZE) * sizeof(Triple));

	// 检查malloc函数是否成功分配了内存
	if (M->element == NULL)
	{
		printf("Memory allocation failed for the sparse matrix elements.\n");
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

	// 定义变量存储读取到的行号、列号及非零元素值
	int rwnum, clnum;
	ElemType data;

	// 根据矩阵的定义预先为非零元素分配足够大的内存空间
	int matrixsize = M->row * M->column;

	Triple *temp = (Triple *)realloc(M->element, (matrixsize + MATRIX_UNIT_SIZE) * sizeof(Triple));
	// 如果重新分配失败，释放原内存并退出程序
	if (temp == NULL)
	{
		printf("Failed to reallocate sparse matrix memory space!\n");
		free(M->element);
		exit(ERROR);
	}
	else
		M->element = temp; // 否则更新M的element指针

	int count = 1;
	do
	{

		// 读取一个非零元素的行号、列号和数据值
		scanf("%d %d", &rwnum, &clnum);
		scan(&data);

		// 将当前读取到的非零元素添加至稀疏矩阵结构体中,，从element[1]开始存储非零元素的数据，element[0]未使用
		if (data != EmptySet)
		{

			M->element[count].rwnum = rwnum;
			M->element[count].clnum = clnum;
			M->element[count].data = data;
			count++;
		}

	} while ((M->elnum != 0) ^ (data != EmptySet) ^ (count <= M->elnum));

	// 循环结束后，根据实际使用情况，释放多余内存
	M->elnum = count - 1;

	if (M->elnum < matrixsize)
	{

		Triple *temp = (Triple *)realloc(M->element, (M->elnum + MATRIX_UNIT_SIZE) * sizeof(Triple));
		// 如果缩减失败释放原内存并退出程序
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

// 清理和重置稀疏矩阵M，使其处于一个已知的初始状态
void DestroySMatrix(TriSMatrix *M)
{

	// 检查传入的指针M是否为空
	if (M == NULL)
	{
		printf("Passing a matrix pointer as an argument to the function fails!\n");
		exit(ERROR);
	}

	// 释放非零元素数组的内存
	free(M->element);

	// 将element指针置空，防止野指针
	M->element = NULL;

	// 将矩阵的行数、列数和非零元素个数重置为零
	M->row = 0;
	M->column = 0;
	M->elnum = 0;
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
	for (count = 1; count <= M->elnum; count++)
	{
		// 打印当前非零元素的行号，列号和数据大小并换行
		printf("%d %d ", M->element[count].rwnum, M->element[count].clnum);
		print(M->element[count].data);
		printf("\n");
	}
}

// 转置稀疏矩阵M，并将结果存储在稀疏矩阵T中（新版）
void TransposeSMatrix(TriSMatrix *M, TriSMatrix *T)
{

	// 检查输入的稀疏矩阵指针M和T是否为空
	if (M == NULL || T == NULL)
	{
		printf("Passing  matrix pointers as arguments to the function fails!\n");
		exit(ERROR);
	}

	// 初始化一个计数数组cpot，用于记录新位置上的非零元素个数，数组长度为M的列数
	int count1, count2, cpot[M->column + 1];

	for (count1 = 0; count1 <= M->column; count1++)
	{
		cpot[count1] = 0; // 每个元素初始计数为0
	}

	// 计算转置后每个列的非零元素在新矩阵中的位置偏移量
	for (count1 = 1; count1 <= M->elnum; count1++)
	{
		for (count2 = M->element[count1].clnum + 1; count2 <= M->column; count2++)
		{
			cpot[count2]++; // 对于每一行，更新对应列的计数
		}
	}

	// 根据计算出的位置偏移量，将M的非零元素转置到T中
	for (count1 = 1; count1 <= M->elnum; count1++)
	{

		count2 = ++cpot[M->element[count1].clnum]; // 获取转置后元素的新位置，并自动增加计数

		// 转置操作：将M的列号变为T的行号，M的行号变为T的列号，数据保持不变
		T->element[count2].rwnum = M->element[count1].clnum;
		T->element[count2].clnum = M->element[count1].rwnum;
		T->element[count2].data = M->element[count1].data;
	}

	// 检验是否成功转置了所有元素，若成功转置（即计数不匹配），则打印错误信息并退出程序
	if (cpot[M->column] != T->elnum)
	{
		printf("The transpose of the sparse matrix is not fully realised!");
		exit(ERROR);
	}
}

// 对两个稀疏矩阵A和T进行乘法运算，并将结果存储在矩阵C中
void MultiplySMatrix(TriSMatrix *A, TriSMatrix *T, TriSMatrix *C)
{
	// 检查输入的稀疏矩阵指针是否有效，任一为空则报错退出
	if (A == NULL || T == NULL || C == NULL)
	{
		printf("Passing  matrix pointers as arguments to the function fails!\n");
		exit(ERROR);
	}

	// 检查两个矩阵是否可以相乘
	if (A->column != T->column)
	{
		printf("The two matrices cannot be multiplied!\n");
		exit(ERROR);
	}

	// 初始化指向各矩阵非零元素的指针
	Triple *pA = &A->element[1], *pT = &T->element[1], *pC = &C->element[1];

	// 检查指针是否正确初始化
	if (pA == NULL || pT == NULL || pC == NULL)
	{
		printf("The initialisation of the pointers generated errors!\n");
		exit(ERROR);
	}

	// 定义计数变量和行计数数组
	int count1, count2;						  // 用于循环计数
	int cpotA[A->row + 2], cpotT[T->row + 2]; // 存储每行非零元素的累计计数

	// 初始化行计数数组
	// cpotA和cpotT数组额外多一个元素用于存储总的非零元素数量
	cpotA[A->row + 1] = A->elnum;
	for (count1 = 0; count1 <= A->row; count1++)
	{
		cpotA[count1] = 0;
	}

	cpotT[T->row + 1] = T->elnum;
	for (count1 = 0; count1 <= T->row; count1++)
	{
		cpotT[count1] = 0;
	}

	// 计算行计数数组
	// 这一步是统计每行开始前的非零元素累积数量，用于快速索引
	while (pA <= &A->element[A->elnum])
	{
		for (count1 = pA->rwnum + 1; count1 <= A->row; count1++)
			cpotA[count1]++;
		pA++;
	}

	while (pT <= &T->element[T->elnum])
	{
		for (count2 = pT->rwnum + 1; count2 <= T->row; count2++)
			cpotT[count2]++;
		pT++;
	}

	// 实施矩阵乘法
	int count = 0; // 记录C中实际填充的非零元素数量
	for (count1 = 0; count1 <= A->row; count1++)
	{ // 遍历A的每一行

		for (count2 = 0; count2 <= T->row; count2++)
		{ // 遍历T的每一行

			ElemType sum = EmptySet;  // 初始化累加和为“空集”标记
			int rwnum = 0, clnum = 0; // 初始化临时变量以存储C矩阵非零元素的行号和列号

			// 使用cpot数组快速定位到A的当前行第一个非零元素
			pA = &A->element[cpotA[count1] + 1];

			while (pA <= &A->element[cpotA[count1 + 1]])
			{ // 遍历A当前行的非零元素

				// 同样定位T的当前行第一个非零元素
				pT = &T->element[cpotT[count2] + 1];

				while (pT <= &T->element[cpotT[count2 + 1]])
				{ // 遍历T当前行的非零元素

					// 如果A和T的当前元素列号相同，则累加乘积
					if (pT->clnum == pA->clnum)
					{
						rwnum = pA->rwnum;			// 记录结果行号
						clnum = pT->rwnum;			// 记录结果列号
						sum += pA->data * pT->data; // 累加乘积
					}
					pT++; // 移动到T的下一个非零元素
				}
				pA++; // 移动到A的下一个非零元素
			}

			// 如果该位置有非零乘积，填充到C中
			if (sum != EmptySet)
			{
				pC->rwnum = rwnum;
				pC->clnum = clnum;
				pC->data = sum;
				pC++;	 // 移动到C的下一个位置
				count++; // 增加非零元素计数
			}
		}
	}

	// 根据实际使用情况调整C的内存大小，释放未使用的内存
	if (count < C->elnum)
	{
		C->elnum = count; // 更新C的非零元素数量

		// 使用realloc函数减小C的内存占用
		Triple *temp = (Triple *)realloc(C->element, (C->elnum + MATRIX_UNIT_SIZE) * sizeof(Triple));
		// 如果内存缩减失败，则释放原内存并报错退出
		if (temp == NULL)
		{
			printf("Failed to shrink memory for the sparse matrix elements.\n");
			free(C->element);
			exit(ERROR);
		}
		else
			C->element = temp; // 否则更新C的element指针
	}
}
