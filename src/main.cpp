#include <blazor_types/blazor_component.hpp>
#include <blazor_types/blazor_document.hpp>
#include <blazor_types/blazor_project.hpp>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

using json = nlohmann::json;

nlohmann::json getJsonFromFile(const char *filepath) {
  std::string line;
  std::ifstream file(filepath);
  nlohmann::json jsonTemplate;
  file >> jsonTemplate;
  return jsonTemplate;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cout << "No input found." << std::endl;
    return -1;
  }

  std::cout << "Reading json template...\n" << std::flush;

  const char *sbJsonFilepath = argv[1];
  json parsedBody = getJsonFromFile(sbJsonFilepath);
  json components = parsedBody["components"];

  std::vector<BlazorComponent> blazorComponents;

  for (json::iterator it = components.begin(); it != components.end(); ++it) {
    BlazorComponent tmp(it.key(), it.value());
    blazorComponents.emplace_back(std::move(tmp));
    if (BlazorProject::componentIds.find(tmp.getId()) != BlazorProject::componentIds.end())
      BlazorProject::componentIds.insert(
          {tmp.getId(), &blazorComponents[blazorComponents.size()]}
      );
  }

  BlazorProject::documents.reserve(blazorComponents.size());

  for (BlazorComponent comp : blazorComponents) {
    BlazorProject::documents.emplace_back(comp.getName().c_str(), comp);
  }

  std::cout << "Blazor Result:\n" << std::flush;

  for (BlazorComponent comp : blazorComponents) {
    comp.streamOutput(&std::cout);
  }

  return 0;
}
