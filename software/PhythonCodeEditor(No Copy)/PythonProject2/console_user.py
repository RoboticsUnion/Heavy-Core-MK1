import state
state.L1 = 0
state.L2 = 0


console_user_running = True

from interpreter import interpret
from colorama import Fore

def clear_last_line():
    # cursor up + clear line (ANSI)
    print("\033[F\033[2K", end="")

def main():
    print(Fore.RED, "--------------------------------------")
    print(Fore.BLUE + " Main Started!")
    import state

    while state.console_user_running:
        import state
        print(Fore.RESET, "->")

        raw = input(Fore.WHITE + " ~")

        clear_last_line()

        full_command = raw.split()
        raw = None

        try:

            command = full_command[0]
            args = full_command[1:]

            interpret(command, args)

            for i in range(len(args)):
                args[i] = None

            state.L2 = state.L2 +1

            if command == "exit":
                print(" closing")
                state.g_code_editor_running = False
                state.console_user_running = False
                state.g_code_starter_running = False
                break

        except IndexError:
            state.L1 = state.L1 + 1
            state.L2 = state.L2 + 1
