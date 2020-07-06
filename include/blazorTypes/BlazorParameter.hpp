#ifndef BLAZORPARAMETER
#define BLAZORPARAMETER

#include "BlazorParameterTypes.hpp"
#include <string>

class BlazorParameter {
    public:
        BlazorParameter();
    private:
        std::string paramName;
        std::string typeName;

};

#endif // BLAZORPARAMETER
