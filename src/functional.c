#include "functional.h"
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#include <stdio.h>

void for_each(void (*func)(void *), array_t list)
{
	// Parcurge fiecare element al listei si aplica functia asupra lui
	void *elem = list.data;
	for (int i = 0; i < list.len; i++) {
		func(elem);
		elem = (char *)elem + list.elem_size;
	}
}

array_t map(void (*func)(void *, void *),
			int new_list_elem_size,
			void (*new_list_destructor)(void *),
			array_t list)
{
	// Initializeaza noua lista
	array_t new_list;
	new_list.len = list.len;
	new_list.elem_size = new_list_elem_size;
	new_list.destructor = new_list_destructor;
	new_list.data = malloc(new_list.len * new_list.elem_size);
	memset(new_list.data, 0, new_list.len * new_list.elem_size);
	// Calculeaza elementele noii liste, conform functiei date
	void *new_p = new_list.data, *old_p = list.data;
	for (int i = 0; i < list.len; i++) {
		func(new_p, old_p);
		new_p = (char *)new_p + new_list.elem_size;
		old_p = (char *)old_p + list.elem_size;
	}
	// Sterge lista veche
	void *elem = list.data;
	for (int i = 0; i < list.len; i++) {
		void *aux = elem;
		elem = (char *)elem + list.elem_size;
		list.destructor(aux);
	}
	free(list.data);
	return new_list;
}

array_t filter(boolean(*func)(void *), array_t list)
{
	// Initializeaza noua lista
	array_t new_list;
	new_list.len = 0;
	new_list.elem_size = list.elem_size;
	new_list.destructor = list.destructor;
	// Numara cate elemente indeplinesc conditia functiei date
	void *elem = list.data;
	for (int i = 0; i < list.len; i++) {
		if (func(elem))
			new_list.len++;
		elem = (char *)elem + list.elem_size;
	}
	// Initializeaza memoria pentru datele noii liste
	new_list.data = malloc(new_list.len * new_list.elem_size);
	/*
	 * Copiaza elementele, care indeplinesc conditia
	 * functiei date, in noua lista si elimina elemente
	 */
	void *new_p = new_list.data, *old_p = list.data;
	for (int i = 0; i < list.len; i++) {
		if (func(old_p)) {
			memcpy(new_p, old_p, new_list.elem_size);
			new_p = (char *)new_p + new_list.elem_size;
		} else {
			if (list.destructor)
				list.destructor(old_p);
		}
		old_p = (char *)old_p + list.elem_size;
	}
	free(list.data);
	return new_list;
}

void *reduce(void (*func)(void *, void *), void *acc, array_t list)
{
	/*
	 * Parcurge fiecare element al listei si
	 * modifica acumulatorul conform functiei date
	 */
	void *elem = list.data;
	for (int i = 0; i < list.len; i++) {
		func(acc, elem);
		elem = (char *)elem + list.elem_size;
	}
	return acc;
}

void for_each_multiple(void(*func)(void **), int varg_c, ...)
{
	array_t lists[varg_c];
	int min_len = 99999;
	va_list ptr;
	va_start(ptr, varg_c);
	// Salveaza listele intr-un vector 'lists'
	for (int i = 0; i < varg_c; i++)
		lists[i] = va_arg(ptr, array_t);

	va_end(ptr);
	// Calculeaza lungimea minima a listelor
	for (int i = 0; i < varg_c; i++) {
		if (min_len > lists[i].len)
			min_len = lists[i].len;
	}

	/*
	 * Parcurge fiecare element al tuturor listelor, in paralel,
	 * si aplica functia asupra lui
	 */
	int size = 0;
	for (int i = 0; i < varg_c; i++)
		size += lists[i].elem_size;
	for (int i = 0; i < min_len; i++) {
		/*
		 * Selecteaza datele de pe pozitiile corespunzatoare,
		 * le introduce intr-un vector 'index-data'
		 */
		void *index_data = malloc(size);
		void *index_p = index_data, *old_p;
		for (int j = 0; j < varg_c; j++) {
			old_p = lists[j].data;
			old_p = (char *)old_p + i * lists[j].elem_size;
			memcpy(index_p, old_p, lists[j].elem_size);
			index_p = (char *)index_p + lists[j].elem_size;
		}

		/*
		 * Copiaza perechea calculata intr-un vector de pointeri,
		 * pentru a-l putea da mai departe functiei date
		 */
		void *p = index_data;
		void **elem = malloc(varg_c * sizeof(void *));
		for (int k = 0; k < varg_c; k++) {
			elem[k] = p;
			p = (char *)p + lists[k].elem_size;
		}

		// Aplica functia asupra elementelor calculate
		func(elem);

		// Sterge elemente ajutatoare
		free(index_data);
		free(elem);
	}
}

array_t map_multiple(void (*func)(void *, void **),
					 int new_list_elem_size,
					 void (*new_list_destructor)(void *),
					 int varg_c, ...)
{
	array_t lists[varg_c];
	int min_len = 99999;
	va_list ptr;
	va_start(ptr, varg_c);
	// Salveaza listele intr-un vector 'lists'
	for (int i = 0; i < varg_c; i++)
		lists[i] = va_arg(ptr, array_t);
	va_end(ptr);
	// Calculeaza lungimea minima a listelor
	for (int i = 0; i < varg_c; i++) {
		if (min_len > lists[i].len)
			min_len = lists[i].len;
	}
	// Initializeaza noua lista
	array_t new_list;
	new_list.elem_size = new_list_elem_size;
	new_list.destructor = new_list_destructor;
	new_list.len = min_len;
	new_list.data = malloc(new_list.len * new_list.elem_size);
	memset(new_list.data, 0, new_list.len * new_list.elem_size);
	void *new_p = new_list.data;
	/*
	 * Parcurge fiecare element al tuturor listelor, in paralel,
	 * si aplica functia asupra lui
	 */
	int size = 0;
	for (int i = 0; i < varg_c; i++)
		size += lists[i].elem_size;
	for (int i = 0; i < min_len; i++) {
		/*
		 * Selecteaza datele de pe pozitiile corespunzatoare,
		 * le introduce intr-un vector 'index-data'
		 */
		void *index_data = malloc(size);
		void *index_p = index_data, *old_p;
		for (int j = 0; j < varg_c; j++) {
			old_p = lists[j].data;
			old_p = (char *)old_p + i * lists[j].elem_size;
			memcpy(index_p, old_p, lists[j].elem_size);
			index_p = (char *)index_p + lists[j].elem_size;
		}
		/*
		 * Copiaza perechea calculata intr-un vector de pointeri,
		 * pentru a-l putea da mai departe functiei date
		 */
		void *p = index_data;
		void **elem = malloc(varg_c * sizeof(void *));
		for (int k = 0; k < varg_c; k++) {
			elem[k] = p;
			p = (char *)p + lists[k].elem_size;
		}
		// Aplica functia asupra elementelor calculate
		func(new_p, elem);
		new_p = (char *)new_p + new_list.elem_size;
		// Sterge elemente ajutatoare
		free(index_data);
		free(elem);
	}
	// Sterge listele vechi
	for (int j = 0; j < varg_c; j++) {
		if (lists[j].destructor) {
			void *elem = lists[0].data;
			for (int i = 0; i < lists[0].len; i++) {
				void *aux = elem;
				elem = (char *)elem + lists[0].elem_size;
				lists[0].destructor(aux);
			}
		}
	}
	for (int i = 0; i < varg_c; i++)
		free(lists[i].data);

	return new_list;
}

void *reduce_multiple(void(*func)(void *, void **), void *acc, int varg_c, ...)
{
	array_t lists[varg_c];
	int min_len = 99999;
	va_list ptr;
	va_start(ptr, varg_c);
	// Salveaza listele intr-un vector 'lists'
	for (int i = 0; i < varg_c; i++)
		lists[i] = va_arg(ptr, array_t);
	va_end(ptr);
	// Calculeaza lungimea minima a listelor
	for (int i = 0; i < varg_c; i++) {
		if (min_len > lists[i].len)
			min_len = lists[i].len;
	}

	/*
	 * Parcurge fiecare element al tuturor listelor, in paralel,
	 * si aplica functia asupra lui
	 */
	int size = 0;
	for (int i = 0; i < varg_c; i++)
		size += lists[i].elem_size;
	for (int i = 0; i < min_len; i++) {
		/*
		 * Selecteaza datele de pe pozitiile corespunzatoare,
		 * le introduce intr-un vector 'index-data'
		 */
		void *index_data = malloc(size);
		void *index_p = index_data, *old_p;
		for (int j = 0; j < varg_c; j++) {
			old_p = lists[j].data;
			old_p = (char *)old_p + i * lists[j].elem_size;
			memcpy(index_p, old_p, lists[j].elem_size);
			index_p = (char *)index_p + lists[j].elem_size;
		}

		/*
		 * Copiaza perechea calculata intr-un vector de pointeri,
		 * pentru a-l putea da mai departe functiei date
		 */
		void *p = index_data;
		void **elem = malloc(varg_c * sizeof(void *));
		for (int k = 0; k < varg_c; k++) {
			elem[k] = p;
			p = (char *)p + lists[k].elem_size;
		}

		// Aplica functia asupra elementelor calculate
		func(acc, elem);

		// Sterge elemente ajutatoare
		free(index_data);
		free(elem);
	}

	return acc;
}
