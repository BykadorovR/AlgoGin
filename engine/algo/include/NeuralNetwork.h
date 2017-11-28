#pragma once
#include <vector>
#include <memory>
#include <map>

using std::vector;
using std::shared_ptr;
using std::pair;
using std::map;
using std::make_shared;

//#define DEBUG

enum layerType {
	inputLayer,
	hiddenLayer,
	outputLayer
};

enum funcCalcMode {
	funcValue,
	derivValue
};

template<class T>
class RandomWeights {
public:
	static RandomWeights& getInstance() {
		static RandomWeights generator;
		return generator;
	}

	T get() {
		return (static_cast<T>(rand()) / (static_cast<T>(RAND_MAX))) / 100;
	}
	RandomWeights(RandomWeights const&) = delete;
	void operator=(RandomWeights const&) = delete;
private:
	RandomWeights() {
		srand(11);
	}
};

class ErrorFunction {
public:
	virtual double funcDerivResult(double current, double expected) = 0;
	virtual double funcResult(vector<double> current, vector<double> expected) = 0;
protected:
};

class CrossEntropy : public ErrorFunction {
public:
	double funcDerivResult(double current, double expected);
	double funcResult(vector<double> current, vector<double> expected);
};

class ActivationFunc {
public:
	//sum is needed for normalization
	virtual double funcResult(vector<double> values, int current) = 0;
	virtual double derivResult(double value) = 0;
};


class SoftMax : public ActivationFunc {
public:
	//sum is needed for normalization
	double funcResult(vector<double> values, int current);
	double derivResult(double value) {
		return -1;
	}
};

class Sigmoida : public ActivationFunc {
public:
	double funcResult(vector<double> values, int current);
	double derivResult(double value);
};

struct Weight {
	Weight(double _weight) : weight(_weight) {

	}
	double weight;
};

class Neuron {
public:
	Neuron(shared_ptr<ActivationFunc> _func);
	~Neuron();
	void setValue(double _value);
	double getValue();
	double getAdj();
	void setAdj(double _adjustment);
	void setFunc(shared_ptr<ActivationFunc> _func);
	shared_ptr<ActivationFunc> getFunc();
	//to simplify access
	vector<pair<shared_ptr<Neuron>, shared_ptr<Weight> > > in;
	vector<pair<shared_ptr<Neuron>, shared_ptr<Weight> > > out;
private:
	double value;
	double adjustment; // for back propagation
	shared_ptr<ActivationFunc> func;
};

class Layer {
public:
	//func by default
	Layer(layerType _type);
	//Init nodes
	void initNeurons(int _nodesCount, shared_ptr<ActivationFunc> _func = nullptr);
	void setNeuronValues(vector<double> _values);
	vector<double> getBias();
	void setBias(vector<double> _bias);
	void applyFunc();
	layerType getType();
	//spread values from this layer to next layers
	//accumulate values for every neuron from previous stage
	void propagateValuesFrom(shared_ptr<Layer> previousLayer);
	~Layer();
	//to simplify access
	vector<shared_ptr<Neuron> > nodes;
	vector<double> bias;
private:
	layerType type;
};

class LayerBinder {
public:
	//init binds and weights between layers
	LayerBinder(vector<shared_ptr<Layer>> _layers, shared_ptr<ErrorFunction> _errorFunc);
	void printNetwork();
	//calculate new values of nodes using functions
	void ForwardPhase(vector<double> x);
	double BackwardPhase(vector<double> y, double speed);
	vector<double> getAnswer();
private:
	void calculateHiddenAdjustments();
	void calculateOutputAdjustments(vector<double> y);
	void fixWeightsAndBiases(double speed);
	shared_ptr<ErrorFunction> errorFunc;
	vector<shared_ptr<Layer> > layers;
	vector<double> answer;
};
