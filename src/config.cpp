#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

#include "../include/config.hpp"

using json = nlohmann::json;

Config::Config()
{
    
}

Config::Config(const std::string& filename) {
    Init(filename);
}

void Config::Init(const std::string& filename) {
    loadFromFile(filename);
}

void Config::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Failed to open configuration file: " + filename);
    }

    try {
        json configJson;
        file >> configJson;
        for (auto& [key, value] : configJson.items()) {
            data[key] = value.dump(); // Store as string for simplicity
        }
    } catch (const std::exception& ex) {
        throw std::runtime_error("Error parsing JSON: " + std::string(ex.what()));
    }
}

int Config::getInt(const std::string& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return std::stoi(it->second);
    }
    throw std::runtime_error("Key not found: " + key);
}

float Config::getFloat(const std::string& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return std::stof(it->second);
    }
    throw std::runtime_error("Key not found: " + key);
}

std::string Config::getString(const std::string& key) const {
    auto it = data.find(key);
    if (it != data.end()) {
        return it->second;
    }
    throw std::runtime_error("Key not found: " + key);
}

int Config::getWindowWidth()
{
    return getInt("window_width");
}

int Config::getWindowHeight()
{
    return getInt("window_height");
}

float Config::getWindowScale()
{
    return getFloat("cell_scale");
}

int Config::getFPSLimit()
{
    return getInt("fps_limit");
}

int Config::getBirthRate()
{
    return getInt("birth_rate");
}
