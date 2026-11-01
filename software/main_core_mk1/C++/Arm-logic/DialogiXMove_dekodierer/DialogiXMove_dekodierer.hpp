#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <variant>

class DeCode {
    public:
        
        struct MOVE{
            int X;
            int Y;
            int Z;
            int Rx;
            int Ry;
            int Rz;
        };

        struct ENAM
        {
            std::string mot_con_nbr;
        };

        struct DISM
        {
            std::string mot_con_nbr;
        };

        struct ENAC
        {
            std::string axis_con_nbr;
        };

        struct DISC
        {
            std::string axis_con_nbr;
        };

        struct CHAMBER
        {
            std::string part;
        };

        struct JOINT
        {
            int joint_nbr;
            int joint_angle;
        };

        struct REPEAT
        {
            int X;
            int Y;
            int Z;
            int Rx;
            int Ry;
            int Rz;

            int repeat_nbr;

            int changex;
            int changey;
            int changez;
        };

        struct functions{
            std::vector<MOVE> moves;
            std::vector<ENAM> enam;
            std::vector<DISM> dism;
            std::vector<ENAC> enac;
            std::vector<DISC> disc;
            std::vector<CHAMBER> chamber;
            std::vector<JOINT> joint;
            std::vector<REPEAT> repeat;
        };

        functions active_functions;

        using CommandResult = std::variant< // summ type
            std::monostate,
            MOVE,
            ENAM,
            ENAC,
            JOINT,
            DISM,
            DISC,
            REPEAT,
            CHAMBER
        >;

        std::vector<CommandResult> DeCode_code_blk(std::vector<std::string> code_blk);
        std::vector<CommandResult> DeCode_code_line(std::string code_line);

    private:



};

extern DeCode de_code;