#include "chunk.h"

using namespace std;


bool checkbot(int numBlock){
	int left=nets[0].bot;
	int right=nets[nets.size()-1].bot;

	bool bot=true;
	//forward directoin
	if(dir==1){
		if(left+numBlock-1<left_boundary[ysize-1-numBlock]||right+numBlock-1>right_boundary[ysize-1-numBlock]){
			bot=false;
			return bot;
		}
			
		//check bottom
		for(int i=right_boundary.size()-1;i>right_boundary.size()-1-numBlock;i--){
			//cout<<"right: "<<right_boundary[i]<<" left: "<<left_boundary[i]<<endl;
			int i2=right_boundary.size()-i;

			if(left+i2<left_boundary[i]||right+i2>right_boundary[i]){
				bot=false;
				return bot;
			}
		}
		return bot;
	}
	//backward direction
	else if(dir==2){
		//check bottom
		if(left-(numBlock-1)<left_boundary[ysize-1-numBlock]||right-(numBlock-1)>right_boundary[ysize-1-numBlock]){
			bot=false;
			return bot;
		}

		for(int i=right_boundary.size()-1;i>right_boundary.size()-1-numBlock;i--){
			//cout<<"right: "<<right_boundary[i]<<" left: "<<left_boundary[i]<<endl;
			int i2=right_boundary.size()-i;

			if(left-i2<left_boundary[i]||right-i2>right_boundary[i]){
				bot=false;
				return bot;
			}
		}
		return bot;
	}
	return false;
}	
bool checktop(int numBlock){
	int left=nets[0].top;
	int right=nets[nets.size()-1].top;

	bool top=true;
	//forward directoin
	if(dir==1){
		//check top
		if(left-(numBlock-1)<left_boundary[numBlock]||left-(numBlock-1)<left_boundary[numBlock+1]||right-(numBlock-1)>right_boundary[numBlock]||right-(numBlock-1)>right_boundary[numBlock+1]){
			top=false;
			return top;	
		}

		
		for(int i=0;i<numBlock;i++){
			//cout<<"right: "<<right_boundary[i]<<" left: "<<left_boundary[i]<<endl;

			if(left-i<left_boundary[i]||right-i>right_boundary[i]){
				top=false;
				return top;
			}
		}
		
		return top;
	}
	//backward direction
	else if(dir==2){
		//check bottom
		if(left+numBlock-1<left_boundary[numBlock]||left+numBlock-1<left_boundary[numBlock+1]||right+numBlock-1>right_boundary[numBlock]||right+numBlock-1>right_boundary[numBlock+1]){
			top=false;
			return top;	
		}

		for(int i=0;i<numBlock;i++){
			//cout<<"right: "<<right_boundary[i]<<" left: "<<left_boundary[i]<<endl;
			
			if(left+i<left_boundary[i]||right+i>right_boundary[i]){
				top=false;
				return top;
			}
		}
		return top;
	}
	return false;
}

//check middle	
bool checkmid(int numBlock, int start){
	int left=left_boundary[start];
	int right=right_boundary[start]-1;

	bool mid;
	bool rightok=true;
	bool leftok=true;
	//forward directoin
	if(dir==1){
		//check top
		while(right-left>=nets.size()){
			mid=true;
			//check first diagonal wire's destination
			if(left-(numBlock)<left_boundary[start+numBlock]||left-(numBlock)<left_boundary[start+numBlock+1]){
				mid=false;	
				leftok=false;
			}
			//check last diagonal wire's destination
			if(right-(numBlock)>right_boundary[start+numBlock]||right-(numBlock)>right_boundary[start+numBlock+1]){
				mid=false;
				rightok=false;
			}
			//check both diagonal wire's entire
			if(mid==true){		
				for(int i=start;i<start+numBlock;i++){
					//cout<<"right: "<<right_boundary[i]<<" left: "<<left_boundary[i]<<endl;

					if(left-(i-start)<left_boundary[i]){	
						mid=false;
						leftok=false;
						break;
					}
					if(right-(i-start)>right_boundary[i]){
						mid=false;
						rightok=false;
						break;
					}
				}
			}
			if(mid==true){
				//make sure there are no unnecessarily detour on the input pins
				if(right>nets[nets.size()-1].top)
					right=nets[nets.size()-1].top;
			
				if(left-(numBlock)<nets[0].bot)
					left=nets[0].bot+numBlock;
				for(int i=0;i<start;i++){
					if(right>right_boundary[i])
						right=right_boundary[i];
				}
				for(int i=start+numBlock;i<ysize;i++){
					if(left<left_boundary[i])
						left=left_boundary[i];
				}


				break;
			}
			if(leftok!=true){
				left++;
				leftok=true;
			}
			if(rightok!=true){
				right--;
				rightok=true;
			}
		}
	}
	//backward direction
	else if(dir==2){
		//check bottom
		while(right-left>=nets.size()){
			mid=true;
			if(left+numBlock<left_boundary[start+numBlock]||left+numBlock<left_boundary[start+numBlock+1]){
				mid=false;
				leftok=false;
			}
			if(right+numBlock>right_boundary[start+numBlock]||right+numBlock>right_boundary[start+numBlock+1]){
				mid=false;
				rightok=false;
			}
			if(mid==true){
				for(int i=start;i<start+numBlock;i++){
					//cout<<"right: "<<right_boundary[i]<<" left: "<<left_boundary[i]<<endl;
			
					if(left+i-start<left_boundary[i]){
						mid=false;
						leftok=false;
						break;
					}
					if(right+i-start>right_boundary[i]){
						mid=false;
						rightok=false;
						break;
					}
				}
			}
			if(mid==true){
				if(left<nets[0].top)
					left=nets[0].top;
			
				if(right+(numBlock)>nets[nets.size()-1].bot)
					right=nets[nets.size()-1].bot+numBlock;

				for(int i=start+numBlock;i<ysize;i++){
					if(right>right_boundary[i])
						right=right_boundary[i];
				}
				for(int i=0;i<start;i++){
					if(left<left_boundary[i])
						left=left_boundary[i];
				}
				break;
			}
			if(leftok!=true){
				leftok=true;
				left++;
			}
			if(rightok!=true){
				rightok=true;
				right--;
			}
		}
	}
	left_pt=left;
	right_pt=right;	
	return mid;
}
