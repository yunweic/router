#include "route.h"
#include <iostream>

// the following macros used for Boundary::reset(bool)
#define LEFT_BNDRY true
#define RIGHT_BNDRY false

// set RBoundaries[net_ind], and mark GPoints
void findRightBoundary(int net_ind){

  RBoundaries[net_ind].reset(RIGHT_BNDRY) ;
  Net& net = nets[net_ind] ;
  
  // find the start and end points
  Point s = Point(net.topT + 1, 1) ;
  Point e = Point(net.bottomT + 1, ysize-1) ;
  
  int max_detour = (net.maxL - (ysize -1 + abs(net.topT-net.bottomT)))/2 ;
  int max_x = min (max(s.x, e.x) + 1 + max_detour, xsize) ;

  // RBoundaries[net_ind].minx = min(s.x, e.x) + 1 ;
  // Note that a right boundary can never be concave nonmonotonic 
  //     in our algorithm. But, still find minx below in case we change
  //     the algorithm later.


  Point p = s ; // start with the first point
  //gpoints[p.x][p.y].is_RB = true ; // mark the grid point as right boundary
  gpoints[p.x][p.y].set_RB(net_ind) ; // mark the grid point as right boundary

  RBoundaries[net_ind].points.push_back(p) ;
  
  // iterate until the end-point is hit
  while (p!= e){
    Point next ;

    if (p.y == e.y&& nets[net_ind].bottomT<p.x) // the last row
      next = Point(p.x-1, p.y) ;
	
	else if(p.y == e.y && nets[net_ind].bottomT>p.x)
		next= Point(p.x+1, p.y);
    
    // first try to go further to the right
    else if (p.x < max_x && ! gpoints[p.x+1][p.y].is_RB() &&
	     //make sure the trail can turn back
	     ! gpoints[p.x+1][p.y+1].is_RB())

      next = Point(p.x+1, p.y) ;

    // if can't go right, try to go down
    else if (!gpoints[p.x][p.y+1].is_RB())
      next = Point(p.x, p.y+1) ;

    // can't go right and down; so have to go left
    else{
#ifdef DEBUG
      if (gpoints[p.x-1][p.y].is_RB())
	throw Logic_error("A right boundary is blocked") ;
#endif
      next = Point(p.x-1, p.y) ;
    }

    //gpoints[next.x][next.y].is_RB = true ;
    gpoints[next.x][next.y].set_RB(net_ind) ;

    RBoundaries[net_ind].points.push_back(next) ;

    if (p.x < RBoundaries[net_ind].minx)
      RBoundaries[net_ind].minx = p.x ;
    if (p.x > RBoundaries[net_ind].maxx)
      RBoundaries[net_ind].maxx = p.x ;

    p = next ;
  }

  // check the endpoint in the end
  if (e.x < RBoundaries[net_ind].minx)
    RBoundaries[net_ind].minx = e.x ;
  if (e.x > RBoundaries[net_ind].maxx)
    RBoundaries[net_ind].maxx = e.x ;

  RBoundaries[net_ind].setType() ;

  RBoundaries[net_ind].set_rows_and_columns() ;

}



// Find the left boundary of net_ind, after it has been flipped completely
// we don't mark gpoints in this function
Boundary find_max_flipped_boundary(int net_ind){

  Boundary b ;
  
  Net& net = nets[net_ind] ;
  
  // find the start and end points
  Point s = Point(net.topT, 1) ;
  Point e = Point(net.bottomT, ysize-1) ;

  // the boundary will be determined by the right boundary of net_ind
  // Note that it can cross right bndry of net_ind - 1

  Point p = s ; // start with the first point
  b.points.push_back(p) ;
  
  bool can_go_right = true ;
  // we need such a bool value, because we don't mark gpoints in this routine

  // iterate until the end-point is hit
  while (p!= e){
    Point next ;

    if (p.y == e.y) // the last row
      next = Point(p.x-1, p.y) ;
    
    // first try to go further to the right
    else if (can_go_right && p.x+1 <= xsize && 
	     !gpoints[p.x+1][p.y].is_RB(net_ind) &&
	     //make sure the trail can turn back
	     ! gpoints[p.x+1][p.y+1].is_RB(net_ind))
      next = Point(p.x+1, p.y) ;

    // if can't go right, try to go down
    else if (!gpoints[p.x][p.y+1].is_RB(net_ind)){
      next = Point(p.x, p.y+1) ;
      can_go_right = true ;
      // after we go down, the boundary can go right again
    }

    // can't go right and down; so have to go left
    else{
#ifdef DEBUG
      if (gpoints[p.x-1][p.y].is_RB(net_ind))
	throw Logic_error("A max-flipped boundary is blocked") ;
#endif
      next = Point(p.x-1, p.y) ;
      can_go_right = false ; 
      // once we turn left, we can't go right on the same row
      // Note that we need this because we are not marking gpoints
    }

    b.points.push_back(next) ;

    if (p.x < b.minx)
      b.minx = p.x ;
    if (p.x > b.maxx)
      b.maxx = p.x ;

    p = next ;
  }

  // check the endpoint in the end
  if (e.x < b.minx)
    b.minx = e.x ;
  if (e.x > b.maxx)
    b.maxx = e.x ;

  b.setType() ;

  b.set_rows_and_columns() ;

  return b ;
}





// set LBoundaries[net_ind], and mark GPoints
void findLeftBoundary(int net_ind){

  LBoundaries[net_ind].reset(LEFT_BNDRY) ;
  Net& net = nets[net_ind] ;
  
  // find the start and end points
  Point s = Point(net.topT, 1) ;
  Point e = Point(net.bottomT, ysize-1) ;
  
  int max_detour = (net.maxL - (ysize -1 + abs(net.topT-net.bottomT)))/2 ;
   //changed here

   int min_x;
   //if(net_ind!=0){
  	min_x = max(min(s.x, e.x) - max_detour, 0) ;
  // }
   //else
//	min_x=0;
   //end here
  //LBoundaries[net_ind].minx = min_x ;
  //LBoundaries[net_ind].maxx = max(s.x, e.x) - 1 ;

  Point p = s ; // start with the first point
  //gpoints[p.x][p.y].is_LB = true ; // mark the grid point as left boundary
  gpoints[p.x][p.y].set_LB(net_ind) ; // mark the grid point as left boundary
  LBoundaries[net_ind].points.push_back(p) ;
  
  // iterate until the end-point is hit
  while (p!= e){
    Point next ;
	if(net_ind!=0){
    	if (p.y == e.y){ // the last row
			if(p.x<e.x)
      			next = Point(p.x+1, p.y) ; // go back to the end point
			else if(p.x>e.x)
				next=Point(p.x-1,p.y);
    	}
    	// first try to go further to the left
    	else if (p.x > 0 && 
		! gpoints[p.x-1][p.y].is_LB() &&
	    // gcells[p.x-1][p.y].is_empty &&
	    //make sure the trail can turn back
	    ! gpoints[p.x-1][p.y+1].is_LB()&&nets[net_ind-1].coord[p.y].second < p.x - 1 && nets[net_ind-1].coord[p.y].first < p.x - 1&&nets[net_ind-1].coord[p.y-1].second < p.x - 1)// && nets[net_ind-1].coord[p.y-1].first < p.x - 1) 
		//&&gcells[p.x-1][p.y+1].is_empty)
      		next = Point(p.x-1, p.y) ;

    	// if can't go left, try to go down
    	else if (!gpoints[p.x][p.y+1].is_LB()&&nets[net_ind-1].coord[p.y+1].second < p.x && nets[net_ind-1].coord[p.y+1].first<p.x)// && gcells[p.x][p.y].is_empty)
      	// note that we use gcells[p.x][p.y] in purpose (i.e. not [p.y-1]).
      	// because we want to check the gridcell whose upperleft corner 
      	//   is p.x, p.y. If it is empty, we can go down
      		next = Point(p.x, p.y+1) ;
			// can't go left and down; so have to go right
    	else{
#ifdef DEBUG
      		//if (gpoints[p.x+1][p.y].is_LB())
			//	throw Logic_error("A left boundary is blocked") ;
#endif
      		next = Point(p.x+1, p.y) ;
    	}

	}
	else{
		if (p.y == e.y) // the last row
      		next = Point(p.x+1, p.y) ; // go back to the end point
    
    	// first try to go further to the left
    	else if (p.x > 0 && 
		! gpoints[p.x-1][p.y].is_LB() &&
	    // gcells[p.x-1][p.y].is_empty &&
	    //make sure the trail can turn back
	    ! gpoints[p.x-1][p.y+1].is_LB()) 
		//&&gcells[p.x-1][p.y+1].is_empty)
      		next = Point(p.x-1, p.y) ;

    	// if can't go left, try to go down
    	else if (!gpoints[p.x][p.y+1].is_LB())// && gcells[p.x][p.y].is_empty)
      	// note that we use gcells[p.x][p.y] in purpose (i.e. not [p.y-1]).
      	// because we want to check the gridcell whose upperleft corner 
      	//   is p.x, p.y. If it is empty, we can go down
      		next = Point(p.x, p.y+1) ;

	

    	// can't go left and down; so have to go right
    	else{
#ifdef DEBUG
      		//if (gpoints[p.x+1][p.y].is_LB())
			//	throw Logic_error("A left boundary is blocked") ;
#endif
      		next = Point(p.x+1, p.y) ;
    	}
	}
    //gpoints[next.x][next.y].is_LB = true ;
    gpoints[next.x][next.y].set_LB(net_ind) ;
    LBoundaries[net_ind].points.push_back(next) ;

    if (p.x < LBoundaries[net_ind].minx)
      LBoundaries[net_ind].minx = p.x ;
    if (p.x > LBoundaries[net_ind].maxx)
      LBoundaries[net_ind].maxx = p.x ;


    p = next ;
  }

  // check the endpoint in the end
  if (e.x < LBoundaries[net_ind].minx)
    LBoundaries[net_ind].minx = e.x ;
  if (e.x > LBoundaries[net_ind].maxx)
    LBoundaries[net_ind].maxx = e.x ;

  LBoundaries[net_ind].setType() ;

  LBoundaries[net_ind].set_rows_and_columns() ;

  
}
// set LBoundaries[net_ind], and mark GPoints
void findLeftBoundary2(int net_ind){

  LBoundaries[net_ind].reset(LEFT_BNDRY) ;
  Net& net = nets[net_ind] ;
  
  // find the start and end points
  Point s = Point(net.topT, 1) ;
  Point e = Point(net.bottomT, ysize-1) ;
  
  int max_detour = (net.maxL - (ysize -1 + abs(net.topT-net.bottomT)))/2 ;
   //changed here

   int min_x;
   //if(net_ind!=0){
  	min_x = max(min(s.x, e.x) - max_detour, 0) ;
  // }
   //else
//	min_x=0;
   //end here
  //LBoundaries[net_ind].minx = min_x ;
  //LBoundaries[net_ind].maxx = max(s.x, e.x) - 1 ;

  Point p = s ; // start with the first point
  //gpoints[p.x][p.y].is_LB = true ; // mark the grid point as left boundary
  gpoints[p.x][p.y].set_LB(net_ind) ; // mark the grid point as left boundary
  LBoundaries[net_ind].points.push_back(p) ;
  
  // iterate until the end-point is hit
  while (p!= e){
    Point next ;
	
		if (p.y == e.y){ // the last row
			if(e.x>p.x)
      			next = Point(p.x+1, p.y) ; // go back to the end point
			else
				next=Point(p.x-1,p.y);
    	}
    	// first try to go further to the left
    	else if (p.x > 0 && 
		! gpoints[p.x-1][p.y].is_LB() &&
	    // gcells[p.x-1][p.y].is_empty &&
	    //make sure the trail can turn back
	    ! gpoints[p.x-1][p.y+1].is_LB()) 
		//&&gcells[p.x-1][p.y+1].is_empty)
      		next = Point(p.x-1, p.y) ;

    	// if can't go left, try to go down
    	else if (!gpoints[p.x][p.y+1].is_LB())// && gcells[p.x][p.y].is_empty)
      	// note that we use gcells[p.x][p.y] in purpose (i.e. not [p.y-1]).
      	// because we want to check the gridcell whose upperleft corner 
      	//   is p.x, p.y. If it is empty, we can go down
      		next = Point(p.x, p.y+1) ;

	

    	// can't go left and down; so have to go right
    	else{
#ifdef DEBUG
      		//if (gpoints[p.x+1][p.y].is_LB())
			//	throw Logic_error("A left boundary is blocked") ;
#endif
      		next = Point(p.x+1, p.y) ;
    	}
	
    //gpoints[next.x][next.y].is_LB = true ;
    gpoints[next.x][next.y].set_LB(net_ind) ;
    LBoundaries[net_ind].points.push_back(next) ;

    if (p.x < LBoundaries[net_ind].minx)
      LBoundaries[net_ind].minx = p.x ;
    if (p.x > LBoundaries[net_ind].maxx)
      LBoundaries[net_ind].maxx = p.x ;


    p = next ;
  }

  // check the endpoint in the end
  if (e.x < LBoundaries[net_ind].minx)
    LBoundaries[net_ind].minx = e.x ;
  if (e.x > LBoundaries[net_ind].maxx)
    LBoundaries[net_ind].maxx = e.x ;

  LBoundaries[net_ind].setType() ;

  LBoundaries[net_ind].set_rows_and_columns() ;

  
}
// assuming "::points", "::minx", and "::maxx" are valid
void Boundary::set_rows_and_columns(){

  rows.resize(ysize) ;
  columns.resize(maxx-minx+1) ;

  rows[0] = points[0].x ;
  for (int i=1; i<points.size(); i++){

    if (points[i-1].y == points[i].y) // a horizontal segment
      addColumn(points[i-1].x, points[i].x, points[i].y) ;
    else if (points[i-1].x == points[i].x) // a vertical segment
      addRow(points[i-1].x, points[i-1].y, points[i].y) ;
#ifdef DEBUG
    else
      throw Logic_error("Two points are not adjacent in a boundary");
#endif

  }

  rows[ysize-1] = points.back().x ; // the last row

}


void Boundary::reset(bool is_left_bndry){
  
  // first reset the grid points on which this bndry is passing through
  for (int i=0;i<points.size(); i++){
    if (is_left_bndry)
      gpoints[points[i].x][points[i].y].set_LB(-1) ;
    else
      gpoints[points[i].x][points[i].y].set_RB(-1) ;
  }

  points.resize(0) ;
  columns.resize(0) ;
  rows.resize(0) ;
  minx = xsize ;
  maxx = 0 ;
}


#include <fstream>
extern void drawBoundary(ofstream& ofs, Boundary b) ;
extern void writeHeaderFig(ostream& os) ;
//extern void drawGrid(ofstream& ofs) ;

void find_all_right_boundaries(){

  ofstream ofs("out_t.fig") ;
  writeHeaderFig(ofs) ;
  //drawGrid(ofs) ;

   for (int i=nets.size()-1; i>=0; i--){
    findRightBoundary(i) ;
    //drawBoundary(ofs, RBoundaries[i]) ;

		/*for(int j=0;j<xsize;j++){
			for(int k=0;k<ysize;k++){
				int temp=gpoints[j][k].return_RB();
				cout<<"net_ind= "<<i<<" j= "<<j<<" k= "<<k<<" here= "<<temp<<endl;;
			}
		}*/
  }
    //made some changes here
/*
 Point p;
 for(int i=0;i<3;i++){
  gpoints[xsize-2][4+i].set_RB(nets.size()-2); 
  
  p=Point(xsize-2,4+i);
  
  RBoundaries[nets.size()-2].points.push_back(p) ;
}

    if (p.x < RBoundaries[nets.size()-2].minx)
      RBoundaries[nets.size()-2].minx = p.x ;
    if (p.x > RBoundaries[nets.size()-2].maxx)
      RBoundaries[nets.size()-2].maxx = p.x ;

	cout<<"here"<<endl;
	//for(int i=0;i<nets.size();i++){
		for(int j=0;j<RBoundaries[2].points.size();j++){
    	    		cout<<"i= "<<2<<" right: "<<RBoundaries[2].points[j].x<<" "<<RBoundaries[2].points[j].y<<endl;
		}

    	//}

	cout<<"end here"<<endl;
  */
//to here

}



