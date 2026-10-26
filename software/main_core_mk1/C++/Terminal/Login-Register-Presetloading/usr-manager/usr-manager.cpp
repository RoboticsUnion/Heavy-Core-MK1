#include "usr-manager.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"
#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../usr-manager/usr-manager.hpp"
#include "../logging-system/logging-system.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

#include "../nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

namespace {
    std::string resolve_database_path(const std::string& preferred_path) {
        const std::vector<std::string> candidates = {
            preferred_path,
            "../Terminal/Login-Register-Presetloading/preset-user.json"
        };

        for (const auto& candidate : candidates) {
            std::ifstream probe(candidate, std::ios::binary);
            if (probe.is_open()) {
                return candidate;
            }
        }

        // If the JSON file has not been created yet, use the location that
        // matches the current project working directory.
        std::ifstream project_root_marker("Terminal/Terminal-OUT/error_list.txt");
        if (project_root_marker.is_open()) {
            return preferred_path;
        }
        logger.log_to("[INFO] Database path resolve");
        return "../Terminal/Login-Register-Presetloading/preset-user.json";
    }

    void print_error(const std::string& key) {
        terminal_out.terminal_custom_output(
            terminal_out.terminal_error_output(key),
            ansi_color_chart::red
        );
        logger.log_to("[INFO] error output");
    }

    std::string to_lower(std::string text) {
        std::transform(text.begin(), text.end(), text.begin(), [](unsigned char c) {
            return std::tolower(c);
        });
        return text;
        logger.log_to("[INFO] string to lower");
    }
 
    bool check_database(const string& user_name, const string& password, const string& db_file, nlohmann::json& db) {
        if (user_name.empty()) {
            print_error("error_empty_username");
            return false;
        }
        if (password.empty()) {
            print_error("error_empty_password");
            return false;
        }

        std::string user_name_lower = to_lower(user_name);
        const std::string database_path = resolve_database_path(db_file);
        db = {{"users", nlohmann::json::object()}};

        std::ifstream file(database_path, std::ios::binary);
        if (file.is_open()) {
            const std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
            file.close();

            // An existing but empty file is a valid first-run state.
            if (contents.find_first_not_of(" \t\r\n") != std::string::npos) {
                try {
                    db = nlohmann::json::parse(contents);
                }
                catch (const nlohmann::json::parse_error& e) {
                    print_error("err_reading_json_login");
                    terminal_out.terminal_custom_output(
                        std::string("JSON parse details: ") + e.what(),
                        ansi_color_chart::red
                    );
                    terminal_out.terminal_custom_output("Database path: " + database_path, ansi_color_chart::red);
                    return false;
                }
            }
        }
        
        logger.log_to("[DEBUG] Database path: " + database_path);
        logger.log_to("[DEBUG] Username to find: " + user_name_lower);
        logger.log_to("[DEBUG] Loaded JSON:\n" + db.dump(4));
        logger.log_to("[DEBUG] Contains david: " + db["users"].contains("david"));

        if (!db.is_object()) {
            print_error("err_invalid_json_structure_login");
            terminal_out.terminal_custom_output("Database path: " + database_path, ansi_color_chart::red);
            return false;
        }
        if (!db.contains("users")) {
            db["users"] = nlohmann::json::object();
        }
        if (!db["users"].is_object()) {
            print_error("err_invalid_json_structure_login");
            terminal_out.terminal_custom_output("Database path: " + database_path, ansi_color_chart::red);
            return false;
        }

        if (!db["users"].contains(user_name_lower)) {
            print_error("usr_!exist");
            return false;
        }
        
        auto& user_data = db["users"][user_name_lower];

        if (!user_data.is_object() ||
            !user_data.contains("password") ||
            !user_data["password"].is_string()) {
            print_error("err_invalid_json_structure_login");
            return false;
        }

        std::string password_read = user_data["password"].get<std::string>();

        if (password_read != password) {
            print_error("wrong_pas");
            return false;
        }


        return true; // Validierung erfolgreich abgeschlossen
    }
}

void UserManager::startup_terminal(string user_name) {
    terminal_out.terminal_custom_output(UserManager::robotics_union, ansi_color_chart::blue);
    string output = "Loged user: " + user_name;
    terminal_out.terminal_custom_output(output, ansi_color_chart::white);
    logger.log_to("[INFO] Startup terminal function");
}

string UserManager::time() {
    const time_t now = std::time(nullptr);
    const tm* local_time = std::localtime(&now);
    char buffer[80] = {};

    if (local_time == nullptr || strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", local_time) == 0) {
        return "unknown";
    }
    return string(buffer);
    logger.log_to("[INFO] Time function");
}

bool UserManager::register_user(string user_name, string password) {
    if (user_name.empty()) {
        print_error("error_empty_username");
        return false;
    }
    if (password.empty()) {
        print_error("error_empty_password");
        return false;
    }

    string user_name_lower = to_lower(user_name); // fixed so every user name is written small

    const string database_path = resolve_database_path(db_file);
    json db = {{"users", json::object()}};

    ifstream file(database_path, ios::binary);
    if (file.is_open()) {
        const string contents((istreambuf_iterator<char>(file)), istreambuf_iterator<char>());
        file.close();

        // An existing but empty file is a valid first-run state.
        if (contents.find_first_not_of(" \t\r\n") != string::npos) {
            try {
                db = json::parse(contents);
            }
            catch (const json::parse_error& e) {
                print_error("err_reading_json_login");
                terminal_out.terminal_custom_output(
                    string("JSON parse details: ") + e.what(),
                    ansi_color_chart::red
                );
                terminal_out.terminal_custom_output("Database path: " + database_path, ansi_color_chart::red);
                return false;
            }
        }
    }

    if (!db.is_object()) {
        print_error("err_invalid_json_structure_login");
        terminal_out.terminal_custom_output("Database path: " + database_path, ansi_color_chart::red);
        return false;
    }
    if (!db.contains("users")) {
        db["users"] = json::object();
    }
    if (!db["users"].is_object()) {
        print_error("err_invalid_json_structure_login");
        terminal_out.terminal_custom_output("Database path: " + database_path, ansi_color_chart::red);
        return false;
    }
    if (db["users"].contains(user_name_lower)) { // fixed overwriting users
        print_error("usr_exist");
        return false;
    }

    db["users"][user_name_lower] = {
        {"password", password},
        {"created_at", time()},
        {"presets", {
            {"standard_l1_lenght", 210},
            {"standard_l2_lenght", 210},
            {"standard_l3_lenght", 210},
            {"standard_l4_lenght", 210},
            {"standard_l5_lenght", 210},
            {"standard_l6_lenght", 210},
            {"product", "####"},
            {"axis_1_speed", 50},
            {"axis_2_speed", 50},
            {"axis_3_speed", 50},
            {"axis_4_speed", 50},
            {"axis_5_speed", 50},
            {"axis_6_speed", 50}
        }}
    };

    ofstream out(database_path, ios::out | ios::trunc);
    if (!out.is_open()) {
        print_error("err_writing_json_login");
        terminal_out.terminal_custom_output("Could not open database path: " + database_path, ansi_color_chart::red);
        return false;
    }

    out << db.dump(4) << '\n';
    out.flush();
    const bool write_succeeded = out.good();
    out.close();

    if (!write_succeeded || out.fail()) {
        print_error("err_writing_json_login");
        terminal_out.terminal_custom_output("Writing failed for database path: " + database_path, ansi_color_chart::red);
        return false;
    }

    logger.log_to("[INFO] login register");
    return true;
}

bool UserManager::login_user(string user_name, string password) {
    json db;

    if(!check_database(user_name, password, db_file, db)) {
        logger.log_to("[ERROR] database/data error");
        return false;
    }

    string user_name_lower = to_lower(user_name);

    if(!presetLoader.load_user_preset(user_name_lower, db_file)){
        return false;
    }

    logger.log_to("[INFO] Login function");
    return true;

}

bool UserManager::delete_user(string user_name, string password) {
    json db;

    if (!check_database(user_name, password, db_file, db)) {
        logger.log_to("[ERROR] database/data error");
        return false;
    }

    const string user_name_lower = to_lower(user_name);
    const string database_path = resolve_database_path(db_file);

    if (db["users"].erase(user_name_lower) == 0) {
        logger.log_to("[ERROR] delete usr");
        return false;
    }

    ofstream file(database_path, ios::binary | ios::trunc);

    if (!file.is_open()) {
        print_error("err_writing_json_login");
        logger.log_to("[ERROR] err_writing_json_login");
        return false;
    }

    file << db.dump(4) << '\n';
    file.flush();

    const bool write_succeeded = file.good();
    file.close();

    if (!write_succeeded || file.fail()) {
        print_error("err_writing_json_login");
        logger.log_to("[ERROR] err_writing_json_login");
        return false;
    }

    logger.log_to("[INFO] Usr del function");
    return true;
}
