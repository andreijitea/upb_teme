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

// Destructor de lista
void list_destructor(void *list) {
    free(((array_t *)list)->data);
}

// Destructor de student
void student_destructor(void *stud) {
    free(((student_t *)stud)->name);
}

// Destructor de string
void string_destructor(void *elem) {
    free(*(char **)elem);
}

// Inverseaza (n-1) numere din lista
void inverse_num(void *old_p, void *elem) {
    int pos = *(int*)elem - 1;
    *((int*)elem + 1) = pos;
    old_p = (int *)old_p + pos;
    *(int*)elem = *(int*)old_p;
}



array_t reverse(array_t list) {
	array_t new_list = generate_list(list.len, list.elem_size, list.destructor);
    *(int*)new_list.data = new_list.len;
    new_list.len--;
    reduce(inverse_num, list.data, new_list);
    new_list.len++;
    // Inverseaza numarul (n)
    *((int*)new_list.data + new_list.len - 1) = *(int*)list.data;
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

// Extrage numele din lista
void get_name(void *new_p, void *elem) {
    strcpy(new_p, ((student_t *)elem)->name);
}

// Alterneaza 0 si 1 in lista
void set_parity(void *elem) {
    if (*(int*)elem == 0)
        *(int*)(elem+sizeof(int)) = 1;
}

// Verifica conditia cerintei
boolean check_string(void *elem) {
    if (**(char**)elem != 0)
        return 1;
    else
        return 0;
}

// Seteaza numele intr-un element al listei
void set_string(void *new_p, void **elem) {
    char **s = (char **)new_p;
    *s = malloc(100);
    if (*(int*)elem[1] == 0)
        strcpy(*s, *(char **)elem[0]);
    else
        memset(*s, 0, 100);
}

array_t get_even_indexed_strings(array_t list) {
    array_t parity_list = generate_list(list.len, sizeof(int), NULL);
    parity_list.len--;
    for_each(set_parity, parity_list);
    parity_list.len++;

    array_t aux_list = map_multiple(set_string, sizeof(char*), string_destructor, 2, list, parity_list);
    array_t new_list = filter(check_string, aux_list);

	return new_list;
}

// Genereaza o lista pentru fiecare element al altei liste
void apply_generator(void *elem) {
	*(array_t *)elem = generate_list(1, sizeof(array_t), NULL);
}



// Seteaza o coloana de numere din matrice
void set_col(void *elem) {
	static int i;
	if (!elem) {
		i = 0;
		return;
	}
	if (!i)
		i = *(int *)elem;
	*(int *)elem = i++;
}

// Seteaza numerele matricei
void set_nums(void *list) {
	int i;
	*(int *)((array_t *)list)->data = i;
	for_each(set_col, *(array_t *)list);
	set_col(NULL);
}

void set_size(void *elem) {
}

array_t generate_square_matrix(int n) {
	array_t new_list_list = generate_list(n, sizeof(array_t), list_destructor);
    for_each(set_size, new_list_list);
	for (int i = 0; i < n; i++) {
		*(array_t *)(new_list_list.data + i * sizeof(array_t)) =
				generate_list(n, sizeof(array_t), NULL);
	}
	for_each(set_nums, new_list_list);
	return new_list_list;
}
