#ifndef BlazorParameterType
#define BlazorParameterType value

class BlazorParameterType {
    public:
        BlazorParameterType();
        BlazorParameterType(const char* typeName, bool isArray);
    private:
        const char* typeName;
        bool isArray;
};
#endif /* ifndef BlazorParameterType */
