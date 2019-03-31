////============================================================
////   parse.h  -- pcb project
////   Contains the functions for parsing the input file
////   Author: Yun-Wei Chang
////   Date:   Jan. 5, 2011
////============================================================
#ifndef _PARSE_H
#define _PARSE_H
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

extern int xsize, ysize;
extern int dir;
extern int right_pt, left_pt;
struct net{
	int top;
	int bot;
	int min;
	int max;
	int desire;

	int manhattan_d;
	int minimum_d;
	int diff;
	float final_d;
};

extern vector<net> nets;

extern vector<int> mid_boundary;
extern vector <int> left_boundary;
extern vector <int> right_boundary;



void print();
void parse(const char* s);
int calculate();
int cal_final_d(int num);
void create_new_file(int num, int region);
void create_post_file();
bool check_bound();
int create_boundary(const char* file);
int create_boundary_chunks(const char* file1, const char* file2);
int create_boundaryBot(int topsize);
bool create_2nd_file(int num, int region);
int create_bot_boundary(int numBlock, int region);
#endif
