#include "route.h"
#include <iostream>
#include <fstream>
#include <sstream>

//declare the functions used for main.C
extern int read_nets() ;
extern void drawGrid(ofstream& ofs, int start) ;
extern void drawBoundary(ofstream& ofs, Boundary b) ;
extern void find_all_right_boundaries() ;
extern void writeHeaderFig(ostream& os) ;
extern void findLeftBoundary(int net_ind) ;
extern void route_all_min_area() ;
extern void route_all_min_length(ofstream& outputfile, int region, int numBlock, int draw_bot) ;
void drawRoute(ofstream& ofs, vector<pair<int,int> > route, int net_ind, int region, int numBlock, int draw_bot) ;
void draw_diagonal(ofstream& ofs, int num, int dir, int region);

extern int create_boundary();
extern int create_boundaryBot(int topsize);

extern vector<vector<pair<int,int> > > routes ;

//the additional vectors used in the new version
//change here
vector<int> right_boundary;
vector<int> left_boundary;
vector<int> prev_route;

bool bound_on;
int min_bound;
int max_bound=0;
int cap;

int diagonal_dir;
//end here

int main(int argc, char* argv[]){
	//initialize the variables used in the new version
	int draw_bot=0;
	int	diagonal_on =0;
	diagonal_dir=0;
	int temp=1;
	int region;
	//read the inline arguments
	if(argc>7){cerr<<"Usage: ./route bound_on cap diagonal_on diagonal_dir diagonal_region bottom"<<endl; return -1;}
	if(argc==2||argc==3||argc==4||argc==5||argc==6||argc==7){
		bound_on=atoi(argv[1]);}
	
	if(argc==4||argc==5||argc==6||argc==7)
		diagonal_on=atoi(argv[3]);
	if(argc==5||argc==6||argc==7)
		diagonal_dir=atoi(argv[4]);
	if(argc==6||argc==7)
		region=atoi(argv[5]);
	if(argc==7)
		draw_bot=atoi(argv[6]);

	if(diagonal_dir==0)
		temp=0;
	
	min_bound=100000;

  try{

    vector<pair<int,int> > rboundary_points;

    if(read_nets()==-1){
		cout<<"Error: The nets do not follow the left to right order in the input file"<<endl;
		return 0;
	}
	//set the default value for the cap variable
	if(ysize/10==0){
		cap=3;
	}
	else if(ysize/10==1){
		cap=4;
	}
	else{
		cap=5;
	}
	
	//set the cap variable if the user specify one
	if(argc==3||argc==4||argc==5||argc==6||argc==7)
		cap=atoi(argv[2]);			

    find_all_right_boundaries() ;

	//if the user uses boundary files
    if(bound_on){
    	//parse the boundary file
    	string s;
    	ifstream ifs("rObstacle");
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
			if (boundary<min_bound)
				min_bound=boundary;
			//cout<<boundary<<endl;
			right_boundary.push_back(boundary);
    	}

		ifs.close();
		//check to see if the right boundary is valid
		if(right_boundary[0]<=nets[nets.size()-2].topT || right_boundary[ysize-1]<=nets[nets.size()-2].bottomT){
			cout<<"Right boundary needs to be more to the right than the rightmost net"<<endl;
			return -1;
		}

		//parse left boundary
		ifstream ifs2("lObstacle");
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
			if(max_bound<boundary)
				max_bound=boundary;
			//cout<<boundary<<endl;

			left_boundary.push_back(boundary);
    	}

		ifs2.close();
		//check left boundary
		if(left_boundary[0]>nets[0].topT || left_boundary[ysize-1]>nets[0].bottomT){
			cout<<"Left boundary needs to be more to the left than the leftmost net"<<endl;
			return -1;
		}
    }
	//if the user didn't specify the boundary, set the right and left boundary vector to be 0 and xsize-1
	if(bound_on==0){
		for(int i=0;i<ysize;i++){
			right_boundary.push_back(xsize-1);
			left_boundary.push_back(0);
			
		}
		/*for(int i=0;i<right_boundary.size();i++){
			cout<<"right "<<right_boundary[i]<<endl;
			cout<<"left "<<left_boundary[i]<<endl;
		}*/
		bound_on=1;
	}

    if(bound_on){
   		
      	//translate the x coordinate into a one that can be used for drawing
		rboundary_points.push_back(make_pair(right_boundary[0]*100,0));
   
   		for(int i=0; i<right_boundary.size();i++){
			if(i!=0){
				if(right_boundary[i]!=right_boundary[i-1]){
					rboundary_points.push_back(make_pair(right_boundary[i]*100,100*i));
				}
			}
			rboundary_points.push_back(make_pair(right_boundary[i]*100,100*i+100));
   		}
   		rboundary_points.push_back(make_pair(right_boundary[right_boundary.size()-1]*100,100*(right_boundary.size()+1)));
    }
    //print all RBoundaries
    /*for(int i=0;i<nets.size();i++){
		for(int j=0;j<RBoundaries[i].points.size();j++){
    	    cout<<"i= "<<i<<" right: "<<RBoundaries[i].points[j].x<<" "<<RBoundaries[i].points[j].y<<endl;
		}
    }*/
	//changed here
	//detremine the direction of the bus
	for(int i=0;i<nets.size();i++){
		//forward direction
		if(nets[i].topT>nets[i].bottomT&&diagonal_dir!=2)
			diagonal_dir=1;
		//backward direction
		else if(nets[i].topT<nets[i].bottomT&&diagonal_dir!=1)
			diagonal_dir=2;
	}

	//determine the number of block used in top region
	int topblock=0;
	if(region==0&&diagonal_on!=0){
		topblock=diagonal_on;
	}

	//end here
	ofstream ofs;
	
	//draw the grid initially
	if(!draw_bot){	
    	ofs.open("out.fig") ;
    	writeHeaderFig(ofs) ;
    	drawGrid(ofs, topblock) ;
	}
	else{
		ofs.open("out.fig", ios_base::app);
		drawGrid(ofs, region+diagonal_on);
	}

    //route_all_min_area() ;
    route_all_min_length(ofs, region, diagonal_on, draw_bot) ;
	
    //print left boundary
    /*for(int i=0;i<nets.size();i++){
		cout<<"size= "<<LBoundaries[i].points.size()<<endl;
		for(int j=0;j<LBoundaries[i].points.size();j++){
    	    cout<<"i= "<<i<<" left: "<<LBoundaries[i].points[j].x<<" "<<LBoundaries[i].points[j].y<<endl;
		}
    }*/
	//changed here
	//end here
	//read the nets length from the previous result
	int prevLength[nets.size()];
	FILE* newfile;
	string s;
    fstream file_op("result",ios::in);
	int prev=0;
	int i=0;
	while(file_op >> s){
	//	cout<<s<<endl;
		if(s[0]=='='){
			file_op>> s;
			istringstream iss(s);
			iss>>prev;
			prevLength[i]=prev;
			i++;
		}
	}
	file_op.close();
	//write the new wire length in the result
	newfile = fopen("result","w");
	int temp2=0;
	if(prevLength[0]!=0)
		temp2=1;	
    for (int i=0; i<nets.size()-1; i++){
      //drawBoundary(ofs, RBoundaries[i]) ;
      //findLeftBoundary(i) ;
      //drawBoundary(ofs, LBoundaries[i]) ;
    /*  drawRoute(ofs, routes[i],i) ;
    }*/
		//print the length of the nets
		//cout<<"Net "<<i<<" length= "<<nets[i].length+ceil(sqrt(2)*diagonal_on*temp+temp2)<<endl;
		fprintf(newfile,"Net %d length = %d\n", i, (int) (nets[i].length+ceil(sqrt(2)*diagonal_on*temp))+prevLength[i]+temp2);
		cout<<"Net "<<i<<" total length = "<< (nets[i].length+ceil(sqrt(2)*diagonal_on*temp))+prevLength[i]+temp2<<endl;
		//print which net is not satisfied
		if(nets[i].minL>nets[i].length){
			cout << "Min length constraint for net " << i << " not satisfied"<<endl; 
		}

		if(nets[i].maxL<nets[i].length){
			cout << "Max length constraint for net " << i << " not satisfied"<<endl; 
		}
	}
	fclose(newfile);
	//changed here
	//print the diagonal file
  cout<<"diagonal: "<<diagonal_on<<endl;
  //draw \ diagonal lines
  if(diagonal_on&&!draw_bot){
 	draw_diagonal(ofs,diagonal_on, diagonal_dir, region); 
  }
  ofs.close();

//end here

  }
  catch (Logic_error e){
    cout << "Logic error: " << e.err << endl ;
  }

}
