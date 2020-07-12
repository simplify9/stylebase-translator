#include <blazorTypes/BlazorDocument.hpp>

BlazorDocument::BlazorDocument() {}

BlazorDocument::BlazorDocument(const char* name):
    name(name)
{}

BlazorDocument::BlazorDocument(const char* name, BlazorComponent comp):
    name(name), mainComponent(comp)
{}


void BlazorDocument::setName(const char* name) {this->name = name;}

inline std::string BlazorDocument::getName() {return name;} 

