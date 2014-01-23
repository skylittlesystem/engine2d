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
#include "renderer/r_polygon.h"
#include "renderer/r_box.h"

void ui_game_draw(struct ui_game* ui_g)
{
	static float red[4] =	{1, 0, 0, 1};
	static float green[4] =	{0, 1, 0, 1};
//	static float blue[4] =	{0, 0, 1, 1};

	GLint pos_loc;
	GLint color_loc;

	struct renderer* R;
	struct game* g;
	struct llist* entl;
	struct llist_node* n;
	g = ui_g->g;
	R = ui_g->R;

	entl = g_entl(g);

	glUseProgram(R->program_id);
	pos_loc = glGetUniformLocation(R->program_id, "pos");
	color_loc = glGetUniformLocation(R->program_id, "color");

	assert (pos_loc != -1);

	for (n = entl->root; n != NULL; n = n->next)
	{
#define e ((struct g_entity*) n->ptr)
		glUniform2fv(pos_loc, 1, (GLfloat*) e->pos);

		switch (e->type)
		{
		case G_PLAYER:
			glUniform4fv(color_loc, 1, red);
			r_box(R, (struct r_box*) e->hit_box);
			//r_polygon(R, (struct r_polygon*) e->poly);
			break;

		case G_TERRAIN:
			glUniform4fv(color_loc, 1, green);
			r_box(R, (struct r_box*) e->hit_box);
			//r_polygon(R, (struct r_polygon*) e->poly);
			break;

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
