#include "flixel++/FlxLog.hpp"
#include <iostream>

using namespace std::literals::string_literals;

std::vector<std::string> Flx::Log::logs = std::vector<std::string>();

void Flx::Log::warn(const char* msg)
{
    std::cout << "[WARN]: " << msg << std::endl;
    logs.push_back("Warning: "s + msg);
}

void Flx::Log::error(const char* msg)
{
    std::cout << "[ERROR]: " << msg << std::endl;
    logs.push_back("Error: "s + msg);
}

const char* Flx::Log::recent(){
    #if __cpp_exceptions
    try{
        return logs.at(logs.size()).c_str();
    }
    catch(std::exception& e){
        return "No recent logs";
    }
    #else
    return "No recent logs";
    #endif
}