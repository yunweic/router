#include "route.h"
#include <queue>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <sstream>

extern int bound_on;
extern int cap;
extern int diagonal_dir;

struct RowEdges{
  int first2first, first2second, second2first, second2second ;
};
vector<RowEdges> edges ;
// edges[i] is the set of edges from vertices[i] to vertices[i+1]

vector<pair<int,int> > vertices ;
vector<pair<int,int> > max_labels ;
//vector<pair<int,int> > min_labels ;
//vector<pair<int,int> > parents ;

vector<vector<pair<int,int> > > routes ;
// routes[i] is the route for net i
// Each pair gives the coord of a grid cell in the route

extern void findLeftBoundary(int net_ind);
extern void findLeftBoundary2(int net_ind) ;
extern Boundary find_max_flipped_boundary(int net_ind) ;
extern void allocate_cells(int net_ind, FlipInfo f) ;

extern int get_leftmost_allocated(const Boundary& lb, int r, int net_index) ;
extern int get_rightmost_allocated(const Boundary& lb, const Boundary& rbo,
				   const Boundary& rbf, FlipInfo f, int r, int net_index) ;

extern vector<int> right_boundary;
extern vector<int> left_boundary;

extern bool adjacent(pair<int,int> gc1, pair<int,int> gc2);
extern int find_ptr(vector<pair<int,int> > route, int net_ind);

extern vector<int> prev_route;

void init_graph(){

  vertices.resize(ysize) ;
  edges.resize(ysize) ;
  max_labels.resize(ysize) ;
}



// The routing is for net "net_ind", and flip of "f". 
// We also need rbf, which is the max_flipped_boundary of net_ind+1
// In a sense, rbf is the final (utmost) right boundary for net "net_ind+1"
void set_graph(int net_ind, FlipInfo f, const Boundary& rbf){

  Boundary& lb = LBoundaries[net_ind] ; // the left boundary for net "net_ind"
  Boundary& rbo = LBoundaries[net_ind+1] ; // the left bndry for "net_ind+1"
  // in a sense, it is the initial right boundary for net "net_ind"

  // handle the first row separately:
  vertices[1] = make_pair(nets[net_ind].topT, nets[net_ind].topT) ;

  	for(int i=0;i<ysize;i++){
		int temp=get_leftmost_allocated(lb,i, net_ind);
		//cout<<"left boundary row= "<<temp<<endl;
	}
	// first calculate the positions of vertices on each row
  for (int i=2;i<ysize; i++){
    // Note that the vertex is on the boundary between rows i and i-1
    // So, we should check both rows to find the exact position of the vertex

    // lb.getRow(i) gives the index of the leftmost available gcell in row i
    // minx is the position of the first vtx on the bndry of row i-1 and i
	int minx;
	if(net_ind==0){
		if(left_boundary[i-1]<left_boundary[i]&&i==ysize-1){
			minx=left_boundary[i];
		}
		else{

			minx=left_boundary[i];
		}
	}
	else{
		if(max(nets[net_ind-1].coord[i-1].second,nets[net_ind-1].coord[i-1].first)<max(nets[net_ind-1].coord[i].second,nets[net_ind-1].coord[i].first)&&i==ysize-1){
			minx=max(nets[net_ind-1].coord[i].first,nets[net_ind-1].coord[i].second);
		}
		else{

			minx=max(nets[net_ind-1].coord[i].first,nets[net_ind-1].coord[i].second);
		}

	}

    // maxx is the position of the second vertex on the bndry of rows i-1 & i
    int maxx = min(get_rightmost_allocated(lb, rbo, rbf, f, i, net_ind),
		   get_rightmost_allocated(lb, rbo, rbf, f, i-1, net_ind)) ;
	//changed here
	if(bound_on){
		//deal with left and right boundary here
    	if(maxx>right_boundary[i]-1-nets.size()+net_ind+2)
			maxx=right_boundary[i]-1-nets.size()+net_ind+2;
		if(net_ind!=nets.size()-2&&maxx>right_boundary[i-1]-1-nets.size()+net_ind+2)
			maxx=right_boundary[i-1]-1-nets.size()+net_ind+2;
		
		if(minx>right_boundary[i]-1)
			minx=right_boundary[i]-1;
		if(net_ind!=nets.size()-2&&minx>right_boundary[i-1]-1)
			minx=right_boundary[i-1]-1;

		if(minx<left_boundary[i])
			minx=left_boundary[i];
		if(net_ind!=nets.size()-2&&minx<left_boundary[i-1])
			minx=left_boundary[i-1];

		if(maxx<left_boundary[i])
			maxx=left_boundary[i];
		if(net_ind!=nets.size()-2&&maxx<left_boundary[i-1])
			maxx=left_boundary[i-1];
		//deal with the previous net here
		if(net_ind>0&&(nets[net_ind-1].coord[i].first>=maxx||nets[net_ind-1].coord[i].second>=maxx))
			maxx=max(nets[net_ind-1].coord[i].first,nets[net_ind-1].coord[i].second)+1;
			
		while(gcells[maxx][i].last_net!=net_ind){
			maxx--;
			if(net_ind>0&&maxx<max(nets[net_ind-1].coord[i].first,nets[net_ind-1].coord[i].second)){
				char buffer [50];
				int n;
				n=sprintf(buffer, "Net %d is not routable to let rest of the nets to be routed", net_ind);
				string error=buffer;
		 
				throw Logic_error(error);

			}
			else if(net_ind==0&&maxx<left_boundary[i]){
				char buffer [50];
				int n;
				n=sprintf(buffer, "Net %d is not routable to let rest of the nets to be routed", net_ind);
				string error=buffer;
		 
				throw Logic_error(error);
	
			}

		}
		while(gcells[minx][i].last_net!=net_ind){
			minx++;
			if(minx>right_boundary[i]){
				char buffer [50];
				int n;
				n=sprintf(buffer, "Net %d is not routable to let rest of the nets to be routed", net_ind);
				string error=buffer;
		 
				throw Logic_error(error);
			}
		}
		//trap cells
		if(i!=ysize-1){
			if(vertices[i-1].first==xsize+10)
				vertices[i-1].first=minx;

			if(vertices[i-1].second==xsize+10)
				vertices[i-1].second=maxx;
		}
		else{
			if(vertices[i-1].first==xsize+10){
				if(net_ind!=0){
					vertices[i-1].first=max(left_boundary[ysize-1],max(nets[net_ind-1].coord[ysize-1].first, nets[net_ind-1].coord[ysize-1].second)+1);
				}
				else{
					vertices[i-1].first=left_boundary[ysize-1];
				}
	
				if(vertices[i-1].second<vertices[i-1].first)
					vertices[i-1].second=vertices[i-1].first;
			}

			if(vertices[i-1].second==xsize+10){
				vertices[i-1].second=min(right_boundary[ysize-2],right_boundary[ysize-1])-1;
				if(net_ind!=nets.size()-2)
					vertices[i-1].second=min(right_boundary[ysize-1]-1, nets[net_ind+1].bottomT-1);
			}
		}
	}
	//need to check if there's trap cells
	for(int j=0;j<nets[net_ind].trap_cell.size();j++){
		if(nets[net_ind].trap_cell[j].second==i){
			if(minx==nets[net_ind].trap_cell[j].first){
				//notify that it should be the same with the next row
				minx=xsize+10;
			}
			else if(maxx==nets[net_ind].trap_cell[j].first){
				//notify that it should be the same with the next row
				maxx=xsize+10;
			}
		}
	}
	//end here
	
    vertices[i] = make_pair(minx, maxx) ;
	if(i==ysize-1)
		vertices[i]=make_pair(nets[net_ind].bottomT,nets[net_ind].bottomT);
  }

	/*for(int j=0;j<ysize;j++){
		cout<<"j= "<<j<<"vertices: "<<vertices[j].first<<" "<<vertices[j].second<<endl;
	}*/
  // then set the edge weights

  for (int i=1; i<ysize-1; i++){
    edges[i].first2first = abs(vertices[i].first-vertices[i+1].first)+1 ;
    edges[i].first2second = abs(vertices[i].first-vertices[i+1].second)+1 ;
    edges[i].second2first = abs(vertices[i].second-vertices[i+1].first)+1 ;
    edges[i].second2second = abs(vertices[i].second-vertices[i+1].second)+1 ;
	//changed here

	//cout<<"i= "<<i<<" first2first= "<<edges[i].first2first<<" first2second "<<edges[i].first2second<<" second2first= "<<edges[i].second2first<<" second2second= "<<edges[i].second2second<<endl;
  }


}


// set the labels of the vertices at row r
void set_max_labels(int r){

  max_labels[r].first = max(max_labels[r-1].first + edges[r-1].first2first,
			    max_labels[r-1].second + edges[r-1].second2first);
  max_labels[r].second = max(max_labels[r-1].first + edges[r-1].first2second,
			     max_labels[r-1].second+edges[r-1].second2second);
}

#define FIRST_VERTEX 0
#define SECOND_VERTEX 1
#define NOT_A_VERTEX -1

int get_max_parent(int r, int vtx){

  if (vtx == FIRST_VERTEX){
    if (max_labels[r-1].first + edges[r-1].first2first >
	max_labels[r-1].second + edges[r-1].second2first)
      return FIRST_VERTEX ;
    else
      return SECOND_VERTEX ;
  }
  else{
    if (max_labels[r-1].first + edges[r-1].first2second >
	max_labels[r-1].second + edges[r-1].second2second)
      return FIRST_VERTEX ;
    else
      return SECOND_VERTEX ;
  }

}


// return the actual coord of vtx on row r
pair<int,int> get_vtx_coord(int r, int vtx){

  if (vtx == FIRST_VERTEX)
    return make_pair(vertices[r].first, r) ;
  else
    return make_pair(vertices[r].second, r) ;
}



void set_min_max_labels(int r){

  max_labels[r].first = max(max_labels[r-1].first + edges[r-1].first2first,
			    max_labels[r-1].second + edges[r-1].second2first);
  max_labels[r].second = max(max_labels[r-1].first + edges[r-1].first2second,
			     max_labels[r-1].second+edges[r-1].second2second);

  /*
  min_labels[r].first = min(max_labels[r-1].first + edges[r-1].first2first,
			    max_labels[r-1].second + edges[r-1].second2first);
  min_labels[r].second = min(max_labels[r-1].first + edges[r-1].first2second,
			     max_labels[r-1].second+edges[r-1].second2second);

  */

  /*
  int l11 = labels[r-1].first + edges[r-1].first2first ;
  int l12 = labels[r-1].second + edges[r-1].second2first ;
  if (l11 > l12){
    labels[r].first = l11 ;
    parents[r].first = FIRST_VERTEX ;
  }
  else{
    labels[r].first = l12 ;
    parents[r].first = SECOND_VERTEX ;
  }


  int l21 = labels[r-1].first + edges[r-1].first2second ;
  int l22 = labels[r-1].second + edges[r-1].second2second ;
  if (l21 > l22){
    labels[r].second = l21 ;
    parents[r].second = FIRST_VERTEX ;
  }
  else{
    labels[r].second = l22 ;
    parents[r].second = SECOND_VERTEX ;
  }
  */

}



// The routing is for net "net_ind", and flip of "f". 
// We also need rbf, which is the max_flipped_boundary of net_ind+1
// In a sense, rbf is the final (utmost) right boundary for net "net_ind+1"
int find_max_length(int net_ind, FlipInfo f, const Boundary& rbf){

  set_graph(net_ind, f, rbf) ;
  
  // first traverse each vertex on each row, and set the labels
  max_labels[1] = make_pair(0,0) ;
  for (int i=2; i<ysize; i++)
    set_max_labels(i) ;
	
  /*for(int i=0;i<ysize;i++){
		cout<<"i= "<<i<<" max label first = "<<max_labels[i].first<<" max label second = "<<max_labels[i].second<<endl;
  }*/// we add 1 corresponding to half segments connected to the top and 
  //     bottom terminals

  return max(max_labels[ysize-1].first, max_labels[ysize-1].second) + 1 ;

}


vector<pair<int, int> > find_max_route(int net_ind, FlipInfo f, const Boundary& rbf){
  set_graph(net_ind, f, rbf) ;

  max_labels[1] = make_pair(0,0) ;
  for (int i=2; i<ysize; i++)
    set_max_labels(i) ;

  vector<pair<int, int> > route ;
  
  int c ; // current vertex
  if (max_labels[ysize-1].first > max_labels[ysize-1].second)
    c = FIRST_VERTEX ;
  else
    c = SECOND_VERTEX ;

  for (int i=ysize-1; i>=1; i--){

    int p ; // parent vertex
    int x ; // x coord of current vertex
    if (c == FIRST_VERTEX){
      x = vertices[i].first ;
      p = get_max_parent(i, FIRST_VERTEX) ;
    }
    else{
      x = vertices[i].second ;
      p = get_max_parent(i, SECOND_VERTEX) ;
    }
    
    route.push_back(make_pair(x, i)) ;
    c = p ;
  }

  // connect the top terminal to the end of the route
  route.push_back(make_pair(route.back().first, 0)) ;

  reverse(route.begin(), route.end()) ;
  // now the route begins from the top terminal

  return route ;
}
// if the gcell "to" is relaxed the first time, we also add it to the queue
void relax_nobound(pair<int,int> from, pair<int,int> to, int net_ind, 
	   queue<pair<int,int> >& q){

  if (gcells[to.first][to.second].last_net == net_ind)
    return ; // vertex already relaxed, don't relax again

  gcells[to.first][to.second].min_label =
    gcells[from.first][from.second].min_label + 1 ;

  gcells[to.first][to.second].last_net = net_ind ;

  q.push(to) ;

}

// if the gcell "to" is relaxed the first time, we also add it to the queue
void relax(pair<int,int> from, pair<int,int> to, int net_ind, 
	   queue<pair<int,int> >& q){

  //if (gcells[to.first][to.second].last_net == net_ind)
   // return ; // vertex already relaxed, don't relax again
	if( gcells[to.first][to.second].last_net!=net_ind||gcells[to.first][to.second].min_label>gcells[from.first][from.second].min_label+1||gcells[to.first][to.second].min_label==0){
  		
		gcells[to.first][to.second].min_label =
    	gcells[from.first][from.second].min_label + 1 ;
	
	  	gcells[to.first][to.second].last_net = net_ind ;
  		q.push(to) ;
	}
	return;
	
}


// find the distance from each gridcell to the top terminal
// We use maze routing to label the gridcells
void set_min_labels(int net_ind, FlipInfo f, const Boundary& rbf){

  Boundary& lb = LBoundaries[net_ind] ; // the left boundary for net "net_ind"
  Boundary& rbo = LBoundaries[net_ind+1] ; // the left bndry for "net_ind+1"

  //change here
/*
  cout<<"rbf= "<<endl;
  for(int i=0;i<rbf.points.size();i++){
 	cout<<rbf.points[i].x<<" "<<rbf.points[i].y<<endl;
  }
  cout<<"rbo= "<<endl;
  for(int i=0;i<rbo.points.size();i++){
 	cout<<rbo.points[i].x<<" "<<rbo.points[i].y<<endl;
  }

*/
  //end here
  // for each row, find the min and max x values based on the flip info
  vector<int> minxv(ysize), maxxv(ysize) ;
  
  for (int i=1; i<ysize-1; i++){ // not setting the terminal rows
    minxv[i] = get_leftmost_allocated(lb, i, net_ind) ;
    maxxv[i] = get_rightmost_allocated(lb, rbo, rbf, f, i, net_ind) ;
	if(maxxv[i]<minxv[i])
		maxxv[i]=minxv[i];
	if(!prev_route.empty()){
		if(maxxv[i]<=prev_route[i+1])
			maxxv[i]=prev_route[i+1]+1;
	}
  }
  prev_route.clear();
   //changed here
	
	//this is the part to make the maximum xv for all net to be xsize-1
	for(int i=0;i<ysize-1;i++){
		//if(net_ind!=nets.size()-2)
			maxxv[i]=xsize-1;
		//cout<<"this is it: "<<net_ind<<" right" <<maxxv[i]<<" left "<<minxv[i]<<endl;
	}
 //end here
  minxv[ysize-1] = maxxv[ysize-1] = nets[net_ind].bottomT ;


  // start with the top gcell, and label each gcell as in maze routing
  
  queue<pair<int,int> > q ; // the queue that stores gridcell coords

  pair<int,int> t = make_pair(nets[net_ind].topT,1); // the top gcell
  gcells[t.first][t.second].last_net = net_ind ;
  gcells[t.first][t.second].min_label = 1 ; 


  // Distance from top of row 1 to row 0 (where the top terminal is) 
  //  is actually 1/2. However, since we ignore the bottom 1/2 connection 
  //  from top of row ysize-1 to the bottom terminal, we set the distance
  //  here (above) to 1, instead of 1/2. This gives the correct result since
  //  we end our route at the top of row ysize-1, instead of at the bottom
  //  terminal (middle of row ysize-1)
 
	//check if the first cell is actually routable
		if(net_ind!=0&&(nets[net_ind-1].coord[1].second>=t.first||nets[net_ind-1].coord[1].first>=t.first)){
			char buffer [50];
			int n;
			n=sprintf(buffer, "Net %d is not routable, the rest of the nets cannot be routed", net_ind);
			string error=buffer;
		 
			throw Logic_error(error);
		}
 

  	q.push(t) ;
  	while (q.size() > 0){
    	pair<int,int> c = q.front() ; // the current gcell coords
    	q.pop() ; // reduce the number of elts
		//cout<<"c.first= "<<c.first<<" c.second= "<<c.second<<endl;
		
		
		//start relaxing all the cells that's availbe for each net
		if(bound_on){
			if(net_ind==0){

				if(nets.size()==2){
					
					if(c.second==ysize-2){
						if (
						// and if the cell below is within the valid bounds
					left_boundary[c.second+1] <= c.first && right_boundary[c.second+1]>c.first+nets.size()-net_ind-2)

      						// relax the gcell immediately below c
      						relax(c, make_pair(c.first, c.second+1), net_ind, q) ;

    					if(left_boundary[c.second] <= c.first - 1) // if the left gcell is within bounds
      						// relax the gcell to the left of c
      						relax(c, make_pair(c.first-1, c.second), net_ind, q) ; 
					}
					else{
						//int temp=min(right_boundary[c.second-1],right_boundary[c.second+1]);

						if (c.second != ysize-1 &&  // if not the bottom gcell
						// and if the cell below is within the valid bounds
						left_boundary[c.second+1] <= c.first &&((ysize-1-(c.second+1)>=nets.size()-net_ind-2&&right_boundary[c.second+1+(nets.size()-net_ind-2)]> c.first+nets.size()-net_ind-2)||(ysize-1-(c.second+1)<nets.size()-net_ind-2&&c.first+(ysize-1-(c.second+1))<nets[net_ind+ysize-1-c.second].bottomT))&&right_boundary[c.second+1]>c.first+nets.size()-net_ind-2)

      						// relax the gcell immediately below c
      						relax(c, make_pair(c.first, c.second+1), net_ind, q) ;

    					if(left_boundary[c.second] <= c.first - 1) // if the left gcell is within bounds
      						// relax the gcell to the left of c
      						relax(c, make_pair(c.first-1, c.second), net_ind, q) ; 

					}
				}


				else{
    				if(c.second==ysize-2){	
						if (
						// and if the cell below is within the valid bounds
						left_boundary[c.second+1] <= c.first &&c.first<nets[net_ind+1].bottomT&&right_boundary[c.second+1]>c.first+nets.size()-net_ind-2)

      						// relax the gcell immediately below c
      						relax(c, make_pair(c.first, c.second+1), net_ind, q) ;

    					if(left_boundary[c.second] <= c.first - 1) // if the left gcell is within bounds
      						// relax the gcell to the left of c
      						relax(c, make_pair(c.first-1, c.second), net_ind, q) ; 
					}
					else{
						if (c.second != ysize-1 &&  // if not the bottom gcell
						// and if the cell below is within the valid bounds
						left_boundary[c.second+1] <= c.first&&((ysize-1-(c.second+1)>=nets.size()-net_ind-2&&right_boundary[c.second+1+(nets.size()-net_ind-2)]> c.first+nets.size()-net_ind-2)||(ysize-1-(c.second+1)<nets.size()-net_ind-2&&c.first+(ysize-1-(c.second+1))<nets[net_ind+ysize-1-c.second].bottomT))&&right_boundary[c.second+1]>c.first+nets.size()-net_ind-2)

      						// relax the gcell immediately below c
      						relax(c, make_pair(c.first, c.second+1), net_ind, q) ;

    					if(left_boundary[c.second] <= c.first - 1) // if the left gcell is within bounds
      						// relax the gcell to the left of c
      						relax(c, make_pair(c.first-1, c.second), net_ind, q) ; 

					}
				}
			}
			else if(net_ind==nets.size()-2){
				if(c.second==ysize-2){
					if (
					// and if the cell below is within the valid bounds
					nets[net_ind-1].coord[c.second+1].second < c.first &&right_boundary[c.second+1]>c.first+nets.size()-net_ind-2)

      					// relax the gcell immediately below c
      					relax(c, make_pair(c.first, c.second+1), net_ind, q) ;

    				if(nets[net_ind-1].coord[c.second].second < c.first - 1 && nets[net_ind-1].coord[c.second].first < c.first - 1&&(nets[net_ind-1].coord[c.second-1].second < c.first - 1 && nets[net_ind-1].coord[c.second-1].first < c.first - 1||nets[net_ind-1].coord[c.second+1].second < c.first - 1 && nets[net_ind-1].coord[c.second+1].first < c.first - 1)) // if the left gcell is within bounds
      					// relax the gcell to the left of c
      					relax(c, make_pair(c.first-1, c.second), net_ind, q) ; 
				}
				else{
					//int temp=min(right_boundary[c.second-1],right_boundary[c.second+1]);

					if (c.second != ysize-1 &&  // if not the bottom gcell
					// and if the cell below is within the valid bounds
					nets[net_ind-1].coord[c.second+1].second < c.first &&(right_boundary[c.second+1+(nets.size()-net_ind-2)]> c.first+nets.size()-net_ind-2||ysize-1-(c.second+1)<nets.size()-net_ind-2)&&right_boundary[c.second+1]>c.first+nets.size()-net_ind-2)

      					// relax the gcell immediately below c
      					relax(c, make_pair(c.first, c.second+1), net_ind, q) ;

    				if(nets[net_ind-1].coord[c.second].second < c.first - 1 && nets[net_ind-1].coord[c.second].first < c.first - 1&&(c.second==ysize-1||nets[net_ind-1].coord[c.second+1].second < c.first - 1 && nets[net_ind-1].coord[c.second+1].first < c.first - 1||nets[net_ind-1].coord[c.second-1].second < c.first - 1 && nets[net_ind-1].coord[c.second-1].first < c.first - 1&&c.second!=1)) // if the left gcell is within bounds
      					// relax the gcell to the left of c
      					relax(c, make_pair(c.first-1, c.second), net_ind, q) ; 

				}
			}
			else{
				if(c.second==ysize-2){
					if (
					// and if the cell below is within the valid bounds
					nets[net_ind-1].coord[c.second+1].second < c.first &&c.first<nets[net_ind+1].bottomT&&right_boundary[c.second+1]>c.first+nets.size()-net_ind-2)
	
    	  				// relax the gcell immediately below c
      					relax(c, make_pair(c.first, c.second+1), net_ind, q) ;

    				if(nets[net_ind-1].coord[c.second].second < c.first - 1 && nets[net_ind-1].coord[c.second].first < c.first - 1&&(nets[net_ind-1].coord[c.second+1].second < c.first - 1 && nets[net_ind-1].coord[c.second+1].first < c.first - 1||nets[net_ind-1].coord[c.second-1].second < c.first - 1 && nets[net_ind-1].coord[c.second-1].first < c.first - 1)) // if the left gcell is within bounds
      					// relax the gcell to the left of c
      					relax(c, make_pair(c.first-1, c.second), net_ind, q) ; 
				}
				else{
					int temp=min(right_boundary[c.second-1],right_boundary[c.second+1]);

					if (c.second != ysize-1 &&  // if not the bottom gcell
					// and if the cell below is within the valid bounds
					nets[net_ind-1].coord[c.second+1].second < c.first&&((ysize-1-(c.second+1)>=nets.size()-net_ind-2&&right_boundary[c.second+1+(nets.size()-net_ind-2)]> c.first+nets.size()-net_ind-2)||(ysize-1-(c.second+1)<nets.size()-net_ind-2&&c.first+(ysize-1-(c.second+1))<nets[net_ind+ysize-1-c.second].bottomT))&&right_boundary[c.second+1]>c.first+nets.size()-net_ind-2)

      					// relax the gcell immediately below c
      					relax(c, make_pair(c.first, c.second+1), net_ind, q) ;

    				if(nets[net_ind-1].coord[c.second].second < c.first - 1 && nets[net_ind-1].coord[c.second].first < c.first - 1&&(c.second==ysize-1||nets[net_ind-1].coord[c.second+1].second < c.first - 1 && nets[net_ind-1].coord[c.second+1].first < c.first - 1||nets[net_ind-1].coord[c.second-1].second < c.first - 1 && nets[net_ind-1].coord[c.second-1].first < c.first - 1&&c.second!=1)) // if the left gcell is within bounds
      					// relax the gcell to the left of c
      					relax(c, make_pair(c.first-1, c.second), net_ind, q) ; 
				}
			}
			if(net_ind==nets.size()-2){
				if(c.second!=ysize-1){
					//int temp=min(right_boundary[c.second-1],right_boundary[c.second+1]);
    				if((min(right_boundary[c.second],right_boundary[c.second+1])-(nets.size()-net_ind-2)> c.first+1)) // if the right gcell is within bounds
      					// relax the gcell to the right of c
      					relax(c, make_pair(c.first+1, c.second), net_ind, q) ; 
				}
				else{
					if(right_boundary[c.second]-(nets.size()-net_ind-2)> c.first+1) // if the right gcell is within bounds
      					// relax the gcell to the right of c
      					relax(c, make_pair(c.first+1, c.second), net_ind, q) ;	
				}
			}
			else{
				if(c.second!=ysize-1){

					int temp=min(right_boundary[c.second-1],right_boundary[c.second+1]);
					bool can_go_right=true;
						
					//top
					if(c.second<nets.size()-net_ind-1&&ysize-1-(c.second)>=nets.size()-net_ind-2){
				
						if(c.first+c.second>=nets[net_ind+c.second].topT){
							can_go_right=false;
						}
						//check all the following grids
						for(int i=1;i<c.second+nets.size()-net_ind-2+1;i++){
							if(i<=ysize-1&&right_boundary[i]<=c.first+1+nets.size()-net_ind-2){
								can_go_right=false;
								break;
							}
						}
					}
					//bottom
					else if(ysize-1-(c.second)<nets.size()-net_ind-2&&c.second>=nets.size()-net_ind-1){
						if(c.first+(ysize-1-c.second)>=nets[net_ind+ysize-1-c.second+1].bottomT-1){
							can_go_right=false;
						}
						//check all the previous grids
						for(int i=1;i<ysize-1-(c.second-(nets.size()-net_ind-2+1));i++){
							if(ysize-1-i>=0&&right_boundary[ysize-1-i]<=c.first+1+nets.size()-net_ind-2){
								can_go_right=false;
								break;
							}
						}

					}
					//if both diagonal lines touch the top and bottom
					else if(ysize-1-(c.second)<nets.size()-net_ind-2&&c.second<nets.size()-net_ind-1){
						if(c.first+c.second>=nets[net_ind+c.second].topT){
							can_go_right=false;
						}
						if(c.first+(ysize-1-c.second)>=nets[net_ind+ysize-1-c.second+1].bottomT-1){
							can_go_right=false;
						}
						//check all the following grids
						for(int i=1;i<ysize-1;i++){
							if(right_boundary[i]<=c.first+1+nets.size()-net_ind-2){
								can_go_right=false;
								break;
							}
						}


					}
						
					else{
						for(int i=0;i<nets.size()-net_ind-2+1;i++){
							if(c.second+i<=ysize-1&&right_boundary[c.second+i]<=c.first+1+nets.size()-net_ind-2){
								can_go_right=false;
								break;
							}
							if(c.second-i>=0&&right_boundary[c.second-i]<=c.first+1+nets.size()-net_ind-2){
								can_go_right=false;
								break;
							}
						}
					}
					if(can_go_right==true){
						// relax the gcell to the right of c
      					relax(c, make_pair(c.first+1, c.second), net_ind, q) ; 
					}
					
				}
				else{
					bool can_go_right=true;
					if(c.first+1<nets[net_ind+1].bottomT){

						// if the right gcell is within bounds
      					for(int i=0;i<nets.size()-net_ind-2;i++){
							if(right_boundary[c.second-i-1]<=c.first+1+nets.size()-net_ind-2){
								can_go_right=false;
								break;
							}
						}
						// relax the gcell to the right of c
						if(can_go_right)
      						relax(c, make_pair(c.first+1, c.second), net_ind, q) ;	
					}
				}

			}
		}
		//there are no boundaries file
		else{
			if (c.second != ysize-1 &&  // if not the bottom gcell
			// and if the cell below is within the valid bounds
			minxv[c.second+1] <= c.first && maxxv[c.second+1] >= c.first)

      			// relax the gcell immediately below c
      			relax_nobound(c, make_pair(c.first, c.second+1), net_ind, q) ;

    		if(minxv[c.second] <= c.first - 1) // if the left gcell is within bounds
      			// relax the gcell to the left of c
      			relax_nobound(c, make_pair(c.first-1, c.second), net_ind, q) ; 

    		if(maxxv[c.second] >= c.first + 1) // if the right gcell is within bounds
      			// relax the gcell to the right of c
      			relax_nobound(c, make_pair(c.first+1, c.second), net_ind, q) ; 

		}
  	}
 //changed here
	/*for(int i=0;i<=xsize;i++){
		for(int j=0;j<ysize;j++){
			//cout<<"last-net "<<i<<" "<<j<<" "<<gcells[i][j].last_net<<" "<<gcells[i][j].min_label<<" "<<gcells[i][j].is_empty<<endl;
		}
	}*/
 
//end here
}


// find the parent gcell of gc, which is on the min-path to the top terminal
pair<int,int> get_parent_gcell(pair<int,int> gc, int net_index, int last_direction,bool snake_just_off,int length){

  int min = INT_INF ;
  pair<int,int> p =make_pair(xsize, ysize);
  
  // check each side of gc
	if(gcells[gc.first][gc.second].last_net!=net_index){
		char buffer [50];
		int n;
		n=sprintf(buffer, "Net %d is not routable, the rest of the nets cannot be routed", net_index);
		string error=buffer;
		 
		throw Logic_error(error);
	}
   
    if(bound_on){
		if(net_index!=0){
		
			// the vtx above is valid
			if(!snake_just_off){
				bool upflag=false;
				if(gc.second>0&&gcells[gc.first][gc.second-1].last_net==gcells[gc.first][gc.second].last_net){
    				p = make_pair(gc.first, gc.second-1) ;
    				min = gcells[p.first][p.second].min_label ;
					nets[net_index].last_dir=1;
					nets[net_index].last_left=false;
					upflag=true;
  				}

				// then check the vtx to the left
  				if (gcells[gc.first-1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the left is valid
      			&& (gcells[gc.first-1][gc.second].min_label +length+1<= nets[net_index].maxL&&gc.second!=1||(gc.second==1&&nets[net_index].topT<gc.first))&&nets[net_index].last_right!=1&&(nets[net_index].last_dir!=2||nets[net_index].snake_on||snake_just_off)&&nets[net_index-1].coord[gc.second-1].first<gc.first-1&&nets[net_index-1].coord[gc.second-1].second<gc.first-1){
    				p = make_pair(gc.first-1, gc.second) ;
    				min = gcells[gc.first-1][gc.second].min_label ;
					nets[net_index].last_dir=0;
					nets[net_index].last_left=true;
					nets[net_index].last_right=false;

  				}

				// finally check the vtx to the right
				else if ((gc.first < right_boundary[gc.second-1] &&
    			gcells[gc.first+1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the right is valid
      			&& gcells[gc.first+1][gc.second].min_label < min&&(nets[net_index].last_left!=true||nets[net_index].snake_on==true||snake_just_off))&&(nets[net_index].furtherleft!=true||upflag==false)){
    				p = make_pair(gc.first+1, gc.second) ;
    				min = gcells[gc.first+1][gc.second].min_label ;
					nets[net_index].last_dir=2;
					nets[net_index].last_left=false;
					nets[net_index].last_right=true;
  				}

				if(nets[net_index].last_dir==1){
					nets[net_index].last_right=false;
					nets[net_index].last_left=false;
				}
				if(nets[net_index].last_dir==0&&gcells[gc.first-1][gc.second].min_label>gcells[gc.first][gc.second-1].min_label)
					nets[net_index].furtherleft=1;
			}
		
			else{
			
				// then check the vtx to the left
  				if (gcells[gc.first-1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the left is valid
      			&& (gcells[gc.first-1][gc.second].min_label +length+1<= nets[net_index].maxL&&gc.second!=1||(gc.second==1&&nets[net_index].topT<gc.first))&&(nets[net_index].last_dir!=2||nets[net_index].snake_on||snake_just_off)&&nets[net_index-1].coord[gc.second-1].first<gc.first-1&&nets[net_index-1].coord[gc.second-1].second<gc.first-1){
    				p = make_pair(gc.first-1, gc.second) ;
    				min = gcells[gc.first-1][gc.second].min_label ;
					nets[net_index].last_dir=0;
  				}

				// finally check the vtx to the right
				else if (gc.first < right_boundary[gc.second-1] &&
    			gcells[gc.first+1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the right is valid
      			&& gcells[gc.first+1][gc.second].min_label < min&&(nets[net_index].last_left!=true||nets[net_index].snake_on==true||snake_just_off)){
    				p = make_pair(gc.first+1, gc.second) ;
    				min = gcells[gc.first+1][gc.second].min_label ;
					nets[net_index].last_dir=2;
  				}
				if(gc.second>0&&gcells[gc.first][gc.second-1].last_net==gcells[gc.first][gc.second].last_net){
    				p = make_pair(gc.first, gc.second-1) ;
    				min = gcells[p.first][p.second].min_label ;
					nets[net_index].last_dir=1;
					nets[net_index].last_left=false;
					nets[net_index].last_right=false;
  				}

					//nets[net_index].up_streak=0;

				//dummy last direction for left
				if(nets[net_index].last_dir==0){
					nets[net_index].last_left=true;
					nets[net_index].last_right=false;
					if(gcells[gc.first-1][gc.second].min_label>gcells[gc.first][gc.second-1].min_label)
						nets[net_index].furtherleft=1;

				}
				if(nets[net_index].last_dir==2){
					nets[net_index].last_left=false;
					nets[net_index].last_right=true;
				}

			}
			
		}
		//the first net
		else{
			//set a minimum up block, 4 is a little bit arbitrary
			int minUpBlock=cap;
			
			if((last_direction==0||last_direction==2||nets[net_index].up_streak>=minUpBlock||diagonal_dir==1)&&!snake_just_off){
				// start with the vtx above
  				if (gc.second > 0 && 
    			gcells[gc.first][gc.second-1].last_net == 
      			gcells[gc.first][gc.second].last_net&&
				(nets[net_index].right_streak<1||nets[net_index].right_streak>=minUpBlock||(gcells[gc.first][gc.second-1].min_label<gcells[gc.first+1][gc.second].min_label||gcells[gc.first+1][gc.second].min_label==0))){ // the vtx above is valid
    				p = make_pair(gc.first, gc.second-1) ;
    				min = gcells[p.first][p.second].min_label ;
					nets[net_index].last_dir=1;
					nets[net_index].last_left=false;
  				}

				// then check the vtx to the left
  				if (gc.first!=0&&
      			gcells[gc.first-1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the left is valid
      			&& gcells[gc.first-1][gc.second].min_label <= min&&(nets[net_index].last_dir!=2||nets[net_index].snake_on==true||snake_just_off)){
    				p = make_pair(gc.first-1, gc.second) ;
    				min = gcells[gc.first-1][gc.second].min_label ;
					nets[net_index].last_dir=0;
  				}

				// finally check the vtx to the right
				if (gc.first<xsize&&
    			gcells[gc.first+1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the right is valid
      			&& gcells[gc.first+1][gc.second].min_label < min&&(nets[net_index].last_left!=true||nets[net_index].snake_on==true||snake_just_off)){
					if(nets[net_index].right_streak<=minUpBlock||min==20000000){
    					p = make_pair(gc.first+1, gc.second) ;
    					min = gcells[gc.first+1][gc.second].min_label ;
						nets[net_index].last_dir=2;
						nets[net_index].right_streak++;
						nets[net_index].last_left=false;
					}
  				}

				//reset the right streak
				if(nets[net_index].last_dir!=2){
					nets[net_index].right_streak=0;
				}

				//reset the upstreak
				if(nets[net_index].last_dir!=1){
					nets[net_index].up_streak=0;
				}
			
				//set the dummy last direction for left
				if(nets[net_index].last_dir==0)
					nets[net_index].last_left=true;
			}
		
			else if(last_direction==1||snake_just_off){
				// then check the vtx to the left
  				if (gc.first!=0&&
      			gcells[gc.first-1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the left is valid
      			&& gcells[gc.first-1][gc.second].min_label < min&&(nets[net_index].last_dir!=2||nets[net_index].snake_on==true||snake_just_off)){
    				p = make_pair(gc.first-1, gc.second) ;
    				min = gcells[gc.first-1][gc.second].min_label ;
					nets[net_index].last_dir=0;
  				}

				// finally check the vtx to the right
				if (gc.first<xsize&&
    			gcells[gc.first+1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the right is valid
      			&& gcells[gc.first+1][gc.second].min_label < min&&(nets[net_index].last_left!=true||nets[net_index].snake_on==true||snake_just_off)&&((gc.second-nets.size()+net_index+1)<=0||gc.first<right_boundary[gc.second-nets.size()+net_index+1])){
    				p = make_pair(gc.first+1, gc.second) ;
    				min = gcells[gc.first+1][gc.second].min_label ;
					nets[net_index].last_dir=2;
					nets[net_index].last_left=false;
  				}

				// end with the vtx above
  				if (gc.second > 0 && 
    			gcells[gc.first][gc.second-1].last_net == 
      			gcells[gc.first][gc.second].last_net&&
				gc.first>=left_boundary[gc.second-1]){ // the vtx above is valid
    				p = make_pair(gc.first, gc.second-1) ;
    				min = gcells[p.first][p.second].min_label ;
					nets[net_index].last_dir=1;
					nets[net_index].last_left=false;
					nets[net_index].right_streak=0;
  				}
				//reset the right streak
				if(nets[net_index].last_dir!=2){
					nets[net_index].right_streak=0;
				}
				//else, increment the right streak
				else{
					nets[net_index].right_streak++;
				}
	
				//reset the upstreak
				if(nets[net_index].last_dir!=1){
					nets[net_index].up_streak=0;
				}
				//else, increment the upstreak
				else{
					nets[net_index].up_streak++;
				}
				if(nets[net_index].last_dir==0)
					nets[net_index].last_left=true;
			}
		}
  }
	//bound is not on
  else{
	if(net_index!=0){
			if((nets[net_index].up_streak>=net_index || diagonal_dir==1)){
				// start with the vtx above
  				if (gc.second > 0 && 
    			gcells[gc.first][gc.second-1].last_net == 
      			gcells[gc.first][gc.second].last_net&&
				gc.first>nets[net_index-1].coord[gc.second-1].second&&(nets[net_index].right_streak<1
				||nets[net_index].right_streak>(ysize-1)
||(gcells[gc.first][gc.second-1].min_label<gcells[gc.first+1][gc.second].min_label||gcells[gc.first+1][gc.second].min_label==0))){ // the vtx above is valid
    				p = make_pair(gc.first, gc.second-1) ;
    				min = gcells[p.first][p.second].min_label ;
					nets[net_index].right_streak=0;
					nets[net_index].last_left=false;
					nets[net_index].last_dir=1;
  				}

				// then check the vtx to the left
  				if (gc.first-1>nets[net_index-1].coord[gc.second].second && 
      			gcells[gc.first-1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the left is valid
      			&& gcells[gc.first-1][gc.second].min_label <= min&&nets[net_index].last_dir!=2&&gc.first-1>nets[net_index-1].coord[gc.second].second&&gc.first-1>nets[net_index-1].coord[gc.second].first){
    				p = make_pair(gc.first-1, gc.second) ;
    				min = gcells[gc.first-1][gc.second].min_label ;
					nets[net_index].last_dir=0;
  				}
		
				// finally check the vtx to the right
				if (gc.first < xsize-1 &&
    			gcells[gc.first+1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the right is valid
      			&& gcells[gc.first+1][gc.second].min_label < min&&nets[net_index].last_left!=true){
    				p = make_pair(gc.first+1, gc.second) ;
    				min = gcells[gc.first+1][gc.second].min_label ;
					nets[net_index].last_dir=2;
					nets[net_index].right_streak++;
					nets[net_index].last_left=false;
  				}
				if(nets[net_index].last_dir==0)
					nets[net_index].last_left=true;
			}
		
			else{
			
				// then check the vtx to the left
  				if (gc.first-1>nets[net_index-1].coord[gc.second].second && 
      			gcells[gc.first-1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the left is valid
      			&& gcells[gc.first-1][gc.second].min_label < min&&nets[net_index].last_dir!=2&&gc.first-1>nets[net_index-1].coord[gc.second].second&&gc.first-1>nets[net_index-1].coord[gc.second].first){
    				p = make_pair(gc.first-1, gc.second) ;
    				min = gcells[gc.first-1][gc.second].min_label ;
					nets[net_index].last_dir=0;
  				}
		
				// finally check the vtx to the right
				if (gc.first < xsize-1 &&
    			gcells[gc.first+1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the right is valid
      			&& gcells[gc.first+1][gc.second].min_label < min&&nets[net_index].last_left!=true){
    				p = make_pair(gc.first+1, gc.second) ;
    				min = gcells[gc.first+1][gc.second].min_label ;
					nets[net_index].last_dir=2;
					nets[net_index].last_left=false;
  				}

				// end with the vtx above
  				if (gc.second > 0 && 
    			gcells[gc.first][gc.second-1].last_net == 
      			gcells[gc.first][gc.second].last_net&&
				gc.first>nets[net_index-1].coord[gc.second-1].second){ // the vtx above is valid
    				p = make_pair(gc.first, gc.second-1) ;
    				min = gcells[p.first][p.second].min_label ;
					nets[net_index].last_dir=1;
					nets[net_index].last_left=false;
  				}
				nets[net_index].up_streak++;

				if(nets[net_index].last_dir==0)
					nets[net_index].last_left=true;
			}
			
		}
		//the first net
		else{
			//set a minimum up block, 4 is a little bit arbitrary
			int minUpBlock=cap;
			
			if((last_direction==0||last_direction==2||nets[net_index].up_streak>=minUpBlock+net_index||diagonal_dir==1)){
				// start with the vtx above
  				if (gc.second > 0 && 
    			gcells[gc.first][gc.second-1].last_net == 
      			gcells[gc.first][gc.second].last_net&&
				(nets[net_index].right_streak<1
				||nets[net_index].right_streak>(ysize-1)
||(gcells[gc.first][gc.second-1].min_label<gcells[gc.first+1][gc.second].min_label||gcells[gc.first+1][gc.second].min_label==0))){ // the vtx above is valid
    				p = make_pair(gc.first, gc.second-1) ;
    				min = gcells[p.first][p.second].min_label ;
					nets[net_index].last_dir=1;
					nets[net_index].right_streak=0;
					nets[net_index].last_left=false;
  				}

				// then check the vtx to the left
  				if (gc.first > 0 && 
      			gcells[gc.first-1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the left is valid
      			&& gcells[gc.first-1][gc.second].min_label <= min&&nets[net_index].last_dir!=2){
    				p = make_pair(gc.first-1, gc.second) ;
    				min = gcells[gc.first-1][gc.second].min_label ;
					nets[net_index].last_dir=0;
  				}
		
				// finally check the vtx to the right
				if (gc.first < xsize-1 &&
    			gcells[gc.first+1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the right is valid
      			&& gcells[gc.first+1][gc.second].min_label < min&&nets[net_index].last_left!=true){
    				p = make_pair(gc.first+1, gc.second) ;
    				min = gcells[gc.first+1][gc.second].min_label ;
					nets[net_index].last_dir=2;
					nets[net_index].right_streak++;
					nets[net_index].last_left=false;
  				}
				nets[net_index].up_streak=0;

				if(nets[net_index].last_dir==0)
					nets[net_index].last_left=true;
			}
		
			else if(last_direction==1){
				// then check the vtx to the left
  				if (gc.first > 0 && 
      			gcells[gc.first-1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the left is valid
      			&& gcells[gc.first-1][gc.second].min_label < min&&nets[net_index].last_dir!=2){
    				p = make_pair(gc.first-1, gc.second) ;
    				min = gcells[gc.first-1][gc.second].min_label ;
					nets[net_index].last_dir=0;
  				}

				// finally check the vtx to the right
				if (gc.first < xsize-1 &&
    			gcells[gc.first+1][gc.second].last_net ==
      			gcells[gc.first][gc.second].last_net // the vtx to the right is valid
      			&& gcells[gc.first+1][gc.second].min_label < min&&nets[net_index].last_left!=true){
    				p = make_pair(gc.first+1, gc.second) ;
    				min = gcells[gc.first+1][gc.second].min_label ;
					nets[net_index].last_dir=2;
					nets[net_index].last_left=false;
  				}

				// end with the vtx above
  				if (gc.second > 0 && 
    			gcells[gc.first][gc.second-1].last_net == 
      			gcells[gc.first][gc.second].last_net){ // the vtx above is valid
    				p = make_pair(gc.first, gc.second-1) ;
    				min = gcells[p.first][p.second].min_label ;
					nets[net_index].last_dir=1;
					nets[net_index].last_left=false;
  				}
				nets[net_index].up_streak++;

				if(nets[net_index].last_dir==0)
					nets[net_index].last_left=true;
			}
		} 
  }

  

  
  return p ;
}


// given the gridcell coord gc, the routed "length" until gc, and the
//   min-length constraint "minL", find the best parent coord that
//   satisfies the minL constraint, but that does not use unnecessary snaking
// ASSUMING THAT GRAPH ALREADY SET FOR THIS NET
pair<int, int> find_best_parent(pair<int,int> gc, int minL, int maxL, int length){

  // the vertices were defined to be on the boundaries
  // so, we can find the boundaries by reading the vertices
  int minx = vertices[gc.second-1].first ;
  int maxx = vertices[gc.second-1].second ;

  int min = INT_INF ;
  pair<int,int> best_p ;
  int x;
  int p_minlabel;
  int p_dist;
  for (x=minx; x<=maxx; x++){
    // check parent p that has the coord (x, gc.second-1)

    // the minlabel of parent
    p_minlabel = gcells[x][gc.second-1].min_label ;
    
    // the distance between gc and p
    p_dist = abs(gc.first-x) + 1 ;

    if (length + p_dist + p_minlabel >= minL // p satisifes minL constraint
	&& p_dist + p_minlabel < min){
      min = p_dist + p_minlabel ;
      best_p = make_pair(x, gc.second-1) ;
    }

  }
	//changed here to accomodate maximum constraint
	while(length+p_dist+p_minlabel>maxL){
		x++;
		p_minlabel=gcells[x][gc.second-1].min_label;
		p_dist=abs(gc.first-x)+1;
		best_p=make_pair(x, gc.second-1);
	}


	//cout<<"best: "<<best_p.first<<" "<<best_p.second<<endl;
  
  return best_p ;
}




// assuming that the area is already allocated (flip info contained in f)
// we may need to "snake" to satisfy minL constraint
vector<pair<int, int> > find_route(int net_ind, FlipInfo f, const Boundary& rbf){

  Net& net = nets[net_ind] ;

  bool snake_just_off=false;

  //set_min_labels(net_ind, f, rbf) ;
  // prepare the graph used for snaking 
  // Labels indicate the max-length path to the top terminal
  set_graph(net_ind, f, rbf) ;

  max_labels[1] = make_pair(1,1) ;
  // Distance from top of row 1 to row 0 (where the top terminal is) 
  //  is actually 1/2. However, since we ignore the bottom 1/2 connection 
  //  from top of row ysize-1 to the bottom terminal, we set the distance
  //  here (above) to 1, instead of 1/2. This gives the correct result since
  //  we end our route at the top of row ysize-1, instead of at the bottom
  //  terminal (middle of row ysize-1)
  for (int i=2; i<ysize; i++){
    set_max_labels(i) ;
	//cout<<"net index= "<<net_ind<<" max_labels first= "<<max_labels[i].first<<" max_labels second: "<<max_labels[i].second<<endl;
	}

  //set_min_labels(net_ind, f, rbf) ;
	nets[net_ind].last_dir=1;
	nets[net_ind].up_streak=0;
	nets[net_ind].last_left=0;
	nets[net_ind].last_right=0;
	nets[net_ind].snake_on=false;
	nets[net_ind].furtherleft=0;
  // labels indicate the min distance to the top terminal

  // We start with traversing the graph used for snaking.
  // When we have done enough snaking, we switch to traversing the
  //   labeled grid cells to find the min path.

  vector<pair<int, int> > route ;
  
  int length = 0 ; // keep track of current length

  // As indicated above, we first traverse the graph, then traverse
  //  gridcells. The variables below keep the current state info.

  int v ; // it can be FIRST_VERTEX, SECOND_VERTEX, or NOT_A_VERTEX
  pair<int,int> gc ; // the current gridcell coord


	//a counter that counts how many rows use snaking.
	int snake_count=0;

  v = FIRST_VERTEX ; 
  // for the last row, two vertices have the same position
  // So, we select arbitrarily the FIRST VERTEX

  gc = make_pair(nets[net_ind].bottomT, ysize-1) ; // the gridcell coord
  
  // find the path to the top terminal
  while (!(gc.second == 1 && gc.first == net.topT)){
    route.push_back(gc) ; // add the current grid cell to "route"
   
	//changed here
    //if(net_ind==nets.size()-2)
		//cout<<"stuck "<<gc.first<<" "<<gc.second<<" "<<net.topT<<endl;
    //end here
    // find the parent gcell that is on the min-path to the top terminal
	//in case we need to get the parent cell again
	int temp=nets[net_ind].last_dir;
    pair<int,int> minp = get_parent_gcell(gc, net_ind, nets[net_ind].last_dir, snake_just_off,length) ; 
	//changed here
	if(minp.first==xsize&&minp.second==ysize&&nets[net_ind].snake_on!=true){
		char buffer [50];
		int n;
		n=sprintf(buffer, "Net %d is not routable, the rest of the nets cannot be routed", net_ind);
		string error=buffer;
		 
		throw Logic_error(error); 
	}
	//end here
    int minp_minlabel = gcells[minp.first][minp.second].min_label ;
	bool continueSnake=false;
	if(length+1+minp_minlabel>=net.minL&&nets[net_ind].snake_on==true){
		if(gc.first!=0&&gcells[gc.first-1][gc.second].last_net==gcells[gc.first][gc.second-1].last_net){
			if(gcells[gc.first-1][gc.second].min_label>gcells[gc.first][gc.second-1].min_label)
				continueSnake=true;
		}
	}
	
    // check if following the min path would satisfy min length constraint
    if (length + 1 + minp_minlabel >= net.minL&&continueSnake!=true){	
		if(nets[net_ind].snake_on==true){
			snake_just_off=true;
		}
		if(snake_just_off==true){
			minp=get_parent_gcell(gc, net_ind, temp, true,length);
			minp_minlabel=gcells[minp.first][minp.second].min_label;
		}
      // follow the min path to the top terminal
      v = NOT_A_VERTEX ; // set c for next iteration of the loop
      gc = minp ; // for next iteration of the loop
      length += 1 ; // since we know that parent must be a neighbour
		  
		nets[net_ind].snake_on=false;
		snake_just_off=false;	
      continue ;
    }

    // else, we need more snaking to satisfy min length constraint

#ifdef DEBUG
    if (v == NOT_A_VERTEX) // means we've already started following min path
      throw Logic_error("Snaking needed while following min path") ;
#endif

	  snake_count++;

    // first, check whether full snaking on this edge is necessary
    int pv = get_max_parent(gc.second, v) ; // the parent vertex
    pair<int,int> p_gc = get_vtx_coord(gc.second-1, pv) ; // its coord

	//changed here
	if(gc.second-2>=0&&(gc.second-2)<right_boundary.size()){
		if(net_ind!=nets.size()-2&&p_gc.first>gc.first&&(right_boundary[gc.second-2]-1)<p_gc.first){
			p_gc.first=right_boundary[gc.second-2]-1;
		}
		//cout<<"right boundary= "<<right_boundary[gc.second-2];
	}
		//cout<<"net_ind: "<<net_ind<<endl;
		//cout<<"pv: "<<pv<<endl;
		//cout<<"p_gc "<<p_gc.first<<" "<<p_gc.second<<endl;
	//end here


    int p_dist = abs(gc.first - p_gc.first) + 1 ; 
    // the distance between v and p
    
    int p_minlabel = gcells[p_gc.first][p_gc.second].min_label ;
    // the min_label of parent gcell, i.e. the min distance from p_gc to top

    
    if (length + p_dist + p_minlabel > net.minL){
      // we don't need full snaking on this edge; so use a partial snaking,
      //  and then continue following min-path to top in later iterations
      
      // find the best parent grid cell based on current length and minL
      p_gc = find_best_parent(gc, net.minL, net.maxL, length) ;
      
      length += (abs(gc.first-p_gc.first) + 1) ;
      
      v = NOT_A_VERTEX ; // for the next iteration
      gc = p_gc ; // for the next iteration

	   //indicate that there's snaking
	  nets[net_ind].snake_on=false;
	  snake_just_off=true;

    }
    else{ // perform full snaking on this edge
      // the calculated values for p_gc and pv still valid

      length += (abs(gc.first-p_gc.first) + 1) ;
      v = pv ; // for the next iteration
      gc = p_gc ; // for the next iteration

	  //indicate that there's snaking
	  nets[net_ind].snake_on=true;
		
    }



  }

  // connect to the last gc (on the first row)
  route.push_back(gc) ;
	  
  // connect the top terminal to the end of the route
  route.push_back(make_pair(route.back().first, 0)) ;

  reverse(route.begin(), route.end()) ;

  // now the route begins from the top terminal

  //indicate that the net cannot satisfy min constraint.
	if(length + 1 + gcells[gc.first][gc.second].min_label < net.minL)
		cout<<"Net "<<net_ind<<" cannot satisfy the minimum length constraint"<<endl;

	//change:print the route info here

	//actually connect all the routes here
	if(find_ptr(route,net_ind)==-1){
		//there is trap so need to reassign the vertices
		route.clear();
		return route;
	}
	//get all the horizontal info


  	for(int i=0;i<nets[net_ind].turn_pt.size();i++){
		if(i==0){
			nets[net_ind].coord.push_back(make_pair(nets[net_ind].turn_pt[i].first, -1));
		}
	
		/*else if(!adjacent(nets[net_ind].turn_pt[i],nets[net_ind].turn_pt[i-1])){
			
			nets[net_ind].coord[nets[net_ind].coord.size()-1].second=nets[net_ind].turn_pt[i].first;
			nets[net_ind].coord.push_back(make_pair(route[i].first,-1));
		}*/
		else{
			if(nets[net_ind].turn_pt[i].second!=nets[net_ind].turn_pt[i-1].second){
				//if(nets[net_ind].coord[nets[net_ind].coord.size()-1].second==-1){
					nets[net_ind].coord[nets[net_ind].coord.size()-1].second=nets[net_ind].turn_pt[i-1].first;
				//}

				nets[net_ind].coord.push_back(make_pair(nets[net_ind].turn_pt[i].first, -1));
			}
		}
	}
	nets[net_ind].coord[nets[net_ind].coord.size()-1].second=nets[net_ind].turn_pt[nets[net_ind].turn_pt.size()-1].first;







	/*for(int i=0;i<nets[net_ind].turn_pt.size();i++){
		//cout<<"i= "<<i<<" turn_pt first= "<<nets[net_ind].turn_pt[i].first<<" turn_pt second= "<<nets[net_ind].turn_pt[i].second<<endl;;
	}*/

	//print out the horizontal segments in each row
	/*for(int i=0;i<nets[net_ind].coord.size();i++){
		cout<<"i= "<<i<<" first2 "<<nets[net_ind].coord[i].first<<" second2= "<<nets[net_ind].coord[i].second<<endl;
	}*/

  	//end here

  return route ;
  
}



extern void drawBoundary(ofstream& ofs, Boundary b) ;
extern void writeHeaderFig(ostream& os) ;
void drawRoute(ofstream& ofs, vector<pair<int,int> > route,int net_ind, int region, int numBlock, int draw_bot) ;

// the last flip may be partial (i.e. the whole column not flipped)
// c_ind is the last column (i.e. the column at which we perform single flips)
// Return value is the info for the best flip sequence (including columnwise
//   flips)
FlipInfo find_last_flip(int net_ind, int c_ind, const Boundary& rbf){

  // the points of left boundary that are at column c_ind
  vector<int> L = LBoundaries[net_ind+1].getColumn(c_ind) ;
  // the points of right boundary that are at column c_ind+1
  vector<int> R = RBoundaries[net_ind+1].getColumn(c_ind+1) ;

  /*if (net_ind == 33){

    ofstream ofs("out_test.fig") ;
    writeHeaderFig(ofs) ;

    for (int i=0; i<33; i++)
      drawRoute(ofs, routes[i], net_ind) ;

    drawBoundary(ofs, LBoundaries[net_ind+1]) ;
    drawBoundary(ofs, RBoundaries[net_ind+1]) ;
  }*/

  int t ; // the top gcell that can be allocated
  int b ; // the bottom gcell that can be allocated
  bool allocate_from_top ; // whether allocate grid cells from top or from 
  //                          bottom. See "rules for flipping" for more info

  // we have 6 cases (see them in the notes)
  if (L.size() == 1 && R.size() == 1 && L[0] < R[0]){ // case 1 in notes
    t = L[0] ;
    b = R[0] - 2 ;
    allocate_from_top = true ;
  }
  else if (L.size() == 1 && R.size() == 1 && L[0] > R[0]){ // case 2 in notes
    t = R[0] + 1 ;
    b = L[0] - 1 ;
    allocate_from_top = false ;
  }
  else if (L.size() == 2 && R.size() == 0){ // case 3 in notes
    t = min(L[0], L[1]) ;
    b = max(L[0], L[1]) - 1 ;
    allocate_from_top = true ;
  }
  else if (L.size() == 0 && R.size() == 2){ // case 4 in notes
    t = min(R[0], R[1]) + 1 ;
    b = max(R[0], R[1]) - 2 ;
    allocate_from_top = true ;
  }
  else if (L.size() == 2 && R.size() == 2){ // case 5 in notes
    
    if (min(R[0],R[1]) == min(L[0],L[1]) - 1){
      // if no space between top segments of L and R
      t = max(L[0], L[1]) ;
      b = max(R[0], R[1]) - 2 ;
      allocate_from_top = true ;
    }
    else if (max(L[0],L[1]) == max(R[0],R[1]) - 1){
      // if no space between bottom segments of L and R
      // t = min(R[0], R[1]) + 1 ;
      // b = min(L[0], L[1]) - 1 ;
      // allocate_from_top = false ;
      // Since we perform single flips from the top, 5(b) is not possible
     // throw Logic_error("Unexpected case in find_last_flip: case 5(b)") ;
		t = 1;
    	b = ysize - 1 ;
    	allocate_from_top = true ;
	}
    else{
		t = 1;
    	b = ysize - 1 ;
    	allocate_from_top = true ;
      //cout << net_ind << " ";
      //throw Logic_error("Unexpected case: right boundary can't be concave monotonic") ;
    }

  }
	//I dont' know what to do here, just try an all hail mary
  else{
 	t = 1;
    b = ysize - 1 ;
    allocate_from_top = true ;
	}
//    throw Logic_error("Unexpected case in find_last_flip") ;


  // now perform binary search to find the min number of single flips
  // between t and b
  // Note that at least one grid cell must be allocated, since 
  //  we know that f.last_column=c_ind - 1  does not satisfy the length const.
  
  FlipInfo f ;
  f.last_column = c_ind - 1 ; // the last complete flip
  f.last_allocated_top = t ;
  f.last_allocated_bottom = b ;
  f.flip_next=false;
  int stepsize = max(1, (t+b+1)/2) ;

  if (allocate_from_top){ // keep f.last_allocated_top=t, 
    // and try to find the min_y such that f.last_allocated_bottom=min_y
    // satisfies the min length consraint, but f.last_allocated_bottom=min_y-1
    // does not.
	
	//a flag to indicate there's an infinte loop.
	int looptimes=0;
    int min_y = b + 2 ; // this is like an INF value
    while (f.last_allocated_bottom != min_y){


      // since we decrease the stepsize at every iteration, the only way
      //  we visit the same y value (i.e. min_y) again is by coming from
      //  below, by a step size of 1.

      int len = find_max_length(net_ind, f, rbf) ;
      if (len >= nets[net_ind].minL){ // satisfies length constraint
	min_y = min(min_y, f.last_allocated_bottom) ;
	f.last_allocated_bottom -= stepsize ;
      }
      else
	f.last_allocated_bottom += stepsize ;
      stepsize = max(1, stepsize/2) ;
		if(f.last_allocated_bottom>=ysize)
			looptimes++;
		if(looptimes>=2)
			return f;
    }
	//indicate that the next line needs to be flipped.
	if(f.last_allocated_bottom==b+2){
		f.flip_next=true;
	}


    // Now, f holds the info for the min flip sequence that satisfies min
    //   length constraint

#ifdef DEBUG
    //if (f.last_allocated_bottom > b)
      //throw Logic_error("Flipped beyond the bottom boundary at last column");
#endif
  }
  else{ // keep f.last_allocated_bottom=b, 
    // and try to find the max_y such that f.last_allocated_top=max_y
    // satisfies the min length consraint, but f.last_allocated_top=max_y+1
    // does not.
	int looptimes=0;
    int max_y = t - 2  ; // this is like an INF value
    while (f.last_allocated_top != max_y){
      // since we decrease the stepsize at every iteration, the only way
      //  we visit the same y value (i.e. max_y) again is by coming from
      //  above, by a step size of 1.

      int len = find_max_length(net_ind, f, rbf) ;
      if (len >= nets[net_ind].minL){ // satisfies length constraint
	max_y = max(max_y, f.last_allocated_top) ;
	f.last_allocated_top += stepsize ;
      }
      else
	f.last_allocated_top -= stepsize ;
      stepsize = max(1, stepsize/2) ;

		if(f.last_allocated_top<0){
			looptimes++;
		}
		if(looptimes>=2){
			return f;
		}
    }
	//indicate that the next line needs to be flipped.
	if(f.last_allocated_top==t-2){
		f.flip_next=true;
	}

    // Now, f holds the info for the min flip sequence that satisfies min
    //   length constraint

#ifdef DEBUG
    if (f.last_allocated_top < t)
      throw Logic_error("Flipped beyond the top boundary at last column");
#endif
  }

  
  return f ;
}


// route to satisfy min length constraints
bool route_min_length(int net_ind){

  // first find left boundaries again based on the previous routes
	  findLeftBoundary(net_ind) ;
	  findLeftBoundary2(net_ind+1) ;

  Boundary rbf = find_max_flipped_boundary(net_ind+1) ;

  
  // the final position of left boundary of "net_ind+1" after it is
  //   completely flipped.
  // In a sense, it is the final (utmost) right boundary for net "net_ind"

  

  // first, use binary search to find the min num. of columnwise flips

  FlipInfo f ;
  f.last_allocated_top = -1 ;
  f.last_allocated_bottom = -1 ; // no single flip on the last column
  f.flip_next=false;


  // start the binary search from the first column (we expect the number
  //   of columnwise flips to be small)
  f.last_column = LBoundaries[net_ind+1].minx-1 ; // start with no flip

  set_min_labels(net_ind, f, rbf) ;
  int len = find_max_length(net_ind, f, rbf) ;
  if (len >= nets[net_ind].minL){
    // the initial position satisfies length constraints,
    // So, no need to flip
    allocate_cells(net_ind, f) ;
    routes[net_ind] = find_route(net_ind, f, rbf);
		
	while(routes[net_ind].size()==0){
		//there are trap cells;
		for(int i=0;i<nets[net_ind].trap_cell.size();i++){
			cout<<"trap cells!!! "<<nets[net_ind].trap_cell[i].first<<" "<<nets[net_ind].trap_cell[i].second<<endl;
		}
		routes[net_ind]=find_route(net_ind, f, rbf);
	}
	len=find_max_length(net_ind, f, rbf);
	//cout<<"i= "<<net_ind<<" herehere "<<len<<endl;
	if(len>=nets[net_ind].minL){
 
		for(int i=0;i<routes[net_ind].size();i++){
			if(i!=0){
				if(routes[net_ind][i].second!=routes[net_ind][i-1].second){
					prev_route.push_back(routes[net_ind][i].first);
				}
			}
		}
    	return true ;
	}
  }
  
  int stepsize = 4 ;
  // we want to find the "c" value such that "f.last_column=c" does not
  // satisfy the min length constraint, but "f.last_column=c+1" does.
  int min_c = xsize + 2 ; // this is like an INF value, since c < xsize
  while (f.last_column < min_c){
    // since we decrease the stepsize at every iteration, the only way
    //  we visit the same column (i.e. min_c) again is by coming from
    //  left, by a step size of 1.
    // If no solution exists, f.last_column can be larger than xsize+2

    len = find_max_length(net_ind, f, rbf) ;
    if (len >= nets[net_ind].minL){ // satisfies length constraint
      min_c = min(min_c, f.last_column) ;
      f.last_column -= stepsize ;
    }
    else
      f.last_column += stepsize ;
    stepsize = max(1, stepsize/2) ;
  }
  if (min_c > xsize){ // the min length constraint is never satisfied
    allocate_cells(net_ind, f) ;
    routes[net_ind] = find_route(net_ind, f, rbf) ;

	while(routes[net_ind].size()==0){
		//there are trap cells;
		for(int i=0;i<nets[net_ind].trap_cell.size();i++)
			cout<<"trap cells!!! "<<nets[net_ind].trap_cell[i].first<<" "<<nets[net_ind].trap_cell[i].second<<endl;
		routes[net_ind]=find_route(net_ind, f, rbf);
	}
	len=find_max_length(net_ind, f, rbf);
	//cout<<"i= "<<net_ind<<" herehere "<<len<<endl;


	for(int i=0;i<routes[net_ind].size();i++){
		if(i!=0){
			if(routes[net_ind][i].second!=routes[net_ind][i-1].second){
				prev_route.push_back(i);
			}
		}
	}

	//sepcial note: let fig.C determine if the net is routable or not at the end. Try this first
    return true ;
  }
  

  // f.last_column is the min. number of columnwise flips needed to satisfy
  //   the length constraint
  // we subtract 1 from it; then find the min. number of single flips on the
  //   last column

  f.last_column -= 1 ;

  	/*for(int i=0;i<right_boundary.size();i++){
		if(right_boundary[i]-nets.size()+net_ind+2<=f.last_column){
			f.last_column=right_boundary[i]-net.size()+net_ind+1;
		}
	}*/

  f = find_last_flip(net_ind, f.last_column+1, rbf) ;
  
  allocate_cells(net_ind, f) ;
  routes[net_ind] = find_route(net_ind, f, rbf); 
	
	while(routes[net_ind].size()==0){
		//there are trap cells;
		for(int i =0;i<nets[net_ind].trap_cell.size();i++){
			cout<<"trap cells!!! "<<nets[net_ind].trap_cell[i].first<<" "<<nets[net_ind].trap_cell[i].second<<endl;
		}
		routes[net_ind]=find_route(net_ind, f, rbf);
	}
	len=find_max_length(net_ind, f, rbf);
	//cout<<"i= "<<net_ind<<" herehere "<<len<<endl;
	//find the last flip again;
	while(len<nets[net_ind].minL){

		//apparently there can be an infinte loop here so need to check
		if(f.last_column>=xsize){
			break;
		}

		//need to reset the coord because it may be repeated		
		nets[net_ind].coord.clear();
		//this one can become infinte loop...
		f = find_last_flip(net_ind, f.last_column+1, rbf) ;
		
		if(f.flip_next==true||f.last_allocated_bottom>=ysize||f.last_allocated_top<0){
			f.last_column++;
			f.flip_next=false;
		}
  		f=find_last_flip(net_ind,f.last_column+1, rbf);
 		allocate_cells(net_ind, f) ;
		
		//need a final while loop here maybe
		do{
		//there are trap cells;
			for(int i =0;i<nets[net_ind].trap_cell.size();i++){
				cout<<"trap cells!!! "<<nets[net_ind].trap_cell[i].first<<" "<<nets[net_ind].trap_cell[i].second<<endl;
			}
			routes[net_ind]=find_route(net_ind, f, rbf);
		}while(routes[net_ind].size()==0);
		len=find_max_length(net_ind, f, rbf);
  		//routes[net_ind] = find_route(net_ind, f, rbf); 
	}

	for(int i=0;i<routes[net_ind].size();i++){
		if(i!=0){
			if(routes[net_ind][i].second!=routes[net_ind][i-1].second){
				prev_route.push_back(i);
			}
		}
	}
  return true ;

}


bool check_length_constraints(int net_ind){

  vector<pair<int,int> >& route = routes[net_ind] ;
  int minL = nets[net_ind].minL ;
  int maxL = nets[net_ind].maxL ;
  

  int length = 0 ;
  for (int i=1; i<route.size(); i++){
    length += (abs(route[i].first-route[i-1].first) 
	       + abs(route[i].second - route[i-1].second)) ;
  }

  if (length >= minL && length <= maxL)
    return true ;
  else 
    return false ;
}


// route to satisfy all min length constraints
void route_all_min_length(ofstream& outputfile, int region, int numBlock, int draw_bot){

  init_graph() ;
  routes.resize(nets.size()) ;
  
  // note that the last net is pseudo
  for (int i=0; i<nets.size()-1; i++){
    
	if (!route_min_length(i)){
      cout << "Min length constraint for net " << i << " not satisfied" 
	   <<endl;
	}
	drawRoute(outputfile,routes[i],i, region, numBlock, draw_bot); 
  }

  for (int i=0; i<nets.size()-1; i++)
    if (!check_length_constraints(i))
      cout << "Length constraint not satisfied for net " << i << endl ;

  //cout << "Note that last net is ignored in this version" << endl ;
}
