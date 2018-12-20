#include "routines.hpp"

using namespace std;

int main(int argc, char const *argv[])
{
	if (argc!=9)
	{
		cerr << "USAGE: ./breakOTS p w1 w2 delta relax sigFile threshold maxBFround\n";
		exit(-1);
	}
	int p = atoi(argv[1]);
	int w1 = atoi(argv[2]);
	int w2 = atoi(argv[3]);
	int delta = atoi(argv[4]);
	int relax = atoi(argv[5]);
	// argv[6] contains the string of the signature file 
	int threshold = atoi(argv[7]);
	int maxBFround = atoi(argv[8]);

	int *c;
	if ((c=(int*)calloc(p,sizeof(int)))==NULL)
	{
		cerr << "Error allocating memory for reading the signature\n";
		exit(-1);
	}
	int *z0, *z1;
	if ((z0=(int*)calloc(p,sizeof(int)))==NULL || ((z1=(int*)calloc(p,sizeof(int)))==NULL))
	{
		cerr << "Error allocating memory for z0 and z1\n";
		exit(-1);
	}
	int *x0, *x1;
	if ((x0=(int*)calloc(p,sizeof(int)))==NULL || ((x1=(int*)calloc(p,sizeof(int)))==NULL))
	{
		cerr << "Error allocating memory for x0 and x1\n";
		exit(-1);
	}
	int *y0, *y1;
	if ((y0=(int*)calloc(p,sizeof(int)))==NULL || ((y1=(int*)calloc(p,sizeof(int)))==NULL))
	{
		cerr << "Error allocating memory for y0 and y1\n";
		exit(-1);
	}

	readSigFromFile(argv[6], p, c, z0, z1);

	xBF(c, z0, w1/2, w2/2, delta, relax, p, x0, y0, threshold, maxBFround, 0);
	xBF(c, z1, w1-weight(x0, p), w2-weight(y0, p), delta, relax, p, x1, y1, threshold, maxBFround, 1);


	free(c);
	free(z0);
	free(z1);
	free(x0);
	free(x1);
	free(y0);
	free(y1);

	return 0;
}




