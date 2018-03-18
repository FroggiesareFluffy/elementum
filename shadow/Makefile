
COMPILE = g++ -std=c++11

LINK_ITEMS = -lShadow

LINK_DIRECTORIES = -L ./lib/
INCLUDE_DIRECTORIES = -I ../


shadow_test: shadow_test.cc
	make shadow
	$(COMPILE) $^ $(pkg-config --cflags --libs sdl2) -o $@ $(INCLUDE_DIRECTORIES) $(LINK_DIRECTORIES) $(LINK_ITEMS) -Wall

shadow: lib/matrix.o lib/vector.o lib/plane.o lib/ray.o lib/shadow.o
	ar rcu lib/libShadow.a $^

lib/shadow.o: shadow.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/matrix.o: matrix.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/vector.o: vector.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/plane.o: plane.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/ray.o: ray.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

clean:
	touch lib/trash || mkdir lib && touch lib/trash
	touch shadow_test
	rm lib/*
	rm shadow_test
	clear
