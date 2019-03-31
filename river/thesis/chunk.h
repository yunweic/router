#ifndef _CHUNK_H
#define _CHUNK_H

#include "parse.h"

vector <pair<int,int> > chunks;

bool checktop(int numBlock);
bool checkbot(int numBlock);
bool checkmid(int numBlock, int start);
//void sortchunk(int left, int right);

#endif
