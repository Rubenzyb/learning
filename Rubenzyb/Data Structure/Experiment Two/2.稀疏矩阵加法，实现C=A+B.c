/*
任务描述
输入两个稀疏矩阵，输出它们相加的结果。
已知若矩阵的行数为row，列数为column，
则矩阵范围为：从第0行至第row行，从第0列至第column列。 

测试说明
输入说明：
第一行输入四个正整数，分别是两个矩阵的行m、列n、第一个矩阵的非零元素的个数t1和第二个矩阵的非零元素的个数t2。
接下来的t1+t2行是三元组，分别是第一个矩阵的数据和第二个矩阵的数据。
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
void AllocSMatrix(TriSMatrix *, int, int, int);            // 为稀疏矩阵设置参数并分配空间
void InitSMatrix(TriSMatrix *);                            // 初始化稀疏矩阵
void DestroySMatrix(TriSMatrix *);                         // 销毁稀疏矩阵
void PrintSMatrix(TriSMatrix *);                           // 输出稀疏矩阵
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

  // 释放程序占用的存储空间并退出
  DestroySMatrix(&MatrixA);
  DestroySMatrix(&MatrixB);
  DestroySMatrix(&MatrixC);

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

// 合并两个稀疏矩阵A和B的元素到C中，如果A和B在相同位置有元素，则相加；否则，直接添加到C中
void SumSMatrix(TriSMatrix *A, TriSMatrix *B, TriSMatrix *C)
{
  // 检查输入的稀疏矩阵指针是否有效，任一为空则报错退出
  if (A == NULL || B == NULL || C == NULL)
  {
    printf("Passing  matrix pointers as arguments to the function fails!\n");
    exit(ERROR);
  }

  // 检查两个矩阵是否是同型矩阵
  if (A->row != B->row || A->column != B->column)
  {
    printf("The two sparse matrices cannot be added together!\n");
    exit(ERROR);
  }

  // 初始化指向各矩阵非零元素的指针
  Triple *pA = &A->element[1], *pB = &B->element[1], *pC = &C->element[1];

  // 检查指针初始化是否成功
  if (pA == NULL || pB == NULL || pC == NULL)
  {
    printf("The initialisation of the pointers generated errors!\n");
    exit(ERROR);
  }

  // 初始化计数器，用于追踪已合并的元素数量
  int count = 0;

  // 遍历两个矩阵的非零元素
  while (pA <= &A->element[A->elnum] && pB <= &B->element[B->elnum])
  {
    // 比较行号和列号，按规则合并元素到C中

    /* 处理A的行号小于B的情况 */
    if (pA->rwnum < pB->rwnum)
    {

      pC->rwnum = pA->rwnum;
      pC->clnum = pA->clnum;
      pC->data = pA->data;
      pC++;
      pA++;
      count++;
    }

    /* 处理A的行号大于B的情况 */
    else if (pA->rwnum > pB->rwnum)
    {

      pC->rwnum = pB->rwnum;
      pC->clnum = pB->clnum;
      pC->data = pB->data;
      pC++;
      pB++;
      count++;
    }

    /* 行号相同，再比较列号，进行合并或添加 */
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

  // 若A有剩余元素，直接追加到C中
  while (pA <= &A->element[A->elnum])
  {
    pC->rwnum = pA->rwnum;
    pC->clnum = pA->clnum;
    pC->data = pA->data;
    pC++;
    pA++;
    count++;
  }

  // 若B有剩余元素，直接追加到C中
  while (pB <= &B->element[B->elnum])
  {
    pC->rwnum = pB->rwnum;
    pC->clnum = pB->clnum;
    pC->data = pB->data;
    pC++;
    pB++;
    count++;
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
