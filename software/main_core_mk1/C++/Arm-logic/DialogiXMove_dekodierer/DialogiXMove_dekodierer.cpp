#include "DialogiXMove_dekodierer.hpp"
#include "../../ansi_color_chart/ansi_color_chart.hpp"

#include "../../Terminal/Terminal-OUT/Terminal-OUT.hpp"
#include "../../Terminal/Terminal-IN/Terminal-IN.hpp"

#include "../../Terminal/Login-Register-Presetloading/logging-system/logging-system.hpp"

#include "../../Terminal/Login-Register-Presetloading/preset-manager/preset-manager.hpp"

#include "../Serial-Data-logic/GUI-data-prep/GUI-data-prep.hpp"

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iterator>
#include <unordered_map>
#include <regex>
#include <sstream>
#include <iterator>
#include <variant>


using namespace std;

namespace{
    vector<string> split(string line){ // splits the input for handeling
        istringstream iss(line);
        vector<string> split((istream_iterator<string>(iss)), istream_iterator<string>());
        logger.log_to("[DEBUG] split function");
        return split;
    }


    DeCode::CommandResult parser(const string&line) { // parser function
        logger.log_to("parser function");
        vector<string> tokens = split(line);
        if(tokens.empty()){
            terminal_out.terminal_custom_output(terminal_out.terminal_error_output("tk_empty"), ansi_color_chart::red);
            return {};
        }
        string command = tokens[0];

        // checks which command exist

        if(command == "MOVE" && tokens.size() >= 7) {
            DeCode::MOVE m{
                stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]),
                stoi(tokens[5]), stoi(tokens[6])
            };

            logger.log_to("[DialogiXMOVE] MOVE-Command");

            return m;

        } else if(command == "ENAM" && tokens.size() >= 2){
            DeCode::ENAM ea{
                tokens[1]
            };

            logger.log_to("[DialogiXMOVE] ENAM-Command");

            return ea;

        } else if(command == "DISM" && tokens.size() >= 2){
            DeCode::DISM dm{
                tokens[1]
            };

            logger.log_to("[DialogiXMOVE] DISM-Command");

            return dm;

        } else if(command == "DISC" && tokens.size() >= 2){
            DeCode::DISC dc{
                tokens[1]
            };

            logger.log_to("[DialogiXMOVE] DISC-Command");

            return dc;

        } else if(command == "ENAC" && tokens.size() >= 2){
            DeCode::ENAC ec{
                tokens[1]
            };

            logger.log_to("[DialogiXMOVE] ENAC-Command");

            return ec;

        } else if(command == "CHAMBER" && tokens.size() >= 2){
            DeCode::CHAMBER chber{
                tokens[1]
            };

            logger.log_to("[DialogiXMOVE] CHAMBER-Command");

            return chber;

        } else if(command == "REPEAT" && tokens.size() >= 11){
            DeCode::REPEAT rep{
                stoi(tokens[1]), stoi(tokens[2]), stoi(tokens[3]), stoi(tokens[4]), stoi(tokens[5]),
                stoi(tokens[6]), stoi(tokens[7]), stoi(tokens[8]), stoi(tokens[9]), stoi(tokens[10])
            };

            logger.log_to("[DialogiXMOVE] REPEAT-Command");

            return rep;

        } else if(command == "JOINT" && tokens.size() >= 3){
            DeCode::JOINT jn{
                stoi(tokens[1]), stoi(tokens[2])
            };

            logger.log_to("[DialogiXMOVE] JOINT-Command");

            return jn;

        } else {
            logger.log_to("[DialogiXMOVE] Command does not exists");
            terminal_out.terminal_custom_output(terminal_out.terminal_error_output("DiXM_ER_!cm"), ansi_color_chart::red);

            return monostate{};
        }

    }
}

vector<DeCode::CommandResult> DeCode::DeCode_code_line(string code_line) { // functions for a  single line reused in code blk
    CommandResult result = parser(code_line);

    vector<CommandResult> single_line_vec;

    if(!holds_alternative<monostate>(result)) { // Checks which command was in line and loads values in
        single_line_vec.push_back(result);

        if (holds_alternative<DeCode::MOVE>(result)) active_functions.moves.push_back(get<DeCode::MOVE>(result));
        else if (holds_alternative<DeCode::ENAM>(result)) active_functions.enam.push_back(get<DeCode::ENAM>(result));
        else if (holds_alternative<DeCode::DISM>(result)) active_functions.dism.push_back(get<DeCode::DISM>(result));
        else if (holds_alternative<DeCode::DISC>(result)) active_functions.disc.push_back(get<DeCode::DISC>(result));
        else if (holds_alternative<DeCode::ENAC>(result)) active_functions.enac.push_back(get<DeCode::ENAC>(result));
        else if (holds_alternative<DeCode::CHAMBER>(result)) active_functions.chamber.push_back(get<DeCode::CHAMBER>(result));
        else if (holds_alternative<DeCode::REPEAT>(result)) active_functions.repeat.push_back(get<DeCode::REPEAT>(result));
        else if (holds_alternative<DeCode::JOINT>(result)) active_functions.joint.push_back(get<DeCode::JOINT>(result));
    }

    return single_line_vec;
      
}

vector<DeCode::CommandResult> DeCode::DeCode_code_blk(vector<string> code_blk) { // reuse code from single line
    vector<CommandResult> parsed_block;

    for(const auto& line : code_blk){ // saves in the vector
        auto line_vec = DeCode_code_line(line);
        if(!line_vec.empty()){
            parsed_block.push_back(line_vec[0]);
        }
    }

    return parsed_block;
}