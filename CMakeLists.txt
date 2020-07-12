cmake_minimum_required(VERSION 3.10)
project(stylebaseTranslator)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_BUILD_TYPE DEBUG)

add_subdirectory(deps/json)

add_executable(
				stylebaseTranslator 
				src/main.cpp
				src/blazorTypes/BlazorComponent.cpp
				src/blazorTypes/BlazorParameter.cpp
				src/blazorTypes/BlazorDocument.cpp
				src/blazorTypes/BlazorProject.cpp
)


target_link_libraries(stylebaseTranslator PRIVATE nlohmann_json::nlohmann_json)

target_include_directories(
				stylebaseTranslator 
				PRIVATE
				include/
)


