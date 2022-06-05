#include "perceptron.h"
#include "layer.h"
#include "mlp.h"
using namespace std;

Perceptron::Perceptron(int aF, int sz)
{
	int i;
	actFunction = aF;
	op=0;
	if(sz==0)
	{
		perceptron_weights_size = 1;
		perceptron_weights.push_back(0);
	}
	else
	{
		perceptron_weights_size = sz;

		for(i=0;i<sz;i++)
		{
			perceptron_weights.push_back((float) rand() / (RAND_MAX));
		}
	}
}

void Perceptron::activate(vector <float> x, float lp)
{
	int i, weighted_sum=0;
	
	for(i=0;i<perceptron_weights_size;i++)
	{
		weighted_sum = weighted_sum + (perceptron_weights[i] * x[i]);
	}
	
	switch(actFunction){
		case 1:
			op = 1/(1+(exp(-lp * weighted_sum)));
			break;
	}
}

float Perceptron::getPerceptronOutput(){
	return op;
}	
	
	
Perceptron::~Perceptron(){
	vector <float>().swap(perceptron_weights);
}	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

