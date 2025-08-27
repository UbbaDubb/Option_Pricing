// Option.cpp

//#ifndef Option_cpp

//#define Option_cpp

#include "Option.hpp"


//////////// Gaussian functions /////////////////////////////////
double Option::n(double x) const //Standard Normal PDF
{
	// Imported normal distribution from boost library
	boost::math::normal_distribution<> norm(0, 1);
	return boost::math::pdf(norm, x);
}

double Option::N(double x) const //Standard Normal CDF
{
	// Imported normal distribution from boost library
	boost::math::normal_distribution<> norm(0, 1);
	return boost::math::cdf(norm, x);
}

// Default Constructor
Option::Option() : r(0.0), sig(0.0), K(0.0), T(0.0), S(0.0), q(0.0), optType("C")  {};

// Constructor by input
Option::Option(double r, double sig, double K, double T, double S, double q, std::string optType) : r(r), sig(sig), K(K), T(T), S(S), q(q), optType(optType){};

// Copy Constructor
Option::Option(const Option& option) : r(option.r), sig(option.sig), K(option.K), T(option.T), S(option.S), q(option.q), optType(option.optType) {}

// Assignment operator
Option&  Option::operator=(const Option& option)
{
	if(this == &option)
		return *this;

	r = option.r;
	sig = option.sig;
	K = option.K;
	T = option.T;
	S = option.S;
	q = option.q;
	optType = option.optType;

	return *this;
}

// Destructor

Option::~Option() {}

// Getter/Setter functions
void Option::rf_rate(double r_in) {r = r_in;}
double Option::rf_rate() const {return r;}
void Option::sigma(double sig_in) { sig = sig_in; }
double Option::sigma() const {return sig;}
void Option::strike(double K_in) { K = K_in; }
double Option::strike() const { return K; }
void Option::time(double T_in) { T = T_in; }
double Option::time() const { return T; }
void Option::spot(double S_in) { S = S_in; }
double Option::spot() const { return S; }
void Option::dividends(double q_in) { q = q_in; } // double q = 0.0; Dividend yield...Option.b = indexOption.r - q;
double Option::dividends() const { return q; }
void Option::type(std::string type) { optType = type; }
std::string Option::type() const { return optType; }


// Modifier function
void Option::toggle()
{ // Change option type (C/P, P/C)
	if (optType == "C")
		optType = "P";
	else
		optType = "C";
}

//#endif 