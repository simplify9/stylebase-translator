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
       //return BlazorComponent("Text", params, props["children"]);
       return BlazorComponent("Text", j);
     }},
    {"Box",
     [](nlohmann::json j) -> BlazorComponent {
       nlohmann::json props = j["props"];
       std::vector<BlazorParameter> params(props.size());
       for (auto it = j.items().begin(); it != j.items().end(); ++it) {
       }
       return BlazorComponent("Box", j);
       //return BlazorComponent("Box", params, props["children"]);
     }},

};

BlazorComponent::BlazorComponent() {}

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
     openingTag('<' + tname + '>'), closingTag("<\\" + tname + '>'),
     parameters(params), children(children.size()) {
  for (auto child = children.items().begin(); child != children.items().end(); ++child)
    this->children.emplace_back(child.key(), child.value());
}

BlazorComponent::BlazorComponent(std::string name, nlohmann::json component):
    openingTag('<' + name + '>'), closingTag("<\\" + name + '>')
{
    nlohmann::json elemRoot = component["elements"][name].is_null() ?
                              component["elements"]["root"] : component["elements"][name];
    if(!elemRoot["props"]["children"].is_array()) return;
    std::vector<std::string> children = elemRoot["props"]["children"]
                                        .get<std::vector<std::string>>();
    for(std::string child : children) {
        nlohmann::json childJson = component["elements"][child];
        std::string childType = childJson["type"]["component"].get<std::string>();
        if(BlazorComponent::componentMap.count(childType.c_str()) == 1){
            std::function<BlazorComponent(nlohmann::json)> func = 
                BlazorComponent::componentMap.find(child.c_str())->second;
            this->children.emplace_back(func(childJson));
        }
        else {
            this->children.emplace_back(child, component);
        }
    }
}
