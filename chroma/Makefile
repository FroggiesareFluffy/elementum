
COMPILE = g++ -std=c++11

LINK_ITEMS = -lLumina -lChroma -lShadow -lSDL2 -lGL -lGLU -lGLEW -lSDL2_image

LINK_DIRECTORIES = -L ./lib/ -L ../lumina/lib/ -L ../shadow/lib/

INCLUDE_DIRECTORIES = -I ../


chroma_test: chroma_test.cc
	make chroma
	$(COMPILE) $^ $(pkg-config --cflags --libs sdl2) -o $@ $(INCLUDE_DIRECTORIES) $(LINK_DIRECTORIES) $(LINK_ITEMS) -Wall

chroma: lib/chroma.o lib/framebuffer.o lib/vertexarray.o lib/vertexbuffer.o lib/indexbuffer.o lib/shader.o lib/program.o lib/context.o lib/texture.o lib/texturedata.o lib/uniform.o
	ar rcu lib/libChroma.a $^

lib/chroma.o: chroma.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/framebuffer.o: framebuffer.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/vertexarray.o: vertexarray.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/vertexbuffer.o: vertexbuffer.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/indexbuffer.o: indexbuffer.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/shader.o: shader.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/program.o: program.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/context.o: context.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/texture.o: texture.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/texturedata.o: texturedata.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/uniform.o: uniform.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

clean:
	touch lib/trash || mkdir lib && touch lib/trash
	touch chroma_test
	rm lib/*
	rm chroma_test
	clear

done:
	make clean
	make chroma_test
	./chroma_test
