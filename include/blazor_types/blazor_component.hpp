#ifndef BLAZORCOMPONENT
#define BLAZORCOMPONENT
#include <nlohmann/json.hpp>
#include "blazor_parameter.hpp"
#include "stylebase_structs/base_structs.hpp"
#include <unordered_map>
#include <vector>

class BlazorDocument;

class BlazorComponent {
    public:
        typedef BlazorComponent (*ComponentMaker)(const char*, nlohmann::json);
        typedef std::unordered_map<std::string, ComponentMaker> ComponentMap;
        static ComponentMap componentMap;

        void setName(const char* name);
        inline std::string getName() {return this->name;};

        std::vector<std::string> getLibraries();

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
        BlazorComponent(std::string tagName, Stylebase::TypeInfo type, std::vector<BlazorParameter> params = std::vector<BlazorParameter>());

        template<class StreamType>
        void streamOutput(StreamType output, int indentCount = -1, bool isParent = 1){
          for (int i = 0; i < indentCount; ++i)
            *output << '\t';

          if(!isParent) *output << this->openingTag + '\n';

          for (BlazorComponent child : this->children) {
            child.streamOutput(output, indentCount + 1, 0);
          }
          for (int i = 0; i < indentCount; ++i)
            *output << '\t';

          if(!isParent) *output << this->closingTag + '\n';
        }

        constexpr inline int getId() {return this->id;};
    private:
        int id;
        std::string name;
        std::string openingTag;
        std::string type;
        std::vector<std::string> usedLibraries;
        std::string closingTag;
        std::vector<BlazorComponent> children;
        std::vector<BlazorParameter> parameters;
};

#endif // BLAZORCOMPONENT 

