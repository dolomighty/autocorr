

CC:=gcc
LIBS  := `pkg-config --libs   sdl2` -lm   
CFLAGS:= `pkg-config --cflags sdl2` -O3 -Werror
SRC:=$(shell find -L . -type f -name "*.c")
HDR:=$(shell find -L . -type f -name "*.h")


.PHONY: all
all : main


.PHONY: run
run : main
	parec | ./$^



OBS+=main.o

main.o: Makefile $(SRC) $(HDR)

main: $(OBS)
	$(CC) $(CPPFLAGS) -o $@ $(OBS) $(LIBS)

#DYN+=draw_scene_gl.h
#draw_scene_gl.h : scenes/scene.obj obj2c.sh
#	./obj2c.sh scenes/scene.obj > $@

.PHONY: clean cl
clean cl :
	file * | awk '/ELF/ { gsub(/:.*/,"") ; print }' | xargs -r rm
	rm -f deps.inc $(DYN)


.PHONY: rebuild re
rebuild re : clean all



