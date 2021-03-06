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
 * test_list.c
 *
 *
 *
 *
 *
 */

#include <string.h>
#include <assert.h>
#include "list.h"

/*
 * Teh main function!!11!1ONE
 *
 */

int main(int argc, char *argv[])
{
	struct llist llist;
	struct alist alist;

	/* linked list */
	memset(&llist, 0, sizeof (llist));

	assert (llist.len == 0);
	assert (llist.root == NULL);

	llist_add(&llist, 0, (void*) 3);
	llist_add(&llist, 0, (void*) 1);
	llist_add(&llist, 1, (void*) 2);
	llist_add(&llist, 3, (void*) 4);

	assert (llist_find(&llist, 0) == (void*) 1);
	assert (llist_find(&llist, 1) == (void*) 2);
	assert (llist_find(&llist, 2) == (void*) 3);
	assert (llist_find(&llist, 3) == (void*) 4);
	assert (llist.len = 4);

	llist_remove(&llist, 2);
	assert (llist_find(&llist, 2) == (void*) 4);

	llist_remove(&llist, 0);
	assert (llist_find(&llist, 0) == (void*) 2);

	llist_remove(&llist, 1);
	llist_remove(&llist, 0);
	assert (llist.len == 0);
	assert (llist.root == NULL);

	/* array list */
	memset(&alist, 0, sizeof (alist));

	assert (alist.len == 0);
	assert (alist.ary == NULL);

	alist_add(&alist, 0, (void*) 3);
	alist_add(&alist, 0, (void*) 1);
	alist_add(&alist, 1, (void*) 2);
	alist_add(&alist, 3, (void*) 4);

	assert (alist_find(&alist, 0) == (void*) 1);
	assert (alist_find(&alist, 1) == (void*) 2);
	assert (alist_find(&alist, 2) == (void*) 3);
	assert (alist_find(&alist, 3) == (void*) 4);
	assert (alist.len = 4);

	alist_remove(&alist, 2);
	assert (alist_find(&alist, 2) == (void*) 4);

	alist_remove(&alist, 0);
	assert (alist_find(&alist, 0) == (void*) 2);

	alist_remove(&alist, 1);
	alist_remove(&alist, 0);
	assert (alist.len == 0);
	assert (alist.ary == NULL);

	return 0;
}
