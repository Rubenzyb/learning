/*
��������
дһ����������ı�/����ϵͳ��Ҫ���ܶ�Ҫ����ı��Ľ��б���ͽ��롣
�����������ʱ��ȨֵС�ķ���������Ȩֵ��ķ�������������ʱ����������Ϊ 1 ������������Ϊ 0 �� 

����˵��
����˵����
�����ʾ�ַ�����СΪ n��n<=100������������
�Լ� n ���ַ��� n ��Ȩֵ����������ֵԽ���ʾ���ַ����ֵĸ���Խ�󣩣�
���봮��С�ڻ���� 100 ��Ŀ�걨�ġ�

���˵����
���������Ķ������룬ռһ�У�
�Լ���Ӧ�����ı��ģ�ռһ�У�
������һ���س�����
*/

// ���������ͷ�ļ�
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// �������״̬����
#define OK 0
#define ERROR 1

// �ṹ������
typedef struct HuffmanNode
{
	int weight;						  // Ȩֵ
	char character;					  // �������ʾ���ַ�
	struct HuffmanNode *left, *right; // ���ӣ��Һ���
} HuffmanNode;						  // �������������ݽṹ
typedef struct CodeTable
{
	int weight;		// Ȩֵ
	char character; // �ַ�
	char *code;		// ��Ӧ����
} CodeTable;		// ���������ݽṹ

// ��������
int InitialiseArray(HuffmanNode **, int);
int InitialiseCode(CodeTable **, HuffmanNode *, int);
int ConstHuffmanTree(HuffmanNode *, int);
int DetermineCode(int, int, char, char *, HuffmanNode *);
int PrintCode(CodeTable *, char **, char *, int, int);
int PrintString(HuffmanNode *, char *, char *, int, int);
int FreeMemory(HuffmanNode *, CodeTable *, char *, int);

int main()
{
	// ��������
	int n, i, tip;
	char Str[110] = {0}, *CodedStr; // Ŀ�걨���ַ���������ı����ַ���
	HuffmanNode *Arr;				// ���������ڵ�����
	CodeTable *Code;				// ��������

	// ��ȡ�ַ�����С
	scanf("%d ", &n);
	if (n <= 0 || n > 100)
	{
		// ��������ַ�����С���Ϸ�������
		printf("Invalid input!\n");
		return (ERROR);
	}

	// ��ʼ������
	tip = InitialiseArray(&Arr, n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// ��ʼ����������
	tip = InitialiseCode(&Code, Arr, n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// ������������
	tip = ConstHuffmanTree(Arr, n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// ����Ŀ�걨��
	getchar();
	scanf("%[^\n]", Str);
	if ((int)strlen(Str) > 100)
	{
		// ��������ַ������ȳ���100������
		printf("The input String is not legal!\n");
		return (ERROR);
	}

	// ȷ��ÿ���ַ��ı���
	for (i = 0; i < n; i++)
	{
		tip = DetermineCode(Code[i].weight, 0, Code[i].character, Code[i].code, &Arr[0]);
		if (tip == ERROR)
		{
			printf("Error in the function return result!\n");
			return (ERROR);
		}

		// ���·����ڴ�����Ӧ�����ַ����ĳ���
		char *temp = (char *)realloc(Code[i].code, (int)strlen(Code[i].code) + 1);
		if (temp == NULL)
		{
			// ����ڴ����ʧ�ܣ�����
			printf("Memory reallocation for code String failed!\n");
			return (ERROR);
		}
		else
			Code[i].code = temp;
	}

	// ��������Ķ�������
	tip = PrintCode(Code, &CodedStr, Str, (int)strlen(Str), n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// �����Ӧ�����ı���
	tip = PrintString(Arr, CodedStr, Str, (int)strlen(Str), n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// �ͷŶ�̬������ڴ�
	tip = FreeMemory(Arr, Code, CodedStr, n);
	if (tip == ERROR)
	{
		printf("Error in the function return result!\n");
		return (ERROR);
	}

	// �������
	return (OK);
}

// Ϊ����������̬�����ڴ沢��ʼ�����нڵ㣬�����������ַ���Ȩֵ�����Ȩֵ����ڵ㡣
int InitialiseArray(HuffmanNode **Arr, int n)
{
	// ȷ��ָ����Ч
	if (Arr == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	int i, j;

	// ��̬������������ڵ����飬�ܽڵ���Ϊn-1��Ҷ�ӽڵ����n-1���ڲ��ڵ�
	(*Arr) = (HuffmanNode *)calloc(2 * n - 1, sizeof(HuffmanNode));
	// ȷ���ڴ����ɹ�
	if ((*Arr) == NULL)
	{
		printf("Memory allocation for Huffman tree nodes failed!\n");
		return (ERROR);
	}

	// ���������ַ���Ȩֵ
	for (i = 0; i < n; ++i)
	{
		scanf("%c ", &(*Arr)[i].character);
	}
	for (i = 0; i < n; ++i)
	{
		scanf("%d", &(*Arr)[i].weight);
	}

	// ����Ȩֵʹ��ð�����򷨽��ڵ������������
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

// Ϊ�����Ĺ��������ڵ����鴴��һ����Ӧ�ı����ṹ�������ַ���Ȩֵ�����롣
int InitialiseCode(CodeTable **Code, HuffmanNode *Arr, int n)
{
	// ȷ��ָ����Ч
	if (Code == NULL || Arr == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	int i, j;

	// ��̬������������
	(*Code) = (CodeTable *)calloc(n, sizeof(CodeTable));
	// ȷ���ڴ����ɹ�
	if ((*Code) == NULL)
	{
		printf("Memory allocation for CodeTable failed!\n");
		return (ERROR);
	}

	// Ϊ������е�ÿһ����Ŀ��̬�����ַ������ַ������ڴ�
	for (i = 0; i < n; i++)
	{
		(*Code)[i].code = (char *)calloc(n, sizeof(char));
		// ȷ���ڴ����ɹ�
		if ((*Code)[i].code == NULL)
		{
			printf("Memory allocation for code String failed!\n");
			// ���ĸ�����ʧ�ܾ��ͷ�֮ǰ�ɹ����������code�ַ����ڴ�
			for (j = 0; j < i; j++)
				free((*Code)[j].code);
			// ����ͷ�CodeTable����
			free(*Code);
			return (ERROR);
		}
	}

	// ��ʼ��������ÿ����Ŀ
	for (i = 0; i < n; i++)
	{
		// �����ַ���Ȩֵ
		(*Code)[i].weight = Arr[i].weight;
		(*Code)[i].character = Arr[i].character;
	}

	return (OK);
}

// �����ṩ���ַ�Ȩֵ��������һ�ù�����������Ϊÿ���ڵ���������ӽڵ�
int ConstHuffmanTree(HuffmanNode *Arr, int n)
{
	// ȷ��ָ����Ч
	if (Arr == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	int i, j, t;

	// �ϲ���СȨֵ�������ڵ㣬�����½ڵ㣬���µ�����ĩβ
	for (i = n - 1, t = n; i >= 1 && t < 2 * n - 1; i--, t++)
	{
		// �½ڵ�����Ϊ���ַ��ڵ㣨��0��ʾ��
		Arr[t].character = 0;
		// ȨֵΪǰ������С�ڵ�Ȩֵ֮��
		Arr[t].weight = Arr[i].weight + Arr[i - 1].weight;

		// ��֤�²���Ľڵ㰴Ȩֵ����
		for (j = t; j >= 1; j--)
		{
			if (Arr[j].weight > Arr[j - 1].weight)
			{
				// ����Ԫ����ά������
				HuffmanNode agency = Arr[j];
				Arr[j] = Arr[j - 1];
				Arr[j - 1] = agency;
			}
		}
	}

	// Ϊÿ���ڲ��ڵ���������ӽڵ�
	HuffmanNode *Temp1 = &Arr[1]; // ��һ���ڵ��ָ��
	HuffmanNode *Temp2 = &Arr[2]; // �ڶ����ڵ��ָ��
	for (i = 0; (i < 2 * n - 1) && (Temp2 <= &Arr[2 * n - 2]); i++)
	{
		if (Arr[i].weight == Temp1->weight + Temp2->weight)
		{
			// ��ǰ�ڵ��Ȩֵ�����������ڵ�Ȩֵ֮��ʱ����������
			Arr[i].right = Temp1; // ���ӽڵ�
			Arr[i].left = Temp2;  // ���ӽڵ�
			Temp1 += 2;			  // �ƶ�����һ�����ܵ����ӽڵ�
			Temp2 += 2;			  // �ƶ�����һ�����ܵ����ӽڵ�
		}
	}

	return (OK);
}

// �ݹ��Ϊָ���ַ��������ڹ��������е�·��������¼Ϊ�����Ʊ���
int DetermineCode(int weight, int count, char character, char *code, HuffmanNode *Temp)
{
	// �����ǰ�ڵ���Ҷ�ӽڵ㣨�������ӽڵ㣩���ҼȲ�������Ҫ�ҵ��ַ������ش�����
	if (Temp->left == NULL && Temp->right == NULL)
		return (ERROR);

	// �����ǰ�ڵ�����ӽڵ�ƥ�䣨Ȩֵ���ַ�����ͬ�������¼'0'�����سɹ�
	else if (Temp->left->weight == weight && Temp->left->character == character)
	{
		code[count] = '0';
		return (OK);
	}

	// �����ǰ�ڵ�����ӽڵ�ƥ�䣬��¼'1'�����سɹ�
	else if (Temp->right->weight == weight && Temp->right->character == character)
	{
		code[count] = '1';
		return (OK);
	}

	// �ݹ����������
	if (Temp->left != NULL)
	{
		code[count] = '0'; // ��������ߣ���¼'0'
		int tip = DetermineCode(weight, count + 1, character, code, Temp->left);
		// ������������ҵ����ַ������سɹ�
		if (tip == OK)
			return (OK);
		else
			code[count] = 0; // ����Ϊ�գ��Ա㳢��������
	}

	// ��������δ�ҵ�������������
	if (Temp->right != NULL)
	{
		code[count] = '1'; // �������ұߣ���¼'1'
		int tip = DetermineCode(weight, count + 1, character, code, Temp->right);
		// ������������ҵ����ַ������سɹ�
		if (tip == OK)
			return (OK);
		else
			code[count] = 0; // ����Ϊ�գ��Ա㷵����һ��
	}

	// �������������û���ҵ��ַ������ش���
	return (ERROR);
}

// ��ӡ�����ı����ַ���
int PrintCode(CodeTable *Code, char **CodedStr, char *Str, int length, int n)
{

	// ȷ��ָ����Ч
	if (Code == NULL || Str == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	// ��̬��������ı����ַ����ڴ�
	*CodedStr = (char *)calloc(length * n, sizeof(char));
	if (*CodedStr == NULL)
	{
		// ����ڴ����ʧ�ܣ�����
		printf("Memory allocation for CodedStr failed!\n");
		return (ERROR);
	}

	int i, j, current_index = 0; // current_index���ڼ�¼��ǰ�����ı����ַ����ĳ���

	// ����ԭʼ�����ַ���������ַ����б���
	for (i = 0; i < length; i++)
	{
		int tip = 0;

		// �����ո�
		if (Str[i] == ' ')
			continue;

		// ������������Ҷ�Ӧ�ַ�
		for (j = 0; j < n; j++)
		{
			// ����ҵ��˶�Ӧ�ַ������������ӵ������ı����ַ�����
			if (Str[i] == Code[j].character)
			{
				strcpy((*CodedStr) + current_index, Code[j].code); // ֱ�Ӹ��Ʊ��뵽��ǰλ��
				current_index += strlen(Code[j].code);			   // ���µ�ǰд��λ��
				tip = 1;
				break;
			}
		}

		// ���û���ҵ���Ӧ�ַ�������
		if (tip == 0)
		{
			printf("Character not found in CodeTable!\n");
			return (ERROR);
		}
	}

	// ���·����ڴ�����Ӧ�����ı����ַ����ĳ���
	char *temp = (char *)realloc(*CodedStr, (int)strlen(*CodedStr) + 1);
	if (temp == NULL)
	{
		// ����ڴ����·���ʧ�ܣ�����
		printf("Memory reallocation for CodedStr failed!\n");
		return (ERROR);
	}
	else
		*CodedStr = temp;

	// ��ӡ�����ı����ַ���
	printf("%s\n", *CodedStr);

	return (OK);
}

// ��ӡԭʼ�����ַ������°溯��
int PrintString(HuffmanNode *Arr, char *CodedStr, char *Str, int length, int n)
{
	// ��֤�����ָ���Ƿ���Ч���κ�һ��Ϊ�����ӡ������Ϣ�����ش�����
	if (Arr == NULL || CodedStr == NULL || Str == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	HuffmanNode *Start;
	int i;

	// ���������ַ�����ֱ�������ַ���������'\0'
	for (i = 0; CodedStr[i] != 0;)
	{
		// ��Start����Ϊ���ڵ㣬׼���Ӹ���ʼ������������
		Start = Arr;

		// ��ǰ�ڵ��������ӽڵ�ʱ���������±���
		while (Start->left != NULL && Start->right != NULL)
		{
			// ���ݱ����ַ����ĵ�ǰ�ַ���'0' �� '1'��ѡ��·��
			if (CodedStr[i] == '0')
				Start = Start->left; // ��Ϊ'0'��ת�����ӽڵ�
			else if (CodedStr[i] == '1')
				Start = Start->right; // ��Ϊ'1'��ת�����ӽڵ�
			i++;					  // �ƶ��������ַ�������һ���ַ�
		}

		// ������Ҷ�ӽڵ�ʱ����ӡ�ýڵ���ַ�����Ϊ�������һ���ַ�
		printf("%c", Start->character);
	}

	printf("\n");

	return (OK);
}

/*
// ��ӡԭʼ�����ַ���(�ɰ�)
int PrintString(HuffmanNode *Arr, char *CodedStr, char *Str, int length, int n)
{
	// ���ַ�����С��Ϊ1ʱ��ִ�й��˿ո񲢴�ӡ�ַ��Ĳ���
	if (n != 1)
	{
		int i;
		// �����ַ���
		for (i = 0; i < length; i++)
		{
			// �����ǰ�ַ����ǿո����ӡ���ַ�
			if (Str[i] != ' ')
				printf("%c", Str[i]);
		}
	}
	// ������������ӡ���з�
	printf("\n");

	return (OK);
}
*/

// �ͷ���HuffmanNode��CodeTable�ṹ������ռ�õ��ڴ�
int FreeMemory(HuffmanNode *Arr, CodeTable *Code, char *CodedStr, int n)
{
	if (Arr == NULL || Code == NULL)
	{
		printf("Invalid pointer!\n");
		return (ERROR);
	}

	int i;

	// �ͷŹ��������ڵ�������ڴ�
	free(Arr);

	// ����������ͷ�ÿ�������ַ���������ڴ�
	for (i = 0; i < n; i++)
		free(Code[i].code);

	// �ͷű�������鱾����ڴ�
	free(Code);

	// �ͷű����ı����ַ������ڴ�
	free(CodedStr);

	return (OK);
}
