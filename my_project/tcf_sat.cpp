////============================================================
////   tcf_sat.cpp  -- tcf project
////   Compute the probability that output will be stable with 
////   the time constraint given by the user
////   Author: Viraj Athavale, Yun-Wei Chang
////   Date:   Sep. 28, 2010
////============================================================
#include "circuit_func.h"
#include "shared_in.h"
#include "decompose.h"
#include "construct_tcf.h"

int main(int argc, char* argv[]){
	//check how many arguments
	if (argc <= 2) {cerr << "Usage: ./tcf_sat <*.blif|*.netblif> [<Max PIs for each node>] [<Timing constraint on output>]" << endl; return -1;}
	char * filename=argv[1];
	int min_in=atoi(argv[2]);
	//int time_constraint=atoi(argv[3]);
	int constraint;
	int max_shared_input;
	//scan in the time constraint
	if(argc>=3){
		constraint=atoi(argv[3]);
	}
	//default to 0 to see the critical path
	else{
		constraint=0;
		cout << "Output time constraint not specified, using default value 0" << endl;
	}
	//scan in the limit number of shared input
	//can change here i think
	if (argc == 5)
	{
		sscanf(argv[4], "%d", &max_shared_input);
		cout << "Maximum number of shared primary inputs: " << max_shared_input << endl;
	}

	//construct the circuit
	circuit* myCircuit=new circuit;
	//parse the circuit blif file
	int tmp=constructCircuit(filename, myCircuit);


	if (tmp) {cerr << "Circuit graph construction failed" << endl; return -1;}

    //propagate the delay for all the primary inputs    
	propagate_in(myCircuit);

    //
	propagate_fanout(myCircuit);
    //decompose the circuit into supergates
	decompose(myCircuit,min_in);
    //construct the tcf for each node
	construct_tcf(myCircuit,constraint);
    //print the circuit
	myCircuit->print();
    //free the circuit class
	delete myCircuit;	
	return 0;

}
