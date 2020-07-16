#include <stylebase_structs/base_structs.hpp>

void Stylebase::to_json(nlohmann::json& j, const TypeInfo type){
        j = nlohmann::json{{"lib", type.lib}, {"component", type.component}};
    }

void Stylebase::from_json(const nlohmann::json& j, TypeInfo& type ){
    j.at("lib").get_to(type.lib);
    j.at("component").get_to(type.component);
}
