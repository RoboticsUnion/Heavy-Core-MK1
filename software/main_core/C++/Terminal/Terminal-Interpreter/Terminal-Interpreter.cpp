#include "../Terminal-OUT/Terminal-OUT.hpp"
#include "Terminal-Interpreter.hpp"
#include "../../ansi_color_chart/ansi_color_chart.hpp"
#include <string>
#include <unordered_map>
#include <functional>
#include <list>

void output(std::string output)
{
    TerminalOUT terminalOut;
    terminalOut.terminal_custom_output(output, ansi_color_chart::white);
}

void test(std::list<std::string> arguments)
{
    output("test");
}

std::list<std::string> arguments;

std::unordered_map<std::string, std::function<void(std::list<std::string>)>> commands = {
    {"test", test}};

std::string formater(std::string input)
{
    arguments.clear();
    if (input.empty())
    {
        return "NIX"; // SCHLECHT!!!! MUSS AUSBESSERN!!!
    }

    while (!input.empty() && input.front() == ' ')
    {
        input.erase(0, 1);
    }

    size_t length = input.find("  ");
    while (length != std::string::npos)
    {
        input.erase(length, 1);
        length = input.find("  ");
    }

    std::string command;
    length = input.find_first_of(" ");
    if (length == std::string::npos)
    {
        return input;
    }
    else
    {
        command = input.substr(0, length);
        input.erase(0, length + 1);
    }

    length = input.find_first_of(" ");

    while (length != std::string::npos)
    {

        arguments.push_back(input.substr(0, length));

        input.erase(0, length + 1);
        length = input.find_first_of(" ");
    }

    if (input.length() > 0)
    {
        arguments.push_back(input);
    }

    return command;
}

void TerminalInterpreter::interpret(std::string input)
{
    std::string command = formater(input);
    auto result = commands.find(command);
    if (result != commands.end())
    {
        result->second(arguments);
    }
}
