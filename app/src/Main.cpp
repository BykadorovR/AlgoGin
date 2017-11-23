#include "NeuralNetwork.h"
const int nodesCount = 5;
int main() {
	shared_ptr<Layer> input = make_shared<Layer>(inputLayer);
	shared_ptr<Layer> hidden = make_shared<Layer>(hiddenLayer);
	shared_ptr<Layer> output = make_shared<Layer>(outputLayer);

	shared_ptr<ActivationFunc> func_name_1 = make_shared<Relu>();
	shared_ptr<ActivationFunc> func_name_2 = make_shared<SoftMax>();
	
	input->initNeurons(nodesCount);
	hidden->initNeurons(nodesCount, func_name_2);
	output->initNeurons(nodesCount, func_name_1);

	vector<shared_ptr<Layer> > layers = { input, hidden, output };
	LayerBinder digitalRecognition(layers);
	digitalRecognition.printNetwork();

	vector<float> inputValues = { 1, 2, 3, 4, 5 };
	vector<float> responceValues = { 1, 2, 3, 4, 5 };
	digitalRecognition.ForwardPhase(inputValues, responceValues);
	digitalRecognition.BackwardPhase();
	//Create layer and say how many nodes in every layer
	//default function for all nodes and opportunity to change for 
	//every node. Call LayerBinder, it init all links between nodes
	//and after pass X and Y to LayerBinder
	return 0;
}