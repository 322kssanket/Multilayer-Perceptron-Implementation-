#include "perceptron.h"
#include "layer.h"
#include "mlp.h"

using namespace std;

Layer::Layer(int no_of_neurons, int x)
{	
	int i;
	layer_size = no_of_neurons;
	previous_size = x;
	for(i=0;i<layer_size;i++)
	{
		Perceptron temp(1,previous_size);
		l.push_back(temp);
	}

}

vector <float> Layer::getLayerOutput()
{
	vector <float> y;
	int i;
	for(i=0;i<layer_size;i++){
		y.push_back(l[i].getPerceptronOutput());
	}
	return y;
}

int Layer::getLayerSize(){
	return layer_size;
}

Layer::~Layer()
{
	vector <Perceptron>().swap(l);

}



