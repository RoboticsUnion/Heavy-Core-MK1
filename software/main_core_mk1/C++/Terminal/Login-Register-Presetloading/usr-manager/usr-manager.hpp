#pragma once
#include <string>
#include "../preset-manager/preset-manager.hpp"

class UserManager {
    public:
        void startup_terminal(std::string user_name);
        bool login_user(std::string user_name, std::string password); 
        void register_user(std::string user_name, std::string password, bool one_time_login); 
        bool delete_user(std::string user_name, std::string password); 

        PresetLoader presetLoader;

    private:
        // json data
        std::string db_file = "../preset-user.json"; 
};
