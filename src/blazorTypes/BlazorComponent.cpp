#include <blazorTypes/BlazorComponent.hpp>
#include <iostream>
#include <cstdlib>
#include <string>

constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

static BlazorComponent textComponent(nlohmann::json j){
   nlohmann::json props = j["props"];
   std::vector<BlazorParameter> params(props.size());
   for (auto it = j.items().begin(); it != j.items().end(); ++it) {
   }
   return BlazorComponent("Text", j);
}

static BlazorComponent boxComponent(nlohmann::json j){
   nlohmann::json props = j["props"];
   std::vector<BlazorParameter> params(props.size());
   for (auto it = j.items().begin(); it != j.items().end(); ++it) {
   }
   return BlazorComponent("Box", j);
}

BlazorComponent::ComponentMap BlazorComponent::componentMap{
    {"Text", &textComponent},
    {"Box", &boxComponent},
};

BlazorComponent::BlazorComponent(): id(rand()) {}

void BlazorComponent::streamOutput(std::ostream* output, int indentCount){
    for(int i = 0; i < indentCount; ++i)
        std::cout << '\t';
    *output << this->openingTag + '\n';
    for(BlazorComponent child : this->children){
        child.streamOutput(output, indentCount + 1);
    }
    for(int i = 0; i < indentCount; ++i)
        std::cout << '\t';
    *output << this->closingTag + '\n';
}

BlazorComponent::BlazorComponent(std::string tname,
     std::vector<BlazorParameter> params,
     nlohmann::json children):
     openingTag('<' + tname + '>'), closingTag("</" + tname + '>'),
     id(rand()), parameters(params), children(children.size()) {
  for (auto child = children.items().begin(); child != children.items().end(); ++child)
    this->children.emplace_back(child.key(), child.value());
}

BlazorComponent::BlazorComponent(std::string name, nlohmann::json component):
    openingTag('<' + name + '>'), closingTag("<\\" + name + '>'), id(rand())
{
    nlohmann::json elemRoot = component["elements"][name].is_null() ?
                              component["elements"]["root"] : component["elements"][name];
    if(!elemRoot["props"]["children"].is_array()) return;
    std::vector<std::string> children = elemRoot["props"]["children"]
                                        .get<std::vector<std::string>>();

    for(std::string child : children) {
        nlohmann::json childJson = component["elements"][child];
        std::string childType = childJson["type"]["component"].get<std::string>();
        auto mapFind = BlazorComponent::componentMap.find(childType);
        if(mapFind != BlazorComponent::componentMap.end()){
            //TODO: check document for existing definitions of this elem
            //this->children.emplace_back(mapFind->second(component));
        }
        else {
            this->children.emplace_back(child, component);
        }
    }
}

void BlazorComponent::setName(const char* name){
    this->name = name;
}
