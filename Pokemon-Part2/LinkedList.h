/*
 * LinkedList.h
 *
 *  Created on: Dec 10, 2021
 *      Author: ise
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "Defs.h"
#include "MaxHeap.h"

typedef struct LinkedList * ls;
typedef struct node * Nd;




ls createLinkedList(copyFunction copyFunc,	freeFunction freeFunc,printFunction printfunc,equalFunction equalfunc);
struct node* creatnode(element data,struct node* next);
void destroyList(ls ls);
void appendNode(ls ls,element element);
status deleteNode(ls ls,element element);
void displayList(ls ls);
element searchByKeyInList(ls ls,element element);
element searchByIndexInList(ls ls , int index);
element list(ls ls );

#endif /* LINKEDLIST_H_ */
