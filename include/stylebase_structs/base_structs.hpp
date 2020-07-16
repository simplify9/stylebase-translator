#ifndef BASE_STRUCTS
#define BASE_STRUCTS 

#include <string>
#include <nlohmann/json.hpp>


namespace Stylebase {
    struct TypeInfo {
        std::string component;
        std::string lib;
        TypeInfo() {}
        TypeInfo(const char* component, const char* lib):
            component(component), lib(lib) {}
    };
    void to_json(nlohmann::json& j, const TypeInfo type);
    void from_json(const nlohmann::json& j, TypeInfo& type );
}

#endif /* ifndef BASE_STRUCTS */

