/*
 *
 *
 *
 *
 * ui_game.c
 *
 *
 *
 *
 *
 */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>

#include "ui_game.h"
#include "game/g_entity/g_player.h"
#include "renderer/r_septagon.h"

/*
 *
 *
 *
 *
 * teh temp
 *
 *
 *
 *
 *
 */

#include <stdio.h>

/*
 *
 *
 *
 *
 * end of teh temp
 *
 *
 *
 *
 *
 */

void ui_game_draw(struct ui_game* ui_g)
{
	GLint T_loc;

	struct renderer* R;
	struct game* g;
	struct llist* entl;
	struct llist_node* n;
	g = ui_g->g;
	R = ui_g->R;

	entl = g_entl(g);

	glUseProgram(R->program_id);
	T_loc = glGetUniformLocation(R->program_id, "T");

	assert (T_loc != -1);

	for (n = entl->root; n != NULL; n = n->next)
	{
#define e ((struct g_entity*) n->ptr)
		glUniformMatrix4fv(T_loc, 1, GL_FALSE, (GLfloat*) e->T);

		switch (e->type)
		{
		case G_PLAYER:
			r_septagon(R);	

		case G_TERRAIN:
		case G_DIRT:
		case G_BRICKS:
		default:
			break;
		}
#undef e
	}
}

void ui_game_frame(struct ui_game* ui_g, unsigned long dt)
{
	ui_game_draw(ui_g);
}
