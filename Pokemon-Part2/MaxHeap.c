/*
 * MaxHeap.c
 *
 *  Created on: Dec 12, 2021
 *      Author: ise
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "MaxHeap.h"
#include "Defs.h"

struct maxHeap
{
	element* array;
	int max_size;
	int counter;
	equalFunction equalfunc;
	copyFunction copyFunc;
	char* heap_name;
	freeFunction freeFunc;
	printFunction printfunc;

};




ph CreateHeap(int max_size,equalFunction equalfunc,char* heap_name,copyFunction copyFunc,freeFunction freeFunc,printFunction printfunc)
{
	struct maxHeap * pm=(ph)malloc(sizeof(struct maxHeap));
	pm->counter=0;
	pm->equalfunc=equalfunc;
	pm->copyFunc=copyFunc;
	pm->freeFunc=freeFunc;
	pm->printfunc=printfunc;
	pm->max_size=max_size+1;
	pm->heap_name=(char*)malloc(sizeof(char)*(strlen(heap_name)+1));
	strcpy(pm->heap_name,heap_name);
	pm->array=(element*)malloc(sizeof(element)*(max_size+1));
	return pm;

}

void destroyHeap(ph  ph)
{
	if(ph==NULL)
		return;
	int i;
	for(i=1;i<ph->counter+1;i++)
	{
		ph->freeFunc(ph->array[i]);
	}

	if(ph!=NULL)
	{
		free(ph->array);
		free(ph->heap_name);
		free(ph);
		ph=NULL;
	}

}

void Swapfunc(element element1,element element2,ph ph,int i)
{
	int parent ;
	if(i%2==0)
		parent= i/2;
	else
	{
		parent=(i-1)/2;
	}

	element temp=ph->array[i];
	ph->array[i]=ph->array[parent];
	ph->array[parent]=temp;


}

status insertToHeap(ph ph,element element1)
{

	ph->counter+=1;
	if(ph->counter==ph->max_size)
		return failure;
	int i=ph->counter;
	ph->array[i]=ph->copyFunc(element1);
	int parent ;
	element LeftChild;
	element RightChild;
	if(i%2==0)
		parent= i/2;
	else
	{
		parent=(i-1)/2;
	}
	LeftChild =ph->array[i];
	RightChild=ph->array[parent];

	while(parent>0 && ph->equalfunc(LeftChild,RightChild)==1)
	{
		 Swapfunc(LeftChild,LeftChild, ph, i);

		i=parent;
		LeftChild =ph->array[i];
		if(i%2==0)
		{
			parent= i/2;
			RightChild=ph->array[parent];
		}

		else
		{
			parent=(i-1)/2;
			RightChild=ph->array[parent];
		}
	}
	return success;

}

void printHeap(ph ph)
{
	int i;
	char * check_name1;
	check_name1=getHeapId(ph);
	printf("*%s*:\n",check_name1);
	if(ph->counter==0)
		printf("No elements.\n\n");
	else
	{
		struct maxHeap* temp_heap=copy_heap(ph );
		while(temp_heap->array[1]!=NULL)
		{
			for(i=1;i<ph->counter+2;i++)
			{
				if(temp_heap->array[i]==NULL)
					return;
				printf("%d. ",i);
				element elem;

				elem=PopMaxHeap(temp_heap);

				temp_heap->printfunc(elem);
			}


		}
		destroyHeap(temp_heap);

	}

}

element PopMaxHeap(ph ph)
{
	if(ph->counter==0)
		return NULL;
	element pop_elm;
	if(ph->counter<=0)
		return NULL;
	else
	{
		pop_elm=ph->array[1];
	}
	ph->array[1]=ph->array[ph->counter];
	ph->counter--;
	int i=1;
	int LeftChild=i*2;
	int RightChild=i*2+1;
	while(( LeftChild <=ph->counter && RightChild<=ph->counter)&&
			(ph->equalfunc(ph->array[i],ph->array[LeftChild])==-1 ||ph->equalfunc(ph->array[i],ph->array[RightChild] )==-1 ))
	{
		int minnumber;
		if(ph->equalfunc(ph->array[LeftChild],ph->array[RightChild])==-1)
		{
			minnumber=RightChild;
		}
		else
		{
			minnumber=LeftChild;
		}
		element temp=ph->array[minnumber];
		ph->array[minnumber]=ph->array[i];
		ph->array[i]=temp;
		i=minnumber;
		LeftChild=i*2;
		RightChild=i*2+1;
	}
	if(LeftChild <=ph->counter &&ph->equalfunc(ph->array[i],ph->array[LeftChild])==-1 )
	{

		element temp=ph->array[LeftChild];
		ph->array[LeftChild]=ph->array[i];
		ph->array[i]=temp;


	}

	return pop_elm;



}

element TopMaxHeap(ph ph)
{
	if(ph->counter==0)
		return NULL;
	//Element* PTopMax=(Element*)malloc(sizeof(Element));
	element* PTopMax;
	PTopMax=ph->array[1];
	return PTopMax;
}


char* getHeapId(ph ph)
{
//	char * name;
	//name=ph->copyFunc(ph->heap_name);
	return ph->heap_name;
}

int getHeapCurrentSize(ph ph)
{
	return ph->counter;
}



ph copy_heap(ph ph1)
{
	struct maxHeap* temp=(ph)malloc(sizeof(struct maxHeap));
	int i;
	temp->counter=0;
	temp->equalfunc=ph1->equalfunc;
	temp->copyFunc=ph1->copyFunc;
	temp->freeFunc=ph1->freeFunc;
	temp->printfunc=ph1->printfunc;
	temp->max_size=ph1->max_size;
	temp->heap_name=(char*)malloc(sizeof(char)*(strlen(ph1->heap_name)+1));
	strcpy(temp->heap_name,ph1->heap_name);
	temp->array=(element*)malloc(sizeof(element)*(ph1->max_size));

	for(i=1;i<ph1->counter+1;i++)
	{
		insertToHeap(temp,ph1->array[i]);
	}
	return temp;
	free(temp->heap_name);
	free(temp->array);
	free(temp);

}


void printHeap_help(ph ph)
{
	int i;
	if(ph->counter==0)
		printf("No elements.\n\n");
	else
	{
		struct maxHeap* temp_heap=copy_heap(ph );
		while(temp_heap->array[1]!=NULL)
		{
			for(i=1;i<ph->counter+1;i++)
			{
				if(temp_heap->array[i]==NULL)
					return;
				printf("%d. ",i);
				element elem;

				elem=PopMaxHeap(temp_heap);

				temp_heap->printfunc(elem);
			}
			if(i==ph->counter+1)
				break;


		}
		destroyHeap(temp_heap);

	}
}




