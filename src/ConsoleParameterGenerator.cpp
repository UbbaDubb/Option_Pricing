//ConsoleParameterGenerator.cpp

#include "ConsoleParameterGenerator.hpp"

// Default Constructor
ConsoleParameterGenerator::ConsoleParameterGenerator() : r(0.0), sig(0.0), K(0.0), T(0.0), S(0.0), q(0.0), var(""), start(0.0), end(0.0), step(0.0) {};

// Copy Constructor
ConsoleParameterGenerator::ConsoleParameterGenerator(const ConsoleParameterGenerator& mpg) 
	: r(mpg.r), sig(mpg.sig), K(mpg.K), T(mpg.T), S(mpg.S), q(mpg.q), var(mpg.var), start(mpg.start), end(mpg.end), step(mpg.step) {};

// Destructor
ConsoleParameterGenerator::~ConsoleParameterGenerator() {};

// Assignment Operator
ConsoleParameterGenerator& ConsoleParameterGenerator::operator=(const ConsoleParameterGenerator& mpg)
{
	if (this == &mpg)
		return *this;

	r = mpg.r;
	sig = mpg.sig;
	K = mpg.K;
	T = mpg.T;
	S = mpg.S;
	q = mpg.q;
	var = mpg.var;
	start = mpg.start;
	end = mpg.end;
	step = mpg.step;

	return *this;
};

// Getter/Setter functions
void ConsoleParameterGenerator::rf_rate(double r_in) { r = r_in; }
double ConsoleParameterGenerator::rf_rate() const { return r; }
void ConsoleParameterGenerator::sigma(double sig_in) { sig = sig_in; }
double ConsoleParameterGenerator::sigma() const { return sig; }
void ConsoleParameterGenerator::strike(double K_in) { K = K_in; }
double ConsoleParameterGenerator::strike() const { return K; }
void ConsoleParameterGenerator::time(double T_in) { T = T_in; }
double ConsoleParameterGenerator::time() const { return T; }
void ConsoleParameterGenerator::spot(double S_in) { S = S_in; }
double ConsoleParameterGenerator::spot() const { return S; }
void ConsoleParameterGenerator::dividends(double q_in) { q = q_in; } // double q = 0.0; Dividend yield...ConsoleParameterGenerator.b = indexConsoleParameterGenerator.r - q;
double ConsoleParameterGenerator::dividends() const { return q; }
void ConsoleParameterGenerator::variable(const std::string& var_in) { var = var_in; }
std::string ConsoleParameterGenerator::variable() const { return var; }
void ConsoleParameterGenerator::console_start(double start_in) { start = start_in; }
double ConsoleParameterGenerator::console_start() const { return start; }
void ConsoleParameterGenerator::console_end(double end_in) { end = end_in; }
double ConsoleParameterGenerator::console_end() const { return end; }
void ConsoleParameterGenerator::console_step(double step_in) { step = step_in; }
double ConsoleParameterGenerator::console_step() const { return step; }

// Parameter Generator for Console
std::vector<std::vector<double>> ConsoleParameterGenerator::generateParameters()
{
	std::vector<std::vector<double>> matrix; // Matrix to hold the parameters
	
	std::vector<double> Console;	// Vector to hold the Console values

	for (double i = start; i <= end; i += step)
	{
		Console.push_back(i);
	}
	
	// Check which column to vary
	int col = -1;
	if (var == "r") col = 0;
	else if (var == "sig") col = 1;
	else if (var == "K") col = 2;
	else if (var == "T") col = 3;
	else if (var == "S") col = 4;
	else if (var == "q") col = 5;

	// Generate matrix

	for (double val : Console)
	{
		std::vector<double> row = { r, sig, K, T, S, q };
		if (col != -1)
		{
			row[col] = val; // Varying parameter
		}
		matrix.push_back(row); // Add the row to the matrix
	}

	return matrix;
}