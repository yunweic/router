#include <fstream>
#include <sstream>
#include <string>


using namespace std ;

int xsize, ysize ;

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


// assuming xsize,ysize are valid
void convert_line(int id, string line, ofstream& ofs){

  istringstream iss(line) ; 
  int top_x, bottom_x, minL, maxL ;

  iss >> top_x >> bottom_x >> minL >> maxL ;

  // we convert from vertical to horizontal
  
  ofs << "{id: " << id << endl ;
  ofs << "bounds: (" << minL << "," << maxL << ")" << endl ;
  ofs << "start_nodes {(" << 1 << "," << top_x+1 << ")}" << endl ;
  ofs << "end_nodes {(" << ysize << "," << bottom_x+1 << ")}}" << endl ;
  // We add 1 to all coords, since the coords start from 1 not 0.

}


int main(){

  ifstream ifs("input_nets") ;
  
  string line = getNextLine(ifs) ;
  istringstream iss(line) ;
  iss >> xsize >> ysize ;

  ofstream ofs("input_nets.old_format") ;
  ofs << ysize+1 << ", " << xsize+1 << endl; 
  //convert from vertical to horizontal
  // Also add 1, since the coords start from 1 instead of 0 in the old format

  line = getNextLine(ifs) ;
  int id = 0 ;
  while (ifs){
    convert_line(id++, line, ofs) ;
    line = getNextLine(ifs) ;
  }
  
  return 0 ;

}
