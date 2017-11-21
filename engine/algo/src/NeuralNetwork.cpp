#include "NeuralNetwork.h"
#include <cassert>

Neuron::Neuron() {
	value = 0;
}

Neuron::~Neuron() {
	value = 0;
	to.clear();
	out.clear();
}

void Neuron::setValue(float _value) {
	value = _value;
}

float Neuron::getValue() {
	return value;
}

void Neuron::setFunc(shared_ptr<ActivationFunc> _func) {
	func = _func;
}

shared_ptr<ActivationFunc> Neuron::getFunc() {
	return func;
}

Layer::Layer(int _nodesCount, layerType _type) {
	nodesCount = _nodesCount;
	type = _type;
}

//for hidden and output layers
void Layer::initNeurons(shared_ptr<ActivationFunc> _func) {
	vector<shared_ptr<Neuron> >::iterator itNodes;
	for (itNodes = nodes.begin(); itNodes != nodes.end(); itNodes++) {
		(*itNodes) = make_shared<Neuron>(_func);
	}
}

//need to calculate values for every neuron from "to" vector
//and propagate this values to next layer
void Layer::propagateValues() {

}

void Layer::setNeuronValues(vector<float> _values) {
	assert(_values.size() != nodes.size());
	for (size_t nodeIndex = 0; nodeIndex < nodes.size(); ++nodeIndex) {
		nodes[nodeIndex]->setValue(_values[nodeIndex]);
	}
}

layerType Layer::getType() {
	return type;
}

Layer::~Layer() {
	nodes.clear();
}

//init weights with random
void initWeights(Layer& _layer1, Layer& _layer2) {
	for (auto node1 = _layer1.nodes.begin(); node1 != _layer1.nodes.end(); ++node1) {
		for (auto node2 = _layer2.nodes.begin(); node2 != _layer2.nodes.end(); ++node2) {
			(*node1)->out.push_back(pair<shared_ptr<Neuron>, float>(*node2, static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
			(*node2)->to.push_back(pair<shared_ptr<Neuron>, float>(*node1, static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
		}
	}
}

LayerBinder::LayerBinder(vector<Layer>& _layers) {
	layers = _layers;
	//init to and out neurons for every neuron
	for (auto layer = _layers.begin() + 1; layer != _layers.end(); ++layer) {
		initWeights(*(layer - 1), *layer);
	}
}

void LayerBinder::ForwardPhase(vector<float>& x, vector<float>& y) {
	assert(layers.size() > 0);
	layers[0].setNeuronValues(x);
}