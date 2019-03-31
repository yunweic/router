#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#define NUMNETS 250
#define XOFFSET 0
#define CHANNEL_WIDTH 200

#define INF 2000000

using namespace std ;

extern float box_muller(float m, float s) ;


struct Net{
  int start ; // position of start terminal
  int end ; // position of end terminal
  int target ;
  inline Net(int s, int e, int t):start(s), end(e), target(t){} ;
};

void writeProblem(int xsize, int ysize, vector<Net>& nets){
  
  ofstream ofs("input_nets") ;

  ofs << "# xsize ysize" << endl << endl ;

  ofs << xsize << " " << ysize << endl << endl ;

  ofs << "# Each line below corresponds to a net" << endl ;
  ofs << "# Format for one line is: <top_term_x> <bottom_term_x> <minL> <maxL>" << endl << endl ;

  for (int i=0; i<nets.size(); i++)
    ofs << nets[i].start << " " << nets[i].end << " " 
	<< nets[i].target << " " << nets[i].target+1 << endl ;
      
}


int main(int argc, char** argv){

  if (argc != 6){
    cout << "Usage is: " << argv[0] 
	 << " density_mean density_dev extra_length_mean extra_length_dev "
	 << "seed" << endl ;
    exit(0) ;
  }
  
  float density_mean = atof( argv[1]) ;
  float density_dev = atof(argv[2]) ;
  float extra_length_mean = atof(argv[3]) ;
  float extra_length_dev = atof(argv[4]) ;
  
  int seed = atoi(argv[5]) ;
  srand(seed) ;

  int xsize ;
  int ysize = CHANNEL_WIDTH ;

  vector<Net> nets ;
  int top_x = 0 ;
  int bottom_x = XOFFSET ;
  for (int i=0;i<NUMNETS;i++){
    
    int top_space = max(1, (int) box_muller(density_mean, density_dev)) ;
    int bottom_space = max(1, (int) box_muller(density_mean, density_dev)) ;

    top_x += top_space ;
    bottom_x += bottom_space ;
    
    int extra_length = max(1, (int) box_muller(extra_length_mean,
					       extra_length_dev)) ;

    int target = abs(top_x - bottom_x) + ysize-1 + extra_length ;

    nets.push_back(Net(top_x, bottom_x, target)) ;

  }

  xsize = max(top_x, bottom_x)+1 ;

  writeProblem(xsize, ysize, nets) ;

  return 0 ;
}



