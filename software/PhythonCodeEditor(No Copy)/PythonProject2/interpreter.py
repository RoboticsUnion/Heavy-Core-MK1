from functions import packet, password, serial, help_functions, calibrate, stats, g_code_editor, g_code_start
from colorama import Fore

def interpret(command, args):
    try:
        if command in commands:
            print(Fore.GREEN, "command existing")
            commands[command](args)
    except Exception as e:
        print(Fore.RED,e)
        print(Fore.RESET)


commands = {
    "pip":packet,
    "pas":password,
    "ser":serial,
    "help":help_functions,
    "cal":calibrate,
    "stat":stats,
    "g-e":g_code_editor,
    "g-s":g_code_start
}
