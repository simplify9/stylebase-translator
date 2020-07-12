#ifndef BLAZORDOCUMENT
#define BLAZORDOCUMENT

#include <string>
#include "blazor_component.hpp"
class BlazorDocument {
    public:
        BlazorDocument();
        BlazorDocument(const char* name);
        BlazorDocument(BlazorComponent mainComp);
        BlazorDocument(const char* name, BlazorComponent mainComp);
        inline std::string getName() {return name;};
        void setName(const char* name);
    private:
        std::string name;
        BlazorComponent mainComponent;
};


#endif // BLAZORDOCUMENT
