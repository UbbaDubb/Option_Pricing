#ifndef CONSOLEPARAMETEGENERATOR_HPP
#define CONSOLEPARAMETEGENERATOR_HPP

#include <vector>
#include <string>
#include "ParameterGenerator.hpp"
#include "Option.hpp"

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
    std::string var;       // Variable that will be varied
    double start, end, step;    // Console parameters

public:
	// Constructors/Destructor
    ConsoleParameterGenerator();
	ConsoleParameterGenerator(const ConsoleParameterGenerator& mpg);
    ~ConsoleParameterGenerator();

	// Assignment operator
    ConsoleParameterGenerator& operator=(const ConsoleParameterGenerator& mpg);

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
    void console_start(double start_in);
    double console_start() const;
    void console_end(double end_in);
    double console_end() const;
	void console_step(double step_in);
	double console_step() const;

    // Generate parameters for the Console
    
	std::vector<std::vector<double>> generateParameters() override;

	// Printing function

   

};

#endif