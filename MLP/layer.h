#ifndef LAYER_H
#define LAYER_H
#include <bits/stdc++.h>
#include "perceptron.h"
using namespace std;

class NeuralNet;
class Layer{
	friend class NeuralNet;
	private :
		vector <Perceptron> l;
		int layer_size, previous_size;
		
	public :
		Layer(int,int);
		vector <float> getLayerOutput();
		int getLayerSize();
		~Layer();
};

#endif
