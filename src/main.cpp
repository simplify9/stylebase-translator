#include <blazor_types/blazor_component.hpp>
#include <blazor_types/blazor_document.hpp>
#include <blazor_types/blazor_project.hpp>
#include <fstream>
#include <chrono>
#include <thread>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>

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

  if(argc > 2) {
      BlazorProject::specifiedDir = true;
      BlazorProject::outputDir = argv[2];
  }

  std::cout << "Reading json template...\n" << std::flush;

  const char *sbJsonFilepath = argv[1];
  json parsedBody = getJsonFromFile(sbJsonFilepath);
  json components = parsedBody["components"];

  for (json::iterator it = components.begin(); it != components.end(); ++it) {
    BlazorProject::components.emplace_back(it.key(), it.value());
    // BlazorComponent* comp = &BlazorProject::components[BlazorProject::components.size()];
    // if (BlazorProject::componentIds.find(comp->calculateIdentity()) == BlazorProject::componentIds.end())
    //   BlazorProject::componentIds.insert({comp->calculateIdentity(), comp});
  }

  for(BlazorComponent comp : BlazorProject::components){
      BlazorProject::documents.emplace_back(comp);
  }

  std::chrono::time_point<std::chrono::high_resolution_clock> start = std::chrono::high_resolution_clock::now();

  for(BlazorDocument doc : BlazorProject::documents){
      std::cout << "Writing " << doc.getName() << "...\n";
      doc.writeToFile();
  }
  double timeElapsed = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(
          std::chrono::high_resolution_clock::now() - start
  ).count();

  std::cout << "Done. Took " << timeElapsed << " seconds" << std::endl;

  return 0;
}
