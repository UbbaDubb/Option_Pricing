#ifndef PARAMETEGENERATOR_HPP
#define PARAMETEGENERATOR_HPP

#include <vector>
#include <string>
#include <iostream>

// Pure Virtual class for Parameter Generators with no data members

class ParameterGenerator
{
public:
    virtual ~ParameterGenerator() {}
    virtual std::vector<std::vector<double>> generateParameters() = 0;
    //virtual std::string getDescription() const = 0;
};

#endif