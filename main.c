#include <stdio.h>
#include <stdlib.h>
#include "table.h"

void print_menu(void){
	printf("Select one of the following options\n");
	printf("0) Exit\n");
	printf("*1) Add element\n");
	printf("*2) Delete element\n");
	printf("*3) Delete element by ks1 key\n");
	printf("*4) Find element by ks1 key\n");
	printf("*5) Find element by ks2 key\n");
	printf("*6) Reorganize ks1\n");
	printf("7) Ks1 print\n");
	printf("8) Ks1 debug print\n");
	printf("9) Ks2 debug print\n");
}


void UI(void){
	int choice;
	Table *table = table_init();
	do{
		print_menu();
		do{
			get_int(&choice);
		} while (choice<0 || choice>9);
		switch (choice){
			case 0:{
				//
				break;
			}
			case 1:{
				table_add(table);
				break;
			}
			case 2:{
				table_del(table);
				break;
			}
			case 3:{
				table_del_by_ks1(table);
				break;
			}
			case 4:{
				find_by_ks1_key(table);
				break;
			}
			case 5:{
				find_by_ks2_key(table);
				break;
			}
			case 6:{
				table_reorganize_ks1(table);
				break;
			}
			case 7:{
				table_ks1_print(table);
				break;
			}
			case 8:{
				table_ks1_debug_print(table);
				break;
			}
			case 9:{
				table_ks2_debug_print(table);
				break;
			}

		}
	} while (choice!=0);
}



int main(void){
	printf("Start\n");
	
	UI();
	
	printf("End\n");
	return 0;
}

