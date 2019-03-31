#include "decompose.h"
#include <queue>
//decompose the circuit
void decompose(circuit* myCircuit, int min){
	cout<<"min: "<<min<<endl;
	//declare a queue for BFS
	queue<int> myqueue;

	map<int, int> shared_in;
	map<int, int>::iterator it_shared;
	pair<map<int, int>::iterator, bool> shared_ret;
	
	//BFS start with output
	int index=myCircuit->getNumInput();
	int currentNode;	
	myqueue.push(index);
	int* myInputArray;

	//loop starts here
	while(!myqueue.empty()){
		//create a hash table to check for shared input
		map<int, int> mymap;
		map<int, int>::iterator it;
		pair<map<int, int>::iterator, bool> ret;

		currentNode=myqueue.front();
		myqueue.pop();
		//check if any inputs are shared
		for(int i=0;i<=myCircuit->get_shared_input_ind(currentNode);i++){
			it_shared=shared_in.find(myCircuit->get_shared_input(currentNode, i));
			if(myCircuit->get_shared_input_ind(currentNode)<(min-1)&&!myCircuit->checkInput(currentNode)){
				myCircuit->set_cut(currentNode, false);
				break;
			}
			if(it_shared!=shared_in.end()&&!myCircuit->checkInput(currentNode)){
				node* current=myCircuit->getNode(currentNode);
				if(current->checkcuttable()==1){
				    	myCircuit->set_cut(currentNode,false);
				}
				break;	
			}
		}
		int gateind=myCircuit->returnInput(currentNode);
		if(gateind<myCircuit->gateLength()){
			myInputArray=myCircuit->getGateInput(gateind);
			int size=myInputArray[0];
			//loop through all the children
			for(int i=0;i<size;i++){
				int tmp=myInputArray[i+1];
				//try to insert the input in the hash table for each node
				for(int j=0;j<=myCircuit->get_shared_input_ind(tmp);j++){
					int in=myCircuit->get_shared_input(tmp, j);
					it=mymap.find(in);
					if(it!=mymap.end()){
						if(it->second!=i){
							shared_in.insert(pair<int, int>(in, i));
						}
					}
					else{
						mymap.insert(pair<int, int>(in,i));
					}
				}	
					
				myqueue.push(myInputArray[i+1]);
			}
		}
	}
	delete [] myInputArray; 
}
