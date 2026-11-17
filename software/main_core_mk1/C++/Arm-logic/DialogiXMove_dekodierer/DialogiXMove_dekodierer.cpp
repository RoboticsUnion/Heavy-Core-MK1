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
    string join_tokens(const vector<string>& tokens, size_t start) {
        string result;

        for (size_t i = start; i < tokens.size(); i++) {
            if (!result.empty()) result += " ";
            result += tokens[i];
        }

    return result;
}

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

        if(command == "MOVE" && tokens.size() == 7) {
            DeCode::MOVE m{
                stod(tokens[1]), stod(tokens[2]), stod(tokens[3]), stod(tokens[4]),
                stod(tokens[5]), stod(tokens[6])
            };

            logger.log_to("[DialogiXMOVE] MOVE-Command");

            return m;

        } else if(command == "ENAM" && tokens.size() >= 2){
            DeCode::ENAM ea{
                join_tokens(tokens, 1)
            };

            logger.log_to("[DialogiXMOVE] ENAM-Command");

            return ea;

        } else if(command == "DISM" && tokens.size() >= 2){
            DeCode::DISM dm{
                join_tokens(tokens, 1)
            };

            logger.log_to("[DialogiXMOVE] DISM-Command");

            return dm;

        } else if(command == "DISC" && tokens.size() >= 2){
            DeCode::DISC dc{
                join_tokens(tokens, 1)
            };

            logger.log_to("[DialogiXMOVE] DISC-Command");

            return dc;

        } else if(command == "ENAC" && tokens.size() >= 2){
            DeCode::ENAC ec{
                join_tokens(tokens, 1)
            };

            logger.log_to("[DialogiXMOVE] ENAC-Command");

            return ec;

        } else if(command == "CHAMBER" && tokens.size() >= 2){
            DeCode::CHAMBER chber{
                join_tokens(tokens, 1)
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

        } else if(command == "SINGLE JOINT MOVE" && tokens.size() >= 3){
            DeCode::JOINT jn{
                stoi(tokens[1]), stoi(tokens[2])
            };

            logger.log_to("[DialogiXMOVE] JOINT-Command");

            return jn;

        } else if(command == "SET" && tokens.size() == 2){

            regex pattern(R"((\w+)\[(\d+)\])");
            smatch match;

            if (!regex_match(tokens[1], match, pattern)) {
            throw invalid_argument("Invalid SET syntax: " + tokens[1]);
            }

            DeCode::SET st{
                match[1].str(),
                stoi(match[2].str())
            };

            logger.log_to("[DialogiXMOVE] SET-Command");

            return st;

        } else if(command.rfind("HOME[", 0) == 0 && tokens.size() == 1){

            regex pattern(R"(HOME\[(\d+)\])");
            smatch match;

            if (!regex_match(command, match, pattern)) {
                throw invalid_argument("Invalid HOME syntax: " + command);
            }

            DeCode::HOME hm{
                stoi(match[1].str())
            };

            logger.log_to("[DialogiXMOVE] HOME-Command");

            return hm;

        } else if(command == "XSTOPX" && tokens.size() == 1){
            DeCode::XSTOPX xs;

            logger.log_to("[DialogiXMOVE] XSTOPX-Command");

            return xs;

        } else if(command == "XENDX" && tokens.size() == 1){
            DeCode::XENDX xe;

            logger.log_to("[DialogiXMOVE] XENDX-Command");

            return xe;

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
        else if (holds_alternative<DeCode::SET>(result))
            active_functions.set.push_back(get<DeCode::SET>(result));

        else if (holds_alternative<DeCode::HOME>(result))
            active_functions.home.push_back(get<DeCode::HOME>(result));

        else if (holds_alternative<DeCode::XSTOPX>(result))
            active_functions.xstopx.push_back(get<DeCode::XSTOPX>(result));

        else if (holds_alternative<DeCode::XENDX>(result))
            active_functions.xendx.push_back(get<DeCode::XENDX>(result));
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