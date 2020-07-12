#ifndef BLAZORPARAMETER
#define BLAZORPARAMETER

#include "blazor_parameter_types.hpp"
#include <string>

class BlazorParameter {
    public:
        BlazorParameter();
    private:
        std::string paramName;
        std::string typeName;

};

#endif // BLAZORPARAMETER
