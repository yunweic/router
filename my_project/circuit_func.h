////============================================================
////   circuit_func.h  -- tcf project
////   Contains the declartion of various variables and functions
////   Author: Viraj Athavale, Yun-Wei Chang
////   Date:   Sep. 28, 2010
////============================================================
#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <list>

using namespace std;


//input_index is the index of the particular input, it can be used again for different levels (different number of gates encountered)
typedef struct{
	int	input_index;
	int	num_of_gates;
}shared_input;

//the structure that tells how many splits there are
typedef struct{
	int node_ind;
	int num_splits;
}branch_cnt;


//the structure that tells how many splits there are
typedef struct{
	bool split;
	int num_branch;
}current_branch_num;

//the Plist structure for TCF propagation
typedef struct{
	bool val;
	int time;
}PListStruct;



class node{
	public:
		node();
		node(string n, bool in);
		~node();
		node& operator=(const node& source);
		void changeName(string n);
		void addInput(int index);
		void addOutput(int index);
		void addSharedIn(shared_input in);
		void print();
		int* returnOutput();
		int returnOutputSize();
		int returnInput();
		int get_shared_input_ind();
		int get_shared_input(int index);
		int get_delay(int index);
		void set_cut(bool con);
        bool checkInput();
        void setPushed(bool con);
        bool checkPushed();
		void changeBranch();
		current_branch_num getBranch();
        //the list for all the fanouts is public
		list<branch_cnt> branch;
		int checkcuttable();
        
        void addPlistStruct(PListStruct listStruct);

        void setOper(int op);
        int getOper();

	private:
		string name;
		int input;
		vector<int> output;
		vector<shared_input> shared;
		//list<branch_cnt> branch;
		bool cuttable;
        bool in_put;
        bool cut;
		current_branch_num myBranchNum;
	    vector<PListStruct> PList;
        int oper;    
};
class gate{
	public:
	gate();
	gate(int type, int input);
	~gate();
	gate& operator=(const gate& source);
	void changeNum(int n);
	void changetype(int n);
    int gettype();
	void pushIn(int index);
	void changeOut(int index);
	void print();
	//void addSharedInput();
	int returnOutput();
	int* returnInput();
	private:
	int gate_type;
	int num_input;
	vector<int> input_index;
	int output;
};

class circuit{
	
	public:
		circuit();
		circuit(string n, int num, string output);
		~circuit();
		circuit& operator=(const circuit& source);
		void changeName(string n);
		void changeOutput(string out);
		void addInput(string n);
		void changeNumInput(int n);
		int getNumInput();
        bool checkInput(int index);
		void print();
		void addGate(gate mygate);
		void addNode(node mynode);
        gate* getGate(int index);
		int gateLength();
		int nodeLength();
		node* getNode(int index);
		void addSharedInput(int index,shared_input in);
		int get_shared_input_ind(int index);
		int get_shared_input(int index, int index2);
		int get_delay(int index, int index2);
		int* returnOutput(int index);
		int returnInput(int index);
		int getGateOutput(int index);
		int* getGateInput(int index);
		void changeInputIN();
		void printNode(int index);
		void set_cut(int index, bool con);
        void set_multi_output(bool con);
		void add_split_node(int index);
		int ret_split_node(int i);
		int getNumSplitNode();
        void printFanout(int index);
        int getMaxDelay();
        void setMaxDelay(int max);
	private:
		string name;
		int input_num;
		string output;
		vector<string> input;
		vector<gate> gate_array;
		vector<node> node_array;
        bool multi_output;
		vector<int> split_node;
        int MaxDelay;
};

int constructCircuit(string file, circuit* myCircuit);
#endif
