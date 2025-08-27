#ifndef MATRIXPRICER_HPP
#define MATRIXPRICER_HPP

#include <vector>
#include "Option.hpp"
#include "MeshParameterGenerator.hpp"
#include <string>
#include <iostream>

class MatrixPricer 
{
	private:
		std::vector<std::vector<double>> parameters;

	public:
	// Constructors/Destructor
		MatrixPricer(); 
		MatrixPricer(const std::vector<std::vector<double>>& parameters_in);
		MatrixPricer(const MatrixPricer& mp);
		~MatrixPricer();

		// Assignment operator
		MatrixPricer& operator=(const MatrixPricer& mp);

		// Getter/Setter functions
		void setParameters(const std::vector<std::vector<double>>& parameters_in);
		std::vector<std::vector<double>> getParameters() const;

		// Print function for parameters
		void printParameters() const;

		// Price options based on the parameter matrix
		std::vector<double> priceOptions(const Option& option) const;
		
		// Extended pricing function to return multiple outputs
		std::vector<std::vector<double>> priceOptionsExtended(const Option& option) const;


};


#endif

