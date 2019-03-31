OBJS = parse.o chunk.o diagonal.o

diagonal : $(OBJS)
	g++ -g -o diagonal $(OBJS)

parse.o : parse.cpp parse.h
	g++ -c -g parse.cpp 

chunk.o : chunk.cpp chunk.h parse.h
	g++ -c -g chunk.cpp 


diagonal.o : diagonal.cpp parse.h
	g++ -c -g diagonal.cpp

clean:
	rm -f diagonal
