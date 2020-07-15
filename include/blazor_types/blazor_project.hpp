#ifndef BLAZORPROJECT
#define BLAZORPROJECT

#include <vector>
#include "blazor_component.hpp"
#include "blazor_document.hpp"

class BlazorProject {
    public:
        static std::unordered_map<int, BlazorComponent*> componentIds;
        static std::vector<BlazorDocument> documents;
        static std::vector<BlazorComponent> components;
        BlazorProject();
    private:
};

#endif // BLAZORPROJECT
