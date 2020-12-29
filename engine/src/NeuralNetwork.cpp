#include "NeuralNetwork.h"
#include <cassert>
#include <algorithm>
#include <math.h>

double Sigmoida::funcResult(vector<double> values, int current) {
	return (1/(1+exp(-2*values[current])));
}

double Sigmoida::derivResult(double values) {
	return 2*(values - values*values);
}

double SoftMax::funcResult(vector<double> values, int current) {
	vector<double> expValues = values;
	for (int i = 0; i < expValues.size(); i++) {
		expValues[i] = exp(expValues[i]);
	}
	double expSum = 0;
	for (auto& expValue : expValues)
		expSum += expValue;

	return expValues[current] / expSum;
}

double CrossEntropy::funcDerivResult(double current, double expected) {
	return current - expected;
}

double CrossEntropy::funcResult(vector<double> current, vector<double> expected) {
	double result = 0;
	for (int i = 0; i < current.size(); i++) {
		result += expected[i] * log(current[i]);
	}
	return -result;
}

Neuron::Neuron(shared_ptr<ActivationFunc> _func) {
	value = 0;
	func = _func;
}

Neuron::~Neuron() {
	value = 0;
	in.clear();
	out.clear();
}

void Neuron::setValue(double _value) {
	value = _value;
}

double Neuron::getValue() {
	return value;
}

shared_ptr<ActivationFunc> Neuron::getFunc() {
	return func;
}

double Neuron::getAdj() {
	return adjustment;
}

void Neuron::setAdj(double _adjustment) {
	adjustment = _adjustment;
}

Layer::Layer(layerType _type) {
	type = _type;
}

//for hidden and output layers
void Layer::initNeurons(int _nodesCount, shared_ptr<ActivationFunc> _func) {
	for (int i = 0; i <  _nodesCount; i++) {
		nodes.push_back(make_shared<Neuron>(_func));
	}

}

//apply func for all neurons
void Layer::applyFunc() {
	vector<double> values;
	//some functions need to do normalization
	for (auto& current : nodes) {
		values.push_back(current->getValue());
	}
	for (int i = 0; i < nodes.size(); i++) {
		auto activationFunc = nodes[i]->getFunc();
		if (activationFunc == nullptr)
			continue;
		nodes[i]->setValue(activationFunc->funcResult(values, i));
	}
}

void Layer::propagateValuesFrom(shared_ptr<Layer> previousLayer) {
	for (int i = 0; i < nodes.size(); i++) {
		for (auto previous = nodes[i]->in.begin(); previous != nodes[i]->in.end(); ++previous) {
			shared_ptr<Neuron> previousNeuron = (*previous).first;
			nodes[i]->setValue(nodes[i]->getValue() + previousNeuron->getValue() * (*previous).second->weight);
		}
		nodes[i]->setValue(nodes[i]->getValue() + previousLayer->bias[i]);
	}
}

layerType Layer::getType() {
	return type;
}

void Layer::setNeuronValues(vector<double> _values) {
	assert(_values.size() == nodes.size());
	for (int nodeIndex = 0; nodeIndex <  nodes.size(); ++nodeIndex) {
		nodes[nodeIndex]->setValue(_values[nodeIndex]);
		if (type == inputLayer)
			nodes[nodeIndex]->setValue(_values[nodeIndex]);
	}
}

Layer::~Layer() {
	nodes.clear();
}

vector<double> Layer::getBias() {
	return bias;
}

void Layer::setBias(vector<double> _bias) {
	bias = _bias;
}

//init weights with random
void initWeights(shared_ptr<Layer> _layer1, shared_ptr<Layer> _layer2) {
	RandomWeights<double>& generator = RandomWeights<double>::getInstance();
	for (auto node1 = _layer1->nodes.begin(); node1 != _layer1->nodes.end(); ++node1) {
		for (auto node2 = _layer2->nodes.begin(); node2 != _layer2->nodes.end(); ++node2) {
			shared_ptr<Weight> randomWeight = make_shared<Weight>(generator.get());
			(*node1)->out.push_back(pair<shared_ptr<Neuron>, shared_ptr<Weight> >(*node2, randomWeight));
			(*node2)->in.push_back(pair<shared_ptr<Neuron>, shared_ptr<Weight> >(*node1, randomWeight));
		}
	}
	//bias has to be initialized for all layers instead of output
	for (int i = 0; i < _layer2->nodes.size(); i++) {
		_layer1->bias.push_back(generator.get());
	}
}

LayerBinder::LayerBinder(vector<shared_ptr<Layer> > _layers, shared_ptr<ErrorFunction> _errorFunc) {
	layers = _layers;
	errorFunc = _errorFunc;
	//init to and out neurons for every neuron
	for (auto layer = _layers.begin() + 1; layer != _layers.end(); ++layer) {
		initWeights(*(layer -1), *layer);
	}
}

void LayerBinder::printNetwork() {
	//get maximum count of nodes between all layers
	int maxNodes = 0;
	for (auto current = layers.begin(); current != layers.end(); ++current) {
		maxNodes = (*current)->nodes.size() > maxNodes ? (*current)->nodes.size() : maxNodes;
	}
	//iterate through all nodes layer by layer
	for (int i = 0; i < maxNodes; i++) {
		for (auto layer = layers.begin(); layer != layers.end(); ++layer) {
			if ((*layer)->getType() != inputLayer) {
				int j = (*layer)->nodes.size() > i ? i : (*layer)->nodes.size() - 1;
				//take all nodes from previous layer which enter to this node
				for (auto node = (*layer)->nodes[j]->in.begin(); node != (*layer)->nodes[j]->in.end(); ++node) {
					//print weghts bettween all nodes from previous layer and node from this layer
					if ((*layer)->nodes.size() > i)
						printf("%6.3f ", (*node).second->weight);
					else
						printf("%6.3s ", "-");
				}
			}
			if ((*layer)->nodes.size() > i) {
				printf("| %6.3f | ", (*layer)->nodes[i]->getValue());
			}
			else {
				printf("| %6.3s | ", "-");
			}
		}
		printf("\n");
	}

	printf("\n");
	printf("\n");
}

void LayerBinder::ForwardPhase(vector<double> x) {
	assert(layers.size() > 0);
#ifdef DEBUG
	printf("Start\n");
	printNetwork();
#endif
	layers[0]->setNeuronValues(x);
#ifdef DEBUG
	printf("Initial values are applied\n");
	printNetwork();
#endif
	for (int i = 1; i < layers.size(); i++) {
		layers[i]->propagateValuesFrom(layers[i-1]);
#ifdef DEBUG
		printf("Values for layer %d were propagated from layer %d\n", i, i-1);
		printNetwork();
#endif
		layers[i]->applyFunc();
#ifdef DEBUG
		printf("Activation func was appliad to layer %d\n", i);
		printNetwork();
#endif
	}
}

vector<double> LayerBinder::getAnswer() {
	answer.clear();
	auto nodes = layers[layers.size() - 1]->nodes;
	//lets fill nodeValue array
	for (int i = 0; i < nodes.size(); i++) {
		answer.push_back(nodes[i]->getValue());
	}
	return answer;
}

void LayerBinder::calculateOutputAdjustments(vector<double> y) {
	auto nodes = layers[layers.size() - 1]->nodes;
	//iterate through output nodes
	for (int j = 0; j < nodes.size(); j++) { // j = arg
		double adjustment = errorFunc->funcDerivResult(nodes[j]->getValue(), y[j]);
		nodes[j]->setAdj(adjustment);
	}
}

void LayerBinder::calculateHiddenAdjustments() {
	//lets calculate error for all hidden layers (not input, not output)
	for (int i = layers.size() - 2; i > 0; i--) { // i = layer
		auto currentNodes = layers[i]->nodes;
		for (int j = 0; j < currentNodes.size(); j++) { //j = current node in hidden layer
			double adjustment = 0;
			auto outNodesFromCurrent = currentNodes[j]->out;
			for (int k = 0; k < outNodesFromCurrent.size(); k++) { // k = all nodes in next layer related to this one
				adjustment += outNodesFromCurrent[k].first->getAdj() * outNodesFromCurrent[k].second->weight;
			}
			//add func derivative
			currentNodes[j]->setAdj(adjustment * currentNodes[j]->getFunc()->derivResult(currentNodes[j]->getValue()));
		}
	}
}

void LayerBinder::fixWeightsAndBiases(double speed) {
	//fix edges using calculated adjustments and biases!!!
	for (int i = layers.size() - 2; i >= 0; i--) { // i = layer
		auto currentNodes = layers[i]->nodes;
		for (int j = 0; j < currentNodes.size(); j++) { // j = current node in layer
			auto outNodesFromCurrent = currentNodes[j]->out;
			for (int k = 0; k < outNodesFromCurrent.size(); k++) { // k = node in next layer
				outNodesFromCurrent[k].second->weight -= speed * outNodesFromCurrent[k].first->getAdj()*currentNodes[j]->getValue();
			}
		}

		auto nextLayerNodes = layers[i + 1]->nodes;
		//bias
		for (int k = 0; k < nextLayerNodes.size(); k++) { // k nodes from next layer
			layers[i]->bias[k] -= (speed * nextLayerNodes[k]->getAdj() * 1);
		}
	}
}

double LayerBinder::BackwardPhase(vector<double> y, double speed) {
	calculateOutputAdjustments(y);
	calculateHiddenAdjustments();
	fixWeightsAndBiases(speed);

	
#ifdef DEBUG
	printNetwork();
#endif

	return errorFunc->funcResult(getAnswer(), y);
}
