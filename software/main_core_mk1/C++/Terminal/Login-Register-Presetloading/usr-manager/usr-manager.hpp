#pragma once
#include <string>
#include "../preset-manager/preset-manager.hpp"

class UserManager {
    public:
        void startup_terminal(std::string user_name);
        bool login_user(std::string user_name, std::string password); 
        bool register_user(std::string user_name, std::string password); 
        bool delete_user(std::string user_name, std::string password); 

        std::string time();

        PresetLoader presetLoader;

    private:
    
        std::string db_file = "Terminal/Login-Register-Presetloading/preset-user.json";


        const std::string robotics_union = R"(
   ___       __        __  _           __  __     _         
  / _ \___  / /  ___  / /_(_)______   / / / /__  (_)__  ___ 
 / , _/ _ \/ _ \/ _ \/ __/ / __(_-<  / /_/ / _ \/ / _ \/ _ \
/_/|_|\___/_.__/\___/\__/_/\__/___/  \____/_//_/_/\___/_//_/
                                                            
)";

};

extern UserManager usr_manager;
