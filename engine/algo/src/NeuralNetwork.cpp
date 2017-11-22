#include "NeuralNetwork.h"
#include <cassert>
#include <algorithm>

Relu::Relu() {
	nodesSum = 0;
}

float Relu::funcResult(float value, funcCalcMode mode) {
	float output = 0;
	switch (mode) {
	case funcValue:
		output = value;
		break;
	case derivValue:
		break;
	}
	return output;
}

float SoftMax::funcResult(float value, funcCalcMode mode) {
	float output = 0;
	switch (mode) {
	case funcValue:
		output = value;
		break;
	case derivValue:
		break;
	}
	return output;
}

SoftMax::SoftMax() {
	nodesSum = 0;
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

void Neuron::setValue(float _value) {
	value = _value;
}

float Neuron::getValue() {
	return value;
}

shared_ptr<ActivationFunc> Neuron::getFunc() {
	return func;
}

Layer::Layer(int _nodesCount, layerType _type) {
	type = _type;
	nodesCount = _nodesCount;
}

//for hidden and output layers
void Layer::initNeurons(shared_ptr<ActivationFunc> _func) {
	//+ bias
	for (int i = 0; i < nodesCount + 1; i++) {
		nodes.push_back(make_shared<Neuron>(_func));
	}

}

//apply func for all neurons
void Layer::applyFunc() {
	for (auto current = nodes.begin(); current != nodes.end(); ++current) {
		auto currentFunc = (*current)->getFunc();
		(*current)->setValue(currentFunc->funcResult((*current)->getValue(), funcValue));
	}
}

void Layer::propagateValues() {
	//iterate using nodes where is bias placed
	for (auto current = nodes.begin(); current != nodes.end(); ++current) {
		for (auto succeeding = (*current)->out.begin(); succeeding != (*current)->out.end(); ++succeeding) {
			shared_ptr<Neuron> succeedingNeuron = (*succeeding).first;
			float weightBetween = (*succeeding).second;
			succeedingNeuron->setValue(succeedingNeuron->getValue() + (*current)->getValue() * weightBetween);
		}
	}
}

layerType Layer::getType() {
	return type;
}

void Layer::setNeuronValues(vector<float>& _values) {
	assert(_values.size() != nodesCount);
	for (int nodeIndex = 0; nodeIndex < nodesCount; ++nodeIndex) {
		nodes[nodeIndex]->setValue(_values[nodeIndex]);
	}
	nodes[nodesCount + 1]->setValue(bias);
}

Layer::~Layer() {
	nodes.clear();
}

//init weights with random
void initWeights(shared_ptr<Layer> _layer1, shared_ptr<Layer> _layer2) {
	for (auto node1 = _layer1->nodes.begin(); node1 != _layer1->nodes.end(); ++node1) {
		for (auto node2 = _layer2->nodes.begin(); node2 != _layer2->nodes.end(); ++node2) {
			(*node1)->out.push_back(pair<shared_ptr<Neuron>, float>(*node2, static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
			(*node2)->in.push_back(pair<shared_ptr<Neuron>, float>(*node1, static_cast<float>(rand()) / static_cast<float>(RAND_MAX)));
		}
	}
}

LayerBinder::LayerBinder(vector<shared_ptr<Layer> >& _layers) {
	layers = _layers;
	//init to and out neurons for every neuron
	for (auto layer = _layers.begin(); layer != _layers.end(); ++layer) {
		initWeights(*(layer -1), *layer);
	}
}

void LayerBinder::ForwardPhase(vector<float>& x, vector<float>& y) {
	assert(layers.size() > 0);
	layers[0]->setNeuronValues(x);
	layers[0]->propagateValues();
	for (size_t i = 1; i < layers.size() - 1; i++) {
		layers[i]->applyFunc();
		layers[i]->propagateValues();
	}
	layers[layers.size() - 1]->applyFunc();
}

void LayerBinder::BackwardPhase() {

}