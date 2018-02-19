/* 	@list-vectors
	@author: Copyright (C) Ainoras Žukauskas (ainoraz@gmail.com)
	@identficiation: VU MIF PS 4 grupė 2 pogrupis
	@@

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in all
	copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
	SOFTWARE.
*/

#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

vector* new_vector(){
	/*
		Creates new vector containing head, tail and size information

		@param		NONE
		@return		Address to new vector or NULL
		@output 	NONE
	*/

	vector *info = (vector*) malloc(sizeof(vector));

	if(info == NULL)
		return info;

	(info)->head = NULL;
	(info)->tail = NULL;
	(info)->size = 0;
	return info;
}

int __empty(vector *info){
	return info->size <= 0;
}

int is_empty(int *out, vector *info){
	/*
		Checks if vector is empty

		@param		address of int for output, address of vector
		@return		1 on error or 0 on success
		@output	 	1 on empty or 0 on not empty
	*/

	if(info == NULL || out == NULL)
		return 1;

	*out = __empty(info);
	return 0;
}

int size(int *out, vector *info){
	/*
		Checks the size of vector

		@param		address of int for output, address of vector
		@return		1 on error or 0 on success
		@output 	the size of vector or not changed
	*/

	if(info == NULL || out == NULL)
		return 1;

	*out = info->size;
	return 0;
}

int is_full(){
	/*
		Checks if memory is full

		@param:		NONE
		@return:	1 if full, 0 if not full
		@output: 	NONE
	*/

	elem *node = (elem*) malloc(sizeof(elem));

	if(node == NULL)
		return 1;

	free(node);
	return 0;
}

int __get_adress(unsigned int index, elem **out, vector info){
	unsigned int counter = 0;
	elem *node = info.head;

	if(index < 0)
		return 1;

	if(index >= info.size)
		return 1;

	while(counter != index){
		if(!(node = node->next))
			return 1;
		counter++;
	}

	*out = node;
	return 0;
}

int get_all(int **out, vector *info){
	/*
		Gets all elements in the vector

		@param:		address of pointer to int, address of vector
		@return:	1 on error or 0 on success
		@output: 	address of array containing all elements in vector or NULL
	*/

	elem *node;
	unsigned int counter;

	if(info == NULL || out == NULL)
		return 1;

	if(__empty(info) == 1)
		return 1;

	*out = (int*) malloc(sizeof(int) * info->size);
	if(*out == NULL)
		return 1;

	node = info->head;
	for(counter = 0; counter < info->size; counter++){
		(*out)[counter] = node->value;
		node = node->next;
	}

	return 0;
}

int get(unsigned int index, int *out, vector *info){
	/*
		Gets specific element of the vector

		@param:		index of element to get, address of int for output,
					address of vector
		@return:	1 on error or 0 on success
		@output: 	value of specified element or not changed
	*/

	elem *head;

	if(info == NULL || out == NULL)
		return 1;

	if(index < 0)
		return 1;

	if(__get_adress(index, &head, *info) == 1)
		return 1;

	*out = head->value;
	return 0;
}

int push(int value, vector *info){
	/*
		Inserts value to the end of the vector

		@param:		value to store, address of vector
		@return:	1 on error or 0 on success
		@output: 	NONE
	*/

	if(info == NULL)
		return 1;

	return insert(info->size, value, info);
}

int pop(int *out, vector *info){
	/*
		Gets value of last element in vector and removes it

		@param:		address of int for output, address of vector
		@return:	1 on error or 0 on success
		@output: 	value of last element or not changed
	*/

	if(out == NULL || info == NULL)
		return 1;

	return remove_and_return((info->size) - 1, out, info);
}

int insert(unsigned int index, int value, vector *info){
	/*
		Insert element to given index

		@param:		index of insertion, value to be inserted, address of vector
		@return:	1 on error or 0 on success
		@output: 	NONE
	*/

	elem *prev, *temp_node, *node;

	if(info == NULL)
		return 1;

	if(index < 0)
		return 1;

	if(index > info->size)
		return 1;

	node = (elem*) malloc(sizeof(elem));
	if(node == NULL)
		return 1;

	node->value = value;
	node->next = NULL;
	if(index == 0){							/* Inserting to 1st position */
		if(__empty(info) == 1){				/* To empty array */
			info->head = node;
			info->tail = node;
			(info->size)++;
			return 0;
		}
		temp_node = info->head;				/* To non-empty array */
		node->next = temp_node;
		info->head = node;
		(info->size)++;
		return 0;
	}

	if(index == info->size){				/* To non-empty array's tail */
		(info->tail)->next = node;
		info->tail = node;
		(info->size)++;
		return 0;
	}

	if(__get_adress(index-1, &prev, *info) == 1)
		return 1;

	temp_node = prev->next;					/* In the middle */
	prev->next = node;
	node->next = temp_node;
	(info->size)++;
	return 0;
}

int set(unsigned int index, int value, vector *info){
	/*
		Set element in given index

		@param:		index for setting, value to be set, address of vector
		@return:	1 on error or 0 on success
		@output: 	NONE
	*/

	elem *node;

	if(info == NULL)
		return 1;

	if(index < 0)
		return 1;

	if(index >= info->size)
		return 1;

	if(__get_adress(index, &node, *info) == 1)
		return 1;

	node->value = value;
	return 0;
}

int remove_element(unsigned int index, vector *info){
	/*
		Remove element in given index

		@param:		index for removal, address of vector
		@return:	1 on error or 0 on success
		@output: 	NONE
	*/

	elem *node, *temp_node;

	if(info == NULL)
		return 1;

	if(index < 0)
		return 1;

	if(index >= info->size)
		return 1;

	if(index == 0){							/* Removing the first element */
		temp_node = info->head;
		info->head = temp_node->next;
		free(temp_node);
		(info->size)--;

		if(__empty(info)){					/* If empty after removal */
			info->head = NULL;
			info->tail = NULL;
		}

		return 0;
	}

	if(__get_adress(index-1, &node, *info) == 1)
		return 1;

	temp_node = node->next;					/* The element to be removed */
	if(index == (info->size) - 1){			/* If removing last element */
		node->next = NULL;
		info->tail = node;
	}
	else									/* Removing middle element */
		node->next = (node->next)->next;

	free(temp_node);
	(info->size)--;
	return 0;
}

int remove_and_return(unsigned int index, int *out, vector *info){
	/*
		Remove element at given index

		@param:		index for removal, address of int for output,
					address of vector
		@return:	1 on error or 0 on success
		@output: 	value of removed element
	*/

	int value, err;

	if(info == NULL || out == NULL)
		return 1;

	if(index < 0)
		return 1;

	if(index >= info->size)
		return 1;

	get(index, &value, info);
	err = remove_element(index, info);
	if(err == 0)
		*out = value;

	return err;
}

int remove_all(vector *info){
	/*
		Remove all elements from vector

		@param:		address of vector
		@return:	1 on error or 0 on success
		@output: 	NONE
	*/

	elem *node;

	if(info == NULL)
		return 1;

	if(__empty(info) == 1)
		return 0;

	if(info->size == 1){
		free(info->head);
		info->head = NULL;
		info->tail = NULL;
		info->size = 0;
		return 0;
	}

	info->size = 0;

	node = info->head;
	while(node->next){
		node = node->next;
		free(info->head);
		info->head = node;
	}

	free(node);
	info->head = NULL;
	info->tail = NULL;
	return 0;
}

int safe_free(vector **info){
	/*
		Remove all elements from vector and free vector

		@param:		address of pointer to vector
		@return:	1 on error or 0 on success
		@output: 	pointer to vector is set to NULL or not changed
	*/

	if(*info == NULL)
		return 1;

	if(remove_all(*info) == 1)
		return 1;

	free(*info);
	*info = NULL;
	return 0;
}
