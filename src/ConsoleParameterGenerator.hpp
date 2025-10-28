#ifndef CONSOLEPARAMETEGENERATOR_HPP
#define CONSOLEPARAMETEGENERATOR_HPP

#include <vector>
#include <string>
#include "ParameterGenerator.hpp"
#include "Option.hpp"
#include "MeshParameterGenerator.hpp"

class ConsoleParameterGenerator : public ParameterGenerator 
{
private:
    // Common parameters for all options
    double r;    // Risk-free interest rate
    double sig;  // Volatility
    double K;    // Strike price
    double T;    // Time to maturity
    double S;    // Current underlying price
    double q;    // Dividends

    // Mesh (Optional)
    bool useMesh;
    std::string var;       // Variable that will be varied
    double start, end, step;    // Console parameters

public:
	// Constructors/Destructor
    ConsoleParameterGenerator();
	ConsoleParameterGenerator(const ConsoleParameterGenerator& cpg);
    ~ConsoleParameterGenerator();

	// Assignment operator
    ConsoleParameterGenerator& operator=(const ConsoleParameterGenerator& mpg);
    
    // Interactive initialisation
    void initialise();

    // Override base class function
    std::vector<std::vector<double>> generateParameters() override;
    
};

#endif