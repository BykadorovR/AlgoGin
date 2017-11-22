#pragma once
#include <vector>
#include <memory>
#include <map>

using std::vector;
using std::shared_ptr;
using std::pair;
using std::map;
using std::make_shared;



enum layerType {
	inputLayer,
	hiddenLayer,
	outputLayer
};

enum funcCalcMode {
	funcValue,
	derivValue
};

class ActivationFunc {
public:
	//Calc func, func derivation results
	virtual float funcResult(float value, funcCalcMode mode) = 0;
protected:
	float nodesSum;
};

class SoftMax : public ActivationFunc {
public:
	SoftMax();
	float funcResult(float value, funcCalcMode mode);
};

class Relu : public ActivationFunc {
public:
	Relu();
	float funcResult(float value, funcCalcMode mode);
};

class Neuron {
public:
	Neuron(shared_ptr<ActivationFunc> _func);
	~Neuron();
	void setValue(float _value);
	float getValue();
	void setFunc(shared_ptr<ActivationFunc> _func);
	shared_ptr<ActivationFunc> getFunc();
	//to simplify access
	vector<pair<shared_ptr<Neuron>, float> > in;
	vector<pair<shared_ptr<Neuron>, float> > out;
private:
	float value;
	shared_ptr<ActivationFunc> func;
};

class Layer {
public:
	//func by default
	Layer(int _nodesCount, layerType _type);
	//Init nodes
	void initNeurons(shared_ptr<ActivationFunc> _func);
	void setNeuronValues(vector<float>& _values);
	void applyFunc();
	layerType getType();
	//spread values from this layer to next layers
	//accumulate values for every neuron from previous stage
	void propagateValues();
	~Layer();
	//to simplify access
	vector<shared_ptr<Neuron> > nodes;
	float bias;
private:
	layerType type;
	int nodesCount;
};

class LayerBinder {
public:
	//init binds and weights between layers
	LayerBinder(vector<shared_ptr<Layer>>& _layers);
	//calculate new values of nodes using functions
	void ForwardPhase(vector<float>& x, vector<float>& y);
	void BackwardPhase();
private:
	vector<shared_ptr<Layer> > layers;
};
