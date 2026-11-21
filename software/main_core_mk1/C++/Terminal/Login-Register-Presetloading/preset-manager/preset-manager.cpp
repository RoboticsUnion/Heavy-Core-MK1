#include "preset-manager.hpp"
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
}

string PresetLoader::load_user_preset(std::string user, std::string preset_name) {
    logger.log_to("[INFO] Load user preset function");
    json db;
    const string database_path = resolve_database_path(db_file);
    std::ifstream file(database_path, std::ios::binary);
    if (file.is_open()) {
        const string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();
        try {
            db = json::parse(contents);
        }
        catch (const json::parse_error& e) {
            print_error("err_reading_json_preset");
            return "";
        }
    }

    const string user_lower = to_lower(user);
    if (db.contains("users") && db["users"].contains(user_lower) && db["users"][user_lower].contains("presets")) {
        const auto& presets_json = db["users"][user_lower]["presets"];

        if (presets_json.contains(preset_name)) {
            logger.log_to("[INFO] Preset loaded");
            
            
            if (presets_json[preset_name].is_string()) {
                return presets_json[preset_name].get<std::string>();
            }
            
            return presets_json[preset_name].dump();
        }
    }

    return ""; // Return an empty string if the user or preset is not found
}

bool PresetLoader::change_user_preset(std::string user, std::string preset_name, std::string preset_value) {
    logger.log_to("[INFO] Change user preset function");
    json db;
    const std::string database_path = resolve_database_path(db_file);
    std::ifstream file(database_path, std::ios::binary);
    if (!file.is_open()) {
        print_error("err_reading_json_preset");
        logger.log_to("[INFO] Failed to open database file");
        return false;
    }

    const std::string contents((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    file.close();
    try {
        db = json::parse(contents);
    }
    catch (const json::parse_error& e) {
        print_error("err_reading_json_preset");
        logger.log_to("[INFO] Failed to parse JSON");
        return false;
    }

    const std::string user_lower = to_lower(user);
    if (db.contains("users") && db["users"].contains(user_lower) && db["users"][user_lower].contains("presets")) {
        auto& presets = db["users"][user_lower]["presets"];

        
        if (presets.contains(preset_name) && presets[preset_name].is_number_integer()) {
            presets[preset_name] = std::stoi(preset_value);
            logger.log_to("[INFO] Preset changed to integer");
        } else if (presets.contains(preset_name) && presets[preset_name].is_number_float()) {
            presets[preset_name] = std::stod(preset_value);
            logger.log_to("[INFO] Preset changed to float");
        } else {
            presets[preset_name] = preset_value;
            logger.log_to("[INFO] Preset changed to string");
        }

        std::ofstream out(database_path, std::ios::out | std::ios::trunc);
        if (!out.is_open()) {
            print_error("err_writing_json_preset");
            logger.log_to("[INFO] Failed to open database file for writing");
            return false;
        }

        out << db.dump(4) << '\n';
        out.flush();
        const bool write_succeeded = out.good();
        out.close();

        if (!write_succeeded || out.fail()) {
            print_error("err_writing_json_preset");
            logger.log_to("[INFO] Failed to write to database file");
            return false;
        }

        return true;
    }

    return false; // User oder "presets" nicht gefunden
}
