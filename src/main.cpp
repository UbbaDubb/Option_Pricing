#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
#include <utility>
#include <algorithm>
#include "EuropeanOption.hpp"

// Structure to represent a bond
struct Bond {
    double maturity;
    double couponRate;
    double price;
    bool showDetails;

    Bond(double t, double c, double p, bool show = false)
        : maturity(t), couponRate(c), price(p), showDetails(show) {
    }
};

// Structure to hold rate results
struct RatePoint {
    double time;
    double rate;

    RatePoint(double t, double r) : time(t), rate(r) {}
};

// Print table of Newton's method iterations
void printAsciiTable(const std::vector<double>& floatList) {
    std::cout << std::left << std::setw(10) << "Index" << "Guesses" << std::endl;
    std::cout << std::string(20, '-') << std::endl;

    for (size_t i = 0; i < floatList.size(); i++) {
        std::cout << std::left << std::setw(8) << (i + 1) << std::fixed << std::setprecision(10) << floatList[i] << std::endl;
    }
}

// Print the zero rate curve results
void printResult(const std::vector<RatePoint>& data) {
    std::cout << std::right << std::setw(5) << "Time" << " | " << std::setw(11) << "Interest" << std::endl;
    std::cout << std::string(19, '-') << std::endl;

    for (const auto& point : data) {
        std::cout << std::fixed << std::setprecision(2) << std::right << std::setw(5) << point.time
            << " | " << std::setprecision(8) << std::setw(11) << point.rate << std::endl;
    }
}

// Calculate the price given current guess of rate
double priceGuess(
    double guessRate,
    double cpnTotalPayout,
    double cpnPayment,
    double cpnFreq,
    double offset,
    double face,
    const Bond& bond,
    const std::vector<RatePoint>& result,
    std::vector<RatePoint>* resultOutput = nullptr
) {
    double time = bond.maturity;
    double recordedPrice = bond.price;

    // Get the last known rate point
    const RatePoint& lastPoint = result.back();
    double lastBondTime = lastPoint.time;
    double lastBondYield = lastPoint.rate;

    double cpnTime = lastBondTime + cpnFreq + offset;

    while (cpnTime < time) {
        // Calculate interpolated rate using linear slope
        double cpnTimeDiff = cpnTime - lastBondTime;
        double guessTimeDiff = time - lastBondTime;
        double slope = (guessRate - lastBondYield) / guessTimeDiff;
        double slopeTimeAdjusted = lastBondYield + (slope * cpnTimeDiff);

        if (resultOutput != nullptr) {
            resultOutput->push_back(RatePoint(cpnTime, slopeTimeAdjusted));
        }

        cpnTotalPayout += cpnPayment * std::exp(-1 * cpnTime * slopeTimeAdjusted);
        cpnTime += cpnFreq;
    }

    double totalPayout = cpnTotalPayout + (face + cpnPayment) * std::exp(-1 * time * guessRate);

    return totalPayout - recordedPrice;
}

// Calculate the derivative for Newton's method
double priceDeriv(
    double guessRate,
    double cpnPayment,
    const Bond& bond,
    double cpnFreq,
    double offset,
    double face,
    const std::vector<RatePoint>& result
) {
    double time = bond.maturity;

    // Get the last known rate point
    const RatePoint& lastPoint = result.back();
    double lastBondTime = lastPoint.time;
    double lastBondYield = lastPoint.rate;

    double cpnTime = lastBondTime + cpnFreq + offset;
    double derivSlope = 1.0 / (time - lastBondTime);
    double cpnDeriv = 0.0;

    while (cpnTime < time) {
        double cpnTimeDiff = cpnTime - lastBondTime;
        double guessTimeDiff = time - lastBondTime;
        double slope = (guessRate - lastBondYield) / guessTimeDiff;
        double slopeTimeAdjusted = lastBondYield + (slope * cpnTimeDiff);

        double basePayment = cpnPayment * std::exp(-1 * cpnTime * slopeTimeAdjusted);

        // Calculate derivative of exponential discount
        double derivOfExp = -cpnTime * derivSlope * cpnTimeDiff;

        cpnDeriv += derivOfExp * basePayment;
        cpnTime += cpnFreq;
    }

    double lastPayment = -time * (face + cpnPayment) * std::exp(-1 * time * guessRate);

    return cpnDeriv + lastPayment;
}

// Main bootstrapping function
void bootstrapZeroRate(
    double initialR,
    double face,
    double cpnFreq,
    std::vector<RatePoint>& result,
    const std::vector<Bond>& bonds,
    double offset
) {
    for (const auto& bond : bonds) {
        double time = bond.maturity;
        double cpnRate = bond.couponRate;
        double price = bond.price;
        bool writeRes = bond.showDetails;

        double cpnTotalPayout = 0.0;
        double cpnPayment = face * (cpnRate * cpnFreq / 100.0);

        std::vector<double> newtonOutput;

        // Calculate present value of known coupons
        for (const auto& point : result) {
            double prevTime = point.time;
            double prevYield = point.rate;

            if (prevTime == 0) continue; // Skip overnight rate

            if (prevTime < time) {
                cpnTotalPayout += cpnPayment * std::exp(-1 * prevTime * prevYield);
            }
        }

        // For 6-month bond or if previous bond maturity is exactly one coupon frequency before
        if (std::abs(time - cpnFreq) < 1e-9 ||
            (result.size() > 0 && std::abs(result.back().time - (time - cpnFreq)) < 1e-9)) {

            double r = std::log((price - cpnTotalPayout) / (face + cpnPayment)) / (-1 * time);
            result.push_back(RatePoint(time, r));
            continue;
        }

        // Use Newton's method for bonds with multiple coupons
        double guessOld = -1000.0;
        double guessR = initialR;
        double tolApprox = 1e-6;

        while (std::abs(guessOld - guessR) > tolApprox) {
            guessOld = guessR;

            double num = priceGuess(guessR, cpnTotalPayout, cpnPayment, cpnFreq, offset, face, bond, result);
            double denom = priceDeriv(guessR, cpnPayment, bond, cpnFreq, offset, face, result);

            double sub = num / denom;
            guessR = guessR - sub;

            if (writeRes) {
                newtonOutput.push_back(guessR);
            }
        }

        // Calculate intermediate points
        std::vector<RatePoint> intermediatePoints;
        priceGuess(guessR, cpnTotalPayout, cpnPayment, cpnFreq, offset, face, bond, result, &intermediatePoints);

        // Add intermediate points to result
        for (const auto& point : intermediatePoints) {
            // Check if this time point already exists
            auto it = std::find_if(result.begin(), result.end(),
                [&point](const RatePoint& rp) { return std::abs(rp.time - point.time) < 1e-9; });

            if (it == result.end()) {
                result.push_back(point);
            }
        }

        // Add final bond rate
        result.push_back(RatePoint(time, guessR));

        std::cout << "Bond at time " << time << " has rate: " << guessR << std::endl;

        if (writeRes && !newtonOutput.empty()) {
            std::cout << "Newton's method iterations:" << std::endl;
            printAsciiTable(newtonOutput);
        }
    }

    // Sort results by time
    std::sort(result.begin(), result.end(),
        [](const RatePoint& a, const RatePoint& b) { return a.time < b.time; });

    std::cout << "\nFinal Zero Rate Curve:" << std::endl;
    printResult(result);
}

int main() {
    std::cout << std::fixed << std::setprecision(6);

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