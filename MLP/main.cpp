#include "perceptron.h"
#include "layer.h"
#include "mlp.h"

using namespace std;
int main(){
	int no_layers,i,output_classes; 
	int * layer_sizes;
	float lp, output;
	vector <vector <float> > input_matrix;
	vector <float> op_vector, op_cp_vector;
	std::ifstream file("wireless_train.txt");
    	std::string line;
	cout<<"Enter the number of layers : "<<endl;
	cin>>no_layers;
	cout<<"Enter the layer_sizes : "<<endl;
	layer_sizes = (int*)malloc(no_layers * sizeof(int));
	for(i=0;i<no_layers;i++)
	{
		if(i==0)
			layer_sizes[0]=0;
		else if(i==no_layers-1)
			layer_sizes[no_layers - 1] = 0;
		else{
			cout<<" Number of neurons in hidden layer "<<i<<" :"<<endl;
			cin>>layer_sizes[i];	
		}
	}
	cout<<" Learning parameter : "<<endl;
	cin>>lp;
	

    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        vector<float> tmp;
        float ch;
        while (iss >> ch) {
            tmp.push_back(ch);
        }
        
        output = tmp[(tmp.size())-1];
        
        input_matrix.push_back(tmp);
        
        op_cp_vector.push_back(output);
    }
    
    	random_shuffle(input_matrix.begin(),input_matrix.end());
    	int op_indx = input_matrix[0].size() - 1;
    	for(int x=0;x<input_matrix.size();x++)
    	{
    		output = input_matrix[x][op_indx];
    		input_matrix[x].pop_back();
    		op_vector.push_back(output);
    	}
    
    
    
    layer_sizes[0]=input_matrix[0].size();
    std::sort(op_cp_vector.begin(),op_cp_vector.end());
    output_classes = std::unique(op_cp_vector.begin(),op_cp_vector.end()) - op_cp_vector.begin();
    layer_sizes[no_layers-1]=output_classes;
    	for(int m=0;m<input_matrix.size();m++)
    	{
    		output = input_matrix[m][input_matrix[0].size()];
    		op_vector.push_back(output);
    	}
    NeuralNet n1(no_layers,layer_sizes,input_matrix,op_vector,lp);
    n1.train();
    
    	vector < vector <float> >().swap(input_matrix);
    	vector <float>().swap(op_vector);
    	vector <float>().swap(op_cp_vector);
    	free(layer_sizes);
    
	return 0;
}

















