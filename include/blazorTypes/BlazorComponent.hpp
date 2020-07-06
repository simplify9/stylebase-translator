#ifndef BLAZORCOMPONENT
#define BLAZORCOMPONENT
#include <nlohmann/json.hpp>
#include "BlazorParameter.hpp"
#include <unordered_map>
#include <vector>


class BlazorComponent {
    public:
        typedef std::unordered_map<const char*, std::function<BlazorComponent(nlohmann::json)>> ComponentMap;
        const static ComponentMap componentMap;

        BlazorComponent();
        BlazorComponent(std::string name, nlohmann::json json);
        BlazorComponent(std::string tagName, std::vector<BlazorParameter> params, nlohmann::json childrenJson = NULL);
        void streamOutput(std::ostream* output);
    private:
        std::string openingTag;
        std::string closingTag;
        std::vector<BlazorComponent> children;
        std::vector<BlazorParameter> parameters;
};

#endif // BLAZORCOMPONENT 

