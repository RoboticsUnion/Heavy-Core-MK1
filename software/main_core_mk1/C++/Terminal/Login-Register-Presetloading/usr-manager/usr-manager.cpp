#include "usr-manager.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"
#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

#include "../nlohmann/json.hpp"
using json = nlohmann::json;
using namespace std;

namespace {
    string resolve_database_path(const string& preferred_path) {
        const vector<string> candidates = {
            preferred_path,
            "../Terminal/Login-Register-Presetloading/preset-user.json"
        };

        for (const auto& candidate : candidates) {
            ifstream probe(candidate, ios::binary);
            if (probe.is_open()) {
                return candidate;
            }
        }

        // If the JSON file has not been created yet, use the location that
        // matches the current project working directory.
        ifstream project_root_marker("Terminal/Terminal-OUT/error_list.txt");
        if (project_root_marker.is_open()) {
            return preferred_path;
        }
        return "../Terminal/Login-Register-Presetloading/preset-user.json";
    }

    void print_error(const string& key) {
        terminal_out.terminal_custom_output(
            terminal_out.terminal_error_output(key),
            ansi_color_chart::red
        );
    }
}

void UserManager::startup_terminal(string user_name) {
    terminal_out.terminal_custom_output(UserManager::robotics_union, ansi_color_chart::blue);
    string output = "Loged user: " + user_name;
    terminal_out.terminal_custom_output(output, ansi_color_chart::white);
}

string UserManager::time() {
    const time_t now = std::time(nullptr);
    const tm* local_time = std::localtime(&now);
    char buffer[80] = {};

    if (local_time == nullptr || strftime(buffer, sizeof(buffer), "%d-%m-%Y %H:%M:%S", local_time) == 0) {
        return "unknown";
    }
    return string(buffer);
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

    db["users"][user_name] = {
        {"password", password},
        {"created_at", time()},
        {"presets", {
            {"standard_l1_lenght", 210},
            {"standard_l2_lenght", 210},
            {"standard_l3_lenght", 210},
            {"standard_l4_lenght", 210},
            {"standard_l5_lenght", 210},
            {"standard_l6_lenght", 210}
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

    return true;
}
