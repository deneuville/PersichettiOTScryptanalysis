#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include <chrono>

using namespace std;


int weight(int* vect, int length);

void readSigFromFile(char* name, int p, int* c, int* z0, int* z1);

int xBF(int* c, int* zi, int w1, int w2, int delta, int relax, int p, int* xi, int* yi, int threshold, int max_tour, int index);
