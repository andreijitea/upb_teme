#include "functional.h"
#include "tasks.h"
#include "tests.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

array_t reverse(array_t list) {
	// Initializeaza o noua lista
	array_t new_list;
	new_list.destructor = list.destructor;
	new_list.elem_size = list.elem_size;
	new_list.len = list.len;
	new_list.data = malloc(new_list.elem_size * new_list.len);

	// Inverseaza elementele listei vechi si le introduce in lista noua
	void *new_p = new_list.data, *old_p = list.data;
	old_p = (char *)old_p + (list.len - 1) * list.elem_size;
	for (int i = 0; i < list.len; i++) {
		memcpy(new_p, old_p, list.elem_size);
		new_p = (char *)new_p + list.elem_size;
		old_p = (char *)old_p - list.elem_size;
	}

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

array_t check_bigger_sum(array_t list_list, array_t int_list) {
	(void)list_list;
	(void)int_list;
	return (array_t){0};
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

array_t generate_square_matrix(int n) {
	(void)n;
	return (array_t){0};
}
