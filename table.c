#include "keyspace1.h"
#include "keyspace2.h"

Table *_initTable(){
	Table *table = (Table*)malloc(sizeof(Table));
	table->msize1 = MAXSIZE1;
	table->csize1 = 0;
	table->ks1 = (KeySpace1*)malloc(table->msize1 * sizeof(KeySpace1));
	for (int i=0; i<table->msize1; i++){
		table->ks1[i].busy = 0;
	};
	table->msize2 = MAXSIZE2;
	table->csize2 = 0;
	table->ks2 = (List_ks2**)malloc(table->msize2 * sizeof(List_ks2*));
	for (int i=0; i<table->msize2; i++){
		table->ks2[i] = NULL;
	}
	return table;
}


InfoType *_initInfo(int first_number, int second_number, char *string){
	InfoType *info = (InfoType*)malloc(sizeof(InfoType));
	info->first_number = first_number;
	info->second_number = second_number;
	info->string = string;
	return info;
}


Item *_initItem(InfoType * info, KeyType1 key1, KeyType2 key2){
	Item *item = (Item*)malloc(sizeof(Item));
	item->next = NULL;
	item->info = info;
	memcpy(item->key1, key1, KEY1LEN*sizeof(char));
	item->key2 = key2;
	return item;
}


int _clearItem(Item *item){
	free(item->info->string);
	free(item->info);
	free(item);
	return 0;
}


Item *_findByPairKey(Table *table, KeyType1 key1, KeyType2 key2){
	if (table->csize1>0){
		List_nd2 *list = NULL;
		list = _getListByKey2(table, key2);
		if (list){
			int release = _getReleaseByKey1(list, key1);
			if (release>=0){
				Node2 *node2 = NULL;
				_takeFromKeyList(list, release, &node2);
				return node2->info;
			}
		}	
	}
	return NULL;
}


int _delFromTable(Table *table, KeyType1 key1, KeyType2 key2){
	if (table->csize1>0){
		List_nd2 *list = NULL;
		list = _getListByKey2(table, key2);
		if (list){
			int release = _getReleaseByKey1(list, key1);
			if (release>=0){
				Node2 *node2 = NULL;
				_takeFromKeyList(list, release, &node2);
				Item *item = node2->info;
				_delFromKs1(table, key1);
				_delFromKs2(table, key2, release);
				_clearItem(item);
				table->csize1--;
				table->csize2--;
				return 0;
			}
		}
	}
	return -1;
}


int _addInTable(Table *table, Item *item){
	if (table->csize1<table->msize1 && table->csize2<table->msize2){
		if (!_checkKey1(table, item->key1)){
			_addInKs1(table, item, item->key1);
			table->csize1++;
			_addInKs2(table, item, item->key2);
			table->csize2++;
			return 0;
		}
	}
	return -1;
}


int _delFromTableByKey1(Table *table, KeyType1 key1){
	if (table->csize1>0){
		if (_checkKey1(table, key1)==1){
			Item *item = _getItemByKey1(table, key1);
			_delFromKs1(table, key1);
			KeyType2 key2 = item->key2;
			List_nd2 *list_nd2 = _getListByKey2(table, key2);
			int release = _getReleaseByKey1(list_nd2, key1);
			_delFromKs2(table, key2, release);
			_clearItem(item);
			table->csize1--;
			table->csize2--;
			return 0;
		}
	}
	return -1;
}


int _delFromTableByKey2(Table *table, KeyType2 key2, int release){
	if (table->csize1 > 0){
		Item *item = _getItemByKey2(table, key2, release);
		if (item){
			_delFromKs2(table, key2, release);
			_delFromKs1(table, item->key1);
			_clearItem(item);
			table->csize1--;
			table->csize2--;
			return 0;
		}
	}
	return -1;
}


int _delAllFromTableByKey2(Table *table, KeyType2 key2){
	if (table->csize1>0){
		List_nd2 *list = NULL;
		list = _getListByKey2(table, key2);
		if (list){
			int len = _lenKeyList(list);
			for (int i=0; i<len; i++){
				Item *item = NULL;
				Node2 *node2 = NULL;
				_takeFromKeyList(list, 0, &node2);
				item = node2->info;
				_delFromKs2(table, key2, 0);
				_delFromKs1(table, item->key1);
				_clearItem(item);
				table->csize1--;
				table->csize2--;
			}
			return 0;
		}
	}
	return -1;
}


int _clearTable(Table *table){
	if (table){
		for (int i=0; i<table->msize1; i++){
			if (table->ks1[i].busy==1){
				_clearItem(table->ks1[i].info);
			}
		}
		free(table->ks1);
		for (int i=0; i<table->msize2; i++){
			if (table->ks2[i]!=NULL){
				_clearHashList(table->ks2[i]);
			}
		}
		free(table->ks2);
		free(table);
		return 0;
	}
	return -1;
}




