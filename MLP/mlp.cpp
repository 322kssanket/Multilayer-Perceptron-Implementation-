#include "perceptron.h"
#include "layer.h"
#include "mlp.h"
#define max_iterations 10000
using namespace std;

NeuralNet::NeuralNet(int t,int * x,vector <vector <float> > ip,vector <float> op, float lp){
	int i,j;
	totalLayers = t;
	learning_params = lp;
	
	for(i=1;i<t;i++)
	{
		Layer l(x[i],x[i-1]+1);
		net.push_back(l);
	}
	input = (float**)malloc(ip.size() * sizeof(float*));
	for(j=0;j<ip.size();j++)
	{
		input[j] = (float*)malloc(ip[0].size() * sizeof(float));
	}
	for(i=0;i<ip.size();i++)
	{
		for(j=0;j<ip[0].size();j++)
		{
			input[i][j] = ip[i][j];
		}
	}
	input_ex = ip.size();
	input_attrs = ip[0].size();
	output = (float*)malloc(op.size() * sizeof(float));
	output_size=op.size();
	for(i=0;i<op.size();i++)
	{
		output[i] = op[i];
	}
	
}

void NeuralNet::train()
{
	int i=0,j,k,epoch,input_index,train_Exmp=0,op_index,wt_index,wt_size,layer_index,err_index,layer_size,classified=0;
	float weighted_sum=0, local_grad, wt_grad_prod, old_op, new_op, y,prev_op,e,avg_err=0,avg_mse,max_op,max_op_index;
	
	ofstream outfile, errFile;
	vector <float> x;
	vector <float> example;
	vector <float> layer_op;
	errFile.open("errVsIters.txt");
	for(epoch=1;epoch<=max_iterations;epoch++)
	{
		//forward pass
		x.clear();
		example.clear();
		x.push_back(1.0);
		example.push_back(1.0);
		for(input_index=0;input_index<input_attrs;input_index++){
			x.push_back(input[train_Exmp][input_index]);
			example.push_back(input[train_Exmp][input_index]);
		}
		
		for(i=0;i<net.size();i++)
		{
			layer_size = net[i].getLayerSize();
			for(j=0;j<layer_size;j++)
			{
				net[i].l[j].activate(x,learning_params);
			}
			x.clear();
			x = net[i].getLayerOutput();
			if(i < net.size()-1)
				x.insert(x.begin(),1);
		}
		max_op=-1;
		for(int a = 0;a<x.size();a++)
		{
			if(max_op < x[a])
			{
				max_op = x[a];
				max_op_index = a+1;
			}	
		}
		if(max_op_index == output[train_Exmp])
		{
			classified++;
		}
		err.clear();
		
		
		for(err_index=0;err_index < x.size();err_index++){
			if(err_index == output[train_Exmp] - 1)
				err.push_back(1 - x[err_index]);
			else
				err.push_back(0 - x[err_index]);	 
		}
		
		
		e=0;
		for(int m=0;m<err.size();m++)
		{
			e += err[m] * err[m];	
		}
		
		e=e/err.size();
		e=e/2;
		avg_err += e;
		
		if(epoch%100==0){
			avg_mse = avg_err/epoch;
			errFile<<epoch<<" "<<avg_mse<<endl;
		}	
		
		op_index = (net.size())-1;
		local_grad = 0;
		for(k=0;k<net[op_index].getLayerSize();k++){
			wt_size = net[op_index].l[k].perceptron_weights_size;
			local_grad = err[k] * x[k] * (1 - x[k]);
			for(wt_index=0;wt_index < wt_size;wt_index++)
			{
				if(wt_index == 0)
					prev_op = 1;
				else
					prev_op = net[op_index - 1].l[wt_index].op;
				net[op_index].l[k].perceptron_weights[wt_index] += learning_params* local_grad * prev_op;
			}
		}

		
		//case 2: for weights of hidden layer
		
		for(layer_index = op_index-1; layer_index >=0; layer_index--){
			layer_op.clear();
			layer_op = net[layer_index].getLayerOutput();
			layer_op.insert(layer_op.begin(),1);
			layer_size = net[layer_index].getLayerSize();
			for(j=0;j < net[layer_index].getLayerSize();j++)
			{
				wt_size = net[layer_index].l[j].perceptron_weights_size;
				wt_grad_prod=0;
				old_op=new_op=0;
				for(k=0;k < net[layer_index + 1].getLayerSize(); k++){
						old_op = net[layer_index+1].l[k].op;
						net[layer_index+1].l[k].activate(layer_op,learning_params);
						new_op = net[layer_index+1].l[k].op;
						wt_grad_prod += (new_op -old_op) * old_op * (1- old_op) * (net[layer_index+1].l[k].perceptron_weights[j+1]);		
				}
					y=0;
					for(i=0;i < wt_size ;i++){
						y = net[layer_index].l[j].op;
						if(layer_index > 0)
						{
							if(i==0){
								net[layer_index].l[j].perceptron_weights[i] += learning_params * (y * (1-y)) * wt_grad_prod * 1;
							}
							else
							{
								net[layer_index].l[j].perceptron_weights[i] += learning_params * (y * (1-y)) * wt_grad_prod * net[layer_index-1].l[i-1].op;
							}
						}
						else
							net[layer_index].l[j].perceptron_weights[i] += learning_params * (y * (1-y)) * wt_grad_prod * example[i];
					}
				
			}
		}
		
		train_Exmp = (	train_Exmp + 1) % input_ex;
	}
	
	cout<<"Number of examples classified = "<<classified<<endl;
	cout<<"Training Accuracy = "<<((float)classified/10000)<<endl;
	errFile.close();
	//printing all the weights in a file
	outfile.open("mlpWeights.txt");
		for(int u = 0;u<net.size();u++)
		{
			outfile<<"Layer"<<"\n";
			for(int v=0;v<net[u].l.size();v++)
			{
				for(int w = 0;w<net[u].l[v].perceptron_weights_size;w++)
				{
					outfile<<net[u].l[v].perceptron_weights[w]<<" ";
				}
				outfile<<"\n";
			}
		}
		
		outfile.close();
	
	vector <float>().swap(x);
	vector <float>().swap(example);
	vector <float>().swap(layer_op);
}

NeuralNet::~NeuralNet()
{
	vector <Layer>().swap(net);
	vector <float>().swap(err);
	free(output);
	for(int i=0;i<input_ex;i++)
	{
		float *tmp = input[i];
		free(tmp);
	}
}








