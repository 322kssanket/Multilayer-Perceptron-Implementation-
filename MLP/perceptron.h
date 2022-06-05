#ifndef PERCEPTRON_H
#define PERCEPTRON_H
#include <bits/stdc++.h>
using namespace std;

class Layer;
class NeuralNet;
class Perceptron{
	friend class Layer;
	friend class NeuralNet;
	private :
		vector <float> perceptron_weights;
		int perceptron_weights_size;
		int actFunction;
		float op;
	public :
		Perceptron(int,int);
		void activate(vector <float>, float);
		float getPerceptronOutput();
		~Perceptron();
};

#endif

