#include "routines.hpp"


int weight(int* vect, int length)
{
	int weight=0;
	for (int i = 0; i < length; ++i)
		if (vect[i]!=0)
			++weight;
	return weight;
}

void printVect(int* vect, int length)
{
	if ((length<=0)||(vect==NULL))
		return;
	cout << "[";
	for (int i = 0; i < length-1; ++i)
		cout << vect[i] << " ";
	cout << vect[length-1] << "]\n";
}

void readSigFromFile(char* name, int p, int* c, int* z0, int* z1)
{
	FILE* f;
	if ((f=fopen(name, "r"))==NULL)
	{
		fprintf(stderr, "Error opening file %s in read mode...\n", name);
		exit(-1);
	}
	int ret;
	ret = fscanf(f, "[%d ", &c[0]);
	if (ret != 1)
		cout << "c[0] --> " << ret << "\n";
	for (int i = 1; i < p-1; ++i)
	{
		ret = fscanf(f, "%d ", &c[i]);
		if (ret != 1)
			cout << "c["<<i<<"] --> " << ret << "\n";
	}
	ret = fscanf(f, "%d]\n", &c[p-1]);
	if (ret != 1)
		cout << "c["<<p-1<<"] --> " << ret << "\n";

	ret = fscanf(f, "[%d ", &z0[0]);
	if (ret != 1)
		cout << "z0[0] --> " << ret << "\n";
	for (int i = 1; i < p-1; ++i)
	{
		ret = fscanf(f, "%d ", &z0[i]);
		if (ret != 1)
			cout << "z0["<<i<<"] --> " << ret << "\n";
	}
	ret = fscanf(f, "%d]\n", &z0[p-1]);
	if (ret != 1)
		cout << "z0["<<p-1<<"] --> " << ret << "\n";

	ret = fscanf(f, "[%d ", &z1[0]);
	if (ret != 1)
		cout << "z1[0] --> " << ret << "\n";
	for (int i = 1; i < p-1; ++i)
	{
		ret = fscanf(f, "%d ", &z1[i]);
		if (ret != 1)
			cout << "z1["<<i<<"] --> " << ret << "\n";
	}
	ret = fscanf(f, "%d]\n", &z1[p-1]);
	if (ret != 1)
		cout << "z1["<<p-1<<"] --> " << ret << "\n";

	fclose(f);
}

int xBF(int* c, int* zi, int w1, int w2, int delta, int relax, int p, int* xi, int* yi, int threshold, int max_tour, int index)
{
	printf("w1=%d, w2=%d, delta=%d, relax=%d, p=%d, threshold=%d, max_tour=%d\n", w1, w2, delta, relax, p, threshold, max_tour);
	int* syndrome;

	if ((syndrome = (int*)malloc(p*sizeof(int))) == NULL)
	{
		cerr << "Error allocating memory to syndrome\n";
		exit(-1);
	}

	int tour = 0;
	int i, j, count;

	for (i = 0; i < p; ++i)
	{
		syndrome[i] = zi[i];
	}

	auto start = chrono::steady_clock::now();
	while((tour<max_tour) && ((weight(syndrome, p)>(w2+relax))))
	{
		for (i = 0; i < p; ++i)
		{
			count=0;
			for (j = 0; j < p; ++j)
				if (c[j]==1)
					if (syndrome[(i+j)%p]==1)
						count++;
			if (count>=threshold)
			{
				xi[i]=1;
				for (j = 0; j < p; ++j)
					if (c[j]==1)
						syndrome[(i+j)%p]=(syndrome[(i+j)%p]+xi[i]*c[j])%2;
			}
		}
		tour++;
	}

	for (i = 0; i < p; ++i)
		for (j = 0; j < p; ++j)
			yi[(i+j)%p]=(yi[(i+j)%p] + zi[(i+j)%p] + xi[i]*c[j])%2;

	auto end = chrono::steady_clock::now();
	auto diff = end - start;
	
	cout << "BitFlipping ends in: " << chrono::duration <double, milli> (diff).count() << " ms\n";

	cout << "wt(x" << index << ") = " << weight(xi, p) << endl;
	cout << "x" << index << " = [";
	for (i = 0; i < p-1; ++i)
		cout << xi[i] << " ";
	cout << xi[p-1] << "]\n";

	free(syndrome);

	return 0;
}

