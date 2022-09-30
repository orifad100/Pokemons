/*
 * BattleByCategory.c
 *
 *  Created on: Dec 14, 2021
 *      Author: ise
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Defs.h"
#include "BattleByCategory.h"
#include "LinkedList.h"
#include "MaxHeap.h"
#include "Pokemon.h"



struct battle_s
{
	struct LinkedList *linkedlist;
	equalFunction equalElementB;
	copyFunction copyElementB;
	freeFunction freeElementB;
	getCategoryFunction getCategoryB;
	getAttackFunction getAttackB;
	printFunction printElementB;
	int capacity;
	int numberOfCategories;
	char* categories;
};


Battle createBattleByCategory(int capacity,int numberOfCategories,char* categories,equalFunction equalElement,copyFunction copyElement,
		freeFunction freeElement,getCategoryFunction getCategory,getAttackFunction getAttack,printFunction printElement)
{
	char psik[5]=",";
	char * token;
	Battle pb=(Battle)malloc(sizeof(struct battle_s));
	if(pb==NULL)
		return NULL;

	pb->equalElementB=equalElement;
	pb->copyElementB=copyElement;
	pb->freeElementB=freeElement;
	pb->getCategoryB=getCategory;
	pb->getAttackB=getAttack;
	pb->printElementB=printElement;
	pb->capacity=capacity;
	pb->numberOfCategories=numberOfCategories;
	pb->categories=categories;


	pb->linkedlist =createLinkedList(copyElement, freeElement,printElement, equalElement);
	char temparr[strlen(pb->categories)];
	strcpy(temparr,pb->categories);
	token=strtok(temparr,psik);
	int counter0=0;
	while(token!=NULL)
	{
		ph maxheap=CreateHeap(pb->capacity, equalElement,token, copyElement, freeElement, printElement);
		element elem3 =pb->copyElementB(maxheap);
		appendNode(pb->linkedlist , elem3);
		counter0++;

		token = strtok(NULL, psik);
	}
	if (pb->linkedlist==NULL)
		return NULL;
	return pb;
}




status destroyBattleByCategory(Battle b)
{
	int i;
	if(b==NULL)
		return failure;
	for(i=0;i<b->numberOfCategories;i++)
	{
		struct maxHeap* heapi;
		heapi=(struct maxHeap*)searchByIndexInList(b->linkedlist,i);
		destroyHeap(heapi);
	}


	destroyList(b->linkedlist);
	free(b);
	return success;
}

status insertObject(Battle b, element elem)
{
	int i,counter1=0;
	char * type_elem ;
	char * check_name;
	int count_heap;
	type_elem=b->getCategoryB(elem);
	for(i=0;i<b->numberOfCategories;i++)
	{

		struct maxHeap* heap=searchByIndexInList(b->linkedlist,i);
		check_name=getHeapId(heap);
		if(strcmp(type_elem,check_name)==0)
		{
			count_heap=getHeapCurrentSize(heap);
			if(count_heap<b->capacity)
			{
				insertToHeap(heap,elem);
				return success;
			}
			else
			{
				return failure;
			}

		}

		counter1++;
	}
	if(counter1==b->numberOfCategories-1)
		return failure;
	return 0;
}


 void displayObjectsByCategories(Battle b)
 {
 	int i;
 	char* check_name;
 	for(i=0;i<b->numberOfCategories;i++)
 	{
 		element heap1=searchByIndexInList(b->linkedlist,i);
 		check_name=getHeapId((ph)heap1);
 		printf("%s:\n",check_name);
 		printHeap_help(heap1);
 	}
  }


 element removeMaxByCategory(Battle b,char* category)
 {
	 int i;
	 element elem;
	 char* check_name2;
	 int count_heap;
	 for(i=0;i<b->numberOfCategories;i++)
	 {
		 struct maxHeap* heap=searchByIndexInList(b->linkedlist,i);
		 check_name2=getHeapId(heap);
		 if(strcmp(category,check_name2)==0)
		 {
			 count_heap=getHeapCurrentSize(heap);
			 if(count_heap>0)
			 {
					elem= PopMaxHeap(heap);
					return elem;

			 }
			 else
			 {
				 return NULL;
			 }
		 }



	 }
	 return 0;
 }

 int getNumberOfObjectsInCategory(Battle b,char* category)
 {
	 int i;
	 char* check_name;
	 int count_heap;
	 for(i=0;i<b->numberOfCategories;i++)
	 {
		 struct maxHeap* heap=searchByIndexInList(b->linkedlist,i);
		check_name=getHeapId(heap);
		if(strcmp(category,check_name)==0)
		 {
			count_heap=getHeapCurrentSize(heap);
			return count_heap;
		 }
	 }
	 return count_heap;

 }


 element fight(Battle b,element elem)
 {

	 int i,j;
	 int num1=0;
	 int num2=0;
	 int num3=0;
	 int* attackFirst=&num1;
	 int* attackSecond=&num2;
	 char* elem_type=b->getCategoryB(elem);
	 element arr[b->numberOfCategories];
	 for(i=0;i<b->numberOfCategories;i++)
	 {
		 struct maxHeap* heap=searchByIndexInList(b->linkedlist,i);
		 element elem2=TopMaxHeap(heap);
		 arr[i]=elem2;
	 }
	 element max_elem;
	 max_elem=arr[0];
	 for(j=0;j<b->numberOfCategories;j++)
	 {
		 if(arr[j]!=NULL)
		 {
			 if(b->equalElementB(max_elem,arr[j])==-1)
			 		max_elem=arr[j];
		 }
		 else
		 {
			num3++;
		 }

	 }
	 if(num3==b->numberOfCategories)
	 {
		 printf("There are no Pokemons to fight against you.\n");
		 return NULL;
	 }

	 char* max_elem_type=b->getCategoryB(max_elem);
	 b->getAttackB(elem,max_elem,attackFirst,attackSecond);
	 for(j=0;j<b->numberOfCategories;j++)
	 {
		 if(arr[j]!=NULL)
		 {

			 if(*attackSecond< get_attack(arr[j]))
			 {
				 max_elem=arr[j];
				 b->getAttackB(elem,max_elem,attackFirst,attackSecond);
			 }

		 }

	 }

	 printf("The final battle between:\n");
	 b->printElementB(elem);
	 printf("In this battle his attack is :%d\n\n",*attackFirst);
	 printf("against ");
	 b->printElementB(max_elem);
	 printf("In this battle his attack is :%d\n\n", *attackSecond);
	 if(* attackFirst-*attackSecond>0)
	 {
		 printf("THE WINNER IS:\n");
		 b->printElementB(elem);
		 return elem;
	 }
	 if(* attackFirst-*attackSecond<0)
	 {
		 printf("THE WINNER IS:\n");
		 b->printElementB(max_elem);
		 return max_elem;
	 }
	 else
		 printf("IT IS A DRAW.\n");
	 return max_elem;


 }













