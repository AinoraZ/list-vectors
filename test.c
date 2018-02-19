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

#include <stdio.h>
#include <stdlib.h>

#include "vector.h"

void print_vector(int *arr, vector *info){
	unsigned int index;
	printf("Current arr : ");
	for(index = 0; index < info->size; index++){
		printf("%d ", arr[index]);
	}
	printf("\n");
}

void get_and_print(int **arr, vector *info){
	if(!get_all(arr, info)){
		print_vector(*arr, info);
		free(*arr);
	}
}

int main(){
	vector *vec = new_vector();
	int out, *arr;

	printf("Test  0: ");						/* New vector creation test */
	if(vec != NULL)
		printf("%s\n", "OK ");
	else
		printf("ERR\n");
	printf("\n");

	/* NO ELEMENTS */
		printf("Test  1: ");					/* Is vector empty?*/
		if(!is_empty(&out, vec))
			printf("%s %d\n", "OK, OUTPUT: ", out);
		else
			printf("ERR\n");
		printf("\n");


		printf("Test  2: ");
		if(!get_all(&arr, vec))					/* Get 0 elements (ERROR) */
			printf("%s\n", "BAD");
		else
			printf("ERR (OK)\n");
		printf("\n");


		printf("Test  3: ");
		safe_free(&vec);
		if(vec == NULL)							/* Free empty vector */
			printf("OK\n");
		else
			printf("ERR\n");
		printf("\n");


		printf("Test  4: ");
		if(!safe_free(&vec))					/* Free non-existent vec (ERR) */
			printf("BAD\n");
		else
			printf("ERR (OK)\n");
		printf("\n");
	/* NO ELEMENTS END*/


	/* PUSH/POP/GET/GET_ALL*/
		vec = new_vector();

		/* PUSH */
		printf("Test  5: ");
		if(!push(5, vec))						/* Push operation test */
			printf("%s\n", "OK ");
		else
			printf("ERR\n");

		get_and_print(&arr, vec);				/* Get all elements and print */
		printf("Expected out: 5\n");
		printf("\n");


		printf("Test  6: ");					/* Push beyond first element */
		push(4, vec);
		push(3, vec);
		push(6, vec);

		get_and_print(&arr, vec);
		printf("         Expected out: 5 4 3 6\n");
		printf("\n");
		/* PUSH END */

		/* GET */


		printf("Test  7: ");					/* Get first element */
		if(!get(0, &out, vec))
			printf("%s\n", "OK ");
		else
			printf("ERR\n");
		printf("\n");

		printf("Test  8: ");					/* Get element beyond first */
		if(!get(3, &out, vec))
			printf("%s\n", "OK ");
		else
			printf("ERR\n");
		printf("\n");


		printf("Test  9: ");					/* Get non-existent (ERR)*/
		if(!get(4, &out, vec))
			printf("%s\n", "BAD");
		else
			printf("ERR (OK)\n");
		printf("\n");
		/* GET END*/

		/* NON EMPTY IS_EMPTY */
		printf("Test 10: ");					/* Check non empty vector */
		is_empty(&out, vec);
		if(!out)
			printf("%s\n", "OK ");
		else
			printf("ERR\n");
		printf("\n");
		/* NON EMPTY IS_EMPTY END*/

		/* POP */
		printf("Test 11: ");					/* Pop non-first element */
		if(!pop(&out, vec))
			printf("%s %d\n", "OK, OUTPUT:", out);
		else
			printf("ERR\n");
		printf("%s\n", "    EXPECTED OUTPUT: 6");
		printf("\n");


		printf("Test 12: ");					/* Pop first element */
		pop(&out, vec);
		pop(&out, vec);
		if(!pop(&out, vec) && vec->head == NULL  && vec->tail == NULL)
			printf("%s %d\n", "OK, OUTPUT:", out);
		else
			printf("ERR\n");
		printf("%s\n", "    EXPECTED OUTPUT: 5");
		printf("\n");

		/* POP END */
	/* PUSH/POP/GET/GET_ALL END */

	/* INSERT/SET/REMOVE */
		/* INSERT */
		printf("Test 13: ");					/* Insert to bad index */
		if(!insert(1, 2, vec))
			printf("%s\n", "BAD");
		else
			printf("ERR (OK)\n");
		printf("\n");


		printf("Test 14: ");					/* Insert first element */
		if(!insert(0, 1, vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		printf("\n");

		get_and_print(&arr, vec);
		printf("Expected out: 1\n");
		printf("\n");


		printf("Test 15: ");					/* Insert tail element */
		if(!insert(1, 3, vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		get_and_print(&arr, vec);
		printf("Expected out: 1 3\n");
		printf("\n");


		printf("Test 16: ");					/* Check tail element */
		if((vec->tail)->value == 3)
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		printf("\n");


		printf("Test 17: ");					/* Insert middle element */
		if(!insert(1, 2, vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		get_and_print(&arr, vec);
		printf("Expected out: 1 2 3\n");
		printf("\n");
		/* INSERT END */

		/* SET */
		printf("Test 18: ");					/* Set middle element */
		if(!set(1, -2, vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		get_and_print(&arr, vec);
		printf("Expected out: 1 -2 3\n");
		printf("\n");


		printf("Test 19: ");					/* Set first element */
		if(!set(0, 0, vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		get_and_print(&arr, vec);
		printf("Expected out: 0 -2 3\n");
		printf("\n");


		printf("Test 20: ");					/* Set last element */
		if(!set(2, 4, vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		get_and_print(&arr, vec);
		printf("Expected out: 0 -2 4\n");
		printf("\n");


		printf("Test 21: ");
		if(!set(3, 500, vec))					/* Set non-existent (ERROR) */
			printf("%s\n", "BAD");
		else
			printf("ERR (OK)\n");
		get_and_print(&arr, vec);				/* Output does not change */
		printf("Expected out: 0 -2 4\n");
		printf("\n");
		/* SET END */

		/* REMOVE */
		printf("Test 22: ");
		if(!remove_element(1, vec))				/* Remove middle element */
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		get_and_print(&arr, vec);
		printf("Expected out: 0 4\n");
		printf("\n");


		printf("Test 23: ");					/* Remove last element */
		if(!remove_element(1, vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		get_and_print(&arr, vec);
		printf("Expected out: 0\n");
		printf("\n");


		printf("Test 24: ");					/* Remove only element */
		if(!remove_element(0, vec) && vec->head == NULL && vec->tail == NULL)
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		printf("\n");

		printf("Test 25: ");					/* Remove first element */
		insert(0, 1, vec);
		insert(1, 5, vec);
		insert(1, 2, vec);
		insert(2, 3, vec);
		insert(3, 4, vec);

		if(!remove_element(0, vec) && vec->head != NULL && vec->tail != NULL)
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		get_and_print(&arr, vec);
		printf("Expected out: 2 3 4 5\n");
		printf("\n");


		printf("Test 26: ");					/* Remove and return element */
		/* Iternally: remove_element() and get(), multiple tests not needed */
		if(!remove_and_return(0, &out, vec))
			printf("%s %d\n", "OK, OUTPUT", out);
		else
			printf("ERR\n");
		printf("      Expected out: 2\n");
		get_and_print(&arr, vec);
		printf("Expected out: 3 4 5\n");
		printf("\n");


		printf("Test 27: ");					/* Clear vector */
		if(!remove_all(vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		printf("\n");

		printf("Test 28: ");						/* Size */
		if(!size(&out, vec))
			printf("%s %d\n", "OK, OUTPUT", out);
		else
			printf("ERR\n");
		printf("Expected out: 0\n");
		printf("\n");

		printf("Test 29: ");					/* Clear empty vector (OK) */
		if(!remove_all(vec))
			printf("%s\n", "OK");
		else
			printf("ERR\n");
		printf("\n");

		/* REMOVE */
	/* INSERT/SET/REMOVE/REMOVE_AND_RETURN END/REMOVE_ALL*/

	insert(0, 1, vec);
	insert(1, 5, vec);
	insert(1, 2, vec);
	insert(2, 3, vec);
	insert(3, 4, vec);

	printf("Test 30: ");						/* Size */
	if(!size(&out, vec))
		printf("%s %d\n", "OK, OUTPUT", out);
	else
		printf("ERR\n");
	printf("Expected out: 5\n");
	printf("\n");

	printf("Test 31: ");						/* Check if full */
	if(!is_full())
		printf("%s\n", "NOT FULL");
	else
		printf("FULL\n");
	printf("\n");

	printf("Test 32: ");						/* Clear all and free */
	if(!safe_free(&vec))
		printf("%s\n", "OK");
	else
		printf("ERR\n");
	printf("\n");

	return 0;
}
