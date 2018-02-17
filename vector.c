#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

vector* new_vector(){
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
	if(info == NULL || out == NULL)
		return 1;

	*out = __empty(info);
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
	elem *node;
	unsigned int counter;

	if(info == NULL || out == NULL)
		return 1;

	if(__empty(info))
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
	return insert(info->size, value, info);
}

int pop(int *out, vector *info){
	/*
		Input: 	Address of output storage, Vector head info
		Output: Popped value, Updated vector
		Return: Error code
	*/
	if(out == NULL)
		return 1;
	return remove_and_return((info->size) - 1, out, info);
}

int insert(unsigned int index, int value, vector *info){
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

	if(index == 0){
		if(__empty(info)){
			info->head = node;
			info->tail = node;
			(info->size)++;
			return 0;
		}
		temp_node = info->head;
		node->next = temp_node;
		info->head = node;
		(info->size)++;
		return 0;
	}

	if(index == info->size){
		(info->tail)->next = node;
		info->tail = node;
		(info->size)++;
		return 0;
	}

	if(__get_adress(index-1, &prev, *info) == 1)
		return 1;

	temp_node = prev->next;
	prev->next = node;
	node->next = temp_node;
	(info->size)++;

	return 0;
}

int set(unsigned int index, int value, vector *info){
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
	elem *node, *temp_node;

	if(info == NULL)
		return 1;

	if(index < 0)
		return 1;

	if(index >= info->size)
		return 1;

	if(index == 0){
		temp_node = info->head;
		info->head = temp_node->next;
		free(temp_node);
		(info->size)--;

		if(__empty(info)){
			info->head = NULL;
			info->tail = NULL;
		}

		return 0;
	}

	if(__get_adress(index-1, &node, *info) == 1)
		return 1;

	temp_node = node->next;
	if(index == (info->size) - 1){
		node->next = NULL;
		info->tail = node;
	}
	else
		node->next = (node->next)->next;

	free(temp_node);
	(info->size)--;

	return 0;
}

int remove_and_return(unsigned int index, int *out, vector *info){
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
	elem *node;

	if(info == NULL)
		return 1;

	if(__empty(info))
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
	if(*info == NULL)
		return 1;

	if(remove_all(*info))
		return 1;

	free(*info);
	*info = NULL;
	return 0;
}
