//MeshParameterGenerator.cpp

#include "MeshParameterGenerator.hpp"

// Default Constructor
MeshParameterGenerator::MeshParameterGenerator() : r(0.0), sig(0.0), K(0.0), T(0.0), S(0.0), q(0.0), var(""), start(0.0), end(0.0), step(0.0) {};

// Constructor by Input
MeshParameterGenerator::MeshParameterGenerator(double r_in, double sig_in, double K_in, double T_in, double S_in, double q_in, const std::string& var_in, double start_in, double end_in, double step_in) : r(r_in), sig(sig_in), K(K_in), T(T_in), S(S_in), q(q_in), var(var_in), start(start_in), end(end_in), step(step_in) {};

// Constructor by Option Onput
MeshParameterGenerator::MeshParameterGenerator(const Option& option, const std::string& var_in, double start_in, double end_in, double step_in) 
	: r(option.rf_rate()), sig(option.sigma()), K(option.strike()), T(option.time()), S(option.spot()), q(option.dividends()), var(var_in), start(start_in), end(end_in), step(step_in) {};

// Copy Constructor
MeshParameterGenerator::MeshParameterGenerator(const MeshParameterGenerator& mpg) 
	: r(mpg.r), sig(mpg.sig), K(mpg.K), T(mpg.T), S(mpg.S), q(mpg.q), var(mpg.var), start(mpg.start), end(mpg.end), step(mpg.step) {};

// Destructor
MeshParameterGenerator::~MeshParameterGenerator() {};

// Assignment Operator
MeshParameterGenerator& MeshParameterGenerator::operator=(const MeshParameterGenerator& mpg)
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
void MeshParameterGenerator::rf_rate(double r_in) { r = r_in; }
double MeshParameterGenerator::rf_rate() const { return r; }
void MeshParameterGenerator::sigma(double sig_in) { sig = sig_in; }
double MeshParameterGenerator::sigma() const { return sig; }
void MeshParameterGenerator::strike(double K_in) { K = K_in; }
double MeshParameterGenerator::strike() const { return K; }
void MeshParameterGenerator::time(double T_in) { T = T_in; }
double MeshParameterGenerator::time() const { return T; }
void MeshParameterGenerator::spot(double S_in) { S = S_in; }
double MeshParameterGenerator::spot() const { return S; }
void MeshParameterGenerator::dividends(double q_in) { q = q_in; } // double q = 0.0; Dividend yield...MeshParameterGenerator.b = indexMeshParameterGenerator.r - q;
double MeshParameterGenerator::dividends() const { return q; }
void MeshParameterGenerator::variable(const std::string& var_in) { var = var_in; }
std::string MeshParameterGenerator::variable() const { return var; }
void MeshParameterGenerator::mesh_start(double start_in) { start = start_in; }
double MeshParameterGenerator::mesh_start() const { return start; }
void MeshParameterGenerator::mesh_end(double end_in) { end = end_in; }
double MeshParameterGenerator::mesh_end() const { return end; }
void MeshParameterGenerator::mesh_step(double step_in) { step = step_in; }
double MeshParameterGenerator::mesh_step() const { return step; }

// Parameter Generator for mesh
std::vector<std::vector<double>> MeshParameterGenerator::generateParameters()
{
	std::vector<std::vector<double>> matrix; // Matrix to hold the parameters
	
	std::vector<double> mesh;	// Vector to hold the mesh values

	for (double i = start; i <= end; i += step)
	{
		mesh.push_back(i);
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

	for (double val : mesh)
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