/*
 * Defs.h
 *
 *  Created on: Nov 26, 2021
 *      Author: ise
 */

#ifndef _DEFS_H
#define _DEFS_H

typedef enum e_bool { False, True } Bool;
typedef enum e_status { success, failure } status;
typedef void * element;
typedef element(*copyFunction) (element);
typedef void(*freeFunction) (element);
typedef void(*printFunction) (element);
typedef int(*equalFunction) (element, element);
typedef char*(*getCategoryFunction)(element);
typedef int(*getAttackFunction)(element firstElem ,element secondElem ,int* attackFirst,int* attackSecond);
element copyheap(element);
void freeheap(element);
void printheapext(element );
int equalheaps(element elem1,element elem2);


#endif /* DEFS_H_ */
