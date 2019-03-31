////============================================================
////   diagonal.cpp  -- pcb routing project
////   Calculate the region for diagonal routing
////   Author: Yun-Wei Chang
////   Date:   Jan. 5, 2011
////============================================================

#include "parse.h"
using namespace std;

//the main function that determine the dimension and location of the diagonal region. 


int xsize, ysize;
int right_pt, left_pt;
vector<net> nets;

vector<int> mid_boundary;
vector <int> left_boundary;
vector <int> right_boundary;

extern vector <pair<int,int> > chunks;
extern bool checktop(int numBlock);
extern bool checkbot(int numBlock);
extern bool checkmid(int numBlock, int start);

int dis;
int dir;

int main (int argc, char* argv[]){
	//check if the number of arg is correct	
	if(argc!=3&&argc!=2&&argc!=4&&argc!=5){
		cout<<"Usage: ./diagonal filename cap boundary create_boundary_filename create_boundary_filename2_if_needed"<<endl;
		return -1;
	}
	int cap;
	
	const char* boundary_file;
	const char* boundary_file2;
	int boundary=0;
	char* filename=argv[1];
	if(argc==6||argc==5||argc==4||argc==3){
		boundary_file2=argv[5];
	}
	if(argc==5||argc==4||argc==3){
		boundary_file=argv[4];
	}
	if(argc==4||argc==3){
		boundary=atoi(argv[3]);
	}
	FILE* file;
	string path;
	//get the path
	path="../";
	path.append(filename);
	
	//parse the file
	parse(path.c_str());

	if(ysize/10==0){
		cap=3;
	}
	else if(ysize/10==1){
		cap=4;
	}
	else{
		cap=5;
	}


	if(argc==3){
		cap=atoi(argv[2]);
	}

	//determine the direction of diagonal region
	dir=0;
	int max=calculate();

	int numBlock=cal_final_d(max);

	if(!check_bound()){
		cout<<"the Diagonal region cannot satisfy both criterion"<<endl;
	}
	else{cout<<"Constraint satisified"<<endl;}
	//print the informaiton of all the nets
	//print();

	cout<<"Max Block = "<<numBlock<<endl;
	
	int i;
  	printf ("Checking if processor is available...");
  	if (system(NULL)) puts ("Ok");
    	else exit (1);

	//generate new boundary file if guide line file is provided
	if((argc==5||argc==6)&&boundary==1){
		int i=create_boundary(boundary_file);
		//check if the guide line file is valid
		if(i==-1){
			cout<<"The guide line file is not valid"<<endl;
			return 0;
		}
		/*for(int j=0; j<mid_boundary.size();j++){
			cout<<"boundary: "<<mid_boundary[j]<<endl;
		}*/
	}
	//generate new boundary file if the chunk file is provided
	else if((argc==5||argc==6)&&boundary==2){
		if(argc==5){
			cout<<"Two files need to be specified the boundary files in lumps"<<endl;
			return 0;
		}
		int i=create_boundary_chunks(boundary_file, boundary_file2);
		//check if the guide line file is valid
		if(i==-1){
			cout<<"The chunk file is not valid"<<endl;
			return 0;
		}
		/*for(int j=0; j<mid_boundary.size();j++){
			cout<<"boundary: "<<mid_boundary[j]<<endl;
		}*/
	}
	else if(argc==4&&boundary!=0){
		cout<<"The files to create the boundary is not specified"<<endl;
		return 0;
	}

	//to indicate where the diagonal region is
	int region=ysize;

	//only create the new input file if the grid needs to be reduced
	if(numBlock>0){
		
		//cout<<"numBlock= "<<numBlock<<" dir= "<<dir<<endl;
	
		//parse the boundary file
   		string s;
   		ifstream ifs("../rObstacle");
   		//cout<<"right boundary is printed here:"<<endl;	
		while(ifs.good()){
		
			getline(ifs,s);
			if(s[0]==0){
				break;
			}
			while(ifs && (s[0]=='#'||s=="")){
				getline(ifs, s);
			}
			istringstream iss(s);
			int boundary;
			iss>>boundary;
			//cout<<boundary<<endl;
			right_boundary.push_back(boundary);
   		}

		ifs.close();
	

		//check left boundary
		ifstream ifs2("../lObstacle");
   		//cout<<"left boundary is printed here"<<endl;	
		while(ifs2.good()){

			getline(ifs2,s);
			if(s[0]==0){
				break;
			}
			while(ifs2 && (s[0]=='#'||s=="")){
  				getline(ifs2, s);
			}
			istringstream iss(s);
			int boundary;
			iss>>boundary;
			//cout<<boundary<<endl;
			left_boundary.push_back(boundary);
		}

		ifs2.close();

/**********************************The diagonal stuff*****************************************************************/		
		//the point for the middle region
		left_pt=0;
		right_pt=xsize;

		//ok need to decide which chunks to use here...may take some time
		bool topOk=checktop(numBlock);
		bool botOk=checkbot(numBlock);
		region=ysize/2-numBlock/2;
		bool midOk=checkmid(numBlock, region);
		cout<<"region= "<<region<<endl;
		//diagonal region at bottom
		if(botOk){
			region=ysize;
		}
		//diagonal region at top
		else if(topOk){
			cout<<"topOK!!!"<<endl;
			//rewrite the boundary file
			create_boundaryBot(numBlock);
		
			region=0;
			//return 0;
		}
		//diagonal region in the middle
		else if(midOk){
			cout<<"Middle"<<endl;
			//ok need to determine the start of the middle region
			region=ysize/2-numBlock/2;
		}
		else{
			for(int i=1; i<region;i++){
				midOk=checkmid(numBlock, region-i);
				if(midOk)
					break;
			}
			if(!midOk){
				for(int i=1;i<region;i++){
					midOk=checkmid(numBlock, region+i);
					if(midOk)
						break;
				}
			}
			if(!midOk){
				cout<<"The diagonal region cannot fit into the graph"<<endl;
				return 0;
			}
		}
		//generating a new output file to call the routing program corresponding to the region
		
			create_new_file(numBlock,region);
		
		
	}

	//execute the snakinig program
	cout<<"region= "<<region<<endl;
  	printf ("Executing command ROUTE...\n");
	chdir("..");
	char buffer [50];
	//with boundary
	
	if(argc==6||argc==4||argc==5){
		sprintf(buffer, "./route 1 %d %d %d %d %d", cap, numBlock, dir, region, 0);
	}
	//without boundary
	if(argc==2||argc==3){
		sprintf(buffer, "./route 0 %d %d %d %d %d", cap, numBlock, dir, region, 0);
	}
  	i=system (buffer);
	

	if(region!=ysize&&region!=0){
		create_2nd_file(numBlock,region);
		//execute the routing again!!!
		//cout<<"REGION= "<<region<<endl;
  		printf ("Executing command ROUTE...\n");
		char buffer [50];
		
		//with boundary
		if(argc==4)
			create_bot_boundary(numBlock, region);
		if(argc==4){
			sprintf(buffer, "./route 1 %d %d %d %d %d", cap, numBlock, 0, region, 1);
		}
		//without boundary
		if(argc==2||argc==3){
			sprintf(buffer, "./route 0 %d %d %d %d %d", cap, numBlock, 0, region, 1);
		}
  		i=system (buffer);
	}

	FILE* result;
	result=fopen("result", "w");
	for(int i=0;i<nets.size();i++)
		fprintf(result, "Net %d length = %d\n", i, 0);
	fclose(result);		

	//draw diagonal regions
	i=system("xfig out.fig &");
	
	//create the actual file again for the user to mask the process
	//create_post_file();


	return 0;
}
