cmake_minimum_required(VERSION 3.10)
project(stylebaseTranslator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(deps/json)

add_executable(
				stylebaseTranslator 
				src/main.cpp
				src/blazor_types/blazor_component.cpp
				src/blazor_types/blazor_parameter.cpp
				src/blazor_types/blazor_document.cpp
				src/blazor_types/blazor_project.cpp
				src/stylebase_structs/base_structs.cpp
)


target_link_libraries(stylebaseTranslator PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(
				stylebaseTranslator 
				PRIVATE
				include/
)


