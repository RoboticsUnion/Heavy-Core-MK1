#include "preset-manager.hpp"
#include "../../../ansi_color_chart/ansi_color_chart.hpp"
#include "../../../Terminal/Terminal-OUT/Terminal-OUT.hpp"

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

bool PresetLoader::load_user_preset(string user, string db_file){
    return true;
}