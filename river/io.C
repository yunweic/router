#include <fstream>
#include <string>
#include <sstream>

#include "route.h"

int xsize, ysize ;
GPoint** gpoints ;
GCell** gcells ;
vector<Net> nets ;
vector<Boundary> LBoundaries ;
vector<Boundary> RBoundaries ;



string getNextLine(ifstream& ifs){

  string s ;
  getline(ifs, s) ;
  
  while (ifs && (s[0] == '#' || s == ""))
    getline(ifs, s) ;

  if (ifs)
    return s ;
  else
    return "" ;

}

//return -1 if reading thet nets fails.
int read_nets(){

  ifstream ifs("input_nets") ;

  string line = getNextLine(ifs) ;
  istringstream iss_first(line) ;

  iss_first >> xsize >> ysize ;
  // xsize/ysize is the number of grid cells in one direction
  // The number of grid points in each direction is one more

  // Since the last net is not explicitly checked in this version, 
  // we add a pseudo net at the end with top/bottom terminals at "xsize". 
  // The target length for this net will be equal to ysize so that it will
  // act as the right boundary. 
  // Due to this net, we increment xsize by 1
  xsize += 1 ; 



  gpoints = new GPoint* [xsize+1] ;
  for (int i=0; i<=xsize; i++)
    gpoints[i] = new GPoint[ysize+1] ;

  gcells = new GCell* [xsize] ;
  for (int i=0; i<=xsize; i++)
    gcells[i] = new GCell[ysize] ;




  line = getNextLine(ifs) ;
  while (ifs){
    istringstream iss(line) ;

    Net n ;
    iss >> n.topT >> n.bottomT >> n.minL >> n.maxL ;
    //n.minL += 5 ;
    //n.maxL += 5 ;

	//check if the nets are in order
	if(nets.size()!=0){
		if((n.topT<=nets[nets.size()-1].topT||n.bottomT<=nets[nets.size()-1].bottomT)){
			return -1;	
		}
	}

    nets.push_back(n) ;

    line = getNextLine(ifs) ;
  }

  
  // add the pseudo net now (see comments above) :
  Net n ;
  n.topT = xsize-1 ;
  n.bottomT = xsize-1 ;
  n.minL = ysize-1 ;
  n.maxL = ysize-1 ;
  nets.push_back(n) ;
  


  LBoundaries.resize(nets.size()) ;
  RBoundaries.resize(nets.size()) ;


}

//create the left and right boundary file base on the guideline.
int create_boundary(){
	
	FILE* outfile;
	FILE* outfile2;

	outfile = fopen("rObstacle", "w");
	outfile2 = fopen("lObstacle", "w");

	for(int i=0; i<ysize;i++){
		fprintf(outfile, "%d\n",xsize-1);
		fprintf(outfile2, "%d\n", 0);			
	}

	fclose(outfile);
	fclose(outfile2);
	
 	return 0;
}
//this is for recovering the boundary files 
/*int create_boundaryBot(int topsize){
	
	FILE* outfile;
	FILE* outfile2;

	outfile = fopen("rObstacle", "w");
	outfile2 = fopen("lObstacle", "w");

	for(int i=topsize; i<right_boundary.size();i++){
		fprintf(outfile, "%d\n",right_boundary[i]);
		fprintf(outfile2, "%d\n", left_boundary[i]);			
	}
	for(int i=0;i<topsize;i++){
		fprintf(outfile, "%d\n",right_boundary[i]);
		fprintf(outfile2, "%d\n", left_boundary[i]);			

	}

	fclose(outfile);
	fclose(outfile2);
	
 	return 0;
}*/



