#ifndef MESHPARAMETEGENERATOR_HPP
#define MESHPARAMETEGENERATOR_HPP

#include <vector>
#include <string>
#include "ParameterGenerator.hpp"
#include "Option.hpp"

class MeshParameterGenerator : public ParameterGenerator 
{
private:
    // Common parameters for all options
    double r;    // Risk-free interest rate
    double sig;  // Volatility
    double K;    // Strike price
    double T;    // Time to maturity
    double S;    // Current underlying price
    double q;    // Dividends
    std::string var;       // Variable that will be varied
    double start, end, step;    // Mesh parameters

public:
	// Constructors/Destructor
    MeshParameterGenerator();
    MeshParameterGenerator(double r_in, double sig_in, double K_in, double T_in, double S_in, double q_in,
        const std::string& var_in, double start_in, double end_in, double step_in);
	MeshParameterGenerator(const Option& option, const std::string& var_in, double start_in, double end_in, double step_in);
    MeshParameterGenerator(const MeshParameterGenerator& mpg);
    ~MeshParameterGenerator();

	// Assignment operator
    MeshParameterGenerator& operator=(const MeshParameterGenerator& mpg);

	// Getter/Setter functions

    void rf_rate(double r_in);
    double rf_rate() const;
    void sigma(double sig_in);
    double sigma() const;
    void strike(double K_in);
    double strike() const;
    void time(double T_in);
    double time() const;
    void spot(double S_in);
    double spot() const;
    void dividends(double q_in);
    double dividends() const;
    void variable(const std::string& var_in);
    std::string variable() const;
    void mesh_start(double start_in);
    double mesh_start() const;
    void mesh_end(double end_in);
    double mesh_end() const;
	void mesh_step(double step_in);
	double mesh_step() const;

    // Generate parameters for the mesh
    
	std::vector<std::vector<double>> generateParameters() override;

	// Printing function

   

};

#endif