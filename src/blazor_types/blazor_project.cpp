#include <blazor_types/blazor_project.hpp>

std::unordered_map<int, BlazorComponent*> BlazorProject::componentIds;
std::vector<BlazorDocument> BlazorProject::documents;
std::vector<BlazorComponent> BlazorProject::components;

BlazorProject::BlazorProject() {}
