from colorama import Fore
import state
from G_Code_starter_functions import help_txt_write, g_code_start

def clear_last_line():
    # cursor up + clear line (ANSI)
    print("\033[F\033[2K", end="")


def interpret(command, arg2):
    try:
        if command in commands:
            print(Fore.GREEN, "command existing")
            commands[command](arg2)
    except Exception as e:
        print(Fore.RED, e)
        print(Fore.RESET)


commands = {
    "help": help_txt_write,
    "start": g_code_start
}


def g_starter():
    print(Fore.RED, "--------------------------------------")
    print(Fore.BLUE + " Welcome to the G-Code starter function")
    print(Fore.WHITE + " This function is exclusive for the Heavy Core Series")
    print(" Terminal-")

    while state.g_code_starter_running:
        ter_in = input(Fore.GREEN + " -")

        clear_last_line()

        if ter_in == "exit":
            print(" closing")
            state.g_code_editor_running = False
            state.console_user_running = True
            state.g_code_starter_running = False
            from console_user import main
            main()
            break

        if not ter_in.strip():
            continue

        try:
            raw = ter_in.split()
            main = raw[0]
            arg2 = raw[1:]

            interpret(main, arg2)

        except Exception as e:
            state.L1 = (state.L1 or 0) + 1
            state.L2 = (state.L2 or 0) + 1
            print(Fore.RED, e)
