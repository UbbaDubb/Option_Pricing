#include <iostream>
#include <boost/math/constants/constants.hpp>
#include <boost/math/distributions/normal.hpp>
#include "Option.hpp"
#include "EuropeanOption.hpp"
#include <functional>
#include <iomanip>
#include "MeshParameterGenerator.hpp"
#include "ConsoleParameterGenerator.hpp"
#include "MatrixPricer.hpp"
#include <fstream>

void printPricerResults(const std::vector<std::vector<double>>& results)
{
    std::cout << "\nParameter Matrix with Results:\n";
    std::cout
        << std::setw(3) << "Row" << " | "
        << std::setw(7) << "r" << " | "
        << std::setw(7) << "sigma" << " | "
        << std::setw(7) << "K" << " | "
        << std::setw(7) << "T" << " | "
        << std::setw(7) << "S" << " | "
        << std::setw(7) << "q" << " | "
        << std::setw(7) << "Call" << " | "
        << std::setw(7) << "Put" << " | "
        << std::setw(7) << "Delta_C" << " | "
        << std::setw(7) << "Delta_P" << " | "
        << std::setw(7) << "Gamma" << " | "
        << std::setw(7) << "Vega" << " | "
        << std::setw(7) << "Theta_C" << " | "
        << std::setw(7) << "Theta_P" << " | "
        << std::setw(7) << "Rho_C" << " | "
        << std::setw(7) << "Rho_P" << " |\n";

    std::cout << std::string(6 + 17 * 9, '-') << "\n"; // separator line

    for (size_t i = 0; i < results.size(); i++)
    {
        std::cout << std::setw(3) << (i + 1) << " | ";
        for (double val : results[i]) {
            std::cout << std::setw(7) << std::fixed << std::setprecision(2) << val << " | ";
        }
        std::cout << "\n";
    }
}

void saveResultsToCSV(const std::string& filename,
    const std::vector<std::vector<double>>& results)
{
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Could not open file " << filename << std::endl;
        return;
    }

    // Write header row
    file << "r,sig,K,T,S,q,Call,Put,Delta(Call),Delta(Put),Gamma,Vega,Theta(Call),Theta(Put),Rho(Call),Rho(Put)\n";

    // Write each row
    for (const auto& row : results) {
        for (size_t i = 0; i < row.size(); ++i) {
            file << row[i];
            if (i != row.size() - 1) file << ","; // comma-separated
        }
        file << "\n";
    }

    file.close();
    std::cout << "Results successfully saved to " << filename << std::endl;
}

int main()
{
	// Put Option r=2%, vol= 25%, K=45, T=0.5, S=45, q=0%
	EuropeanOption put1 = EuropeanOption(0.02, 0.25, 45, 0.5, 45, 0, "P");
	put1.info();

	//Implied Volatility
	std::cout << "\nImplied Volatility Convergence:" << "\n";
    EuropeanOption call1;
	call1.rf_rate(0.03);
    call1.strike(30);
	call1.time(0.5);
	call1.spot(30);
	call1.dividends(0.01);
    std::vector<double> call1_impvol = call1.impliedVol(2.5, 0.1, 0.00000001, 100); // price, x0, tol, max_iters
    std::cout << std::fixed << std::setprecision(10);

    for (int i = 0; i < call1_impvol.size(); i++)
    {
        std::cout << "i = " << i << std::setw(10) << "" << call1_impvol[i];
        std::cout << std::fixed << "\n";
    }



    EuropeanOption opt1 = EuropeanOption();

    opt1.rf_rate(0.03);
    opt1.sigma(0.25);
    opt1.time(0.5);
    opt1.spot(50);
    opt1.dividends(0.01);
    opt1.type("C");

    std::cout << "\nStrike convergence:" << "\n";
    std::vector<double> opt1_approx = opt1.strike_approx(50, 0.00000001, 100);

    std::cout << std::fixed << std::setprecision(10);
    for (int i = 0; i < opt1_approx.size(); i++)
    {
        std::cout << "i = " << i << std::setw(10) << "" << opt1_approx[i];
        std::cout << std::fixed << "\n";
    }

	EuropeanOption opt2 = EuropeanOption(0.03, 0.25, 50, 0.5, 50, 0, "C");

    std::cout << "\nEuropean Option Price: \n";
    opt2.info();

	std::cout << "\n\nMesh Parameter Generator Example:" << std::endl;
	MeshParameterGenerator mpg(opt2, "sig", 0.1, 0.5, 0.05);

	std::vector<std::vector<double>> parameters = mpg.generateParameters();

	// Create MatrixPricer with generated parameters
	MatrixPricer pricer;
	pricer.setParameters(parameters);
	pricer.printParameters();
	EuropeanOption opt_temp = EuropeanOption();

	std::vector<double> prices = pricer.priceOptions(opt_temp);

	std::cout << "\nComputed European Option Prices:" << std::endl;
    for (size_t i = 0; i < prices.size(); i++)
    {
		std::cout << "Option " << (i + 1) << ": Price = " << std::fixed << std::setprecision(4) << prices[i] << std::endl;
    }

	//std::vector<std::vector<double>> results = pricer.priceOptionsExtended(opt_temp);
	//printPricerResults(results);

    saveResultsToCSV("option_results.csv", pricer.priceOptionsExtended(opt_temp));

    return 0;
}

/*
    // Example 1
    std::cout << "Example 1: 1yr, 1.5yr, 3yr bonds" << std::endl;
    std::vector<Bond> bonds1 = {
        Bond(1.0, 3.0, 101.25),
        Bond(1.5, 2.0, 99.95),
        Bond(3.0, 5.0, 110.30, true)  // Show details for 3yr bond
    };

    double cpnFreq = 0.5;
    double face = 100.0;
    double initialR = 0.05;
    double offset = 0.0;

    std::vector<RatePoint> result1 = { RatePoint(0.0, 0.015) };  // Overnight rate
    bootstrapZeroRate(initialR, face, cpnFreq, result1, bonds1, offset);

    // Example 2
    std::cout << "\n\nExample 2: 6mo, 1yr, 3yr, 5yr bonds" << std::endl;
    std::vector<Bond> bonds2 = {
        Bond(0.5, 0.0, 97.5),
        Bond(1.0, 5.0, 100.0),
        Bond(3.0, 5.0, 102.0, true),  // Show details for 3yr bond
        Bond(5.0, 6.0, 104.0)
    };

    std::vector<RatePoint> result2 = { RatePoint(0.0, 0.05) };  // Overnight rate
    bootstrapZeroRate(initialR, face, cpnFreq, result2, bonds2, offset);

    // Example 3
    std::cout << "\n\nExample 3: 6mo, 12mo, 2year, 3year, 5yr bonds, 10year" << std::endl;
    std::vector<Bond> bonds3 = {
        Bond(0.5, 0.0, 99.4565),
        Bond(1.0, 0.0, 98.6196),
        Bond(2.0, 2.0, 101.546875, true),
        Bond(3.0, 4.5, 107.5625, true),
        Bond(5.0, 3.125, 102.25, true),
        Bond(10.0, 4.0, 103.265625, true)
    };

    std::vector<RatePoint> result3 = { RatePoint(0.0, 0.05) };  // Overnight rate
    bootstrapZeroRate(initialR, face, cpnFreq, result3, bonds3, offset);

    //EuropeanOption opt(0.1, 0.36, 100, 0.5, 105, 0, "C");
	//opt.info();



	

    return 0;
}

*/