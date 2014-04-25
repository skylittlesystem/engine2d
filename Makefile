#
# TEH NEW ENGINE MAKEFIEL!!1!11ONE!
#

CC := gcc
LD := gcc
CFLAGS := -std=c99 -Wall -pipe -ggdb -DOPENGL_ES
LDFLAGS := 

SDL2_CFLAGS := `sdl2-config --cflags`
SDL2_LIBS := `sdl2-config --libs` -lGLESv2

CFLAGS := -Isauce -Ibuild/renderer/shaders $(SDL2_CFLAGS) $(CFLAGS)
LDFLAGS := $(SDL2_LIBS) $(LDFLAGS)

CC := $(CC) $(CFLAGS)
LD := $(LD) $(LDFLAGS)

#
# 3rd party lib objects
#

#
# misc objects
#

MISC_OBJ := \
	build/misc/list.o \
	build/misc/simd.o \
	build/misc/js0n.o \
	build/misc/j0g.o \
	build/misc/j0g2.o \

#
# engine objects
#
RENDERER_OBJ := \
	build/renderer/renderer.o \
	build/renderer/r_game.o \

R_SHADERS := \
	build/renderer/shaders/vshader.glsl.c \
	build/renderer/shaders/fshader.glsl.c \

UI_OBJ := \
	build/ui/ui.o \
	build/ui/ui_game.o \

G_ENTITIES_OBJ := \
	build/game/g_entity/g_entity.o \
	build/game/g_entity/g_player.o \
	build/game/g_entity/g_terrain.o \

GAME_OBJ := \
	build/game/g_zawarudo.o \
	build/game/game.o \
	$(G_ENTITIES_OBJ) \

ENGINE_OBJ := \
	build/engine.o \
	$(RENDERER_OBJ) \
	$(UI_OBJ) \
	$(GAME_OBJ) \
	$(MISC_OBJ) \

#
# programs
#

ENGINE_PRG := \
	build/engine \

ALL_OBJ := $(MISC_OBJ) $(ENGINE_OBJ)
ALL_PRG := $(ENGINE_PRG)

#
# targets
#

build/%.o: sauce/%.c
	$(CC) -o $@ -c $<

build/%.glsl.c: sauce/%.glsl
	xxd -i < $< > $@

$(ENGINE_PRG): $(ENGINE_OBJ)
	echo $(ENGINE_OBJ)
	$(LD) -o $@ $^

.PHONY: all clean

clean:
	rm -f $(ALL_OBJ) $(ALL_PRG) $(R_SHADERS)

all: $(ENGINE_PRG)

#
# shaders
#
build/renderer/renderer.o: $(R_SHADERS)

#
# tests
#

build/%test: sauce/%test.c
	$(LD) -o $@ $^
	$@
	rm -f $@

build/misc/list_test: build/misc/list.o
