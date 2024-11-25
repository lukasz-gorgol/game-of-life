#pragma once

#include <string>
#include <unordered_map>

class Config {
public:
    Config();
    Config(const std::string& filename);
    void Init(const std::string& filename);

    int getWindowWidth();
    int getWindowHeight();
    float getWindowScale();
    int getFPSLimit();
    int getBirthRate();

protected:
    int getInt(const std::string& key) const;
    float getFloat(const std::string& key) const;
    std::string getString(const std::string& key) const;

private:
    std::unordered_map<std::string, std::string> data;
    void loadFromFile(const std::string& filename);
};
