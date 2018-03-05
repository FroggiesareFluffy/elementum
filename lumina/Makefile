
COMPILE = g++ -std=c++11

LINK_ITEMS = -lLumina -lChroma -lSDL2main -lSDL2 -lGL -lGLU -lGLEW -lSDL2_image

LINK_DIRECTORIES = -L ./lib/ -L ../chroma/lib/

INCLUDE_DIRECTORIES = -I ../


lumina_test: lumina_test.cc
	make lumina
	$(COMPILE) $^ $(pkg-config --cflags --libs sdl2) -o $@ $(INCLUDE_DIRECTORIES) $(LINK_DIRECTORIES) $(LINK_ITEMS) -Wall

lumina: lib/lumina.o lib/window.o lib/cursor.o lib/keyboard.o
	ar rcu lib/libLumina.a $^

lib/lumina.o: lumina.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/window.o: window.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/cursor.o: cursor.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/keyboard.o: keyboard.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

clean:
	touch lib/trash
	touch lumina_test
	rm lib/*
	rm lumina_test
	clear
