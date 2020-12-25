#pragma once 
#include <functional>

using namespace std::placeholders;


float linear(float x)
{
	return 3* x + 1;
}

class Graph
{
public:
	std::vector<std::function<float(float)>> functions;
	int r, g, b;

	Graph(std::string function)
	{
		r = rand() % 256;
		g = rand() % 256;
		b = rand() % 256;

		std::function<float(float)> f;
		// Interprete string
		if (function == "x")
			f = std::bind(static_cast<float(*)(float)>(sin), _1);
		else if (function == "l")
			f = std::bind(static_cast<float(*)(float)>(floorf), _1);
		else
			f = std::bind(linear, _1);

		functions.push_back(f);
		// Assign functions
	}
	~Graph(){}

	float Calculate(float x, float t = 0)
	{
		float result = 0;
		for (auto f : functions) {
			result += f(x);
		}
		return result;
	}

private:
	static std::vector<std::function<int(double)>> Interpret(std::string raw)
	{
		std::vector<std::function<int(double)>> functions;

		return functions;
	}
};
