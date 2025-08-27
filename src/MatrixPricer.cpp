//MatrixPricer.cpp

#include "MatrixPricer.hpp"

// Default Constructor
MatrixPricer::MatrixPricer() : parameters() {}

// Constructor by Input
MatrixPricer::MatrixPricer(const std::vector<std::vector<double>>& parameters_in) : parameters(parameters_in) {}

// Copy Constructor
MatrixPricer::MatrixPricer(const MatrixPricer& mp) : parameters(mp.parameters) {}

// Destructor
MatrixPricer::~MatrixPricer() {}


// Assignment Operator
MatrixPricer& MatrixPricer::operator=(const MatrixPricer& mp)
{
	if (this == &mp)
		return *this;
	parameters = mp.parameters;
	return *this;
};

// Getter/Setter functions
void MatrixPricer::setParameters(const std::vector<std::vector<double>>& parameters_in) { parameters = parameters_in; }
std::vector<std::vector<double>> MatrixPricer::getParameters() const { return parameters; }

void MatrixPricer::printParameters() const
{
	std::cout << "\nParameter Matrix:" << std::endl;
	std::cout << "Row | r     | sig   | K     | T     | S     | q     |" << std::endl;
	std::cout << "----+-------+-------+-------+-------+-------+-------+" << std::endl;

	for (size_t i = 0; i < parameters.size(); i++) {
		std::cout << std::setw(3) << (i + 1) << " | ";
		for (size_t j = 0; j < parameters[i].size(); j++) {
			std::cout << std::setw(5) << std::fixed << std::setprecision(2)
				<< parameters[i][j] << " | ";
		}
		std::cout << std::endl;
	}
}


// Price options based on the parameter matrix
std::vector<double> MatrixPricer::priceOptions(const Option& option) const
{
	std::vector<double> prices; // Vector to store computed prices

	for (const auto& paramSet : parameters) {
		if (paramSet.size() != 6) {
			std::cerr << "Error: Each parameter set must contain exactly 6 values (r, sig, K, T, S, q)." << std::endl;
			continue;
		}
		double r = paramSet[0];
		double sig = paramSet[1];
		double K = paramSet[2];
		double T = paramSet[3];
		double S = paramSet[4];
		double q = paramSet[5];
		
		std::unique_ptr<Option> tempOption(option.clone());

		tempOption->rf_rate(r);
		tempOption->sigma(sig);
		tempOption->strike(K);
		tempOption->time(T);
		tempOption->spot(S);
		tempOption->dividends(q);
		prices.push_back(tempOption->Price());
		
	}
	return prices;
}

std::vector<std::vector<double>> MatrixPricer::priceOptionsExtended(const Option& option) const
{
	std::vector<std::vector<double>> results;

	for (const auto& paramSet : parameters) {
		if (paramSet.size() != 6) {
			std::cerr << "Error: Each parameter set must contain exactly 6 values." << std::endl;
			continue;
		}

		double r = paramSet[0];
		double sig = paramSet[1];
		double K = paramSet[2];
		double T = paramSet[3];
		double S = paramSet[4];
		double q = paramSet[5];

		// Copy the option and set parameters
		std::unique_ptr<Option> tempOption(option.clone());
		tempOption->rf_rate(r);
		tempOption->sigma(sig);
		tempOption->strike(K);
		tempOption->time(T);
		tempOption->spot(S);
		tempOption->dividends(q);

		// Compute outputs
		tempOption->type("C");
		double callPrice = tempOption->Price();
		tempOption->type("P");
		double putPrice = tempOption->Price();
		tempOption->type("C");
		double calldelta = tempOption->Delta();
		tempOption->type("P");
		double putdelta = tempOption->Delta();
		double gamma = tempOption->Gamma();
		double vega = tempOption->Vega();
		tempOption->type("C");
		double calltheta = tempOption->Theta();
		tempOption->type("P");
		double puttheta = tempOption->Theta();
		tempOption->type("C");
		double callrho = tempOption->Rho();
		tempOption->type("P");
		double putrho = tempOption->Rho();

		// Append row: params + results
		std::vector<double> row = { r, sig, K, T, S, q, callPrice, putPrice, calldelta, 
			putdelta, gamma, vega, calltheta, puttheta, callrho, putrho };
		results.push_back(row);
	}

	return results;
}
