////============================================================
////   diagonal.cpp  -- pcb routing project
////   Calculate the region for diagonal routing
////   Author: Yun-Wei Chang
////   Date:   Jan. 5, 2011
////============================================================

#include "parse.h"

using namespace std;

extern int dis;

extern int dir;

int mindiffx;

//get the next line
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

//print all the nets
void print(){
	for(int i=0;i<nets.size();i++){
		cout<<nets[i].top<<" "<<nets[i].bot<<" "<<nets[i].min<<" "<<nets[i].max<<" "<<nets[i].manhattan_d<<" "<<nets[i].final_d<<endl;
	}
	return;
}
//parse the inputfile 
void parse(const char* s){
	
	ifstream ifs(s,ifstream::in);
	string line=getNextLine(ifs);
	istringstream iss_first(line);
	//get the xsize and ysize
	iss_first>>xsize;
	iss_first>>ysize;

	line=getNextLine(ifs);

	while(ifs){
		istringstream iss(line);
		net n;
		iss>>n.top>>n.bot>>n.min>>n.max>>n.desire;
		if(n.desire==0)
			n.desire=n.max;
		//cout<<"top "<<n.top<<" bot "<<n.bot<<" n.min "<<n.min<<" max "<<n.max<<" desire "<<n.desire<<endl;
		nets.push_back(n);
		line=getNextLine(ifs);
	}

	//cout<<"x= "<<xsize<<" y= "<<ysize<<endl;

	ifs.close();	

 	return;
}

//calculate the maximum number of blocks for the diagonal region
int calculate(){
	int max=0;
	mindiffx=10000000;
	for(int i=0;i<nets.size();i++){
		nets[i].manhattan_d=abs(nets[i].top-nets[i].bot)+ysize;
		nets[i].diff=nets[i].manhattan_d-nets[i].desire;
		nets[i].minimum_d=ceil(abs(nets[i].top-nets[i].bot)*sqrt(2))+ysize-abs(nets[i].top-nets[i].bot);
		//calculate the max difference of minimum and manhattan difference
		if(nets[i].diff>max&&nets[i].minimum_d<nets[i].max) max= nets[i].diff;

		//calculate the max difference in x coordinates
		if(abs(nets[i].top-nets[i].bot)<mindiffx) mindiffx=abs(nets[i].top-nets[i].bot);
		//forward direction
		if(nets[i].top>nets[i].bot&&dir!=2)
			dir=1;
		//backward direction
		else if(nets[i].top<nets[i].bot&&dir!=1)
			dir=2;
	}
	return max;
}

//calculate the final net length for each length
int cal_final_d(int num){
	int min_dia=ceil(num/(2-sqrt(2)));

	//check if the number of block exceeded the boundary
	//4 for top and 4 for bottom
	if(ysize-min_dia<8){
		min_dia=ysize-8;
	}

	//cap the number of diagonal block to be mindiffx
	if(min_dia>mindiffx){
		min_dia=mindiffx;
	}
	//min_dia is the maximum number of block (for now)
	cout<<"min_dia= "<<min_dia<<endl;

	//enforce that the router will always satisfy minimum length bound	
	
	for(int i=0;i<nets.size();i++){
		nets[i].final_d=nets[i].manhattan_d-(2*min_dia)+(sqrt(2)*min_dia);
	}	

	return min_dia;
}


//create lObstacle, rObstacle, and the  input file
void create_new_file(int num, int region){
	FILE* newfile;
	newfile = fopen("../input_nets","w");
	
	if(dir!=0&&(region==ysize||region==0)){
		fprintf(newfile, "%d %d\n",xsize, ysize-num);
	}
	//diagonal region at the bottom
	if(region==ysize){
		for(int i=0;i<nets.size();i++){
			if(dir==2){
				if(nets[i].min-ceil(sqrt(2)*num)>=0)
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, nets[i].bot-num, (int) (nets[i].min-ceil(sqrt(2)*num)),(int) (nets[i].desire-ceil(sqrt(2)*num)), nets[i].desire);

				else
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, nets[i].bot-num, 0,(int) (nets[i].desire-ceil(sqrt(2)*num)),(int) (nets[i].desire));
			}
			else if(dir==1){
				if(nets[i].min-ceil(sqrt(2)*num)>=0)
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, nets[i].bot+num, (int) (nets[i].min-ceil(sqrt(2)*num)),(int) (nets[i].desire-ceil(sqrt(2)*num)), nets[i].desire);

				else
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, nets[i].bot+num, 0,(int) (nets[i].desire-ceil(sqrt(2)*num)),(int) (nets[i].desire));
			}
		
		}
	}
	
	//diagonal region at the top
	else if(region==0){
		for(int i=0;i<nets.size();i++){
			if(dir==2){
				if(nets[i].min-ceil(sqrt(2)*num)>=0)
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top+num, nets[i].bot, (int) (nets[i].min-ceil(sqrt(2)*num)),(int) (nets[i].desire-ceil(sqrt(2)*num)), nets[i].desire);

				else
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top+num, nets[i].bot, 0,(int) (nets[i].desire-ceil(sqrt(2)*num)),(int) (nets[i].desire));
			}
			else if(dir==1){
				if(nets[i].min-ceil(sqrt(2)*num)>=0)
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top-num, nets[i].bot, (int) (nets[i].min-ceil(sqrt(2)*num)),(int) (nets[i].desire-ceil(sqrt(2)*num)), nets[i].desire);

				else
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top-num, nets[i].bot, 0,(int) (nets[i].desire-ceil(sqrt(2)*num)),(int) (nets[i].desire));
			}
		
		}
	}
	//diagonal region in the middle
	else{
		int space=(right_pt-left_pt)/nets.size();
		fprintf(newfile, "%d %d\n",xsize, region);
		for(int i=0;i<nets.size();i++){
			int extra=(nets[i].desire-ceil(sqrt(2)*num)-nets[i].manhattan_d+2*num)/2;
			//back diagonal
			if(dir==2){
				
				int bottom;
				
				if(left_pt+i*space<nets[i].top)
					bottom=nets[i].top;
				else if(left_pt+i*space+num>nets[i].bot){
					
					if(nets[i].bot-num>=left_pt)
						bottom=nets[i].bot-num;
					else
						bottom=left_pt;
				}
				else
					bottom=left_pt+i*space;
				int max=abs(nets[i].top-bottom)+region+extra;
				int manhattan= abs(nets[i].top-bottom)+ysize-num-1;

				if(max==(int) (nets[i].min-ceil(sqrt(2)*num))/2){
					if((max-manhattan)%2)
						max++;
				}

				if(nets[i].min-ceil(sqrt(2)*num)>=0)
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, bottom, (int) (nets[i].min-ceil(sqrt(2)*num))/2, max, nets[i].desire);
					
				else
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, bottom, 0,max,(int) (nets[i].desire));
			}
			//forward diagonal
			else if(dir==1){
				
				int bottom;
				
				if(left_pt+i*space>nets[i].top)
					bottom=nets[i].top;
				else if(left_pt+i*space-num<nets[i].bot){
					if(nets[i].bot+num<right_pt)
						bottom=nets[i].bot+num;
					else
						bottom=right_pt;
				}
				else
					bottom=left_pt+i*space;

				int max=abs(nets[i].top-bottom)+region+extra;
				int manhattan= abs(nets[i].top-bottom)+ysize-num-1;
				if(max==(int) (nets[i].min-ceil(sqrt(2)*num))/2){
					if((max-manhattan)%2)
						max++;
				}

				if(nets[i].min-ceil(sqrt(2)*num)>=0)
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, bottom, (int) (nets[i].min-ceil(sqrt(2)*num))/2, max, nets[i].desire);

				else
					fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, bottom, 0, max,(int) (nets[i].desire));
			}
		
		}

	}
	fclose(newfile);
	return;
}

//create lObstacle, rObstacle, and the  input file
void create_post_file(){
	FILE* newfile;
	newfile = fopen("input_nets","w");
	
	if(dir!=0){
		fprintf(newfile, "%d %d\n",xsize, ysize);
	}

	for(int i=0;i<nets.size();i++){
		if(dir==2)
			fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, nets[i].bot, (int) (nets[i].min),(int) (nets[i].max), nets[i].desire);
		else if(dir==1){
			fprintf(newfile,"%d %d %d %d %d\n",nets[i].top, nets[i].bot, (int) (nets[i].min),(int) (nets[i].max), nets[i].desire);
		}
		
	}
	fclose(newfile);
	return;
}


//check to see if all the bounds are satisfied with the maximum constraint
bool check_bound(){
	for(int i=0;i<nets.size();i++){
		if(nets[i].final_d>nets[i].max)
		return false;	
	}
	
	return true;
}
//create the left and right boundary file base on the guideline.
int create_boundary(const char* file){
	
	ifstream ifs(file,ifstream::in);
	if(ifs.fail())
		return -1;
	string line;
	int bond;
	
	line=getNextLine(ifs);
	istringstream distance(line);	
	
	distance>>dis;
	//cout<<"distance: "<<dis<<endl;
	while(ifs){
		line=getNextLine(ifs);
		//cout<<line<<endl;
		istringstream iss(line);
		iss>>bond;
		if(line.compare("")!=0){
			mid_boundary.push_back(bond);
		}
	}

	ifs.close();

	FILE* outfile;
	FILE* outfile2;

	outfile = fopen("../rObstacle", "w");
	outfile2 = fopen("../lObstacle", "w");

	for(int i=0; i<mid_boundary.size();i++){
		if(mid_boundary[i]+dis<=xsize)
			fprintf(outfile, "%d\n",mid_boundary[i]+dis);
		else
			fprintf(outfile, "%d\n", xsize);
		if(mid_boundary[i]-dis<0)
			fprintf(outfile2, "%d\n", 0);			
		else
			fprintf(outfile2, "%d\n",mid_boundary[i]-dis);
	}

	fclose(outfile);
	fclose(outfile2);
	
 	return 0;
}

//create boundary that has the top reserved for diagonal region
int create_boundary_chunks(const char* left_file,  const char* right_file){
	
	ifstream ifs(left_file,ifstream::in);
	if(ifs.fail())
		return -1;
	string line;
	
	FILE* outfile;
	outfile = fopen("../lObstacle", "w");
	int x_coord;
	int y_coord;
	int size;
	int count=0;
	int temp;	
	while(ifs){
		line=getNextLine(ifs);
		if(line.compare("")==0){
			continue;
		}
		//cout<<line<<endl;
		istringstream iss(line);
		iss>>y_coord>>x_coord>>size;
		//cout<<"x= "<<x_coord<<" y= "<<y_coord<<" size= "<<size<<endl;
		
		for(int i=count;i<y_coord;i++){
			fprintf(outfile,"%d\n",0);
			count++;
		}
		for(int i=y_coord;i<size+y_coord;i++){
			fprintf(outfile,"%d\n",x_coord);
			count++;
		}
	}
	if(count!=ysize){
		for(int i=count;i<ysize;i++)
			fprintf(outfile, "%d\n", 0);
	}

	fclose(outfile);
	ifs.close();


	//right boundary
	ifstream ifs2(right_file,ifstream::in);
	if(ifs2.fail())
		return -1;
	string line2;

	FILE* outfile2;
	outfile2 = fopen("../rObstacle", "w");
	count=0;
	while(ifs2){
		line2=getNextLine(ifs2);
		if(line2.compare("")==0){
			continue;
		}
		//cout<<line2<<endl;
		istringstream iss(line2);
		iss>>y_coord>>x_coord>>size;
		//cout<<"x= "<<x_coord<<" y= "<<y_coord<<" size= "<<size<<endl;
		for(int i=count;i<y_coord;i++){
			fprintf(outfile2,"%d\n",xsize-1);

			count++;
		}
		for(int i=y_coord;i<y_coord+size;i++){
			fprintf(outfile2,"%d\n",x_coord);
			count++;
		}
	}
	if(count!=ysize){
		for(int i=count;i<ysize;i++)
			fprintf(outfile2, "%d\n", xsize-1);
	}

	fclose(outfile2);
	ifs2.close();
 	return 0;
}
//create the 2nd file for the second region for the route program.
bool create_2nd_file(int num, int region){
	int space=(right_pt-left_pt)/nets.size();
	FILE* newfile;
	newfile = fopen("input_nets","w");
	int extra;
	
	if(dir!=0){
		fprintf(newfile, "%d %d\n",xsize, ysize-region-num);
	}
	
	for(int i=0;i<nets.size();i++){
		//calculate the extra wire length to add to the maximum length bound.
		if((nets[i].desire-(int)(ceil(sqrt(2)*num))-nets[i].manhattan_d+2*num)%2!=0)
			extra=(nets[i].desire-ceil(sqrt(2)*num)-nets[i].manhattan_d+2*num)/2+1;
		else
			extra=(nets[i].desire-ceil(sqrt(2)*num)-nets[i].manhattan_d+2*num)/2;

		//back diagonal
		if(dir==2){
			int top;
				
			if(left_pt+i*space<nets[i].top)
				top=nets[i].top;
			else if(left_pt+i*space+num>nets[i].bot)
				if(nets[i].bot-num>=left_pt)
					top=nets[i].bot-num;
				else
					top=left_pt;
			else
				top=left_pt+i*space;

			int max=abs(nets[i].bot-(top+num))+ysize-region-num+extra;
			int manhattan= abs(top+num-nets[i].bot)+ysize-region-num-1;
			if(max== (int) (nets[i].min-ceil(sqrt(2)*num))/2){
				if((max-manhattan)%2)
					max++;
			}			

			if(nets[i].min-ceil(sqrt(2)*num)>=0)
				fprintf(newfile,"%d %d %d %d %d\n", top+num, nets[i].bot, (int) (nets[i].min-ceil(sqrt(2)*num))/2, max, nets[i].desire);

			else
				fprintf(newfile,"%d %d %d %d %d\n", top+num, nets[i].bot, 0, max,(int) (nets[i].desire));
		}
		//forward diagonal
		else if(dir==1){
			int top;
				
			if(left_pt+i*space>nets[i].top)
				top=nets[i].top;
			else if(left_pt+i*space-num<nets[i].bot)
				if(nets[i].bot+num<right_pt)
					top=nets[i].bot+num;
				else
					top=right_pt;

			else
				top=left_pt+i*space;

			int max=abs(nets[i].bot-(top-num))+ysize-region-num+extra;
			int manhattan= abs(top-num-nets[i].bot)+ysize-region-num-1;
			if(max== (int) (nets[i].min-ceil(sqrt(2)*num))/2){
				if((max-manhattan)%2)
					max++;
			}

			if(nets[i].min-ceil(sqrt(2)*num)>=0)
				fprintf(newfile,"%d %d %d %d %d\n", top-num, nets[i].bot, (int) (nets[i].min-ceil(sqrt(2)*num))/2, max, nets[i].desire);
			else
				fprintf(newfile,"%d %d %d %d %d\n", top-num, nets[i].bot, 0, max, (nets[i].desire));
		}
		
	}
	fclose(newfile);
	return true;
}

//create bottom boundary that has the middle region
int create_bot_boundary(int numBlock, int region){
	
	FILE* outfile;
	FILE* outfile2;

	outfile = fopen("rObstacle", "w");
	outfile2 = fopen("lObstacle", "w");

	for(int i=numBlock+region; i<right_boundary.size();i++){
		fprintf(outfile, "%d\n",right_boundary[i]);
		fprintf(outfile2, "%d\n", left_boundary[i]);			
	}

	fclose(outfile);
	fclose(outfile2);
	
 	return 0;
}
//create the boundary file for the bottom region
int create_boundaryBot(int topsize){
	
	FILE* outfile;
	FILE* outfile2;

	outfile = fopen("../rObstacle", "w");
	outfile2 = fopen("../lObstacle", "w");

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
}
