OBJS = tcf_sat.o circuit_func.o shared_in.o decompose.o construct_tcf.o

tcf_sat: $(OBJS)
	g++ -g -o tcf_sat $(OBJS)

tcf_sat.o : tcf_sat.cpp circuit_func.h
	g++ -c -g tcf_sat.cpp

circuit_func.o : circuit_func.cpp circuit_func.h
	g++ -c -g circuit_func.cpp

shared_in.o : shared_in.cpp shared_in.h circuit_func.h
	g++ -c -g shared_in.cpp

decompose.o : decompose.cpp decompose.h circuit_func.h	
	g++ -c -g decompose.cpp

construct_tcf.o : construct_tcf.cpp construct_tcf.h circuit_func.h	
	g++ -c -g construct_tcf.cpp
clean:
	rm -f *.o
