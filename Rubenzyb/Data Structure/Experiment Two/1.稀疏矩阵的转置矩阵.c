/*
任务描述
输出稀疏矩阵的转置矩阵。（行列均不大于20）
已知若矩阵的行数为row，列数为column，
则矩阵范围为：从第0行至第row行，从第0列至第column列。 

测试说明
输入说明：
第一行输入两个正整数 n 和 m ,分别表示矩阵的行数和列数，
然后输入矩阵三元组，
最后输入（0 0 0）表示结束输入。

输出说明：
转置后的矩阵。
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

#define MATRIX_UNIT_SIZE 1       // 稀疏矩阵存储空间的单位分配量
#define ElemType int             // 自定义稀疏矩阵的数据元素类型
#define EmptySet 0               // 自定义稀疏矩阵数据元素零符号
#define print(x) printf("%d", x) // 自定义数据元素的输入函数
#define scan(x) scanf("%d", x)   // 自定义数据元素的输出函数
// 以上部分可根据需求进行修改

typedef struct
{

  int rwnum, clnum; // 非零元素的行号和列号
  ElemType data;

} Triple;

typedef struct
{

  Triple *element;        // 从element[1]开始存储数据的三元组表
  int row, column, elnum; // 矩阵的行数,列数与非零元素个数

} TriSMatrix;

// 自定义函数
void AllocSMatrix(TriSMatrix *, int, int, int);    // 为稀疏矩阵设置参数并分配空间
void InitSMatrix(TriSMatrix *);                    // 初始化稀疏矩阵
void DestroySMatrix(TriSMatrix *);                 // 销毁稀疏矩阵
void PrintSMatrix(TriSMatrix *);                   // 输出稀疏矩阵
void TransposeSMatrix(TriSMatrix *, TriSMatrix *); // 求稀疏矩阵的转置矩阵

int main()
{

  // 从终端接收两个正整数n和m，分别表示输入的矩阵的行数和列数
  int n, m;
  scanf("%d %d", &n, &m);

  // 创建并初始化两个稀疏矩阵SMatrix和TMatrix，前者存储输入的矩阵，后者存储转置后的矩阵
  TriSMatrix SMatrix, TMatrix;

  AllocSMatrix(&SMatrix, n, m, 0);
  InitSMatrix(&SMatrix);
  AllocSMatrix(&TMatrix, m, n, SMatrix.elnum);

  // 将稀疏矩阵SMatrix的转置矩阵储存在TMatrix中并输出
  TransposeSMatrix(&SMatrix, &TMatrix);
  PrintSMatrix(&TMatrix);

  // 释放程序占用的存储空间并退出
  DestroySMatrix(&SMatrix);
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
void TransposeSMatrix(TriSMatrix *M, TriSMatrix *T) {

	// 检查输入的稀疏矩阵指针M和T是否为空
	if (M == NULL || T == NULL) {
		printf("Passing  matrix pointers as arguments to the function fails!\n");
		exit(ERROR);
	}

	// 初始化一个计数数组cpot，用于记录新位置上的非零元素个数，数组长度为M的列数
	int count1, count2, cpot[M->column+1];

	for (count1 = 0; count1 <= M->column; count1++) {
		cpot[count1] = 0; // 每个元素初始计数为0
	}

	// 计算转置后每个列的非零元素在新矩阵中的位置偏移量
	for (count1 = 1; count1 <= M->elnum; count1++) {
		for (count2 = M->element[count1].clnum + 1; count2 <= M->column; count2++) {
			cpot[count2]++; // 对于每一行，更新对应列的计数
		}
	}

	// 根据计算出的位置偏移量，将M的非零元素转置到T中
	for (count1 = 1; count1 <= M->elnum; count1++) {

		count2 = ++cpot[M->element[count1].clnum]; // 获取转置后元素的新位置，并自动增加计数

		// 转置操作：将M的列号变为T的行号，M的行号变为T的列号，数据保持不变
		T->element[count2].rwnum = M->element[count1].clnum;
		T->element[count2].clnum = M->element[count1].rwnum;
		T->element[count2].data = M->element[count1].data;
	}

	// 检验是否成功转置了所有元素，若成功转置（即计数不匹配），则打印错误信息并退出程序
	if (cpot[M->column] != T->elnum) {
		printf("The transpose of the sparse matrix is not fully realised!");
		exit(ERROR);
	}
}


//// 转置稀疏矩阵M，并将结果存储在稀疏矩阵T中（原版）
//void TransposeSMatrix(TriSMatrix *M, TriSMatrix *T)
//{
//
//  // 检查输入的稀疏矩阵指针M和T是否为空
//  if (M == NULL || T == NULL)
//  {
//    printf("Passing  matrix pointers as arguments to the function fails!\n");
//    exit(ERROR);
//  }
//
//  // 遍历目标矩阵T的行数以及已存储元素数量，进行转置操作
//  int mcount, tcount, order;
//  for (order = 0, tcount = 0; order <= T->row && tcount <= T->elnum; order++)
//  {
//
//    // 遍历原稀疏矩阵M的非零元素
//    for (mcount = 1; mcount <= M->elnum; mcount++)
//    {
//
//      // 寻找M中列号等于当前转置矩阵行号的元素，进行转置操作
//      if (M->element[mcount].clnum == order)
//      {
//
//        tcount++;
//        // 转置操作：将M的列号变为T的行号，M的行号变为T的列号，数据保持不变
//        T->element[tcount].rwnum = M->element[mcount].clnum;
//        T->element[tcount].clnum = M->element[mcount].rwnum;
//        T->element[tcount].data = M->element[mcount].data;
//      }
//    }
//  }
//
//  // 检验是否成功转置了所有元素，若成功转置（即计数不匹配），则打印错误信息并退出程序
//  if (tcount != T->elnum)
//  {
//    printf("The transpose of the sparse matrix is not fully realised!");
//    exit(ERROR);
//  }
//}
