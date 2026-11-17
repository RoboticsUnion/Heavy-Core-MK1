#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <variant>

class DeCode {
    public:
<<<<<<< Updated upstream
        
        struct MOVE{
            int X;
            int Y;
            int Z;
            int Rx;
            int Ry;
            int Rz;
=======

        struct SET {
            std::string setting;
            int value;
        };

        struct HOME {
            int axis;
        };

        struct XSTOPX {};

        struct XENDX {};
        
        struct MOVE{
            double X;
            double Y;
            double Z;
            double Rx;
            double Ry;
            double Rz;
>>>>>>> Stashed changes

            //bool oldX = false;
            //bool oldY = false;
            //bool oldZ = false;
            //bool oldA = false;
            //bool oldB = false;
            //bool oldC = false;
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
<<<<<<< Updated upstream
=======
            std::vector<SET> set;
            std::vector<HOME> home;
            std::vector<XSTOPX> xstopx;
            std::vector<XENDX> xendx;
>>>>>>> Stashed changes
        };

        functions active_functions;

<<<<<<< Updated upstream
        using CommandResult = std::variant< // summ type
=======
        using CommandResult = std::variant<
>>>>>>> Stashed changes
            std::monostate,
            MOVE,
            ENAM,
            ENAC,
            JOINT,
            DISM,
            DISC,
            REPEAT,
<<<<<<< Updated upstream
            CHAMBER
=======
            CHAMBER,
            SET,
            HOME,
            XSTOPX,
            XENDX
>>>>>>> Stashed changes
        >;

        std::vector<CommandResult> DeCode_code_blk(std::vector<std::string> code_blk);
        std::vector<CommandResult> DeCode_code_line(std::string code_line);

    private:



};

extern DeCode de_code;