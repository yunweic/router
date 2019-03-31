#include"shared_in.h"
#include <queue>

//The depth first search function to propagate the constraint
void depthFirstSearch(circuit* myCircuit, int index, int input, int num_gates){
	//push the content of the current node
	shared_input in;
	in.input_index=input;
	in.num_of_gates=num_gates;
	myCircuit->addSharedInput(index, in);	
	

	int* outgate=myCircuit->returnOutput(index);
	int size=outgate[0];
	//check to see if the current node has multiple fanouts

	for(int i=0;i<size;i++){
		int nodeIndex=myCircuit->getGateOutput(outgate[i+1]);
		depthFirstSearch(myCircuit, nodeIndex, input, num_gates+1);
	}

}
//keep track of the number of split of each fanout node
void DFSforSplit(circuit* myCircuit, int index){
	//push the content of the current node
	
	node* currentNode=myCircuit->getNode(index);	

	int* outgate=myCircuit->returnOutput(index);
	int size=outgate[0];
	//check to see if the current node has multiple fanouts
	bool cond=(currentNode->getBranch()).split;
	
	for(int i=0;i<size;i++){
		int nodeIndex=myCircuit->getGateOutput(outgate[i+1]);
		node* nextNode=myCircuit->getNode(nodeIndex);
		//if there's multiple fanouts, denote that
		
        if(cond){
			list<branch_cnt>::iterator it2;
            list<branch_cnt>::iterator it1;
            it1=currentNode->branch.begin();
            it2=nextNode->branch.begin();

			//find if it has been visited already
            //visited
			if(it1->node_ind==it2->node_ind){
				if(it2->num_splits<it1->num_splits){
                    if(it2->num_splits!=0){
                        it2->num_splits--;
                    }
                }
                else{
                    if(it1->num_splits!=0)
                        it2->num_splits=it1->num_splits-1;
                    else
                        it2->num_splits=0;
                }
            }	
			else{
					branch_cnt nextBranch=*it1;
                    int temp=currentNode->returnOutputSize()-1;
					nextBranch.num_splits+=temp;
					nextNode->branch.push_front(nextBranch);	
		    }
		}
		else{
			
			list<branch_cnt>::iterator it1;
			list<branch_cnt>::iterator it2;
            it1=currentNode->branch.begin();
            it2=nextNode->branch.begin();

			//find if there's a match
			if(it1->node_ind==it2->node_ind){
				if(it2->num_splits<it1->num_splits){
                    if(it2->num_splits!=0)
                        it2->num_splits--;
                }
                else{
                    if(it1->num_splits!=0)
                        it2->num_splits=it1->num_splits-1;
                    else
                        it2->num_splits=0;
                }
            }
                
            else{
					branch_cnt nextBranch=*it1;
					nextNode->branch.push_front(nextBranch);    
				}	
        }
		DFSforSplit(myCircuit, nodeIndex);
	}

}
//propagate the delay for all nodes depending on the primary input
void propagate_in(circuit* myCircuit){
	//start with one of the input node
	int input_index;
	//int index;
	//iterate through all the primary input
	for(input_index=0;input_index<myCircuit->getNumInput();input_index++){

		depthFirstSearch(myCircuit, input_index, input_index, 0);
		
	}
}


//propagate the node starting from the multiple fanout ones
void propagate_fanout(circuit* myCircuit){
	//start with one of the input node
	int split_node_index;
	//int index;
	//iterate through all the primary input	
    for(split_node_index=0;split_node_index<myCircuit->getNumSplitNode();split_node_index++){
        myCircuit->printFanout(split_node_index);
		
	}
	for(int i=0;i<myCircuit->getNumSplitNode();i++){
       
		int index=myCircuit->ret_split_node(i);
        
        node* currentNode=myCircuit->getNode(index);

		branch_cnt currentBranch;
		currentBranch.node_ind=index;
		currentBranch.num_splits=0;
		currentNode->branch.push_front(currentBranch);

		DFSforSplit(myCircuit, index);
		
	}
}


