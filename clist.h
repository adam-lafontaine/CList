#ifndef	__CLIST_H__
#define __CLIST_H__

#include <ctype.h>
#include <stdbool.h>

typedef double value_type;

typedef struct CList {

	value_type* data;
	size_t capacity;
	size_t size;

} clist;

clist* clist_create(size_t capacity);

void clist_destroy(clist* list);

bool clist_push_back(clist* list, value_type value);

void clist_sort_asc(clist* list);

void clist_sort_desc(clist* list);

void clist_erase(clist* list, size_t index);

value_type clist_remove(clist* list, size_t index);



#endif
