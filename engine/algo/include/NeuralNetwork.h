#pragma once
#include <vector>
#include <memory>

using std::vector;
using std::shared_ptr;
using std::pair;
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
	ActivationFunc();
	//Calc func, func derivation results
	virtual float funcResult(funcCalcMode mode);
	virtual ~ActivationFunc();
private:
	float nodesSum;
};

class SoftMax : public ActivationFunc {
public:
	SoftMax();
	float funcResult(funcCalcMode mode);
	SoftMax();
};

class Neuron {
public:
	//if func isn't defined so let's Layer class bind the func for all uninitialiazed neurons
	Neuron(float _value = 0);
	Neuron(shared_ptr<ActivationFunc> _func, float _value = 0);
	~Neuron();
	float getValue();
	//function is available for every neuron separately
	void applyFunc();
	void setFunc(shared_ptr<ActivationFunc> _func);
	//to simplify access
	vector<pair<shared_ptr<Neuron>, float> > to;
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
	void InitNeurons(shared_ptr<ActivationFunc> _func);
	~Layer();
	float operator[](int index);
	//to simplify access
	vector<shared_ptr<Neuron> > nodes;
private:
	void initNeurons();
	layerType type;
	int nodesCount;
};

class LayerBinder {
public:
	//init binds and weights between layers
	LayerBinder(vector<Layer> _layers);
	~LayerBinder();
	//calculate new values of nodes using functions
	void ForwardPhase();
private:
	vector<Layer> layers;
};
