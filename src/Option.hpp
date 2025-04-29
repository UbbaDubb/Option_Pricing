// Option.hpp
#ifndef OPTION_H
#define OPTION_H

#include <string>
#include <boost/math/distributions/normal.hpp>
#include <cmath>
#include <iostream>

class Option 
{
protected:
    // Common parameters for all options
    double r;    // Risk-free interest rate
    double sig;  // Volatility
    double K;    // Strike price
    double T;    // Time to maturity
    double S;    // Current underlying price
    double q;    // Dividends

    std::string optType;  // "C" for Call, "P" for Put

    // Utility functions for normal distribution
    double n(double x) const;  // PDF
    double N(double x) const;  // CDF

public:
    // Constructors/Destructor
    Option();
    Option(double r, double sig, double K, double T, double S, double q, std::string optType);
    Option(const Option& option);
    virtual ~Option() = 0;  // Pure virtual destructor makes this an abstract class

    // Assignment operator
    Option& operator=(const Option& option);

    // Pure virtual methods that must be implemented by derived classes
    virtual double Price() const = 0;
    virtual double Price(double v, std::string var) const = 0;
    virtual double Delta() const = 0;
    virtual double Delta(double v, std::string var) const = 0;
    virtual double Theta() const = 0;
	virtual double Theta(double v, std::string var) const = 0;
    virtual double Gamma() const = 0;
	virtual double Gamma(double v, std::string var) const = 0;
    virtual double Vega() const = 0;
    virtual double Vega(double v, std::string var) const = 0;
    virtual double Rho() const = 0;
    virtual double Rho(double v, std::string var) const = 0;

    // Accessor/modifier methods for parameters
    void rf_rate(double r_in);
    const double rf_rate();
    void sigma(double sig_in);
    const double sigma();
    void strike(double K_in);
    const double strike();
    void time(double T_in);
    const double time();
    void spot(double S_in);
    const double spot();
    void dividends(double q_in);
    const double dividends();
    void type(std::string type);
    const std::string type();

    // Toggle between Call and Put
    void toggle();
};

#endif