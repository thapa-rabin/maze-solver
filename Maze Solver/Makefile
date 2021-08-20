CFLAGS = -c -I$(HOME)/Programming/include
LFLAGS = -L$(HOME)/Programming/lib
LIBS = -ldataStructures

Project4: main.o output.o disjointset.o sampler.o
	g++ $(LFLAGS) -o Project4 main.o output.o disjointset.o sampler.o $(LIBS)

main.o: main.cpp
	g++ $(CFLAGS) -c main.cpp

output.o: output.cpp
	g++ $(CFLAGS) -c output.cpp

disjointset.o: disjointset.cpp
	g++ $(CFLAGS) -c disjointset.cpp

sampler.o: sampler.cpp
	g++  $(CFLAGS) -c sampler.cpp

clean:
		rm Project4 main.o output.o disjointset.o sampler.o

