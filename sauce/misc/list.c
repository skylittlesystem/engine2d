/*
 * Copyright (C) 2014 Igor de Sant'Ana Fontana.
 * <rogi@skylittlesystem.org>
 *
 * This file is part of engine2d.
 *
 * engine2d is free software: you can redistribute it and/or modify it
 * under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * engine2d is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public
 * License along with engine2d.  If not, see
 * <http://www.gnu.org/licenses/>.
 *
 */

/*
 *
 *
 *
 *
 * list.c
 *
 *
 *
 *
 *
 */

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

/* find by index */
void* llist_find(struct llist* list, unsigned i)
{
	struct llist_node* node = list->root;

	assert (i < list->len);

	while (i--)
	{
		assert (node);
		node = node->next;
	}

	assert (node);
	return node->ptr;
}

void* alist_find(struct alist* list, unsigned i)
{
	assert (i < list->len);
	return list->ary[i];
}


/* add */
void llist_add(struct llist* list, unsigned i, void* ptr)
{
	struct llist_node* node;

	assert (i <= list->len);

	node = calloc(1, sizeof (struct llist_node));
	node->ptr = ptr;

	if (i == 0)
	{
		if (list->root)
			node->next = list->root;

		list->root = node;
	}

	else
	{
		struct llist_node* pnode;
		pnode = list->root;

		assert (i > 0);
		while (--i)
			pnode = pnode->next;

		node->next = pnode->next;
		pnode->next = node;
	}

	++list->len;
}

void alist_add(struct alist* list, unsigned i, void* ptr)
{
	assert (i <= list->len);

	list->ary = realloc(list->ary, sizeof (void*) * (list->len + 1));
	assert (list->ary);

	memmove(&list->ary[i+1], &list->ary[i], list->len - i);

	list->ary[i] = ptr;
	++list->len;
}

/* remove */
void llist_remove(struct llist* list, unsigned i)
{
	struct llist_node* node;

	assert (i < list->len);

	if (i == 0)
	{
		node = list->root;
		if (list->root->next)
			list->root = list->root->next;

		if (list->len == 1)
			list->root = NULL;
	}

	else
	{
		struct llist_node* pnode;
		pnode = list->root;

		assert (i > 0);
		while (--i)
			pnode = pnode->next;

		node = pnode->next;

		if (pnode->next)
			pnode->next = pnode->next->next;
	}

	free(node);
	--list->len;
}

void alist_remove(struct alist* list, unsigned i)
{
	assert (i < list->len);

	memmove(&list->ary[i], &list->ary[i+1], list->len - i - 1);

	list->ary = realloc(list->ary, sizeof (void*) * (list->len - 1));
	if (list->len > 1)
		assert (list->ary);

	--list->len;
}
