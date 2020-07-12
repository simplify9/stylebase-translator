#include <blazorTypes/BlazorProject.hpp>

std::unordered_map<int, BlazorComponent*> BlazorProject::componentIds;
std::vector<BlazorDocument> BlazorProject::documents;

BlazorProject::BlazorProject() {}
