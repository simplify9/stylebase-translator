#ifndef BLAZORPROJECT
#define BLAZORPROJECT

#include <vector>
#include <blazorTypes/BlazorComponent.hpp>

class BlazorProject {
    public:
        static std::unordered_map<int, BlazorComponent*> componentIds;
        static std::vector<BlazorDocument> documents;
        BlazorProject();
    private:
};

#endif // BLAZORPROJECT
