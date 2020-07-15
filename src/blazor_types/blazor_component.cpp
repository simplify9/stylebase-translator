#include <iostream>
#include <cstdlib>
#include <string>
#include <blazor_types/blazor_component.hpp>
#include <blazor_types/blazor_project.hpp>

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

std::vector<BlazorParameter> blazorParamsFromJson(nlohmann::json* _props){
    nlohmann::json props = *_props;
    std::vector<BlazorParameter> params(props.size());
    return params;
}

BlazorComponent::BlazorComponent(std::string tname,
     std::vector<BlazorParameter> params,
     nlohmann::json children):
     openingTag('<' + tname + '>'), closingTag("</" + tname + '>'),
     id(rand()), parameters(params), children(children.size()) {
  for (auto child = children.items().begin(); child != children.items().end(); ++child)
    this->children.emplace_back(child.key(), child.value());
}

BlazorComponent::BlazorComponent(std::string name, nlohmann::json component, std::string elementName):
    name(name), openingTag('<' + name + '>'), closingTag("<\\" + name + '>'), id(rand())
{
    //TODO:
    // 1. Let component map return a component to borrow from
    // 2. Construct the component as normal, but attach borrowed elements before emplacing
    nlohmann::json focusedElem = component["elements"][elementName];
    nlohmann::json* compProps = &focusedElem["props"];
    nlohmann::json* compTypeInfo = &focusedElem["type"];

    this->parameters = blazorParamsFromJson(compProps);
    nlohmann::json children = (*compProps)["children"];
    if(children.is_array()){
        this->children.reserve((*compProps)["children"].size());
        for(std::string child : (*compProps)["children"].get<std::vector<std::string>>()){
            this->children.emplace_back(child, component, child);
        }
    }

}

void BlazorComponent::setName(const char* name){
    this->name = name;
}
