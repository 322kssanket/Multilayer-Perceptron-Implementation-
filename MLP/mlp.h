#ifndef MLP_H
#define MLP_H
#include <bits/stdc++.h>
#include "perceptron.h"
#include "layer.h"
using namespace std;

class NeuralNet{
	private :
		vector <Layer> net;
		vector <float> err;
		float **input;
		float *output;
		int totalLayers,input_attrs,input_ex,output_size;
		float learning_params;

	public :
		NeuralNet(int,int*,vector < vector<float> >, vector <float>, float);
		void train();
		void test();
		~NeuralNet();	
};

#endif
