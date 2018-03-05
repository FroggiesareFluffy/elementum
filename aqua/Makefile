

COMPILE = g++ -std=c++11

LIB_DIRECTORIES = -L ../thirdparty/udt4/src -L ./lib
INCLUDE_DIRECTORIES = -I ../
OPTIONS = -lAqua -ludt -lstdc++ -lpthread

serialize_test: serialize_test.cc
	make aqua
	$(COMPILE) $^ -o $@ $(INCLUDE_DIRECTORIES) $(LIB_DIRECTORIES) $(OPTIONS) 

client_test: client_test.cc
	make aqua
	$(COMPILE) $^ -o $@ $(INCLUDE_DIRECTORIES) $(LIB_DIRECTORIES) $(OPTIONS) 

server_test: server_test.cc
	make aqua
	$(COMPILE) $^ -o $@ $(INCLUDE_DIRECTORIES) $(LIB_DIRECTORIES) $(OPTIONS)

aqua: lib/server.o lib/connection.o
	ar rcu lib/libAqua.a $^

lib/server.o: server.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/connection.o: connection.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)

lib/serializer.o: serializer.cc
	$(COMPILE) -c $^ -o $@ $(INCLUDE_DIRECTORIES)


clean:
	touch lib/x
	touch serializer_test
	touch server_test
	touch client_test
	rm serializer_test
	rm server_test
	rm client_test
	rm lib/*
	clear
