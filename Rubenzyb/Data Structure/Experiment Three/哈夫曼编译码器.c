/*
任务描述
写一个哈夫曼码的编/译码系统，要求能对要传输的报文进行编码和解码。
构造哈夫曼树时，权值小的放左子树，权值大的放右子树，编码时右子树编码为 1 ，左子树编码为 0 。 

测试说明
输入说明：
输入表示字符集大小为 n（n<=100）的正整数，
以及 n 个字符和 n 个权值（正整数，值越大表示该字符出现的概率越大）；
输入串长小于或等于 100 的目标报文。

输出说明：
经过编码后的二进制码，占一行；
以及对应解码后的报文，占一行；
最后输出一个回车符。
*/

// 程序包含的头文件
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 函数结果状态代码
#define OK 0
#define ERROR 1

// 结构体声明
typedef struct HuffmanNode
{
	int weight;						  // 权值
	char character;					  // 结点所表示的字符
	struct HuffmanNode *left, *right; // 左孩子，右孩子
} HuffmanNode;						  // 哈夫曼树的数据结构
typedef struct CodeTable
{
	int weight;		// 权值
	char character; // 字符
	char *code;		// 对应编码
} CodeTable;		// 编码表的数据结构

// 函数声明
int InitialiseArray(HuffmanNode **, int);
int InitialiseCode(CodeTable **, HuffmanNode *, int);
int ConstHuffmanTree(HuffmanNode *, int);
int DetermineCode(int, int, char, char *, HuffmanNode *);
int PrintCode(CodeTable *, char **, char *, int, int);
int PrintString(HuffmanNode *, char *, char *, int, int);
int FreeMemory(HuffmanNode *, CodeTable *, char *, int);

int main()
{
	// 变量声明
	int n, i, tip;
	char Str[110] = {0}, *CodedStr; // 目标报文字符串与编码后的报文字符串
	HuffmanNode *Arr;				// 哈夫曼树节点数组
	CodeTable *Code;				// 编码数组

	// 获取字符集大小
	scanf("%d ", &n);
	if (n <= 0 || n > 100)
	{
		// 如果输入字符集大小不合法，报错
		printf("Invalid input!\n");
		return (ERROR);
	}

	// 初始化数组
	tip = InitialiseArray(&Arr, n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// 初始化编码数组
	tip = InitialiseCode(&Code, Arr, n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// 构建哈夫曼树
	tip = ConstHuffmanTree(Arr, n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// 输入目标报文
	getchar();
	scanf("%[^\n]", Str);
	if ((int)strlen(Str) > 100)
	{
		// 如果输入字符串长度超过100，报错
		printf("The input String is not legal!\n");
		return (ERROR);
	}

	// 确定每个字符的编码
	for (i = 0; i < n; i++)
	{
		tip = DetermineCode(Code[i].weight, 0, Code[i].character, Code[i].code, &Arr[0]);
		if (tip == ERROR)
		{
			printf("Error in the function return result!\n");
			return (ERROR);
		}

		// 重新分配内存以适应编码字符串的长度
		char *temp = (char *)realloc(Code[i].code, (int)strlen(Code[i].code) + 1);
		if (temp == NULL)
		{
			// 如果内存分配失败，报错
			printf("Memory reallocation for code String failed!\n");
			return (ERROR);
		}
		else
			Code[i].code = temp;
	}

	// 输出编码后的二进制码
	tip = PrintCode(Code, &CodedStr, Str, (int)strlen(Str), n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// 输出对应解码后的报文
	tip = PrintString(Arr, CodedStr, Str, (int)strlen(Str), n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// 释放动态分配的内存
	tip = FreeMemory(Arr, Code, CodedStr, n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// 程序结束
	return (OK);
}

// 为哈夫曼树动态分配内存并初始化所有节点，随后接收输入字符和权值，最后按权值排序节点。
int InitialiseArray(HuffmanNode **Arr, int n)
{
	// 确认指针有效
	if (Arr == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	int i, j;

	// 动态分配哈夫曼树节点数组，总节点数为n-1个叶子节点加上n-1个内部节点
	(*Arr) = (HuffmanNode *)calloc(2 * n - 1, sizeof(HuffmanNode));
	// 确认内存分配成功
	if ((*Arr) == NULL)
	{
		printf("Memory allocation for Huffman tree nodes failed!\n");
		return (ERROR);
	}

	// 依次输入字符和权值
	for (i = 0; i < n; ++i)
	{
		scanf("%c ", &(*Arr)[i].character);
	}
	for (i = 0; i < n; ++i)
	{
		scanf("%d", &(*Arr)[i].weight);
	}

	// 根据权值使用冒泡排序法将节点进行升序排序
	for (i = 1; i < n; ++i)
	{
		for (j = 0; j < n - i; ++j)
		{
			if ((*Arr)[j].weight < (*Arr)[j + 1].weight)
			{
				HuffmanNode agency = (*Arr)[j];
				(*Arr)[j] = (*Arr)[j + 1];
				(*Arr)[j + 1] = agency;
			}
		}
	}

	return (OK);
}

// 为给定的哈夫曼树节点数组创建一个对应的编码表结构，包括字符、权值及编码。
int InitialiseCode(CodeTable **Code, HuffmanNode *Arr, int n)
{
	// 确认指针有效
	if (Code == NULL || Arr == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	int i, j;

	// 动态分配编码表数组
	(*Code) = (CodeTable *)calloc(n, sizeof(CodeTable));
	// 确认内存分配成功
	if ((*Code) == NULL)
	{
		printf("Memory allocation for CodeTable failed!\n");
		return (ERROR);
	}

	// 为编码表中的每一个条目动态分配字符编码字符串的内存
	for (i = 0; i < n; i++)
	{
		(*Code)[i].code = (char *)calloc(n, sizeof(char));
		// 确认内存分配成功
		if ((*Code)[i].code == NULL)
		{
			printf("Memory allocation for code String failed!\n");
			// 有哪个分配失败就释放之前成功分配的所有code字符串内存
			for (j = 0; j < i; j++)
				free((*Code)[j].code);
			// 最后释放CodeTable本身
			free(*Code);
			return (ERROR);
		}
	}

	// 初始化编码表的每个条目
	for (i = 0; i < n; i++)
	{
		// 设置字符和权值
		(*Code)[i].weight = Arr[i].weight;
		(*Code)[i].character = Arr[i].character;
	}

	return (OK);
}

// 根据提供的字符权值数组生成一棵哈夫曼树，并为每个节点分配左右子节点
int ConstHuffmanTree(HuffmanNode *Arr, int n)
{
	// 确认指针有效
	if (Arr == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	int i, j, t;

	// 合并最小权值的两个节点，生成新节点，更新到数组末尾
	for (i = n - 1, t = n; i >= 1 && t < 2 * n - 1; i--, t++)
	{
		// 新节点设置为非字符节点（用0表示）
		Arr[t].character = 0;
		// 权值为前两个最小节点权值之和
		Arr[t].weight = Arr[i].weight + Arr[i - 1].weight;

		// 保证新插入的节点按权值有序
		for (j = t; j >= 1; j--)
		{
			if (Arr[j].weight > Arr[j - 1].weight)
			{
				// 交换元素以维持排序
				HuffmanNode agency = Arr[j];
				Arr[j] = Arr[j - 1];
				Arr[j - 1] = agency;
			}
		}
	}

	// 为每个内部节点分配左右子节点
	HuffmanNode *Temp1 = &Arr[1]; // 第一个节点的指针
	HuffmanNode *Temp2 = &Arr[2]; // 第二个节点的指针
	for (i = 0; (i < 2 * n - 1) && (Temp2 <= &Arr[2 * n - 2]); i++)
	{
		if (Arr[i].weight == Temp1->weight + Temp2->weight)
		{
			// 当前节点的权值等于相邻两节点权值之和时，建立连接
			Arr[i].right = Temp1; // 右子节点
			Arr[i].left = Temp2;  // 左子节点
			Temp1 += 2;			  // 移动到下一个可能的右子节点
			Temp2 += 2;			  // 移动到下一个可能的左子节点
		}
	}

	return (OK);
}

// 递归地为指定字符查找其在哈夫曼树中的路径，并记录为二进制编码
int DetermineCode(int weight, int count, char character, char *code, HuffmanNode *Temp)
{
	// 如果当前节点是叶子节点（无左右子节点），且既不是我们要找的字符，返回错误标记
	if (Temp->left == NULL && Temp->right == NULL)
		return (ERROR);

	// 如果当前节点的左子节点匹配（权值和字符都相同），则记录'0'并返回成功
	else if (Temp->left->weight == weight && Temp->left->character == character)
	{
		code[count] = '0';
		return (OK);
	}

	// 如果当前节点的右子节点匹配，记录'1'并返回成功
	else if (Temp->right->weight == weight && Temp->right->character == character)
	{
		code[count] = '1';
		return (OK);
	}

	// 递归进入左子树
	if (Temp->left != NULL)
	{
		code[count] = '0'; // 假设走左边，记录'0'
		int tip = DetermineCode(weight, count + 1, character, code, Temp->left);
		// 如果在左子树找到了字符，返回成功
		if (tip == OK)
			return (OK);
		else
			code[count] = 0; // 重置为空，以便尝试右子树
	}

	// 若左子树未找到，尝试右子树
	if (Temp->right != NULL)
	{
		code[count] = '1'; // 假设走右边，记录'1'
		int tip = DetermineCode(weight, count + 1, character, code, Temp->right);
		// 如果在右子树找到了字符，返回成功
		if (tip == OK)
			return (OK);
		else
			code[count] = 0; // 重置为空，以便返回上一层
	}

	// 如果左右子树都没有找到字符，返回错误
	return (ERROR);
}

// 打印编码后的报文字符串
int PrintCode(CodeTable *Code, char **CodedStr, char *Str, int length, int n)
{

	// 确认指针有效
	if (Code == NULL || Str == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	// 动态分配编码后的报文字符串内存
	*CodedStr = (char *)calloc(length * n, sizeof(char));
	if (*CodedStr == NULL)
	{
		// 如果内存分配失败，报错
		printf("Memory allocation for CodedStr failed!\n");
		return (ERROR);
	}

	int i, j, current_index = 0; // current_index用于记录当前编码后的报文字符串的长度

	// 遍历原始报文字符串，逐个字符进行编码
	for (i = 0; i < length; i++)
	{
		int tip = 0;

		// 跳过空格
		if (Str[i] == ' ')
			continue;

		// 遍历编码表，查找对应字符
		for (j = 0; j < n; j++)
		{
			// 如果找到了对应字符，将其编码添加到编码后的报文字符串中
			if (Str[i] == Code[j].character)
			{
				strcpy((*CodedStr) + current_index, Code[j].code); // 直接复制编码到当前位置
				current_index += strlen(Code[j].code);			   // 更新当前写入位置
				tip = 1;
				break;
			}
		}

		// 如果没有找到对应字符，报错
		if (tip == 0)
		{
			printf("Character not found in CodeTable!\n");
			return (ERROR);
		}
	}

	// 重新分配内存以适应编码后的报文字符串的长度
	char *temp = (char *)realloc(*CodedStr, (int)strlen(*CodedStr) + 1);
	if (temp == NULL)
	{
		// 如果内存重新分配失败，报错
		printf("Memory reallocation for CodedStr failed!\n");
		return (ERROR);
	}
	else
		*CodedStr = temp;

	// 打印编码后的报文字符串
	printf("%s\n", *CodedStr);

	return (OK);
}

// 打印原始报文字符串的新版函数
int PrintString(HuffmanNode *Arr, char *CodedStr, char *Str, int length, int n)
{
	// 验证输入的指针是否有效，任何一个为空则打印错误信息并返回错误码
	if (Arr == NULL || CodedStr == NULL || Str == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	HuffmanNode *Start;
	int i;

	// 遍历编码字符串，直到遇到字符串结束符'\0'
	for (i = 0; CodedStr[i] != 0;)
	{
		// 将Start重置为根节点，准备从根开始遍历哈夫曼树
		Start = Arr;

		// 当前节点有左右子节点时，继续向下遍历
		while (Start->left != NULL && Start->right != NULL)
		{
			// 根据编码字符串的当前字符（'0' 或 '1'）选择路径
			if (CodedStr[i] == '0')
				Start = Start->left; // 若为'0'，转向左子节点
			else if (CodedStr[i] == '1')
				Start = Start->right; // 若为'1'，转向右子节点
			i++;					  // 移动到编码字符串的下一个字符
		}

		// 当到达叶子节点时，打印该节点的字符，即为解码出的一个字符
		printf("%c", Start->character);
	}

	printf("\n");

	return (OK);
}

/*
// 打印原始报文字符串(旧版)
int PrintString(HuffmanNode *Arr, char *CodedStr, char *Str, int length, int n)
{
	// 当字符集大小不为1时，执行过滤空格并打印字符的操作
	if (n != 1)
	{
		int i;
		// 遍历字符串
		for (i = 0; i < length; i++)
		{
			// 如果当前字符不是空格，则打印该字符
			if (Str[i] != ' ')
				printf("%c", Str[i]);
		}
	}
	// 在输出结束后打印换行符
	printf("\n");

	return (OK);
}
*/

// 释放由HuffmanNode和CodeTable结构体数组占用的内存
int FreeMemory(HuffmanNode *Arr, CodeTable *Code, char *CodedStr, int n)
{
	if (Arr == NULL || Code == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	int i;

	// 释放哈夫曼树节点数组的内存
	free(Arr);

	// 遍历编码表，释放每个编码字符串分配的内存
	for (i = 0; i < n; i++)
		free(Code[i].code);

	// 释放编码表数组本身的内存
	free(Code);

	// 释放编码后的报文字符串的内存
	free(CodedStr);

	return (OK);
}
