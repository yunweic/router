#include "construct_tcf.h"

#define NOT 0
#define NAND 1
#define NOR 2
#define AND 3
#define OR 4
#define XOR 5
#define DUMMY 6
//propagate the constraint for the entire circuit
void propagateConstraint(circuit* myCircuit, int index, int time){
    
    node* currentNode=myCircuit->getNode(index);
    PListStruct listStruct;
    listStruct.val=0;
    listStruct.time=time;
    currentNode->addPlistStruct(listStruct);
    
    listStruct.val=1;
    currentNode->addPlistStruct(listStruct);

    int gateInd=myCircuit->returnInput(index);

    int* gateInput=myCircuit->getGateInput(gateInd);
    int size= gateInput[0];

    for(int i=0;i<size;i++){
        
        propagateConstraint(myCircuit,gateInput[i+1],time-1);

    }
    
}

//get the tcf expression from 
void getTCF(circuit* myCircuit, int index, int time, int val){
    node* currentNode=myCircuit->getNode(index);
    
    //get the return input of index
    int gateInd=myCircuit->returnInput(index);
    gate* currentGate=myCircuit->getGate(gateInd);
    int type=currentGate->gettype();
    int nextval;
    switch(type){
        case NOT:
            if(val==1){
                nextval=0;
            }
            else{
                nextval=1;
                //currentNode->setOper();
            }
            break;
        case NAND:
            if(val==1){
                nextval=0;
                currentNode->setOper(1);
            }
            else{
                nextval=1;
                 currentNode->setOper(0);

            }
            break;
        case NOR:
            if(val==1){
                nextval=0;
                currentNode->setOper(0);

            }
            else{
                nextval=1;
                currentNode->setOper(1);
            }

            break;
        case AND:
            if(val==1){
                nextval=1;
                currentNode->setOper(0);
            }
            else{
                nextval=0;
                currentNode->setOper(1);
            }

            break;
        case OR:
            if(val==1){
                nextval=1;
                currentNode->setOper(1);

            }
            else{
                nextval=0;
                currentNode->setOper(0);
            }

            break;
        /*case XOR:
            if(val==1)
                nextval=0;
            else
                nextval=1;

            break;*/  
        case DUMMY:
            if(val==1)
                nextval=1;
            else
                nextval=0;
            time++;
            currentNode->setOper(-1);
            break;
        default:
            break;  
    }

    int* gateInput=myCircuit->getGateInput(gateInd);
    int size= gateInput[0];

    for(int i=0;i<size;i++){
        getTCF(myCircuit, gateInput[i+1], time-1, nextval);
    }
}

//propagate the tcf from output to input with a recursive approach
void construct_tcf(circuit* myCircuit, int time){
	//get output index
	int output_ind=myCircuit->getNumInput();
	
	int shared_size=myCircuit->get_shared_input_ind(output_ind);
	int min=myCircuit->gateLength();
	int max=0;
	//find the maximum and minimum delay
	for(int i=0;i<=shared_size;i++){
		int tmp=myCircuit->get_delay(output_ind, i);
		if(tmp>max){max=tmp;}
		if(tmp<min){min=tmp;}
	}

        myCircuit->setMaxDelay(max);

	//time constraint is impossible to meet
	if(time<min){
		cout<<"Probability to meet the time constraint is 0"<<endl;
		return;
	}

	//time constraint is greater than the maximum delay
	if(time>max){
		cout<<"Probability to meet the time constraint is 100"<<endl;
        return;
	}

    
    int index=myCircuit->getNumInput();
    
    propagateConstraint(myCircuit, index, time);	

    getTCF(myCircuit, output_ind, time, 0);

    //contstruct blif file for output =0
    //createBlifFile();

    getTCF(myCircuit, output_ind, time, 1);

    //contstruct blif file for output =1
    //createBlifFile();
}

