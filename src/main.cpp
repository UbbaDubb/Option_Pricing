#include <iostream>
#include <boost/math/constants/constants.hpp>
#include <boost/math/distributions/normal.hpp>
#include "Option.hpp"
#include "EuropeanOption.hpp"
#include <functional>


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

    return 0;
}


