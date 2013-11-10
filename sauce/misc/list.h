/*
 *
 *
 *
 *
 * list.h
 *
 *
 *
 *
 *
 */

#ifndef HAS_LIST_H
#define HAS_LIST_H

struct llist_node
{
	void* ptr; /* pointer to whatever */
	struct llist_node* next; /* next */
};

struct llist
{
	struct llist_node* root; /* root of teh list */
	unsigned len; /* length */
};

struct alist
{
	void** ary; /* teh ary */
	unsigned len; /* length */
};

void* llist_find(struct llist* list, unsigned i);
void* alist_find(struct alist* list, unsigned i);

void llist_add(struct llist* list, unsigned i, void* ptr);
void alist_add(struct alist* list, unsigned i, void* ptr);

void llist_remove(struct llist* list, unsigned i);
void alist_remove(struct alist* list, unsigned i);

#define llist_push(l, p) llist_add((l), (l)->len, (p));
#define alist_push(l, p) alist_add((l), (l)->len, (p));

#define llist_pop(l, p) llist_remove((l), 0, (p));
#define alist_pop(l, p) alist_remove((l), 0, (p));

#define llist_shift(l, p) llist_remove((l), (l)->len-1, (p));
#define alist_shift(l, p) alist_remove((l), (l)->len-1, (p));

#define llist_unshift(l, p) llist_add((l), 0, (p));
#define alist_unshift(l, p) alist_add((l), 0, (p));

#endif /* HAS_LIST_H */
