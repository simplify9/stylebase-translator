#include <blazor_types/blazor_document.hpp>
#include <constants/stylebase_consts.hpp>

#include <fstream>
#include <filesystem>
#include <blazor_types/blazor_project.hpp>
#include <blazor_types/blazor_parameter.hpp>

BlazorDocument::BlazorDocument() {}

BlazorDocument::BlazorDocument(const char* name):
    name(name)
{}

BlazorDocument::BlazorDocument(const char* name, BlazorComponent comp):
    name(name), mainComponent(comp)
{}

BlazorDocument::BlazorDocument(BlazorComponent comp):
    name(comp.getName() + ".razor"), mainComponent(comp), csharp_namespace("Stylebase.Components")
{
    for(std::string lib : comp.getLibraries()){
        this->usings.emplace_back(lib);
    }
}

void BlazorDocument::writeToFile(){
    const std::string ns = "@namespace " + this->csharp_namespace;
    std::string usingStatements = "";

    for(std::string lib : mainComponent.getLibraries())
        usingStatements += "\n@using " + STYLEBASE_LIB + '.' + lib;

    std::ofstream file;

    if(BlazorProject::specifiedDir){
        bool isDirectory = std::filesystem::is_directory(BlazorProject::outputDir);
        bool exists = std::filesystem::exists(BlazorProject::outputDir);
        if(!exists || !isDirectory)
            std::filesystem::create_directory(BlazorProject::outputDir);
        file.open(BlazorProject::outputDir + '/' + name);
    }
    else file.open(name);

    file << ns << usingStatements << std::endl;
    mainComponent.streamOutput(&file);

    std::string code = "\n@code {\n";

    for(BlazorParameter param : mainComponent.getParams()){
        code += "\t[Parameter]\n";
        code += "\tpublic string " + param.getName() + " { get; set; }\n";
    }

    code += "}\n";
    file << code;


    file.close();
}


void BlazorDocument::setName(const char* name) {this->name = name;}

