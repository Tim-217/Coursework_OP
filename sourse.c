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
int N;//счетчик элементов в базе
void menu()
{
	printf("Для вывода списка рецептов нажмите s\n");
	printf("Для вывода нужного рецепта нажмите v\n");
	printf("Для добавления нового рецепта нажмите d\n");
	printf("Для удаления рецепта нажмите u\n");
	printf("Для поиска по ингредиентам нажмите p\n");
	printf("Для выхода из программы дважды нажмите x\n\n");
}
void sort(RECEPT *recept)//функция сортировки
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
void search(RECEPT *recept)//функция поиска
{
	system("cls");
	menu();
	char word1[20], word2[20], word3[20];
	int flag = 0;
	printf("Введите названия нужных ингредиентов (если вам нужен всего один или два ингредиента, то в пустых позициях поставьте Enter)\n");
	printf("Ингредиент 1: ");
	gets(word1);
	if (strlen(word1) == 0)
	{
		printf("Ошибка ввода. Пожалуйста, попробуйте еще раз\n");
		return;
	}
	printf("Ингредиент 2: ");
	gets(word2);
	printf("Ингредиент 3: ");
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
		printf("Рецептов с данным игредиентом нет");
}
void print(RECEPT* recept)//функция вывода всех элементов базы
{
	system("cls");
	menu();
	for (int i = 0; i < N; i++)
		printf("%d %s", i + 1, recept[i].name);
}
void dobav(RECEPT** recept, int *n)//функция добавления элемента в базу
{
	if (N == *n)
	{
		RECEPT* tmp = realloc(*recept, ((*n)+1) * sizeof(RECEPT));
		*n = *n + 1;
		if (tmp == NULL)
		{
			printf("Ошибка выделения памяти\n");
			return 1;
		}
		*recept = tmp;
	}
	system("cls");
	menu();
	printf("Название: ");
	gets((*recept)[N].name);
	if (strlen((*recept)[N].name) == 0)
	{
		printf("\nПри вводе произошла ошибка. Пожалуйста, попробуйте еще раз\n");
		return;
	}
	(*recept)[N].name[strcspn((*recept)[N].name, "\0")] = '\n';
	(*recept)[N].name[strcspn((*recept)[N].name, "\n")+1] = '\0';
	printf("Ингредиенты: ");
	gets((*recept)[N].ingredients);
	(*recept)[N].ingredients[strcspn((*recept)[N].ingredients, "\0")] = '\n';
	(*recept)[N].ingredients[strcspn((*recept)[N].ingredients, "\n")+1] = '\0';
	printf("Приготовление: ");
	gets((*recept)[N].prigotov);
	(*recept)[N].prigotov[strcspn((*recept)[N].prigotov, "\0")] = '\n';
	(*recept)[N].prigotov[strcspn((*recept)[N].prigotov, "\n")+1] = '\0';
	N++;
	sort(*recept);
	printf("\nВаш рецепт добавлен\n");
}
void del(RECEPT* recept)//функция удаления элемента из базы по заданному номеру
{
	system("cls");
	menu();
	int i;
	printf("Введите номер удаляемого рецепта: ");
	scanf("%d", &i);
	if (i < 1 || i > N)
	{
		printf("Рецепт с данным номером не существует\n");
		return;
	}
	for (i--; i < N - 1; i++)
		recept[i] = recept[i + 1];
	N--;
	printf("\nРецепт удален\n");
}
void vivod(RECEPT* recept)//функция для вывода рецепта по заданному номеру
{
	system("cls");
	menu();
	int i;
	printf("Введите номер нужного рецепта: ");
	scanf("%d", &i);
	if (i < 1 || i > N)
	{
		printf("Рецепт с данным номером не существует\n");
		return;
	}
	else
	{
		printf("Название: %s", recept[i - 1].name);
		printf("Ингредиенты: %s", recept[i - 1].ingredients);
		printf("Приготовление: %s", recept[i - 1].prigotov);
	}
}
void open(RECEPT** recept, int* n)//функция для заполнения базы
{
	FILE* f = fopen("base.dat", "r+");
	if (f == NULL)
	{
		fprintf(stderr, "Ошибка при открытии файла\n");
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
				printf("Ошибка выделения памяти\n");
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
void save(RECEPT* recept)//функция для сохранения базы
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
	int n = 15;//переменная, определяющая размер базы
	RECEPT *recept =(RECEPT*)malloc(n*sizeof(RECEPT));
	if (recept == NULL)
	{
		printf("Ошибка выделения памяти\n");
		return 1;
	}
	open(&recept, &n);//извлечение данных из файла и их передача в базу данных
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