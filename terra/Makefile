
COMPILE = g++ -std=c++11

LINK_ITEMS = -lTerra

LINK_DIRECTORIES = -L ./lib/

INCLUDE_DIRECTORIES = -I ../


terra_test: terra_test.cc
	make terra
	$(COMPILE) $^ $(pkg-config --cflags --libs sdl2) -o $@ $(INCLUDE_DIRECTORIES) $(LINK_DIRECTORIES) $(LINK_ITEMS) -Wall

terra: lib/terra.o
	ar rcu lib/libTerra.a $^

lib/terra.o: terra.cc
	g++ -c $^ -o $@ $(INCLUDE_DIRECTORIES)


clean:
	touch lib/trash
	touch terra_test
	rm lib/*
	rm terra_test
	clear
