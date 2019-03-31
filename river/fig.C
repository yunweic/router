#include <fstream>
#include <iostream>
#include "route.h"

#define SCALE 100
//changed here
extern bool bound_on;
extern vector<int> right_boundary;
extern vector<int> left_boundary;
extern int min_bound;

extern vector<pair<int,int> > max_labels;
//end here

void writeHeaderFig(ostream& os){

  os << "#FIG 3.2" << endl ;
  os << "Landscape" << endl ;
  os << "Center" << endl ;
  os << "Metric" << endl ;
  os << "A4" << endl ;
  os << "100.00" << endl ;
  os << "Single" << endl ;
  os << "-2" << endl ;
  os << "1200 2" << endl ;

}

typedef enum LineType{SOLID, DASHED, DOTTED} ;

// (x,y) is the upper left corner
// distx,disty is the width and height of the rectangle
void drawRectangle(ostream&os, int x, int y, int distx, int disty, LineType t){

  os << "2 2 " << t << " 1 0 7 50 0 -1 0.000 0 0 -1 0 0 5" << endl ;
  os << x << " " << y << " " << x+distx << " " << y << " " 
     << x+distx << " " << y+disty << " " << x << " " << y+disty << " " 
     << x << " " << y << endl ;

}

void drawPolyLine(ostream& os, const vector<pair<int,int> >& points, LineType t, int width=1, int color = 1, int depth=50){

  os << "2 1 "<<t<<" " << width << " " << color << " 7 " << depth << " 0 -1 0.000 0 0 -1 0 0 " << points.size() <<endl;
  
  for (int i=0; i<points.size(); i++){
    os << points[i].first << " " << points[i].second << " " ;
  }
  os << endl ;

}


void drawCircle(ostream& os, int x, int y, int r, LineType t){

  os << "1 3 " << t << " 1 0 7 50 0 -1 0.000 1 0.0000 "
     << x << " " << y << " " << r << " " << r << " "
     << x << " " << y << " " << x+r << " " << y << endl ; 

}


// (x,y) is the upper left corner
// distx,disty is the width and height of the rectangle
void drawFilledRectangle(ostream&os, int x, int y, int distx, int disty, LineType t){

  //os << "2 2 " << t << " 1 0 7 50 0 -1 0.000 0 0 -1 0 0 5" << endl ;

  os << "2 2 " << t << " 1 0 17 50 0 46 4.000 0 0 -1 0 0 5" << endl ;
  os << x << " " << y << " " << x+distx << " " << y << " " 
     << x+distx << " " << y+disty << " " << x << " " << y+disty << " " 
     << x << " " << y << endl ;

}

void putText(ostream& os, int x, int y, string str, int fontsize){

  os << "4 0 0 50 0 0 " << fontsize <<  " 0.0000 4 135 495 " << x << " " << y 
     << " " << str << "\\001" << endl << endl ;
}



inline pair<int,int> getGPointCoord(Point p){
  return make_pair(p.x * SCALE, p.y * SCALE) ;
}

inline pair<int,int> getGCellCoord(pair<int,int> p){
  return make_pair(p.first * SCALE + SCALE/2, p.second * SCALE + SCALE/2) ;
}



void drawGrid(ofstream& ofs, int start){

  vector<pair<int,int> > points(2) ;
  int top=ysize;

  if(!bound_on){
  	// first draw the vertical lines
  	for (int i=0; i<=xsize; i++){
		points[0] = getGPointCoord(Point(i,0)) ;
    		points[1] = getGPointCoord(Point(i,ysize));
    		drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
  	}

  	// then draw the horizontal lines
  	for (int i=0; i<=ysize; i++){
    		points[0] = getGPointCoord(Point(0,i)) ;
    		points[1] = getGPointCoord(Point(xsize,i)) ;
    		drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
  	}
  }
  else{
	for(int i=0;i<ysize;i++){
		int left=left_boundary[i];
		int right=right_boundary[i];
		
		points[0]=getGPointCoord(Point(left,i+start));
		points[1]=getGPointCoord(Point(right,i+start));
    		drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
			

		points[0]=getGPointCoord(Point(left,i+start+1));
		points[1]=getGPointCoord(Point(right,i+start+1));
    		drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);

		
		for(int j=left;j<=right;j++){
			points[0]=getGPointCoord(Point(j,i+start));
			points[1]=getGPointCoord(Point(j,i+start+1));
    			drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
		}
	}
  }

}


void drawBoundary(ofstream& ofs, Boundary b){

  vector<pair<int, int> > points ;

  for (int i=0; i<b.points.size(); i++)
    points.push_back(getGPointCoord(b.points[i])) ;

  drawPolyLine(ofs, points, SOLID) ;

}

bool adjacent(pair<int,int> gc1, pair<int,int> gc2){

  if ( (abs(gc1.first - gc2.first) == 1 &&
	gc1.second == gc2.second) ||
       (abs(gc1.second - gc2.second) == 1 &&
	gc1.first == gc2.first))
    return true ;
  else
    return false ;
}

void drawRoute(ofstream& ofs, vector<pair<int,int> > route, int net_ind, int region, int numBlock, int draw_bot){
  
  	if (route.size() == 0)
    	return ;

  	vector<pair<int,int> > points ;
	
	//print all the points

	//the case for up diagonal region
	if(region==0){
		for(int i=0;i<nets[net_ind].turn_pt.size();i++)
			nets[net_ind].turn_pt[i].second+=numBlock;
	}
	if(draw_bot){
		int top=numBlock+region;
		for(int i=0;i<nets[net_ind].turn_pt.size();i++)
			nets[net_ind].turn_pt[i].second+=top;
	}


	for(int i=0;i<nets[net_ind].turn_pt.size();i++){
		if(i==0&&draw_bot){
			points.push_back(getGCellCoord(make_pair(nets[net_ind].turn_pt[i].first, nets[net_ind].turn_pt[i].second-1)));
		}
		points.push_back(getGCellCoord(nets[net_ind].turn_pt[i]));
	}

  	drawPolyLine(ofs, points, SOLID) ;
}

//draw back diagonal region
void draw_diagonal(ofstream& ofs, int num, int dir, int region){
  vector<pair<int,int> > points(2) ;
	if(bound_on){
		if(region==ysize+num){
			for(int i=0;i<num;i++){
				int left=left_boundary[left_boundary.size()-num+i];
				int right=right_boundary[left_boundary.size()-num+i];
				points[0]=getGPointCoord(Point(left, i+ysize));
				points[1]=getGPointCoord(Point(right, i+ysize));
				drawPolyLine(ofs, points, DASHED, 1, 3, 51);
		
				points[0]=getGPointCoord(Point(left, i+ysize+1));
				points[1]=getGPointCoord(Point(right, i+ysize+1));
				drawPolyLine(ofs, points, DASHED, 1, 3, 51);
		
				for(int j=left;j<=right;j++){
					points[0]=getGPointCoord(Point(j,i+ysize));
					points[1]=getGPointCoord(Point(j,i+ysize+1));
    					drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
				}

			}
		}
		//diagonal region at top
		else if(region==0){
			for(int i=0;i<num;i++){
				int left=left_boundary[left_boundary.size()-num+i];
				int right=right_boundary[left_boundary.size()-num+i];
				points[0]=getGPointCoord(Point(left, i));
				points[1]=getGPointCoord(Point(right, i));
				drawPolyLine(ofs, points, DASHED, 1, 3, 51);
		
				points[0]=getGPointCoord(Point(left, i+1));
				points[1]=getGPointCoord(Point(right, i+1));
				drawPolyLine(ofs, points, DASHED, 1, 3, 51);
		
				for(int j=left;j<=right;j++){
					points[0]=getGPointCoord(Point(j,i));
					points[1]=getGPointCoord(Point(j,i+1));
    					drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
				}

			}
		}
		//diagonal region in the middle
		//this place is not used actually
		else{
			for(int i=0;i<num;i++){
				int left=left_boundary[ysize+i];
				int right=right_boundary[ysize+i];
				points[0]=getGPointCoord(Point(left, i+ysize));
				points[1]=getGPointCoord(Point(right, i+ysize));
				drawPolyLine(ofs, points, DASHED, 1, 3, 51);
		
				points[0]=getGPointCoord(Point(left, i+ysize+1));
				points[1]=getGPointCoord(Point(right, i+ysize+1));
				drawPolyLine(ofs, points, DASHED, 1, 3, 51);
		
				for(int j=left;j<=right;j++){
					points[0]=getGPointCoord(Point(j,i+ysize));
					points[1]=getGPointCoord(Point(j,i+ysize+1));
    					drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
				}

			}
	
		}
	}
	//draw the grid without boundary
	else{
		for (int i=0; i<=xsize; i++){
			points[0] = getGPointCoord(Point(i,ysize)) ;
    			points[1] = getGPointCoord(Point(i,ysize+num));
    			drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
  		}

  		// then draw the horizontal lines
  		for (int i=0; i<=num; i++){
    			points[0] = getGPointCoord(Point(0,ysize+i)) ;
    			points[1] = getGPointCoord(Point(xsize,ysize+i)) ;
    			drawPolyLine(ofs, points, DASHED, 1, 3 /*cyan*/, 51 /*depth--deeper*/);
  		}


	}
	//if diagonal region at the bottom
	//draw the diagonal lines
	if(region!=0){
		for(int i=0;i<nets.size()-1;i++){
		 
			points[0]=getGPointCoord(Point(nets[i].bottomT,ysize));
			if(dir==2){
				points[1]=getGPointCoord(Point(nets[i].bottomT+num,ysize+num));
			}
			else if(dir==1){
				points[1]=getGPointCoord(Point(nets[i].bottomT-num,ysize+num));
			}
			points[0].first+=50;
			points[0].second-=50;
			points[1].first+=50;
			points[1].second-=50;
			drawPolyLine(ofs, points, SOLID) ;
		}
	}
		//if diagonal region at the top
	else if(region==0){
		//draw the diagonal lines
		for(int i=0;i<nets.size()-1;i++){
		 
			if(dir==2){
				points[0]=getGPointCoord(Point(nets[i].topT-num,0));
				points[1]=getGPointCoord(Point(nets[i].topT,num));
			}
			else if(dir==1){
				points[0]=getGPointCoord(Point(nets[i].topT+num,0));
				points[1]=getGPointCoord(Point(nets[i].topT,num));
			}
			points[0].first+=50;
			points[0].second+=50;
			points[1].first+=50;
			points[1].second+=50;
			drawPolyLine(ofs, points, SOLID) ;
		}
	}

}
//big note this is added to add the turn point at the find route stage so it's easier for the next route to set vertices. 
int find_ptr(vector<pair<int,int> > route, int net_ind){
  
  	if (route.size() == 0)
    	return -1;
	/*for(int i=0;i<ysize;i++){
		cout<<"i= "<<i<<" max label first = "<<max_labels[i].first<<" max label second = "<<max_labels[i].second<<endl;
	}*/

  	vector<pair<int,int> > points ;
	/*for(int i=0;i<route.size();i++){
		cout<<"route.first= "<<route[i].first<<"route.second "<<route[i].second<<endl;
	}*/

  	points.push_back(route[0]) ;

	//reset the nets length
	nets[net_ind].length=0;
	for (int i=1; i<route.size(); i++){
    	if (!adjacent(route[i-1], route[i])){ // if gcells are not adjacent
      		pair<int,int> interm ; // intermediate point while drawing
				
				if(net_ind!=0){
					//the case where interm is the upper cell
					if((right_boundary[route[i].second-1]>route[i].first&&left_boundary[route[i].second-1]<=route[i].first&&route[i].first>nets[net_ind-1].coord[route[i].second-1].first&&route[i].first>nets[net_ind-1].coord[route[i].second-1].second&&gcells[route[i].first][route[i-1].second].last_net==net_ind&&(points.size()<2||points[points.size()-2].second!=points[points.size()-1].second||(points[points.size()-2].second==points[points.size()-1].second)&&(points[points.size()-2].first<points[points.size()-1].first&&route[i].first>points[points.size()-1].first||points[points.size()-2].first>points[points.size()-1].first&&route[i].first<points[points.size()-1].first)))&&(net_ind==nets.size()-2||(route[i].second!=2||(route[i].second==2&&route[i].first<nets[net_ind+1].topT)))){
						interm.first=route[i].first;
						interm.second=route[i-1].second;

						//calculate the nets length
						nets[net_ind].length=nets[net_ind].length+abs(route[i].first-route[i-1].first)+1;

					}
					//the case where interm is on the same cell with the current row
 					else if(route[i-1].first<route[i].first&&(points.size()<2||points[points.size()-2].second!=route[i].second)){
						//detect if there is a trap cell
						if(route[i].second==ysize-2&&net_ind!=nets.size()-2&&route[i].first>=nets[net_ind+1].bottomT){
							nets[net_ind].trap_cell.push_back(make_pair(route[i].first,route[i].second));
							return -1;
						}

						//need to check if the route is routable, if not, need to change the vertices
						else if(route[i].second==ysize-1||gcells[route[i].first][route[i].second+1].last_net==net_ind){
							//one intermediate point
							if(nets[net_ind-1].coord[route[i].second].first<route[i-1].first&&nets[net_ind-1].coord[route[i].second].second<route[i-1].first)							 {
								interm.first=route[i-1].first;
								interm.second=route[i].second;
							}
							//need two intermediate points to connect
							else{
								pair<int, int> interm2;
								if(nets[net_ind-1].coord[route[i].second].first>nets[net_ind-1].coord[route[i].second].second){
									interm2.first=nets[net_ind-1].coord[route[i].second].first+1;

								}
								else{
									interm2.first=nets[net_ind-1].coord[route[i].second].second+1;
								}
								interm2.second=route[i-1].second;
								points.push_back(interm2);
				
								interm.first=interm2.first;
								interm.second=route[i].second;

							}
							//calculate the nets length
							nets[net_ind].length=nets[net_ind].length+abs(route[i].first-route[i-1].first)+1;
						}
						//indicate there's a trap so the vertices needs to be changed
						else{
							nets[net_ind].trap_cell.push_back(make_pair(route[i].first, route[i].second));
					
							return -1;
						}	

					}
					//second case
					else if(route[i-1].first>route[i].first&&(points.size()<2||points[points.size()-2].second!=route[i].second)){
						if(route[i].second==ysize-1||gcells[route[i].first][route[i].second+1].last_net==net_ind){
							if(net_ind!=nets.size()-2){
								//intermediate point on the same row
								if(gcells[route[i-1].first][route[i].second].last_net==net_ind&&(net_ind==nets.size()-2||route[i].second!=ysize-1||route[i].second==ysize-1&&route[i-1].first<nets[net_ind].bottomT)){
									interm.first=route[i-1].first;
									interm.second=route[i].second;
								}
								//there are two intermediate points
								else{
									int j=route[i-1].first;
									if(net_ind!=0&&j<=max(nets[net_ind-1].coord[route[i].second].first, nets[net_ind-1].coord[route[i].second].second))
										j=max(nets[net_ind-1].coord[route[i].second].first, nets[net_ind-1].coord[route[i].second].second)+1;

									while(gcells[j][route[i].second].last_net!=net_ind)
										j--;
									pair<int, int> interm2;
									interm2.first=j;
									interm2.second=route[i-1].second;
									if(route[i].second==ysize-1&&interm2.first>=nets[net_ind+1].bottomT&&gcells[nets[net_ind+1].bottomT-1][ysize-2].last_net==net_ind){
										interm2.first=nets[net_ind+1].bottomT-1;
									}
	
									points.push_back(interm2);
				
									interm.first=interm2.first;
									interm.second=route[i].second;
								}
							}
							//not the last net
							else{
								if(gcells[route[i-1].first][route[i].second].last_net==net_ind&&(net_ind==nets.size()-2||route[i].second!=ysize-1||route[i].second==ysize-1&&route[i-1].first<nets[net_ind].bottomT)){
									interm.first=route[i-1].first;
									interm.second=route[i].second;
								}
								else{
									int j=route[i-1].first;
									if (j>=right_boundary[route[i].second])
										j=right_boundary[route[i].second]-1;
									while(gcells[j][route[i].second].last_net!=net_ind)
										j++;

									pair<int, int> interm2;
									interm2.first=j;
									interm2.second=route[i-1].second;
									points.push_back(interm2);
				
									interm.first=interm2.first;
									interm.second=route[i].second;
								}
							}
							//calculate the nets length
							nets[net_ind].length=nets[net_ind].length+abs(route[i].first-route[i-1].first)+1;
						}
						//indicate that there has been a trap
						else{
							nets[net_ind].trap_cell.push_back(make_pair(route[i].first, route[i].second));
							return -1;
						}		
						
					}
				}
				//this is the first net
				else{
					
					//the regular decision of how snaking is done
					if(right_boundary[route[i-1].second]>route[i].first&&left_boundary[route[i-1].second]<=route[i].first&&gcells[route[i].first][route[i-1].second].last_net==net_ind&&(points.size()<2||points[points.size()-2].second!=points[points.size()-1].second||(points[points.size()-2].second==points[points.size()-1].second)&&(points[points.size()-2].first<points[points.size()-1].first&&route[i].first>points[points.size()-1].first||points[points.size()-2].first>points[points.size()-1].first&&route[i].first<points[points.size()-1].first))&&(net_ind==nets.size()-2||route[i].second!=2||(route[i].second==2&&route[i].first<nets[net_ind+1].topT))){
						interm.first=route[i].first;
						interm.second=route[i-1].second;

						//calculate the nets length
						nets[net_ind].length=nets[net_ind].length+abs(route[i].first-route[i-1].first)+1;

					}
					//vertex is at the left side.
					else if(route[i-1].first<route[i].first&&(points.size()<2||points[points.size()-2].second!=route[i].second)){
						if(route[i].second==ysize-2&&net_ind!=nets.size()-2&&route[i].first>=nets[net_ind+1].bottomT){
							nets[net_ind].trap_cell.push_back(make_pair(route[i].first,route[i].second));
							return -1;
						}
						
						else if(route[i].second==ysize-1||gcells[route[i].first][route[i].second+1].last_net==net_ind){
							if(left_boundary[route[i].second]<=route[i-1].first){
								interm.first=route[i-1].first;
								interm.second=route[i].second;
							}
							//need one more interm to connect the two dots
							else{
								pair<int, int> interm2;
								interm2.first=left_boundary[route[i].second];
								interm2.second=route[i-1].second;
								points.push_back(interm2);
					
								interm.first=left_boundary[route[i].second];
								interm.second=route[i].second;
							}
							//calculate the nets length
							nets[net_ind].length=nets[net_ind].length+abs(route[i].first-route[i-1].first)+1;
						}
						else{
							nets[net_ind].trap_cell.push_back(make_pair(route[i].first, route[i].second));

							return -1;
						}
					}
					//vertex is at the right side
					else if(route[i-1].first>route[i].first&&(points.size()<2||points[points.size()-2].second!=route[i].second)){
						if(route[i].second==ysize-1||gcells[route[i].first][route[i].second+1].last_net==net_ind){
							if(net_ind!=nets.size()-2){
								if(gcells[route[i-1].first][route[i].second].last_net==net_ind&&(net_ind==nets.size()-2||route[i].second!=ysize-1||route[i].second==ysize-1&&route[i-1].first<nets[net_ind].bottomT)){
									interm.first=route[i-1].first;
									interm.second=route[i].second;
								}
								//two intermediate points
								else{
									
									int j=route[i-1].first;
									if(net_ind!=0&&j<=max(nets[net_ind-1].coord[route[i].second].first, nets[net_ind-1].coord[route[i].second].second))
										j=max(nets[net_ind-1].coord[route[i].second].first, nets[net_ind-1].coord[route[i].second].second)+1;
									while(gcells[j][route[i].second].last_net!=net_ind){
										j--;
									}
	
									pair<int, int> interm2;
									interm2.first=j;
									interm2.second=route[i-1].second;
									if(route[i].second==ysize-1&&interm2.first>=nets[net_ind+1].bottomT&&gcells[nets[net_ind+1].bottomT-1][ysize-2].last_net==net_ind){
										interm2.first=nets[net_ind+1].bottomT-1;
									}

									points.push_back(interm2);
					
									interm.first=interm2.first;
									interm.second=route[i].second;
								}
							}
							//last net
							else{
								if(gcells[route[i-1].first][route[i].second].last_net==net_ind){
									interm.first=route[i-1].first;
									interm.second=route[i].second;
								}
								//two intermediate points
								else{
									int j=route[i-1].first;
									if(j>=right_boundary[route[i].second])
										j=right_boundary[route[i].second]-1;
									while(gcells[j][route[i].second].last_net!=net_ind){
										j++;
									}

									pair<int, int> interm2;
									interm2.first=j;
									interm2.second=route[i-1].second;
									points.push_back(interm2);
					
									interm.first=interm2.first;
									interm.second=route[i].second;
								}
							}
							//calculate the nets length
							nets[net_ind].length=nets[net_ind].length+abs(route[i].first-route[i-1].first)+1;
						}
						else{
							nets[net_ind].trap_cell.push_back(make_pair(route[i].first, route[i].second));
							return -1;

						}
					}
				}
      		points.push_back(interm) ;
    	}
		//it is adjacent so calculate the length
		else{
			nets[net_ind].length++;	
		}
    	points.push_back(route[i]) ;
  	}
		

	nets[net_ind].turn_pt=points;

}

