#ifndef BLAZORCOMPONENT
#define BLAZORCOMPONENT
#include <nlohmann/json.hpp>
#include "blazor_parameter.hpp"
#include <unordered_map>
#include <vector>

class BlazorDocument;

class BlazorComponent {
    public:
        typedef BlazorComponent (*componentMaker)(nlohmann::json);
        typedef std::unordered_map<std::string, componentMaker> ComponentMap;
        static ComponentMap componentMap;

        void setName(const char* name);
        inline std::string getName() {return this->name;};

        BlazorComponent();
        BlazorComponent(std::string name, nlohmann::json json, std::string elementName = "root");
        BlazorComponent(std::string tagName, std::vector<BlazorParameter> params, nlohmann::json childrenJson = NULL);

        void streamOutput(std::ostream* output, int indentCount = 1);

        constexpr inline int getId() {return this->id;};
    private:
        std::string name;
        int id;
        std::string openingTag;
        std::string closingTag;
        std::vector<BlazorComponent> children;
        std::vector<BlazorParameter> parameters;
};

#endif // BLAZORCOMPONENT 

