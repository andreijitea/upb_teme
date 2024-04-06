#include "functional.h"
#include "tasks.h"
#include "tests.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// Genereaza o lista
array_t generate_list(int len, int elem_size, void (*destructor)(void *)) {
    array_t list;
    list.elem_size = elem_size;
    list.len = len;
    list.destructor = destructor;
    list.data = malloc(list.len * list.elem_size);
    memset(list.data, 0, list.len * list.elem_size);
    return list;
}

// Schimba 2 elemente ale listei intre ele
void switch_elem(void *elem) {
    void *aux = malloc(sizeof(void*));
    memset(aux, 0, sizeof(void*));
    memcpy(aux, elem, sizeof(int));
    memcpy(elem, elem+sizeof(int), sizeof(int));
    memcpy(elem+sizeof(int), aux, sizeof(int));
    free(aux);
}



array_t reverse(array_t list) {
	// Inverseaza in loc lista data
    int len = list.len;
    for (int i = 0; i < len; i++) {
        list.len--;
        for_each(switch_elem, list);
    }
    list.len = len;
    array_t new_list = generate_list(list.len, list.elem_size, list.destructor);
    memcpy(new_list.data, list.data, list.len * list.elem_size);

	return new_list;
}

// Produce un element al listei de numere
void create_number(void *new_p, void **elem) {
	((number_t *)new_p)->integer_part = *(int *)elem[0];
	((number_t *)new_p)->fractional_part = *(int *)(elem[0] + sizeof(int));
	((number_t *)new_p)->string = malloc(sizeof(char *));
	sprintf(((number_t *)new_p)->string, "%d.%d",
			((number_t *)new_p)->integer_part,
			((number_t *)new_p)->fractional_part);
}

// Destructor pentru un element al listei de numere
void free_number(void *elem) {
	free(((number_t *)elem)->string);
}

array_t create_number_array(array_t integer_part, array_t fractional_part) {
	array_t new_list = map_multiple(create_number, sizeof(number_t),
									free_number, 2, integer_part,
									fractional_part);
	return new_list;
}

// Produce un element al listei de nume
void create_st_name(void *new_p, void *elem) {
	((student_t *)new_p)->name = malloc(strlen(((student_t *)elem)->name)
			* sizeof(char *));
	strcpy(((student_t *)new_p)->name, ((student_t *)elem)->name);
}

// Destructor pentru un element al listei de nume
void free_st(void *elem) {
	free(((student_t *)elem)->name);
}

array_t get_passing_students_names(array_t list) {
	array_t new_list = map(create_st_name, sizeof(student_t),
						   free_st, list);
	return new_list;
}

// Calculeaza suma unei liste
void calc_sum(void *acc, void *elem) {
	*(int *)acc += *(int *)elem;
}

// Initializeaza lista sumelor
void create_sum_list(void *new_p, void *elem) {
	array_t aux_list = *(array_t *)elem;

	reduce(calc_sum, new_p, aux_list);
}

// Verifica daca suma este mai mare sau egala cu valoarea salvata
void check_sum(void *new_p, void **elem) {
	*(boolean *)new_p = (*(int *)((array_t *)elem)->data >=
			*(int *)(((array_t *)elem)->data + sizeof(int))) ? 1 : 0;
}

array_t check_bigger_sum(array_t list_list, array_t int_list) {
	array_t sum_list = map(create_sum_list, sizeof(int), NULL, list_list);
	array_t new_list = map_multiple(check_sum, sizeof(boolean),
									NULL, 2, sum_list, int_list);
	return new_list;
}

/*
 * Retine adresa capului listei, calculeaza pozitia
 * elementului in raport cu adresa capului listei
 */
boolean index_string(void *elem) {
	static void *p;
	if (!p)
		p = elem;
	if ((elem - p) / sizeof(student_t *) % 2 == 0)
		return 1;
	return 0;
}

array_t get_even_indexed_strings(array_t list) {
	array_t new_list = filter(index_string, list);
	return new_list;
}

//void set_col(void *elem) {
//    static void *p;
//    if (!p)
//        p = elem;
//    elem = (elem-p)/sizeof(array_t) + 1;
//    printf("%ld\n", (long)elem);
//}
//

//
//void apply_generator(void *elem) {
//    *(array_t*)elem = generate_list(0, sizeof(array_t), NULL);
//}
//
array_t generate_square_matrix(int n) {
//    array_t new_list_list = generate_list(n, sizeof(array_t), NULL);
//    for_each(apply_generator, new_list_list);
//    for_each(set_col, new_list_list);
//	return new_list_list;
    return (array_t){0};
}
