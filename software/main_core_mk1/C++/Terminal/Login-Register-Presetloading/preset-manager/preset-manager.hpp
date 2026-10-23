#pragma once
#include <string>
#include <vector>
#include <map>

class PresetLoader {
    public:
        bool load_user_preset(std::string user, std::string db_file); 
        void reset_to_standard_user_preset(std::string user, std::string db_file);
        void change_user_preset(std::string user, std::string password, std::map<std::string, std::string> changes, std::string db_file); 

        // loaded variables
        std::map<std::string, std::string> active_presets;
};

extern PresetLoader prset_loader;