#ifndef _ROUTE_H
#define _ROUTE_H

#include <vector>
#include <string>
#include <cmath>
#include <cstdlib>
using namespace std;

#define DEBUG

#define INT_INF 20000000 ;

extern int xsize, ysize ; // number of grid points

struct Logic_error{
  string err ;
  Logic_error(string s):err(s){} ;
};

struct Point{
  int x, y ;
  inline Point(int ix, int iy):x(ix),y(iy){} ;
  inline Point():x(-1), y(-1) {} ;
} ;

inline bool operator==(const Point& p1, const Point& p2){
  return p1.x == p2.x && p1.y == p2.y ;
}

inline bool operator!=(const Point& p1, const Point& p2){
  return !(p1==p2) ;
}

typedef enum BoundaryType {FALLING_MONOTONIC, RISING_MONOTONIC,
			   CONVEX_NONMONOTONIC, CONCAVE_NONMONOTONIC} ;

class Boundary{
  // each column can contain at most 2 segments in our algorithm
  vector<vector<int> > columns ; 
  vector<int> empty ; // a dummy vector to return as empty
  vector<int> rows ; // each row can contain exactly one segment

 public:
  BoundaryType type ;
  int minx, maxx ; // the span of the boundary
  vector<Point> points ;
  
  inline const vector<int>& getColumn(int c) const{
    if (c >= minx && c < maxx) // hor. segment i is between points [i,i+1]
      return columns[c-minx] ;
    else
      return empty ;
  }

  // given two adjacent points (x1,y) and (x2,y),
  // add the horizontal segment [x1,x2] to columns
  inline void addColumn(int x1, int x2, int y){
#ifdef DEBUG
    if (abs(x1-x2) != 1)
      throw Logic_error("The input points to addColumn are not adjacent") ;
#endif
    columns[min(x1,x2)-minx].push_back(y) ;
  }

  inline void addRow(int x, int y1, int y2){
    rows[min(y1,y2)] = x ;
  }

  inline int getRow(int r) const{
    return rows[r] ;
  }

  inline void setType(){
    if (minx < points[0].x && minx < points.back().x)
      type = CONCAVE_NONMONOTONIC ;
    else if (minx > points[0].x && minx > points.back().x)
      type = CONVEX_NONMONOTONIC ;
    else if (points[0].x > points.back().x)
      type = RISING_MONOTONIC ;
    else
      type = FALLING_MONOTONIC ;
  }

  void set_rows_and_columns() ;
  void reset(bool is_left_bndry) ;
  
  inline Boundary():minx(xsize), maxx(0){} ;

};

extern vector<Boundary> LBoundaries, RBoundaries ;

struct GPoint{ 
  //bool is_RB ; // a right boundary passing through this grid point ?
  //bool is_LB ; // a left boundary passing through this grid point ?
  inline GPoint():RB_index(-2), LB_index(-2){} ;

  inline bool is_LB(){ // a left boundary passing through this grid point ?
    return LB_index >= 0 ;
  }

  inline bool is_LB(int n){ // left bndry of n passing through this gpoint?
    return n >= 0 && LB_index == n ; 
  }
  inline void set_LB(int n){ // left bndry of n is passing through
    LB_index = n ;
  	}
	inline int return_LB(){
		return LB_index;

  }


  inline bool is_RB(){ // a right boundary passing through this grid point ?
    return RB_index >= 0 ;
  }

  inline bool is_RB(int n){ // right bndry of n passing through this gpoint?
    return n>=0 && RB_index == n ; 
  }
  inline void set_RB(int n){ // right bndry of n is passing through
    RB_index = n ;
  }

  inline int return_RB(){
		return RB_index;
	}

  private:
  int LB_index, RB_index ;

};

extern GPoint** gpoints ;


struct GCell{
  bool is_empty ;
  int min_label ; // used in findRoute() -- after the best flip found,
  //   and when we need to find the actual route
  // It is the distance from top of the gridcell to the bottom terminal

  int last_net ; // last_net is used as a timestamp
  inline GCell():last_net(-1), is_empty(true){}

};

extern GCell** gcells;

//big change here to accommodate the new program. A lot of attributes are used here
struct Net{
  int topT, bottomT ;  // top and bottom terminals
  int maxL, minL ; // max and min length constraints ;
  int length;
  
  vector<pair<int,int> > coord;
  vector<pair<int,int> >turn_pt;

  int last_dir;
  
  int up_streak;
  int right_streak;
  bool last_left;
  bool last_right;
  bool snake_on;
  bool furtherleft;
  vector<pair<int, int> > trap_cell;
} ;

extern vector<Net> nets ;


struct FlipInfo{

  int last_column ; // the last columnwise flip to perform
  int last_allocated_top ; // the y coord. of top gcell allocated by the
  //                            last set of "single flips"
  int last_allocated_bottom ; // the y coord. of top gcell allocated by the
  //                               last set of "single flips"
  // a flag to indicate that the next column also needs to be fliped. 
  bool flip_next;

  inline void set_invalid(){
    last_column = -1 ; last_allocated_top = -1; last_allocated_bottom = -1;}

};

#endif
