/***************************************************************
* Wordmorph @ AED-Project 2016-2017
* by
* Madalena Muller & Mariana Martins
*
* heap.c
* All functions auxiliary for running dijkstra
****************************************************************/

#include "heap.h"

struct _heap_element {
	int dic_index;
	int weight;
};

struct _path_element {
	int total_weight;
	int parent;
};


/************************* HASH TABLE ***************************/

int *create_hash_table(int n_elements) {

	int *hash_table = NULL;

	hash_table = (int *)calloc(n_elements, sizeof(int));
	if(hash_table == NULL)
		memory_error("Unable to reserve hash table memory");

	return hash_table;
}

int get_hash_table_value(int i, int *hash_table) {
	return hash_table[i];
}

void set_hash_table_value(int _value, int i, int *hash_table) {
	hash_table[i] = _value;
}

/********************* HASH FUNCTIONS ***************************/

void swap_hash_values(int *hash_table, int i, int j) {

	int temp = 0;
	temp = hash_table[i];
	hash_table[i] = hash_table[j];
	hash_table[j] = temp;
	return;
}

void print_hash_table(int *hash_table, int size) {
	int i = 0;
	spam(("HASH TABLE\n"));
	for (i = 0; i < size; ++i) {
		spam((KRED"dic_index=%d : heap_vector_pos=%d \n"RESET,
			i, hash_table[i]));
	}
}

/*********************** PATH VECTOR ***************************/

path_element *create_path_vector(int n_elements) {

	path_element *path_vector = NULL;

	path_vector = (path_element *)malloc(n_elements*sizeof(path_element));
    if (path_vector == NULL) {
        memory_error("Unable to reserve heap_vector memory");
    }
    return path_vector;
}

path_element get_path_vector_element(int i, path_element *path_vector) {
	return path_vector[i];
}

/********************* PATH VECTOR ELEMENT **********************/

int get_path_element_total_weight(int i, path_element *path_vector) {
	return path_vector[i].total_weight;
}

int get_path_element_parent(int i, path_element *path_vector) {
	return path_vector[i].parent;
}

void set_path_element_total_weight(int _total_weight, int i, path_element *path_vector) {
	path_vector[i].total_weight = _total_weight;
}

void set_path_element_parent(int _parent, int i, path_element *path_vector) {
	path_vector[i].parent =_parent;
}

void print_path_vector(path_element *path_vector, int size) {
	int i = 0;
	spam(("PATH VECTOR\n"));
	for (i = 0; i < size; ++i) {
		spam((KGRN"%d : total_weight=%d parent=%d\n"RESET,
			i, path_vector[i].total_weight, path_vector[i].parent));
	}
}

/************************ HEAP VECTOR ***************************/

heap_element *create_heap_vector(int n_elements) {

	heap_element *heap_vector = NULL;

	heap_vector = (heap_element *)malloc(n_elements*sizeof(heap_element));
    if (heap_vector == NULL) {
        memory_error("Unable to reserve heap_vector memory");
    }
    return heap_vector;
}

heap_element get_heap_vector_element(int i, heap_element *heap_vector) {
	return heap_vector[i];
}

/******************** HEAP VECTOR ELEMENT ***********************/

int get_heap_element_dic_index(int i, heap_element *heap_vector) {
	return heap_vector[i].dic_index;
}

int get_heap_element_weight(int i, heap_element *heap_vector) {
	return heap_vector[i].weight;
}

void set_heap_element_dic_index(int _dic_index, int i, heap_element *heap_vector) {
	heap_vector[i].dic_index =_dic_index;
}

void set_heap_element_weight(int _weight, int i, heap_element *heap_vector) {
	heap_vector[i].weight =_weight;
}

/*********************** HEAP FUNCTIONS ************************/

void print_heap_vector(heap_element *heap_vector, int size) {
	int i = 0;
	spam(("HEAP\n"));
	for (i = 0; i <= size; i++) {
		spam((KYEL"%d : weight=%d dic_index=%d\n"RESET,
			i, heap_vector[i].weight, heap_vector[i].dic_index));
	}
}

void initialize_heap(int size, int *hash_table, path_element *path_vector, heap_element *heap_vector) {

	int i = 0;
	while(i<size+1) {
		if(i<size) {
			path_vector[i].parent = ORFAN;
			path_vector[i].total_weight = INF;
			hash_table[i] = i+1;
		}
		heap_vector[i].dic_index = i-1;
		heap_vector[i].weight = INF;
		i++;
	}
	return;
}

void swap_heaps(heap_element *heap_vector, int i, int j) {

	heap_element aux_heap;

	aux_heap = heap_vector[i];
	heap_vector[i] = heap_vector[j];
	heap_vector[j] = aux_heap;
	return;	
}

void heapify(int i, int size, int *hash_table, heap_element *heap_vector) {

	/*While there is still a left child heap */
	while(2*i <= size) {
		/*If there is no right child heap */
		if((2*i)+1 > size) {
			/*Check if child heap is smaller than his parent*/
			if(heap_vector[i].weight > heap_vector[2*i].weight) {
				swap_hash_values(hash_table, 
					heap_vector[2*i].dic_index, 
					heap_vector[i].dic_index);
				swap_heaps(heap_vector, i, 2*i);
			}
			break;
		}
		/*If any of the children are smaller than their parent*/
		if(heap_vector[i].weight > heap_vector[2*i].weight ||
			heap_vector[i].weight > heap_vector[(2*i)+1].weight) {
			if(heap_vector[2*i].weight <= heap_vector[(2*i)+1].weight) {
				swap_hash_values(hash_table, 
					heap_vector[2*i].dic_index, 
					heap_vector[i].dic_index);
				swap_heaps(heap_vector, i, 2*i);
				i = 2*i;
			}
			else if(heap_vector[2*i].weight > heap_vector[(2*i)+1].weight) {
				swap_hash_values(hash_table, 
					heap_vector[(2*i)+1].dic_index, 
					heap_vector[i].dic_index);
				swap_heaps(heap_vector, i, (2*i)+1);
				i = (2*i)+1;
			}
		}
		/*Its already heapified!*/
		else 
			break;
	}
}

int get_first_heap_dic_index(int *hash_table, int size, heap_element *heap_vector) {

	heap_element first_heap;

	swap_hash_values(hash_table, heap_vector[1].dic_index, heap_vector[size].dic_index);
    first_heap = heap_vector[1];
    swap_heaps(heap_vector, 1, size);
    heapify(1, size-1, hash_table, heap_vector);
     
    return first_heap.dic_index;
}

/********************* DIJKSTRA ALGORITHM **********************/

void find_better_path(path_element *path_vector, int curr_heap_dic_index, adj_element *node, int *hash_table, heap_element *heap_vector) {

	int adj_weight = 0, adj_dic_index = 0, i = 0, new_weight = 0;

	adj_weight = get_adj_element_weight(node);
	adj_dic_index = get_adj_element_dic_index(node);
	new_weight = SUM(path_vector[curr_heap_dic_index].total_weight, adj_weight);

	/*If a new shorter path is discovered, define the new values for the variables*/
	if((path_vector[adj_dic_index].total_weight > new_weight) && 
		(path_vector[curr_heap_dic_index].total_weight != INF)) {

		path_vector[adj_dic_index].total_weight = new_weight;
		
		path_vector[adj_dic_index].parent = curr_heap_dic_index;
	
		i = hash_table[adj_dic_index];
		heap_vector[i].weight = path_vector[adj_dic_index].total_weight;

		/*Make the disordered "heap" into a heap again*/
		while(i > 1) {
			if(heap_vector[i].weight < heap_vector[i/2].weight) {
				swap_hash_values(hash_table, heap_vector[i].dic_index, heap_vector[i/2].dic_index);
				swap_heaps(heap_vector, i, i/2);
				i = i/2;
			}
			else
				break;
		}
	}
	return;
}