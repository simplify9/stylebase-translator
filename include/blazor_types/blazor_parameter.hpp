#ifndef BLAZORPARAMETER
#define BLAZORPARAMETER

#include "blazor_parameter_types.hpp"
#include <string>

class BlazorParameter {
    public:
        BlazorParameter();
        inline std::string getName() {return name;}
    private:
        std::string name;
        std::string typeName;

};

#endif // BLAZORPARAMETER
