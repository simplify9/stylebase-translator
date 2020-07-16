#include <blazor_types/blazor_component.hpp>
#include <blazor_types/blazor_project.hpp>
#include <cstdlib>
#include <iostream>
#include <string>
#include <stylebase_structs/base_structs.hpp>

static BlazorComponent textComponent(const char *elemName, nlohmann::json j) {
  nlohmann::json props = j["props"];
  std::vector<BlazorParameter> params(props.size());
  for (auto it = j.items().begin(); it != j.items().end(); ++it) {
  }
  return BlazorComponent("Text", j, elemName);
}

static BlazorComponent boxComponent(const char *elemName, nlohmann::json j) {
  nlohmann::json props = j["props"];
  std::vector<BlazorParameter> params(props.size());
  for (auto it = j.items().begin(); it != j.items().end(); ++it) {
  }
  return BlazorComponent("Box", j, elemName);
}

BlazorComponent::ComponentMap BlazorComponent::componentMap{
    {"boxes:Text", &textComponent},
    {"boxes:Box", &boxComponent},
};

BlazorComponent::BlazorComponent() : id(rand()) {}

void BlazorComponent::streamOutput(std::ostream *output, int indentCount) {
  for (int i = 0; i < indentCount; ++i)
    std::cout << '\t';
  *output << this->openingTag + '\n';
  for (BlazorComponent child : this->children) {
    child.streamOutput(output, indentCount + 1);
  }
  for (int i = 0; i < indentCount; ++i)
    std::cout << '\t';
  *output << this->closingTag + '\n';
}

std::vector<BlazorParameter> blazorParamsFromJson(nlohmann::json *_props) {
  nlohmann::json props = *_props;
  std::vector<BlazorParameter> params(props.size());
  return params;
}

inline BlazorComponent::ComponentMaker getCompMapFunc(std::string e) {
  auto it = BlazorComponent::componentMap.find(e);
  if (it != BlazorComponent::componentMap.end())
    return it->second;
  return nullptr;
}


BlazorComponent::BlazorComponent(std::string tname, Stylebase::TypeInfo typeInfo,
                                 std::vector<BlazorParameter> params)
    : id(rand()), parameters(params), type(typeInfo.lib + ':' + typeInfo.component) {
        ComponentMaker maker = getCompMapFunc(typeInfo.lib+':'+typeInfo.component);
        if(maker != nullptr){
            this->openingTag = '<' + typeInfo.component + '>'; 
            this->closingTag = "<\\" + typeInfo.component + '>';
        }
    }

BlazorComponent::BlazorComponent(std::string name, nlohmann::json component,
                                 std::string elementName)
    : name(name), openingTag('<' + name + '>'), closingTag("<\\" + name + '>'),
      id(rand()), type("Wrapper") {

  nlohmann::json innerElems = component["elements"];
  nlohmann::json rootElem = innerElems["root"];

  this->children.emplace_back("root", rootElem["type"].get<Stylebase::TypeInfo>());
  BlazorComponent* rootComp = &this->children[children.size()];

  for (auto it = innerElems.begin(); it != innerElems.end(); ++it) {
    if (it.key() == "root") {
      continue;
    } else {
        rootComp->children.emplace_back(it.key(), rootElem["type"].get<Stylebase::TypeInfo>());
    }
  }
}

void BlazorComponent::setName(const char *name) { this->name = name; }
