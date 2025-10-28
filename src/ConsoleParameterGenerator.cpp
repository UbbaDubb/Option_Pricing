//ConsoleParameterGenerator.cpp

#include "ConsoleParameterGenerator.hpp"

// Default Constructor
ConsoleParameterGenerator::ConsoleParameterGenerator() : r(0.0), sig(0.0), K(0.0), T(0.0), S(0.0), q(0.0), useMesh(false), var(""), start(0.0), end(0.0), step(0.0) {};

// Copy Constructor
ConsoleParameterGenerator::ConsoleParameterGenerator(const ConsoleParameterGenerator& cpg) 
	: r(cpg.r), sig(cpg.sig), K(cpg.K), T(cpg.T), S(cpg.S), q(cpg.q), var(cpg.var), start(cpg.start), end(cpg.end), step(cpg.step) {};

// Destructor
ConsoleParameterGenerator::~ConsoleParameterGenerator() {};

// Assignment Operator
ConsoleParameterGenerator& ConsoleParameterGenerator::operator=(const ConsoleParameterGenerator& cpg)
{
	if (this == &cpg)
		return *this;

	r = cpg.r;
	sig = cpg.sig;
	K = cpg.K;
	T = cpg.T;
	S = cpg.S;
	q = cpg.q;
	var = cpg.var;
	start = cpg.start;
	end = cpg.end;
	step = cpg.step;

	return *this;
};


// Ask user for input
void ConsoleParameterGenerator::initialise()
{
	char meshChoice;
	std::cout << "Would you like to generate a mesh? (y/n): ";
	std::cin >> meshChoice;
	useMesh = (tolower(meshChoice) == 'y');

	std::cout << "Enter risk-free rate (r): ";
	std::cin >> r;
	std::cout << "Enter volatility (sig): ";
	std::cin >> sig;
	std::cout << "Enter strike price (K): ";
	std::cin >> K;
	std::cout << "Enter time to maturity (T): ";
	std::cin >> T;
	std::cout << "Enter current underlying price (S): ";
	std::cin >> S;
	std::cout << "Enter dividend yield (q): ";
	std::cin >> q;

	if (useMesh)
	{
		std::cout << "Which parameter to vary (r, sig, K, T, S, q): ";
		std::cin >> var;
		std::cout << "Enter mesh start: ";
		std::cin >> start;
		std::cout << "Enter mesh end: ";
		std::cin >> end;
		std::cout << "Enter mesh step: ";
		std::cin >> step;
	}
}

// Generate parameters based on user setup
std::vector<std::vector<double>> ConsoleParameterGenerator::generateParameters()
{
	if (useMesh)
	{
		MeshParameterGenerator meshGen(r, sig, K, T, S, q, var, start, end, step);
		return meshGen.generateParameters();
	}
	else
	{
		// Single row of parameters
		std::vector<std::vector<double>> params = { {r, sig, K, T, S, q} };
		return params;
	}
}