#ifndef MESHPARAMETEGENERATOR_HPP
#define MESHPARAMETEGENERATOR_HPP

#include <vector>
#include <string>
#include "ParameterGenerator.hpp"    

class MeshParameterGenerator : public ParameterGenerator 
{
private:
    double T, K, sig, r, b, S;  // Base option parameters
    std::string variable;       // Which variable to vary
    double start, end, step;    // Mesh parameters

public:

};

#endif