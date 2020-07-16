#ifndef BLAZOR_ELEMENT
#define BLAZOR_ELEMENT value

#include <string>

class BlazorElement {
    public:
        BlazorElement();
    private:
        std::string name;
        std::string openingTag;
        std::string closingTag;
};

#endif /* ifndef BLAZOR_ELEMENT */
