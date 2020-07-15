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

        inline long int calculateIdentity() {
            std::string tmp = name + type;
            const char* compStr = tmp.c_str();
            int resultLength = 0;
            long int result = 0;
            char focusedChar = compStr[resultLength];
            while(focusedChar != '\0'){
                ++resultLength;
                result += focusedChar * resultLength;
            }
            return result;
        }

        BlazorComponent();
        BlazorComponent(std::string name, nlohmann::json json, std::string elementName = "root");
        BlazorComponent(std::string tagName, std::vector<BlazorParameter> params, nlohmann::json childrenJson = NULL);

        void streamOutput(std::ostream* output, int indentCount = 1);

        constexpr inline int getId() {return this->id;};
    private:
        int id;
        std::string name;
        std::string openingTag;
        std::string type;
        std::string closingTag;
        std::vector<BlazorComponent> children;
        std::vector<BlazorParameter> parameters;
};

#endif // BLAZORCOMPONENT 

