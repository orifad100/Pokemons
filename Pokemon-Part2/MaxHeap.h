/*
 * MaxHeap.h
 *
 *  Created on: Dec 12, 2021
 *      Author: ise
 */

#ifndef MAXHEAP_H_
#define MAXHEAP_H_
#include "Defs.h"


typedef struct maxHeap* ph;

ph CreateHeap(int max_size,equalFunction equalFunc,char* heap_name,copyFunction copyFunc,freeFunction freeFunc,printFunction printfunc);
void destroyHeap(ph  ph);
status insertToHeap(ph ph,element element);
void Swapfunc(element element1,element element2,ph ph,int i);
void printHeap(ph ph);
element PopMaxHeap(ph ph);
element TopMaxHeap(ph ph);
char* getHeapId(ph ph);
int getHeapCurrentSize(ph ph);
ph copy_heap(ph ph);
void printHeap_help(ph ph);

#endif /* MAXHEAP_H_ */
