#include <blazorTypes/BlazorComponent.hpp>
#include <iostream>
#include <string>

constexpr unsigned int str2int(const char *str, int h = 0) {
  return !str[h] ? 5381 : (str2int(str, h + 1) * 33) ^ str[h];
}

const BlazorComponent::ComponentMap BlazorComponent::componentMap{
    {"Text",
     [](nlohmann::json j) -> BlazorComponent {
       nlohmann::json props = j["props"];
       std::vector<BlazorParameter> params(props.size());
       for (auto it = j.items().begin(); it != j.items().end(); ++it) {
       }
       return BlazorComponent("Text", params, props["children"]);
     }},
    {"Box",
     [](nlohmann::json j) -> BlazorComponent {
       nlohmann::json props = j["props"];
       std::vector<BlazorParameter> params(props.size());
       for (auto it = j.items().begin(); it != j.items().end(); ++it) {
       }
       return BlazorComponent("Box", params, props["children"]);
     }},

};

BlazorComponent::BlazorComponent() {}

void BlazorComponent::streamOutput(std::ostream* output){
    *output << '\t' + this->openingTag + '\n';
    for(BlazorComponent child : this->children)
        child.streamOutput(output);
    *output << '\t' + this->closingTag + '\n';
}

BlazorComponent::BlazorComponent(std::string tname,
     std::vector<BlazorParameter> params,
     nlohmann::json children):
     openingTag('<' + tname + '>'), closingTag("<\\" + tname + '>'),
     parameters(params), children(children.size()) {
  for (auto child = children.items().begin(); child != children.items().end(); ++child)
    this->children.emplace_back(child.key(), child.value());
}

BlazorComponent::BlazorComponent(std::string name, nlohmann::json component):
    openingTag('<' + name + '>'), closingTag("<\\" + name + '>')
{
    nlohmann::json childrenJson = component["elements"]["props"]["children"];
    this->children.reserve(childrenJson.size());
    for(auto child = childrenJson.items().begin(); child != childrenJson.items().end(); ++child){
        nlohmann::json childVal = component["elements"][child.key()];
        std::string childType = (std::string)childVal["type"]["component"];
        if(BlazorComponent::componentMap.count(childType.c_str()) == 1){
            std::function<BlazorComponent(nlohmann::json)> func = 
                BlazorComponent::componentMap.find(child.key().c_str())->second;
            this->children.emplace_back(func(child.value()));
        }
        else {
            this->children.emplace_back(child.key(), childVal);
        }
    }
}
