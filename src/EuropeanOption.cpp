// EuropeanOption.cpp
#include "EuropeanOption.hpp"
#include <iomanip>
#include <cmath>

//////////// Price Functions /////////////////////////////////
double EuropeanOption::CallPrice() const //Call Price
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return (S * exp(q * T) * N(d1)) - (K * exp(-r * T) * N(d2));
}

double EuropeanOption::CallPrice(double v, std::string var) const //Call Price with  input
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + ((r-q) + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (S * exp(-q * T) * N(d1)) - (K * exp(-v * T) * N(d2));
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r-q + (v * v) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (S * exp(-q * T) * N(d1)) - (K * exp(-r * T) * N(d2));
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r-q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (S * exp(-q * T) * N(d1)) - (v * exp(-r * T) * N(d2));
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		double d2 = d1 - tmp;
		return (S * exp(-q * v) * N(d1)) - (K * exp(-r * v) * N(d2));
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;

		return (v * exp(q * T) * N(d1)) - (K * exp(-r * T) * N(d2));
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (S * exp(v * T) * N(d1)) - (K * exp(-r * T) * N(d2));
	}
}

double EuropeanOption::PutPrice() const //Put Price
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (r - q  + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return (K * exp(-r * T) * N(-d2)) - (S * exp(-q * T) * N(-d1));
}

double EuropeanOption::PutPrice(double v, std::string var) const //Put Price with input
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + ((r - q) + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (K * exp(-v * T) * N(-d2)) - (S * exp(-q * T) * N(-d1));
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (K * exp(-r * T) * N(-d2)) - (S * exp(-q * T) * N(-d1));
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (v * exp(-r * T) * N(-d2)) - (S * exp(-q * T) * N(-d1));
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		double d2 = d1 - tmp;
		return (K * exp(-r * v) * N(-d2)) - (S * exp(-q * v) * N(-d1));
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;

		return (K * exp(-r * T) * N(-d2)) - (v * exp(-q * T) * N(-d1));
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (K * exp(-r * T) * N(-d2)) - (S * exp(-v * T) * N(-d1));
	}
}


//////////// Greeks /////////////////////////////////
double EuropeanOption::CallDelta() const //Delta of a Call Option
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (r -q + (sig * sig) * 0.5) * T) / tmp;

	return exp(-q * T) * N(d1);
}

double EuropeanOption::CallDelta(double v, std::string var) const
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (v - q + (sig * sig) * 0.5) * T) / tmp;
		return exp(-q * T) * N(d1);
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		return exp(-q * T) * N(d1);
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		return exp(-q * T) * N(d1);
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		return exp(-q * v) * N(d1);
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		return exp(-q * T) * N(d1);
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		return exp(-v * T) * N(d1);
	}
}

double EuropeanOption::PutDelta() const //Delta of a put option
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;

	return exp(-q * T) * (N(d1) - 1.0);
}

double EuropeanOption::PutDelta(double v, std::string var) const
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (v - q + (sig * sig) * 0.5) * T) / tmp;
		return exp(-q * T) * (N(d1) - 1.0);
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		return exp(-q * T) * (N(d1) - 1.0);
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		return exp(-q * T) * (N(d1) - 1.0);
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		return exp(-q * v) * (N(d1) - 1.0);
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		return exp(-q * T) * (N(d1) - 1.0);
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		return exp(-v * T) * (N(d1) - 1.0);
	}
}

double EuropeanOption::CallTheta() const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return (-1 * (S * sig * exp(-q * T) * n(d1)) / (2 * sqrt(T))) + (-q * S * exp(-q * T) * N(d1)) - (r * K * exp(-r * T) * N(d2));

}

double EuropeanOption::CallTheta(double v, std::string var) const
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (v - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * sig * exp(-q * T) * n(d1)) / (2 * sqrt(T))) + (-q * S * exp(-q * T) * N(d1)) - (v * K * exp(-v * T) * N(d2));
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * v * exp(-q * T) * n(d1)) / (2 * sqrt(T))) + (-q * S * exp(-q * T) * N(d1)) - (r * K * exp(-r * T) * N(d2));
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * sig * exp(-q * T) * n(d1)) / (2 * sqrt(T))) + (-q * S * exp(-q * T) * N(d1)) - ((v * K * exp(-r * T) * N(d2)));
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * sig * exp(-q * v) * n(d1)) / (2 * sqrt(v))) + (-q * S * exp(-q * v) * N(d1)) - ((K * v * exp(-r * v) * N(d2)));
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (v * sig * exp(-q * T) * n(d1)) / (2 * sqrt(T))) + (-q * v * exp(-q * T) * N(d1)) - (K * exp(-r * T) * N(d2));
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * sig * exp(-v * T) * n(d1)) / (2 * sqrt(T))) + (-q * S * exp(-q * T) * N(d1)) - (K * exp(-r * T) * N(d2));
	}
}

double EuropeanOption::PutTheta() const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;

	return (-1 * (S * sig * exp(-q * T) * n(d1)) / (2 * sqrt(T))) - (-q * S * exp(-q * T) * N(-d1)) + (r * K * exp(-r * T) * N(-d2));

}

double EuropeanOption::PutTheta(double v, std::string var) const
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (v - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * sig * exp(-q * T) * n(d1)) / (2 * sqrt(T))) - (-q * S * exp(-q * T) * N(-d1)) + (v * K * exp(-v * T) * N(-d2));
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * v * exp(-q * T) * n(d1)) / (2 * sqrt(T))) - (-q * S * exp(-q * T) * N(-d1)) + (r * K * exp(-r * T) * N(-d2));
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * sig * exp(-q * T) * n(d1)) / (2 * sqrt(T))) - (-q * S * exp(-q * T) * N(-d1)) + ((v * K * exp(-r * T) * N(-d2)));
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * sig * exp(-q * v) * n(d1)) / (2 * sqrt(v))) - (-q * S * exp(-q * v) * N(-d1)) + ((K * v * exp(-r * v) * N(-d2)));
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (v * sig * exp(-q * T) * n(d1)) / (2 * sqrt(T))) - (-q * v * exp(-q * T) * N(-d1)) + (K * exp(-r * T) * N(-d2));
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-1 * (S * sig * exp(-v * T) * n(d1)) / (2 * sqrt(T))) - (-q * S * exp(-q * T) * N(-d1)) + (K * exp(-r * T) * N(-d2));
	}
}

double EuropeanOption::OptionGamma() const
{
	double tmp = sig * sqrt(T);

	double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;

	return (n(d1) * exp(-q * T)) / (S * tmp);

}

double EuropeanOption::OptionGamma(double v, std::string var) const
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (v - q + (sig * sig) * 0.5) * T) / tmp;
		return (n(d1) * exp(-q * T)) / (S * tmp);
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		return (n(d1) * exp(-q * T)) / (S * tmp);
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		return (n(d1) * exp(-q * T)) / (S * tmp);
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		return (n(d1) * exp(-q * v)) / (S * tmp);
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		return ((n(d1) * exp(-q * T)) - ((v - K) / S));
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		return ((n(d1) * exp(-v * T)) - ((S - K) / S));
	}
}

double EuropeanOption::OptionVega() const
{
	double tmp = sig * sqrt(T);
	
	double d1 = (log(S / K) + ( r - q + (sig * sig) * 0.5) * T) / tmp;

	return ((S * sqrt(T) * exp(-q * T) * n(d1)));
}

double EuropeanOption::OptionVega(double v, std::string var) const
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (v - q + (sig * sig) * 0.5) * T) / tmp;
		return S * sqrt(T) * exp(-q * T) * n(d1);
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		return S * sqrt(T) * exp(-q * T) * n(d1);
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		return S * sqrt(T) * exp(-q * T) * n(d1);
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		return S * sqrt(v) * exp(-q * v) * n(d1);
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		return v * sqrt(T) * exp(-q * T) * n(d1);
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		return S * sqrt(T) * exp(-v * T) * n(d1);
	}
}

double EuropeanOption::CallRho() const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;
	return (K * T * exp(-r * T) * N(d2));
}

double EuropeanOption::CallRho(double v, std::string var) const
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (v - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (K * T * exp(-v * T) * N(d2));
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (K * T * exp(-r * T) * N(d2));
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (v * T * exp(-r * T) * N(d2));
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		double d2 = d1 - tmp;
		return (K * v * exp(-r * v) * N(d2));
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return ((K * T * exp(-r * T) * N(d2)) - (v * T * exp(-q * T) * N(d1)));
	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (K * T * exp(-r * T) * N(d2)) - (S * T * exp(-v * T) * N(d1));
	}
}

double EuropeanOption::PutRho() const
{
	double tmp = sig * sqrt(T);
	double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
	double d2 = d1 - tmp;
	return (-K * T * exp(-r * T) * N(-d2));
}

double EuropeanOption::PutRho(double v, std::string var) const
{
	if (var == "r")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (v - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-K * T * exp(-v * T) * N(-d2));
	}
	else if (var == "sig")
	{
		double tmp = v * sqrt(T);
		double d1 = (log(S / K) + (r - q + (v * v) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-K * T * exp(-r * T) * N(-d2));
	}
	else if (var == "K")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / v) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;
		return (-v * T * exp(-r * T) * N(-d2));
	}
	else if (var == "T")
	{
		double tmp = sig * sqrt(v);
		double d1 = (log(S / K) + (r - q + (sig * sig) * 0.5) * v) / tmp;
		double d2 = d1 - tmp;
		return (-K * v * exp(-r * v) * N(-d2));
	}
	else if (var == "S")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(v / K) + (r - q + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;

		return ((-K * T * exp(-r * T) * N(-d2)) + ((v * T * exp(-q * T) * N(d1))));

	}
	else if (var == "q")
	{
		double tmp = sig * sqrt(T);
		double d1 = (log(S / K) + (r - v + (sig * sig) * 0.5) * T) / tmp;
		double d2 = d1 - tmp;

		return (-K * T * exp(-r * T) * N(-d2)) + (S * T * exp(-v * T) * N(-d1));
	}
}


//////////// Constructors/Destructor/Assignment Operator /////////////////////////////////

// Default Constructor
EuropeanOption::EuropeanOption() : Option() {}

// Constructor by input
EuropeanOption::EuropeanOption(double r, double sig, double K, double T, double S, double q, std::string optType) : Option(r, sig, K, T, S, q, optType) {}

// Copy Constructor
EuropeanOption::EuropeanOption(const EuropeanOption& option) : Option(option) {}

// Destructor
EuropeanOption::~EuropeanOption() {}

// Assignment operator
EuropeanOption& EuropeanOption::operator=(const EuropeanOption& option)
{
	if (this == &option)
		return *this;

	Option::operator=(option);

	return *this;
}

//////////// Pure Virtual Methods /////////////////////////////////

double EuropeanOption::Price() const
{
	if (optType == "C")
		return CallPrice();
	else
		return PutPrice();
}

double EuropeanOption::Price(double v, std::string var) const //Option Price input
{
	if (optType == "C")
	{
		return CallPrice(v, var);
	}
	else
	{
		return PutPrice(v, var);
	}
}

double EuropeanOption::Delta() const
{
	if (optType == "C")
		return CallDelta();
	else
		return PutDelta();
}

double EuropeanOption::Delta(double v, std::string var) const
{
	if (optType == "C")
		return CallDelta(v,var);
	else
		return PutDelta(v,var);
}

double EuropeanOption::Theta() const 
{
	if (optType == "C")
		return CallTheta();
	else
		return PutTheta();
}

double EuropeanOption::Gamma() const
{
	return OptionGamma();
}

double EuropeanOption::Vega() const
{
	return OptionVega();
}

double EuropeanOption::Vega(double v, std::string var) const
{
	return OptionVega(v, var);
}

double EuropeanOption::Rho() const
{
	if (optType == "C")
		return CallRho();
	else
		return PutRho();
}

double EuropeanOption::Rho(double v, std::string var) const
{
	if (optType == "C")
		return CallRho(v, var);
	else
		return PutRho(v, var);
}


//////////// Numerical/Finite Difference Functions /////////////////////////////////

double EuropeanOption::NumCallDelta(double h) const
{
	return ((CallPrice((S+h), "S")) - (CallPrice((S-h), "S"))) / (2 * h);
}

double EuropeanOption::NumPutDelta(double h) const
{
	return ((PutPrice((S+h), "S")) - (PutPrice((S - h), "S"))) / (2 * h);
}

double EuropeanOption::NumTheta(double h) const
{
	return ((PutPrice((T-h), "T")) - (PutPrice(T, "T"))) / (h);
}

double EuropeanOption::NumGamma(double h) const
{
	double price = S + h;
	return (CallPrice(price, "S") - (2 * CallPrice()) + CallPrice(price, "S")) / (h * h);
}

double EuropeanOption::NumVega(double h) const
{
	return ((CallPrice((sig + h), "sig")) - (CallPrice((sig - h), "sig"))) / (2 * h);
}

double EuropeanOption::NumCallRho(double h) const
{
	return ((CallPrice((r + h), "r")) - (CallPrice((r - h), "r"))) / (2 * h);
}

double EuropeanOption::NumPutRho(double h) const
{
	return ((PutPrice((r + h), "r")) - (PutPrice((r - h), "r"))) / (2 * h);
}


//Implied Volatility
std::vector<double> EuropeanOption::impliedVol(double price, double x0, double tol, int max_iters) const
{
	std::vector<double> approximations; // Vector to store approximations
	double sig_prev = x0; // Initial guess
	double sig_current = 0;  //Current guess

	

	//Call
	if (optType == "C")
	{
		for (int i = 0; i < max_iters; i++)
		{
			std::cout << "X0: " << sig_prev << std::endl;
			double tmp = sig_prev * sqrt(T);
			double d1 = (log(S / K) + (r - q + (sig_prev * sig_prev) * 0.5) * T) / tmp;
			double d2 = d1 - tmp;

			double fx = (S * exp(-q * T) * N(d1)) - (K * exp(-r * T) * N(d2)) - price;
			double vegax = Vega(sig_prev, "sig");

			sig_current = sig_prev - (fx/vegax);
			approximations.push_back(sig_current);

			if (i > 0)
			{
				double diff = fabs((sig_current - sig_prev) / sig_current); //check difference

				if (diff < tol) { break; } //finish if tolerance reached
			}
			sig_prev = sig_current; //assigning for next iteration
		}
		
	}
	else if (optType == "P")
	{
		for (int i = 0; i < max_iters; i++)
		{
			double tmp = sig_prev * sqrt(T);
			double d1 = (log(S / K) + (r - q + (sig_prev * sig_prev) * 0.5) * T) / tmp;
			double d2 = d1 - tmp;

			double fx = -(S * exp(-q * T) * N(d1)) + (K * exp(-r * T) * N(d2)) - price;
			double vegax = Vega(sig_prev, "sig");
			

			sig_current = sig_prev - (fx / vegax);
			approximations.push_back(sig_current);

			if (i > 0)
			{
				double diff = fabs((sig_current - sig_prev) / sig_current); //check difference

				if (diff < tol) { break; } //finish if tolerance reached
			}
			sig_prev = sig_current; //assigning for next iteration
		}
	}
	return approximations;
}

std::vector<double> EuropeanOption::strike_approx(double x0, double tol, int max_iters) const
{
	std::vector<double> approximations; // Vector to store approximations
	double k_prev = x0; // Initial guess
	double k_current = 0;  //Current guess
	approximations.push_back(k_prev);

	//Call
	if (optType == "C")
	{
		for (int i = 0; i < max_iters; i++)
		{
			double tmp = sig * sqrt(T);
			double d1 = (log(S / k_prev) + (r - q + (sig * sig) * 0.5) * T) / tmp;
			double d2 = d1 - tmp;

			double fx = Price(k_prev, "K") + k_prev - S;
			double fdx = (-exp(-r * T) * N(d2)) + ((exp(-r * T) * n(d2)) / tmp) - ((S * exp(-q * T) * n(d1)) / (k_prev * tmp)) + 1;


			k_current = k_prev - (fx / fdx);
			
			approximations.push_back(k_current);

			if (i > 0)
			{
				double diff = fabs((k_current - k_prev) / k_current); //check difference

				if (diff < tol) { break; } //finish if tolerance reached
			}
			k_prev = k_current; //assigning for next iteration
		}

	}
	else if (optType == "P")
	{
		for (int i = 0; i < max_iters; i++)
		{
			
			double tmp = sig * sqrt(T);
			double d1 = (log(S / k_prev) + (r - q + (sig * sig) * 0.5) * T) / tmp;
			double d2 = d1 - tmp;

			double fx = Price(k_prev, "K") - k_prev + S ;
			double fdx = (exp(-r*T)*N(-d2)) + ((exp(-r*T)*n(d2))/tmp) - ((S*exp(-q*T)*n(d1))/(k_prev*tmp)) - 1;
			
			

			k_current = k_prev - (fx / fdx);
			approximations.push_back(k_current);

			if (i > 0)
			{
				double diff = fabs((k_current - k_prev) / k_current); //check difference

				if (diff < tol) { break; } //finish if tolerance reached
			}
			k_prev = k_current; //assigning for next iteration
		}
	}
	return approximations;
}

void EuropeanOption::info() const
{
	std::cout << std::fixed << std::setprecision(8); // Set precision to 8 decimal places

	std::cout << " " << std::setw(24) << "Call Option" << std::setw(20) << "Put Option" << std::endl;
	std::cout << "Price" << std::setw(20) << CallPrice() << std::setw(20) << PutPrice() << std::endl;
	std::cout << "Delta" << std::setw(20) << CallDelta() << std::setw(20) << PutDelta() << std::endl;
	std::cout << "Gamma" << std::setw(20) << Gamma() << std::setw(20) << Gamma() << std::endl; // Gamma is the same for Call and Put
	std::cout << "Vega" << std::setw(21) << Vega() << std::setw(20) << Vega() << std::endl; // Vega is the same for Call and Put
	std::cout << "Theta" << std::setw(20) << CallTheta() << std::setw(20) << PutTheta() << std::endl;
	std::cout << "Rho" << std::setw(22) << CallRho() << std::setw(20) << PutRho() << std::endl; // Rho is negative for Put
}