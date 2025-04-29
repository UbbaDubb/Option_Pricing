// EuropeanOption.hpp
#ifndef EUROPEAN_OPTION_HPP
#define EUROPEAN_OPTION_HPP

#include "Option.hpp"
#include <cmath>

class EuropeanOption : public Option {
private:
    // European option specific methods
    double CallPrice() const;
    double CallPrice(double v, std::string var) const;
    double PutPrice() const;
    double PutPrice(double v, std::string var) const;
    double CallDelta() const;
    double CallDelta(double v, std::string var) const;
    double PutDelta() const;
    double PutDelta(double v, std::string var) const;
    double CallTheta() const;
	double CallTheta(double v, std::string var) const; 
    double PutTheta() const;
	double PutTheta(double v, std::string var) const;
    double OptionGamma() const;
	double OptionGamma(double v, std::string var) const;
    double OptionVega() const;
    double OptionVega(double v, std::string var) const;
	double CallRho() const;
    double CallRho(double v, std::string var) const;
	double PutRho() const;
	double PutRho(double v, std::string var) const;
    

public:
    // Constructors/Destructor
    EuropeanOption();
    EuropeanOption(double r, double sig, double K, double T, double S, double q, std::string optType);
    EuropeanOption(const EuropeanOption& option);
    ~EuropeanOption();

    // Assignment operator
    EuropeanOption& operator=(const EuropeanOption& option);

    // Implementation of pure virtual methods
    virtual double Price() const override;
    virtual double Price(double v, std::string var) const override;
    virtual double Delta() const override;
    virtual double Delta(double v, std::string var) const override;
    virtual double Theta() const override;
    virtual double Gamma() const override;
    virtual double Vega() const override;
    virtual double Vega(double v, std::string var) const override;
    virtual double Rho() const override;
    virtual double Rho(double v, std::string var) const override;
    
    // European option specific methods
    double NumCallDelta(double h) const;
    double NumPutDelta(double h) const;
    double NumTheta(double h) const;
    double NumGamma(double h) const;
    double NumVega(double h) const;
	double NumCallRho(double h) const;
	double NumPutRho(double h) const;

    std::vector<double> impliedVol(double price, double x0, double tol, int max_iters) const;
    std::vector<double> strike_approx(double x0, double tol, int max_iters) const;
   
    void info() const;
 
};

#endif