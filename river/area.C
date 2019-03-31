#include "route.h"
#include <iostream>

extern void findLeftBoundary(int net_ind) ;
extern Boundary find_max_flipped_boundary(int net_ind) ;

extern int bound_on;

extern vector<int> left_boundary;
extern vector<int> right_boundary;
//returns the max available area if a columnwise flip is performed at "column"
// it is assumed that area is for net "net_ind". So, the boundary to flip
// is LBoundaries[net_ind+1]
int find_avail_area(int net_ind, int c_ind){

  // the points of left boundary that are on column c_ind
  vector<int> L = LBoundaries[net_ind+1].getColumn(c_ind) ;
  // the points of right boundary that are on column c_ind+1
  vector<int> R = RBoundaries[net_ind+1].getColumn(c_ind+1) ;
  
  // we have 6 cases (see them in the notes)

  if (L.size() == 1 && R.size() == 1 && L[0] < R[0]) // case 1 in notes
    return R[0] - L[0] - 1 ;
  else if (L.size() == 1 && R.size() == 1 && L[0] > R[0]) // case 2 in notes
    return L[0] - R[0] - 1 ;
  else if (L.size() == 2 && R.size() == 0) // case 3 in notes
    return max(L[0], L[1]) - min(L[0], L[1]) ; 
  else if (L.size() == 0 && R.size() == 2) // case 4 in notes
    return max(R[0],R[1]) - min(R[0],R[1]) - 2 ;
  else if (L.size() == 2 && R.size() == 2){ // case 5 in notes
    
    if (min(R[0],R[1]) == min(R[0],R[1]) - 1) 
      // if no space between top segments of L and R
      return max(R[0],R[1]) - max(L[0],L[1]) - 1 ;
    else if (max(R[0],R[1]) == max(R[0],R[1]) - 1)
      // if no space between bottom segments of L and R
      //return min(L[0],L[1]) - min(R[0],R[1]) - 1 ;
      // Since we perform single flips from the top, 5(b) is not possible
      throw Logic_error("Unexpected case in find_avail_area: case 5(b)") ;
    else 
      throw Logic_error("Unexpected case: right boundary can't be concave monotonic") ;

  }
  else
    throw Logic_error("Unexpected case in find_avail_area") ;
  
}


// the last flip may be partial (i.e. the whole column not flipped)
// return value is the top and bottom grid cell allocated on the last column
// It is assumed that area_needed is less than the avail area on the column
pair<int,int> find_last_flip(int net_ind, int c_ind, int area_needed){

#ifdef DEBUG
  if (find_avail_area(net_ind, c_ind) < area_needed)
    throw Logic_error("Trying to allocate more than avail gcell on the last column") ;
#endif

  // the points of left boundary that are on column c_ind
  vector<int> L = LBoundaries[net_ind+1].getColumn(c_ind) ;
  // the points of right boundary that are on column c_ind+1
  vector<int> R = RBoundaries[net_ind+1].getColumn(c_ind+1) ;
  
  // we have 6 cases (see them in the notes)

  if (L.size() == 1 && R.size() == 1 && L[0] < R[0]) // case 1 in notes
    return make_pair(L[0], L[0]+ area_needed -1) ;
  else if (L.size() == 1 && R.size() == 1 && L[0] > R[0]) // case 2 in notes
    return make_pair(L[0]-area_needed, L[0]-1) ;
  else if (L.size() == 2 && R.size() == 0) // case 3 in notes
    return make_pair(min(L[0],L[1]), min(L[0],L[1])+area_needed - 1) ;
  else if (L.size() == 0 && R.size() == 2) // case 4 in notes
    return make_pair(min(R[0],R[1])+1, min(R[0],R[1])+area_needed) ;
  else if (L.size() == 2 && R.size() == 2){ // case 5 in notes
    
    if (min(R[0],R[1]) == min(R[0],R[1]) - 1) 
      // if no space between top segments of L and R
      return make_pair(max(L[0],L[1]), max(L[0],L[1])+area_needed-1) ;
    else if (max(R[0],R[1]) == max(R[0],R[1]) - 1)
      // if no space between bottom segments of L and R
      //return make_pair(min(L[0],L[1])-area_needed, min(L[0],L[1])-1) ;
      // Since we perform single flips from the top, 5(b) is not possible
      throw Logic_error("Unexpected case in find_last_flip: case 5(b)") ;
    else 
      throw Logic_error("Unexpected case: right boundary can't be concave monotonic") ;

  }
  else
    throw Logic_error("Unexpected case in find_last_flip") ;
 
}



// the area is for net net_ind; we are flipping boundary net_ind+1
FlipInfo find_min_flips(int net_ind, int area_needed){
  
  Boundary& lbndry = LBoundaries[net_ind+1] ;

  int area_alloc = 0 ;
  int i = lbndry.minx ;
  while (i < lbndry.maxx && area_alloc < area_needed){
    area_alloc += find_avail_area(net_ind, i) ;
    i ++ ;
  }
  
  FlipInfo f ;
  if (area_alloc < area_needed){ // could not allocate enough area
    cout << "Could not allocate enough area for net " << net_ind << endl ;
    
    f.last_column = i-2 ; // for consistency, we assume that the last
    //                       full columnwise flip is at i-1, altough
    //                       column i-1 is completely flipped, too.
    pair<int,int> p = find_last_flip(net_ind, i-1,
				     find_avail_area(net_ind, i-1)) ;
    f.last_allocated_top = p.first ;
    f.last_allocated_bottom = p.second ;
  }
  else{ // (possibly more than) enough area allocated
    // the last columnwise flip was i-1
    // We roll back that columnwise flip:
    area_alloc -= find_avail_area(net_ind, i-1) ; // 

    // Then we find min number of single unit flips needed on the last column
    pair<int, int> p = find_last_flip(net_ind, i-1, area_needed-area_alloc);
    f.last_column = i-2 ; // the last full-columnwise flip
    f.last_allocated_top = p.first ;
    f.last_allocated_bottom = p.second ;
  }


  return f ;

}


// given the left boundary and the row number, find the index of the leftmost
//   gridcell that is allocated
int get_leftmost_allocated(const Boundary& lb, int r, int net_index){
  //changed here
	int temp = lb.getRow(r);
	if(bound_on){
		if(net_index!=0){
			if(temp<=nets[net_index-1].coord[r].second)
				return nets[net_index-1].coord[r].second+1;
			}
	}
  //end here
  return lb.getRow(r) ;
}

// given the flip info,etc. find the index of the rightmost allocated gridcell
// lb: left boundary for the current net
// rbo: the left boundary for the right neighbour; in a sense, it is the
//      initial right boundary for this net
// rbf: the final position of left boundary of right neighbour after it is
//      is completely flipped. In a sense, it is the final right bndry for
//      the current net
int get_rightmost_allocated(const Boundary& lb, const Boundary& rbo, 
			    const Boundary& rbf, FlipInfo f, int r, int net_index){  
  int ret;
	//if(r==ysize-2){ 
	//}
	if(r<=2){
		ret= max(rbo.getRow(r)-1, // it will be at least adjacent to rbo
	     min(f.last_column +  // the last column completely flipped
		 ((r>=f.last_allocated_top&& r<=f.last_allocated_bottom)?
		  1:0), // check if single-flips on the last column
		 //          allocate one extra gridcell in this row
		 
		 rbf.getRow(r)-1)); // it can be at most adjacent to rbf
	}
	else{
		ret=max(rbo.getRow(r)-1, // it will be at least adjacent to rbo
	     f.last_column +  // the last column completely flipped
		 ((r>=f.last_allocated_top&& r<=f.last_allocated_bottom)?
		  1:0)); 

	}

//	}// check if single-flips on the last column
		 //          allocate one extra gridcell in this row
		 
		 //rbf.getRow(r)-1)); // it can be at most adjacent to rbf
	/*if(net_index!=0){
		if(ret<(nets[net_index-1].coord[r-1].second))
			ret=nets[net_index-1].coord[r-1].second+1;
		else if(ret<nets[net_index-1].coord[r+1].second)
			ret=nets[net_index-1].coord[r+1].second+1;
	}*/
	if(bound_on&&net_index==0){
		if(ret<left_boundary[r-1])
			ret=left_boundary[r-1];
		//else if(ret<left_boundary[r+1])
		//	ret=left_boundary[r+1]+1;
		}
	return ret;

}

void allocate_cells(int net_ind, FlipInfo f){

  Boundary& lb = LBoundaries[net_ind] ; // the left boundary for net "net_ind"

  Boundary& rbo = LBoundaries[net_ind+1] ; // the left bndry for "net_ind+1"
  // in a sense, it is the initial right boundary for net "net_ind"

  Boundary rbf = find_max_flipped_boundary(net_ind+1) ;
  // the final position of left boundary of "net_ind+1" after it is
  //   completely flipped.
  // In a sense, it is the final (utmost) right boundary for net "net_ind"

  
  int no_allocated = 0 ;
  // traverse each row, and update the grid cells allocated
  for (int i=1; i<ysize-1; i++){ // no space allocation on terminal rows
    int minx = get_leftmost_allocated(lb, i, net_ind) ;
    int maxx = get_rightmost_allocated(lb, rbo, rbf, f, i, net_ind) ;

	//change here

	//make sure the maxx and minx are within the boundary
	if(bound_on){
		
    	if(maxx>right_boundary[i]-1-nets.size()+net_ind+2)
			maxx=right_boundary[i]-1-nets.size()+net_ind+2;
		if(maxx>right_boundary[i-1]-1-nets.size()+net_ind+2)
			maxx=right_boundary[i-1]-1-nets.size()+net_ind+2;
		if(net_ind!=nets.size()-2){
			if(maxx>right_boundary[i-2]-1-nets.size()+net_ind+2)
				maxx=right_boundary[i-2]-1-nets.size()+net_ind+2;
			if(i!=ysize-1){
				if(maxx>right_boundary[i+1]-1-nets.size()+net_ind+2)
					maxx=right_boundary[i+1]-1-nets.size()+net_ind+2;
			}
		}

		if(minx>right_boundary[i]-1)
			minx=right_boundary[i]-1;
		if(minx>right_boundary[i-1]-1)
			minx=right_boundary[i-1]-1;

		if(minx<left_boundary[i])
			minx=left_boundary[i];
		if(minx<left_boundary[i-1])
			minx=left_boundary[i-1];

		if(maxx<left_boundary[i])
			maxx=left_boundary[i];
		if(maxx<left_boundary[i-1])
			maxx=left_boundary[i-1];
	}


	//end here


    // allocate the grid cells between minx and maxx
    no_allocated += (maxx-minx+1) ;
    for (int j=minx; j<=maxx; j++)
      gcells[j][i].is_empty = false ;
  }

  no_allocated += 1 ; // we assume that the top terminals are in the middle 
  // of row 0, and bottom terminals are in the middle of row ysize-1.
  // Above, we traverse rows [1, ysize-1]. So, we add 1 for the
  //  connections from terminals (1/2 + 1/2 = 1)

	//changed here: Comment this out here because it doesnt' seem to make sense anyway
  //if (no_allocated < nets[net_ind].minL)
    //cout << "Min area constraint not satisfied for net " << net_ind << endl;
	//end here

}



void route_min_area(int net_ind){

  // first find left boundaries again based on the previous routes
  findLeftBoundary(net_ind) ;
  findLeftBoundary(net_ind+1) ;

  // now, find the area available between L[net_ind] and L[net_ind+1]

  int init_area = 0 ;
  for (int i=1; i<ysize-1; i++) // no allocation on terminal rows
    init_area += (LBoundaries[net_ind+1].getRow(i) - 
		  LBoundaries[net_ind].getRow(i)) ;
  init_area += 1 ; // we assume that the top terminals are in the middle 
  // of row 0, and bottom terminals are in the middle of row ysize-1.
  // Above, we traverse rows [1, ysize-1]. So, we add 1 for the
  //  connections from terminals (1/2 + 1/2 = 1)

  int area_needed = nets[net_ind].minL - init_area ;

  FlipInfo f ;
  if (area_needed > 0)
    f = find_min_flips(net_ind, area_needed) ;
  else
    f.set_invalid() ;
  
  allocate_cells(net_ind, f) ;

}



void route_all_min_area(){

  for (int i=0; i<nets.size()-1; i++)
    route_min_area(i) ;

  cout << "Note that the last net is not checked in this version" << endl ;
}
