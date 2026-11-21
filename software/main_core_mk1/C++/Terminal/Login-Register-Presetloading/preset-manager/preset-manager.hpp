#pragma once
#include <string>
#include <vector>
#include <map>

class PresetLoader {
    public:
        std::string load_user_preset(std::string user, std::string preset_name); 
        bool change_user_preset(std::string user, std::string preset_name, std::string preset_value); 

        
    private:
        std::string db_file = "Terminal/Login-Register-Presetloading/preset-user.json";
};

extern PresetLoader prset_loader;