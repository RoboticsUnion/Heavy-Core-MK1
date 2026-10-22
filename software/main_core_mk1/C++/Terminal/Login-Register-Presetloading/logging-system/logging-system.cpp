#include "../../../ansi_color_chart/ansi_color_chart.hpp"
#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"

#include "logging-system.hpp"
Logging logger;
#include "../usr-manager/usr-manager.hpp"

#include <fstream>
#include <string>

using namespace std;

namespace{
    void print_error(const std::string& key) {
        terminal_out.terminal_custom_output(
        terminal_out.terminal_error_output(key),
        ansi_color_chart::red
        );
        logger.log_to("[INFO] error output");
    }
}


string Logging::log_to(string contents)
{
    UserManager usr_manager;

    ofstream output_file(log_txt_path, ios::app);

    if (!output_file.is_open()) {
        print_error("!log_open");
        return "ERROR: Could not open log file.";
    }

    string time_stamp = usr_manager.time();

    string log_final = "[" + time_stamp + "] " + contents;

    output_file << log_final << '\n';

    if (!output_file.good()) {
        print_error("!write_log");
        return "ERROR: Could not write to log file.";
    }

    return "OK";
}
