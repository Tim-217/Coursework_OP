#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <malloc.h>
typedef struct
{	
	char name[100];
	char ingredients[500];
	char prigotov[1000];

}RECEPT;
int N;//������� ��������� � ����
void menu()
{
	printf("��� ������ ������ �������� ������� s\n");
	printf("��� ������ ������� ������� ������� v\n");
	printf("��� ���������� ������ ������� ������� d\n");
	printf("��� �������� ������� ������� u\n");
	printf("��� ������ �� ������������ ������� p\n");
	printf("��� ������ �� ��������� ������ ������� x\n\n");
}
void sort(RECEPT *recept)//������� ����������
{
	RECEPT p;
	int i, j, minp;
	for (i = 0; i < N; i++)
	{
		minp = i;
		for (j = i + 1; j < N; j++)
			if (strcmp(recept[minp].name, recept[j].name) > 0)
				minp = j;
		p = recept[minp];
		recept[minp] = recept[i];
		recept[i] = p;
	}
}
void search(RECEPT *recept)//������� ������
{
	system("cls");
	menu();
	char word1[20], word2[20], word3[20];
	int flag = 0;
	printf("������� �������� ������ ������������ (���� ��� ����� ����� ���� ��� ��� �����������, �� � ������ �������� ��������� Enter)\n");
	printf("���������� 1: ");
	gets(word1);
	if (strlen(word1) == 0)
	{
		printf("������ �����. ����������, ���������� ��� ���\n");
		return;
	}
	printf("���������� 2: ");
	gets(word2);
	printf("���������� 3: ");
	gets(word3);
	for (int i = 0; i < N; i++)
	{
		if (strstr(recept[i].ingredients, word1) && strstr(recept[i].ingredients, word2) && strstr(recept[i].ingredients, word3))
		{
			printf("%d %s", i + 1, recept[i].name);
			flag = 1;
		}

	}
	if (flag == 0)
		printf("�������� � ������ ����������� ���");
}
void print(RECEPT* recept)//������� ������ ���� ��������� ����
{
	system("cls");
	menu();
	for (int i = 0; i < N; i++)
		printf("%d %s", i + 1, recept[i].name);
}
void dobav(RECEPT** recept, int *n)//������� ���������� �������� � ����
{
	if (N == *n)
	{
		RECEPT* tmp = realloc(*recept, ((*n)+1) * sizeof(RECEPT));
		*n = *n + 1;
		if (tmp == NULL)
		{
			printf("������ ��������� ������\n");
			return 1;
		}
		*recept = tmp;
	}
	system("cls");
	menu();
	printf("��������: ");
	gets((*recept)[N].name);
	if (strlen((*recept)[N].name) == 0)
	{
		printf("\n��� ����� ��������� ������. ����������, ���������� ��� ���\n");
		return;
	}
	(*recept)[N].name[strcspn((*recept)[N].name, "\0")] = '\n';
	(*recept)[N].name[strcspn((*recept)[N].name, "\n")+1] = '\0';
	printf("�����������: ");
	gets((*recept)[N].ingredients);
	(*recept)[N].ingredients[strcspn((*recept)[N].ingredients, "\0")] = '\n';
	(*recept)[N].ingredients[strcspn((*recept)[N].ingredients, "\n")+1] = '\0';
	printf("�������������: ");
	gets((*recept)[N].prigotov);
	(*recept)[N].prigotov[strcspn((*recept)[N].prigotov, "\0")] = '\n';
	(*recept)[N].prigotov[strcspn((*recept)[N].prigotov, "\n")+1] = '\0';
	N++;
	sort(*recept);
	printf("\n��� ������ ��������\n");
}
void del(RECEPT* recept)//������� �������� �������� �� ���� �� ��������� ������
{
	system("cls");
	menu();
	int i;
	printf("������� ����� ���������� �������: ");
	scanf("%d", &i);
	if (i < 1 || i > N)
	{
		printf("������ � ������ ������� �� ����������\n");
		return;
	}
	for (i--; i < N - 1; i++)
		recept[i] = recept[i + 1];
	N--;
	printf("\n������ ������\n");
}
void vivod(RECEPT* recept)//������� ��� ������ ������� �� ��������� ������
{
	system("cls");
	menu();
	int i;
	printf("������� ����� ������� �������: ");
	scanf("%d", &i);
	if (i < 1 || i > N)
	{
		printf("������ � ������ ������� �� ����������\n");
		return;
	}
	else
	{
		printf("��������: %s", recept[i - 1].name);
		printf("�����������: %s", recept[i - 1].ingredients);
		printf("�������������: %s", recept[i - 1].prigotov);
	}
}
void open(RECEPT** recept, int* n)//������� ��� ���������� ����
{
	FILE* f = fopen("base.dat", "r+");
	if (f == NULL)
	{
		fprintf(stderr, "������ ��� �������� �����\n");
		return;
	}
	while (!feof(f))
	{
		if (N == *n)
		{
			RECEPT* tmp = realloc(*recept, ((*n) + 1) * sizeof(RECEPT));
			*n = *n + 1;
			if (tmp == NULL)
			{
				printf("������ ��������� ������\n");
				return 1;
			}
			*recept = tmp;
		}
		fgets((*recept)[N].name, sizeof((*recept)[N].name), f);
		fgets((*recept)[N].ingredients, sizeof((*recept)[N].ingredients), f);
		fgets((*recept)[N].prigotov, sizeof((*recept)[N].prigotov), f);
		N++;
	}
	fclose(f);
	sort(*recept);
	menu();
}
void save(RECEPT* recept)//������� ��� ���������� ����
{
	FILE* f = fopen("base.dat", "w+");
	int i;
	for (i = 0; i < N; i++)
		fprintf(f, "%s%s%s", recept[i].name, recept[i].ingredients, recept[i].prigotov);
	fclose(f);
}
int main(void)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int n = 15;//����������, ������������ ������ ����
	RECEPT *recept =(RECEPT*)malloc(n*sizeof(RECEPT));
	if (recept == NULL)
	{
		printf("������ ��������� ������\n");
		return 1;
	}
	open(&recept, &n);//���������� ������ �� ����� � �� �������� � ���� ������
	while (1)
	{
		switch (getch())
		{
		case 's': print(recept); break;
		case 'v': vivod(recept); break;
		case 'd': dobav(&recept, &n); break;
		case 'u': del(recept); break;
		case 'p': search(recept); break;
		case 'x': save(recept); free(recept); return 0;
		}
	}
}