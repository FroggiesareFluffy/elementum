
COMPILE = g++ -std=c++11

LINK_ITEMS = -lAqua -lLumina -lChroma -lPrisma -lSDL2 -lGL -lGLU -lGLEW -lSDL2_image

LINK_DIRECTORIES = -L ./lib/ -L ../chroma/lib/ -L ../lumina/lib/ -L ../aqua/lib/

INCLUDE_DIRECTORIES = -I ../


prisma_test: prisma_test.cc
	make prisma
	$(COMPILE) $^ $(pkg-config --cflags --libs sdl2) -o $@ $(INCLUDE_DIRECTORIES) $(LINK_DIRECTORIES) $(LINK_ITEMS) -Wall

prisma: lib/prisma.o
	ar rcu lib/libPrisma.a $^

lib/prisma.o: prisma.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

clean:
	touch lib/trash || mkdir lib && touch lib/trash
	touch prisma_test
	rm lib/*
	rm prisma_test
	clear
