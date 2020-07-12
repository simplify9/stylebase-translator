#include <blazor_types/blazor_document.hpp>

BlazorDocument::BlazorDocument() {}

BlazorDocument::BlazorDocument(const char* name):
    name(name)
{}

BlazorDocument::BlazorDocument(const char* name, BlazorComponent comp):
    name(name), mainComponent(comp)
{}

BlazorDocument::BlazorDocument(BlazorComponent comp):
    name(comp.getName()), mainComponent(comp)
{}


void BlazorDocument::setName(const char* name) {this->name = name;}

