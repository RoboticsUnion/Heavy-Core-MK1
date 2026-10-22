#include "logging-system.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"
#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../Login-Register-Presetloading/usr-manager/usr-manager.hpp"

#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

using namespace std;

string Logging::log_to(string contents) {
    UserManager usr_manager;
    ofstream output_file(Logging::log_txt_path);
    ostream_iterator<string> output_iterator(output_file, "\n");
    string time_stamp = usr_manager.time();
    string log_final = time_stamp,contents;
    copy(contents.begin(), contents.end(), log_final);

}