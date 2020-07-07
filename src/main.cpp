#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <nlohmann/json.hpp>
#include <blazorTypes/BlazorComponent.hpp>


using json = nlohmann::json;

nlohmann::json getJsonFromFile(const char* filepath){
    std::string line;
    std::ifstream file(filepath);
    nlohmann::json jsonTemplate;
    file >> jsonTemplate;
    return jsonTemplate;
}


int main(int argc, char** argv){
    if(argc < 2){
        std::cout << "No input found." << std::endl;
        return -1;
    }

    std::cout << "Reading json template...\n" << std::flush;

    const char* sbJsonFilepath = argv[1];
    json parsedBody = getJsonFromFile(sbJsonFilepath);
    json components = parsedBody["components"];
    std::vector<BlazorComponent> blazorComponents;

    for(json::iterator it = components.begin(); it != components.end(); ++it){
        blazorComponents.emplace_back(it.key(), it.value());
    }

    std::cout << "Blazor Result:\n" << std::flush;

    for(BlazorComponent comp : blazorComponents){
        comp.streamOutput(&std::cout);
    }

    

    return 0;

    
}
