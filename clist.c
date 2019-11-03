#include <stdlib.h>

#include "clist.h"

#define LIST_BLOCK_SIZE 64

clist* clist_create(size_t capacity) {
	clist* list = (clist*)malloc(sizeof(clist));
	if (list == NULL)
		return NULL;

	list->capacity = capacity;
	list->size = 0;

	value_type* block = (value_type*)calloc(capacity, sizeof(value_type));
	if (block == NULL)
		return NULL;

	list->data = block;

	return list;
}

void clist_destroy(clist* list) {
	if (list == NULL)
		return;

	free(list->data);
	free(list);
}

bool clist_push_back(clist* list, value_type value) {
	if (list->size == list->capacity) {
		size_t cap = list->capacity;
		size_t new_capacity = cap + LIST_BLOCK_SIZE;

		value_type* block = (value_type*)realloc(list->data, new_capacity * sizeof(value_type));
		if (block == NULL)
			return false;

		list->data = block;
		list->capacity = new_capacity;
	}

	list->data[list->size++] = value;

	return true;
}

int compare_asc(const void* p_lhs, const void* p_rhs) {

	const value_type lhs = *(const value_type*)p_lhs;
	const value_type rhs = *(const value_type*)p_rhs;

	if (lhs < rhs) return -1;
	if (lhs > rhs) return 1;
	return 0;
}

int compare_desc(const void* p_lhs, const void* p_rhs) {

	const value_type lhs = *(const value_type*)p_lhs;
	const value_type rhs = *(const value_type*)p_rhs;

	if (lhs < rhs) return 1;
	if (lhs > rhs) return -1;
	return 0;
}

void clist_sort_asc(clist* list) {
	qsort(list->data, list->size, sizeof(value_type), compare_asc);
}

void clist_sort_desc(clist* list) {
	qsort(list->data, list->size, sizeof(value_type), compare_desc);
}

void clist_erase(clist* list, size_t index) {
	while (index < list->size - 1) {
		list->data[index] = list->data[index + 1];
		++index;
	}
	
	--list->size;
}

value_type clist_remove(clist* list, size_t index) {
	value_type val = list->data[index];

	while (index < list->size - 1) {
		list->data[index] = list->data[index + 1];
		++index;
	}

	return val;
}