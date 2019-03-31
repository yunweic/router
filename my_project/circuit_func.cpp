////============================================================
////   circuit_func.cpp  -- tcf project
////   Contain various functions to compute the probability
////   Author: Viraj Athavale, Yun-Wei Chang
////   Date:   Sep. 28, 2010
////============================================================
#include "circuit_func.h"

#define NOT 0
#define NAND 1
#define NOR 2
#define AND 3
#define OR 4
#define XOR 5
#define DUMMY 6

// constructCircuit reads the input blif file
//  and parse it into various pieces needed to compute
//  probability.
//  It returns -1 if no errors are encountered.  Otherwise,
//  0 is returned with an appropriate error message in err.
int constructCircuit(string file,circuit* myCircuit){
	string name;
	int n;
	string out1;	
	cout<<file<<endl;

	//declare a map
	map<string, int>myMap;
	map<string, int>::iterator it;
	pair<map<string,int>::iterator,bool>ret;
	
	ifstream ifs(file.c_str());
	//check to see if the file can be opend
	if(!ifs.good()){
		cout<<"Unable to open file"<<endl;
		return -1;
	}
	string word;
	*myCircuit=circuit();	
	int temp=0;
	bool flag=1;
	//keep reading the file until end of file
	while(!ifs.eof()){	
		ifs>> word;
		//get circuit name
		if(word==".model"){
			ifs>>name;
			myCircuit->changeName(name);	
		}
		//inputs
		else if(word==".inputs"){
			ifs>>word;
			while(word[0]!='.'){
				myCircuit->addInput(word);
				temp++;
				
				node myNode=node(word, true);
				myCircuit->addNode(myNode);
				myMap.insert(pair<string,int>(word,myCircuit->nodeLength()-1));
	
				ifs>>word;

			}
		}
		//outputs
		if(word==".outputs"){
			ifs>>out1;
		    char c=ifs.peek();
            //check if there's multiple outputs
            if(c!='\n'){
                node myNode=node("dummy", false);
		myNode.addInput(0);
                myCircuit->addNode(myNode);
                int dummy_ind=myCircuit->nodeLength()-1;
                myMap.insert(pair<string,int>("dummy",dummy_ind));
                myCircuit->changeOutput("dummy");

                gate myGate=gate();
                myGate.changetype(DUMMY);
                int num_of_out=0;

                while(out1[0]!='.'){
                    node temp_node=node(out1, false);
                    temp_node.addOutput(0);
                    myCircuit->addNode(temp_node);
                    myMap.insert(pair<string,int>(out1,myCircuit->nodeLength()-1));
                    myGate.pushIn(myCircuit->nodeLength()-1);
                    num_of_out++;
                    ifs>>out1;
                }
                myGate.changeNum(num_of_out);
                myGate.changeOut(dummy_ind);
                myCircuit->addGate(myGate);
		word=out1;

            }
            else{
			    node myNode=node(out1, false);
			    myCircuit->addNode(myNode);
			    myMap.insert(pair<string,int>(out1,myCircuit->nodeLength()-1));

			    myCircuit->changeOutput(out1);
            }
		}
		//extract gates
		if(word==".gate"){
			char numofinput;
			size_t tmpword;
			int num;
			string out;
			ifs>>word;
				if(word.compare(0, 3, "not")==0||word.compare(0,3, "inv")==0){
					gate myGate=gate();
					myGate.changetype(NOT);
					numofinput=word[3];
					num=(int)(numofinput-'0');
					myGate.changeNum(num);
						
					ifs>>word;
					for(int i=0;i<num;i++){

						string in;
						tmpword=word.find_first_of('=');
						in=word.substr(tmpword+1);
						//the node is not yet pushed
						it=myMap.find(in);
						if(it==myMap.end()){
							node myNode=node(in, false);
							myNode.addOutput(myCircuit->gateLength());
							myCircuit->addNode(myNode);
							myMap.insert(pair<string,int>(in,myCircuit->nodeLength()-1));
							myGate.pushIn(myCircuit->nodeLength()-1);
						}
						else{
							int temp=it->second;
							node* myNode=myCircuit->getNode(temp);	
							myNode->addOutput(myCircuit->gateLength());

							//don't change branch if output was 0
							if(myNode->returnOutputSize()==2){
								myNode->changeBranch();
								myCircuit->add_split_node(temp);
							}
							myGate.pushIn(temp);
						}
						ifs>>word;
					}
					tmpword=word.find_first_of('=');
					out=word.substr(tmpword+1);
					
					//the node is not yet pushed
					it=myMap.find(out);
					if(it==myMap.end()){
						node myNode=node(out, false);
						myNode.addInput(myCircuit->gateLength());
						myCircuit->addNode(myNode);
						myMap.insert(pair<string,int>(out,myCircuit->nodeLength()-1));
						myGate.changeOut(myCircuit->nodeLength()-1);
					}
					else{
						int temp=it->second;
						node* myNode=myCircuit->getNode(temp);	
						myNode->addInput(myCircuit->gateLength());
						myGate.changeOut(temp);
					}

					myCircuit->addGate(myGate);
				}
				else if(word.compare(0, 3, "and")==0){
					gate myGate=gate();
					myGate.changetype(AND);
					numofinput=word[3];
					num=(int)(numofinput-'0');
					myGate.changeNum(num);
					ifs>>word;
					for(int i=0;i<num;i++){

						string in;
						tmpword=word.find_first_of('=');
						in=word.substr(tmpword+1);
						//the node is not yet pushed
						it=myMap.find(in);
						if(it==myMap.end()){
							node myNode=node(in, false);
							myNode.addOutput(myCircuit->gateLength());
							myCircuit->addNode(myNode);
							myMap.insert(pair<string,int>(in,myCircuit->nodeLength()-1));
							myGate.pushIn(myCircuit->nodeLength()-1);
						}
						else{
							int temp=it->second;
							node* myNode=myCircuit->getNode(temp);	
							myNode->addOutput(myCircuit->gateLength());
							//don't change if it was 0
							if(myNode->returnOutputSize()==2){
								myNode->changeBranch();
								myCircuit->add_split_node(temp);
							}
							myGate.pushIn(temp);
						}

						ifs>>word;
					}
					tmpword=word.find_first_of('=');
					out=word.substr(tmpword+1);
					//the node is not yet pushed
					it=myMap.find(out);
					if(it==myMap.end()){
						node myNode=node(out,false);
						myNode.addInput(myCircuit->gateLength());
						myCircuit->addNode(myNode);
						myMap.insert(pair<string,int>(out,myCircuit->nodeLength()-1));
						myGate.changeOut(myCircuit->nodeLength()-1);
					}
					else{
						int temp=it->second;
						node* myNode=myCircuit->getNode(temp);	
						myNode->addInput(myCircuit->gateLength());
						myGate.changeOut(temp);
					}

					myCircuit->addGate(myGate);

				}
				else if(word.compare(0, 3, "nor")==0){
					gate myGate=gate();
					myGate.changetype(NOR);
					numofinput=word[3];
					num=(int)(numofinput-'0');
					myGate.changeNum(num);
					ifs>>word;
					for(int i=0;i<num;i++){

						string in;
						tmpword=word.find_first_of('=');
						in=word.substr(tmpword+1);
						//the node is not yet pushed
						it=myMap.find(in);
						if(it==myMap.end()){
							node myNode=node(in,false);
							myNode.addOutput(myCircuit->gateLength());
							myCircuit->addNode(myNode);
							myMap.insert(pair<string,int>(in,myCircuit->nodeLength()-1));
							myGate.pushIn(myCircuit->nodeLength()-1);
						}
						else{
							int temp=it->second;
							node* myNode=myCircuit->getNode(temp);	
							myNode->addOutput(myCircuit->gateLength());
							//don't change branch if output was 0
							if(myNode->returnOutputSize()==2){
								myNode->changeBranch();
								myCircuit->add_split_node(temp);
							}

							myGate.pushIn(temp);
						}

						ifs>>word;
					}
					tmpword=word.find_first_of('=');
					out=word.substr(tmpword+1);
					//the node is not yet pushed
					it=myMap.find(out);
					if(it==myMap.end()){
						node myNode=node(out,false);
						myNode.addInput(myCircuit->gateLength());
						myCircuit->addNode(myNode);
						myMap.insert(pair<string,int>(out,myCircuit->nodeLength()-1));
						myGate.changeOut(myCircuit->nodeLength()-1);
					}
					else{
						int temp=it->second;
						node* myNode=myCircuit->getNode(temp);	
						myNode->addInput(myCircuit->gateLength());
						myGate.changeOut(temp);
					}

					myCircuit->addGate(myGate);

				}
				else if(word.compare(0, 4, "nand")==0){
					gate myGate=gate();
					myGate.changetype(NAND);
					numofinput=word[4];
					num=(int)(numofinput-'0');
					myGate.changeNum(num);
					ifs>>word;
					for(int i=0;i<num;i++){
						string in;
						tmpword=word.find_first_of('=');
						in=word.substr(tmpword+1);
						//the node is not yet pushed
						it=myMap.find(in);
						if(it==myMap.end()){
							node myNode=node(in,false);
							myNode.addOutput(myCircuit->gateLength());
							myCircuit->addNode(myNode);
							myMap.insert(pair<string,int>(in,myCircuit->nodeLength()-1));
							myGate.pushIn(myCircuit->nodeLength()-1);
						}
						else{
							int temp=it->second;
							node* myNode=myCircuit->getNode(temp);	
							myNode->addOutput(myCircuit->gateLength());
							//don't change branch if output was 0
							if(myNode->returnOutputSize()==2){
								myNode->changeBranch();
								myCircuit->add_split_node(temp);
							}
;
							myGate.pushIn(temp);
						}

						ifs>>word;
					}
					tmpword=word.find_first_of('=');
					out=word.substr(tmpword+1);
					//the node is not yet pushed
					it=myMap.find(out);
					if(it==myMap.end()){
						node myNode=node(out,false);
						myNode.addInput(myCircuit->gateLength());
						myCircuit->addNode(myNode);
						myMap.insert(pair<string,int>(out,myCircuit->nodeLength()-1));
						myGate.changeOut(myCircuit->nodeLength()-1);
					}
					else{
						int temp=it->second;
						node* myNode=myCircuit->getNode(temp);	
						myNode->addInput(myCircuit->gateLength());
						myGate.changeOut(temp);
					}

					myCircuit->addGate(myGate);

				}
				else if(word.compare(0, 2, "or")==0){
					gate myGate=gate();
					myGate.changetype(OR);
					numofinput=word[2];
					num=(int)(numofinput-'0');
					myGate.changeNum(num);
					ifs>>word;
					for(int i=0;i<num;i++){
						string in;
						tmpword=word.find_first_of('=');
						in=word.substr(tmpword+1);
						//the node is not yet pushed
						it=myMap.find(in);
						if(it==myMap.end()){
							node myNode=node(in,false);
							myNode.addOutput(myCircuit->gateLength());
							myCircuit->addNode(myNode);
							myMap.insert(pair<string,int>(in,myCircuit->nodeLength()-1));
							myGate.pushIn(myCircuit->nodeLength()-1);
						}
						else{
							int temp=it->second;
							node* myNode=myCircuit->getNode(temp);	
							myNode->addOutput(myCircuit->gateLength());
							
							//don't change branch if output was 0
							if(myNode->returnOutputSize()==2){
								myNode->changeBranch();
								myCircuit->add_split_node(temp);
							}
;
							myGate.pushIn(temp);
						}

						ifs>>word;
					}
					tmpword=word.find_first_of('=');
					out=word.substr(tmpword+1);
					//the node is not yet pushed
					it=myMap.find(out);
					if(it==myMap.end()){
						node myNode=node(out,false);
						myNode.addInput(myCircuit->gateLength());
						myCircuit->addNode(myNode);
						myMap.insert(pair<string,int>(out,myCircuit->nodeLength()-1));
						myGate.changeOut(myCircuit->nodeLength()-1);
					}
					else{
						int temp=it->second;
						node* myNode=myCircuit->getNode(temp);	
						myNode->addInput(myCircuit->gateLength());
						myGate.changeOut(temp);
					}

					myCircuit->addGate(myGate);

				}
				else if(word.compare(0, 2, "xor")==0){
					gate myGate=gate();
					myGate.changetype(XOR);
					numofinput=word[2];
					num=(int)(numofinput-'0');
					myGate.changeNum(num);
					ifs>>word;
					for(int i=0;i<num;i++){
						string in;
						tmpword=word.find_first_of('=');
						in=word.substr(tmpword+1);
						//the node is not yet pushed
						it=myMap.find(in);
						if(it==myMap.end()){
							node myNode=node(in,false);
							myNode.addOutput(myCircuit->gateLength());
							myCircuit->addNode(myNode);
							myMap.insert(pair<string,int>(in,myCircuit->nodeLength()-1));
							myGate.pushIn(myCircuit->nodeLength()-1);
						}
						else{
							int temp=it->second;
							node* myNode=myCircuit->getNode(temp);	
							myNode->addOutput(myCircuit->gateLength());
							//don't change branch if output was 0
							if(myNode->returnOutputSize()==2){
								myNode->changeBranch();
								myCircuit->add_split_node(temp);
							}
;
							myGate.pushIn(temp);
						}

						ifs>>word;
					}
					tmpword=word.find_first_of('=');
					out=word.substr(tmpword+1);
					//the node is not yet pushed
					it=myMap.find(out);
					if(it==myMap.end()){
						node myNode=node(out,false);
						myNode.addInput(myCircuit->gateLength());
						myCircuit->addNode(myNode);
						myMap.insert(pair<string,int>(out,myCircuit->nodeLength()-1));
						myGate.changeOut(myCircuit->nodeLength()-1);
					}
					else{
						int temp=it->second;
						node* myNode=myCircuit->getNode(temp);	
						myNode->addInput(myCircuit->gateLength());
						myGate.changeOut(temp);
					}

					myCircuit->addGate(myGate);

				}
				
		}	
	}
	myCircuit->changeNumInput(temp);
	myCircuit->changeInputIN();
	
 return 0;	
}

//default constructor for the circuit class
circuit::circuit(){
	name="myCircuit";
	input_num=0;
	output='0';
}
//constructor that initialize the fields
circuit::circuit(string n, int num, string out){
	name=n;
	input_num=num;
	output=out;
}
//desctructor
circuit::~circuit(){
}

//overloading operator
circuit & circuit::operator=(const circuit& source){
	cout<<source.name<<endl;
	name=source.name;
	input_num=source.input_num;
	output=source.output;
	for(int i=0; i<source.input.size();i++)
	{	
		input[i]=source.input[i];
	}
	
	for(int i=0; i<source.gate_array.size();i++)
	{	
		gate_array[i]=source.gate_array[i];
	}

	return *this;
}

//modify the circuit name
void circuit::changeName(string n){
	name=n;
}
//modify output char
void circuit::changeOutput(string out){
	output=out;
}
//add the input name in the vector
void circuit::addInput(string in){
	input.push_back(in);	
}
//change the number of inputs of the circuit
void circuit::changeNumInput(int n){
	input_num=n;	
}
//return the number of inputs
int circuit::getNumInput(){
	return input_num;
}
//add the gate in the vector
void circuit::addGate(gate mygate){
	gate_array.push_back(mygate);	
}
//add the node in the vector
void circuit::addNode(node mynode){
	node_array.push_back(mynode);	
}
//print the circuit
void circuit::print(){
	cout<<"printing circuit"<<endl;
	cout<<"name= "<<name<<endl;
	cout<<"input_num= "<<input_num<<endl;
	
	for(int i=0; i<input.size();i++){
		cout<<input[i]<<" "; 
	}
	cout<<endl<<"output= "<<output<<endl;
	for(int i=0;i<gate_array.size();i++){
		cout<<"gate index: "<<i<<endl;
		gate_array[i].print();
	}
	for(int i=0;i<node_array.size();i++){
		cout<<"node index: "<<i<<endl;
		node_array[i].print();
	}

    cout<<"maximum delay= "<<MaxDelay<<endl;

}

//change the input for all primary input
void circuit::changeInputIN(){
	for(int i=0;i<input_num;i++)
		node_array[i].addInput(node_array.size());
}

//return the size of gate
int circuit::gateLength(){
	return gate_array.size();
}
//return the number of nodes
int circuit::nodeLength(){
	return node_array.size();
}
//return the gate correspond to the gate index
gate* circuit::getGate(int index){
	return &gate_array[index];
}
//return the node correspond to the node index
node* circuit::getNode(int index){

	return &node_array[index];
}
//return all the output of current node
int* circuit::returnOutput(int index){
	int* output_array=node_array[index].returnOutput();
	return output_array;
}
//return the input of current node
int circuit::returnInput(int index){
	int myInput=node_array[index].returnInput();
	return myInput;
}

//push output Shared_input
void circuit::addSharedInput(int index, shared_input in){
	node_array[index].addSharedIn(in);
}

//get index of Shared_input
int circuit::get_shared_input_ind(int index){
	node_array[index].get_shared_input_ind();
}
//get index of Shared_input, specified by the index
int circuit::get_shared_input(int index, int index2){
	node_array[index].get_shared_input(index2);
}

//get index of Shared_input, specified by the index
int circuit::get_delay(int index, int index2){
	node_array[index].get_delay(index2);
}
//set if the node is cuttable
void circuit::set_cut(int index, bool con){
	node_array[index].set_cut(con);
}

//return the output of current gate
int circuit::getGateOutput(int index){
	int output=gate_array[index].returnOutput();
	return output;
}
//return all the input of current gate
int* circuit::getGateInput(int index){
	int* input=gate_array[index].returnInput();
	return input;
}
//print the current node
void circuit::printNode(int index){
	node_array[index].print();
}
//call the checkInput function corresponding to the index
bool circuit::checkInput(int index){
    return node_array[index].checkInput();
}
//flag the circuit to be a multiple output circuit
void circuit::set_multi_output(bool con){
    multi_output=con;
}
//add more split nodes
void circuit::add_split_node(int index){
	split_node.push_back(index);	
}

//return split nodes
int circuit::ret_split_node(int i){
	return split_node[i];	
}
//return number of split nodes
int circuit::getNumSplitNode(){
	return split_node.size();	
}
//print the multiple fanout nodes
void circuit::printFanout(int index){
    cout<<"fanout node= "<<split_node[index]<<endl;
}
//set the critical path time
void circuit::setMaxDelay(int max){
    MaxDelay=max;
}
//get the critical path time
int circuit::getMaxDelay(){
    return MaxDelay;
}

//default constructor for the gate class
gate::gate(){
	gate_type=0;
	num_input=0;
}
//constructor that initialize the fields
gate::gate(int type, int input){
	gate_type=type;
	num_input=input;
}
//desctructor
gate::~gate(){
}

//overloading operator
gate & gate::operator=(const gate& source){
	gate_type=source.gate_type;
	num_input=source.num_input;
	for(int i=0; i<source.input_index.size();i++)
	{	
		input_index[i]=source.input_index[i];
	}
	
	output=source.output;

	return *this;
}
//change number of input
void gate::changeNum(int n){
	num_input=n;	
}

//change gate type
void gate::changetype(int n){
	gate_type=n;	
}

//get gatetype
int gate::gettype(){
    return gate_type;
}
    
//push input wire name
void gate::pushIn(int index){
	input_index.push_back(index);
}
//push output wire name
void gate::changeOut(int index){
	output=index;
}
//print the information of gate
void gate::print(){
	cout<<"printing gate"<<endl;
	cout<<"type= "<<gate_type<<endl;
	cout<<"input_num= "<<num_input<<endl;
	
	for(int i=0; i<input_index.size();i++){
		cout<<input_index[i]<<" "; 
	}
	cout<<endl;
	cout<<"output= "<<output<<endl;

}

//return the output node of the gate
int gate::returnOutput(){
	return output;

}
//return the input nodes of the gate
int* gate::returnInput(){
	
	int size = input_index.size();
	int* input_array=new int [size+1];
	input_array[0]=size;
	for(int i=0;i<size;i++){
		//cout<<input_index[i];
		input_array[i+1]=input_index[i];
	}
	return input_array;
}


//default constructor
node::node(){
	name="default name";
	cuttable=true;
	cut=false;
	myBranchNum.split=false;
	myBranchNum.num_branch=0;
}
//constructor that initialize the fields
node::node(string n, bool in){
	name=n;
    in_put=in;
	cuttable=true;
    cut=false;
	myBranchNum.split=false;
	myBranchNum.num_branch=0;
}

//desctructor
node::~node(){
}

//overloading operator
node & node::operator=(const node& source){
	name=source.name;	
	input=source.input;
	
	for(int i=0; i<source.output.size();i++)
	{	
		output[i]=source.output[i];
	}
	cuttable=source.cuttable;
    	cut=source.cut;
    	in_put=source.in_put;
	myBranchNum=source.myBranchNum;
	return *this;
}

//change gate type
void node::changeName(string n){
	name=n;	
}
//push input wire name
void node::addInput(int n){
	input=n;
}
//push output wire name
void node::addOutput(int n){
	output.push_back(n);
}
//print the information of node
void node::print(){
	cout<<"printing node"<<endl;
	cout<<"node name= "<<name<<endl;
	cout<<"input: "<<input<<" "<<endl; 
	for(int i=0;i<output.size();i++){
		cout<<"output: "<<output[i]<<endl;
	}
	cout<<"shared size= "<<	shared.size()<<endl;
	for(int i=0;i<shared.size();i++){
		cout<<"Shared input: "<<shared[i].input_index<<" Num of stages: "<<shared[i].num_of_gates<<endl;
	}
    if(in_put){
		cout<<"this node is input"<<endl;
	}
	else{
		cout<<"this node is not input"<<endl;
	}

	if(cuttable){
		cout<<"this is for decomposition, this node is cuttable"<<endl;
	}
	else{
		cout<<"this is for decomposition, this node is uncuttable"<<endl;
	}
    if(cut){
		cout<<"this is for decomposition, this node is cut"<<endl;
	}
	else{
		cout<<"this is for decomposition, this node is not cut"<<endl;
	}
	if(!(myBranchNum.split)){
		cout<<"This node doesn't branch"<<endl;
	}
	else{
		cout<<"This node has "<<myBranchNum.num_branch<<" number of branches"<<endl;
	}
	for(int i=0;i<PList.size();i++){
		cout<<"value: "<<PList[i].val<<" time"<<PList[i].time<<endl;
	}

}

//push Shared_input
void node::addSharedIn(shared_input in){
	shared.push_back(in);
}
//return all the output of current node
int* node::returnOutput(){
	int size = output.size();
	int* output_array=new int [size+1];
	output_array[0]=size;
	for(int i=0;i<size;i++){
		//cout<<output[i];
		output_array[i+1]=output[i];
	}
	return output_array;
}
//return output size
int node::returnOutputSize(){
	return output.size();
}


//return the input of current node
int node::returnInput(){
	int myInput=input;
	return myInput;
}
//get Shared_input index
int node::get_shared_input_ind(){
	return shared.size()-1;
}
//get Shared_input index
int node::get_shared_input(int index){
	return shared[index].input_index;
}
//get delay based on the index
int node::get_delay(int index){
	return shared[index].num_of_gates;
}
//set if the node is cuttable
void node::set_cut(bool con){
	cuttable=con;
}

//check if the node is cuttable
bool node::checkInput(){
	return in_put;
}

//change the branch structure for reconvergent fanout

void node::changeBranch(){
	myBranchNum.split=true;
	myBranchNum.num_branch++;
}
//return the branch strucutre it request
current_branch_num node::getBranch(){
	return myBranchNum;
}

//check all split structure to see if it's cuttable
int node::checkcuttable(){
	list<branch_cnt>::iterator it;
	if(branch.size()==0){
		return 0;	
	}
	for(it=branch.begin();it!=branch.end();it++){
		if(it->num_splits!=0){
			return 1;
		}
			
	}
	return 0;
}
//add the plist structure for the given node
void node::addPlistStruct(PListStruct listStruct){
    PList.push_back(listStruct);
}

void node::setOper(int op){
    oper=op;
}

int node::getOper(){
    return oper;
}
