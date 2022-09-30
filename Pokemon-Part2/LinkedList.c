/*
 * LinkedList.c
 *
 *  Created on: Dec 10, 2021
 *      Author: ise
 */

#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"
#include "Defs.h"
#include "MaxHeap.h"
struct node
{
	element data;
	struct node* next;
};

struct LinkedList
{
	copyFunction copyFunc;
	freeFunction freeFunc;
	printFunction printfunc;
	equalFunction equalfunc;
	int size_ls;
	struct node* head;
};




ls createLinkedList(copyFunction copyFunc,	freeFunction freeFunc,printFunction printfunc,equalFunction equalfunc)
{
	if(copyFunc==NULL ||freeFunc==NULL|| printfunc==NULL)
		return NULL;
	ls pl=(ls)malloc(sizeof(struct LinkedList));
	if (pl==NULL)
		return NULL;
	pl->size_ls=0;
	pl->copyFunc= copyFunc;
	pl->freeFunc= freeFunc;
	pl->printfunc= printfunc;
	pl->equalfunc=equalfunc;
	pl->head=NULL;
	return pl ;

}

void destroyList(ls ls)
{
	int i;
	if(ls==NULL)
		return ;
	for(i=0;i<ls->size_ls;i++)
	{
		if(ls->head!=NULL)
		{
			free(ls->head);
			ls->head=ls->head->next;
		}
	}
	free(ls);
}

void appendNode(ls ls,element element1)

{
	if(ls==NULL)
		return;
	struct node* pn=(struct node*)malloc(sizeof(struct node));
	if(pn==NULL)
		return ;
	pn->data=ls->copyFunc( element1);
	pn->next=NULL;
	if(ls->size_ls==0)
	{
		ls->head=pn;
		ls->size_ls++;
		return;
	}
	else
	{
		struct node* temp1=ls->head;
		struct node* temp2=ls->head->next;
		if(temp2==NULL)
		{
			temp1->next=pn;
			ls->size_ls++;
			return;
		}
		while(temp2!=NULL)
		{
			temp2=temp2->next;
			temp1=temp1->next;
			if(temp2==NULL)
			{
				temp1->next=pn;
				ls->size_ls++;
				return;
			}
		}

	}
	free(pn);


}

status deleteNode(ls ls,element element_check)
{
	if(ls==NULL || element_check==NULL)
		return failure;
	if(ls->head==NULL)
		return failure;
	struct node* temp1;
	struct node* temp2;
	struct node* check;
	check=ls->head;
	temp1=ls->head;
	temp2=ls->head->next;
	int counter1;
	if(ls->equalfunc(temp1->data,element_check)==0)
	{
		ls->freeFunc(temp1->data);
		ls->head=temp2;
		free(temp1);
		ls->size_ls--;
		return success;
	}
	while(ls->equalfunc(check->data,element_check)!=0)
	{
		counter1++;
		check=check->next;
	}
	if(counter1==ls->size_ls)
		return failure;

	while(ls->equalfunc(temp2->data,element_check)!=0)
	{
		temp2=temp2->next;
		temp1=temp1->next;
	}
	if(temp2->next==NULL)
	{
		temp1->next=NULL;
		//free(temp2->data);
		ls->freeFunc(temp2->data);
		//free(temp2);
		free(temp2);
		ls->size_ls--;
		return success;
	}
	else
	{
		temp1->next=temp2->next;
		//free(temp2->data);
		ls->freeFunc(temp2->data);
		//free(temp2);
		free(temp2);
		ls->size_ls--;
		return success;
	}


}

void displayList(ls ls)
{
	if(ls==NULL)
		return;
	struct node* p_node=ls->head;
	int i;
	for (i = 0; i < ls->size_ls; ++i)
	{
		ls->printfunc(p_node->data);
		if (p_node->next != NULL)
				p_node = p_node->next;
	}
	printf("\n");
}

element searchByKeyInList(ls ls ,element elem)
{
	if(ls==NULL || elem==NULL)
		return NULL;
	int counter;
	struct node* node_search=ls->head;
	while(ls->equalfunc(node_search->data,elem)!=0)
	{
		node_search=node_search->next;
		counter++;
		if(node_search==NULL)
			return NULL;
	}
	return node_search;


}

element searchByIndexInList(ls ls , int index)
{
	if(ls==NULL || ls->size_ls <= index)
		return NULL;
	int counter=0;
	struct node* node_search=ls->head;
	while(counter < ls->size_ls)
	{
		if(counter == index)
			return node_search->data;
		node_search=node_search->next;
		counter++;
	}
	if(counter==ls->size_ls)
		return NULL;
	return node_search->data;

}

element list(ls ls )
{
	return ls->head->next->data;
}









