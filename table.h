#ifndef TABLE_H
#define TABLE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSIZE1 5
#define MAXSIZE2 5
#define KEY1LEN 23
typedef int RelType;
typedef int BusyType1;
typedef char KeyType1[KEY1LEN+1];
typedef unsigned KeyType2;
typedef int IndexType1;
typedef int IndexType2;

typedef struct{
	int first_number;
	int second_number;
	char *string;
} InfoType;

typedef struct _Item{
	InfoType *info;
	struct _Item *next;
	KeyType1 key1;
	KeyType2 key2;
} Item;

typedef struct{
		BusyType1 busy;
		KeyType1 key;
		Item *info;
} KeySpace1;

typedef struct _Node2{
		Item *info;
		struct _Node2 *next;
} Node2; // List_element

typedef struct{
	Node2 *head;
} List_nd2; // List одинаковых ключей

typedef struct _KeySpace2{
	KeyType2 key;
	List_nd2 *node;
	struct _KeySpace2 *next;
} KeySpace2; // List_element

typedef struct{
	KeySpace2 *head;
} List_ks2; // List

typedef struct{
		KeySpace1 	*ks1;	
		IndexType1 	msize1;
		IndexType1 	csize1;
		List_ks2 	**ks2;
		IndexType2 	msize2;
		IndexType2 	csize2;		
} Table;


Table *_initTable();
// Создание таблицы.

InfoType *_initInfo(int first_number, int second_number, char *string);
// Создание информации.

Item *_initItem(InfoType * info, KeyType1 key1, KeyType2 key2);
// Создание поля в таблице.

int _clearItem(Item *item);
// Очиста поля.

Item *_findByPairKey(Table *table, KeyType1 key1, KeyType2 key2);
// Поиск поля по двум ключам.

int _delFromTable(Table *table, KeyType1 key1, KeyType2 key2);
// Удаление из таблицы по двум ключам

int _addInTable(Table *table, Item *item);
// Добавление в таблицу поля.

int _delFromTableByKey1(Table *table, KeyType1 key1);
// Удаление из таблицы по ключу key1.

int _delFromTableByKey2(Table *table, KeyType2 key2, int release);
// Удаление из таблицы по ключу key2 и релизу.

int _delAllFromTableByKey2(Table *table, KeyType2 key2);
// Удаление из таблицы всех элементов по ключу key2.

int _clearTable(Table *table);
// Удаление всеё тааблицы.

#endif