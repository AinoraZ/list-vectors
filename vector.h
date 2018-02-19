#ifndef VECTOR_H_
	#define VECTOR_H_

	struct elem{
	   int value;
	   struct elem *next;
	};

	typedef struct elem elem;

	struct vector{
		elem *head;
		elem *tail;
		unsigned int size;
	};

	typedef struct vector vector;

	vector* new_vector();
	int is_empty(int*, vector*);
	int size(int*, vector*);
	int is_full();
	int get_all(int**, vector*);
	int get(unsigned int, int*, vector*);
	int push(int, vector*);
	int pop(int*, vector*);
	int insert(unsigned int, int, vector*);
	int set(unsigned int, int, vector*);
	int remove_element(unsigned int, vector*);
	int remove_and_return(unsigned int, int*, vector*);
	int remove_all(vector*);
	int safe_free(vector**);

#endif
