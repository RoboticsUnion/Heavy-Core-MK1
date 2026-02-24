from colorama import Fore
import state

def help_txt_write(arg2):
    print(Fore.RED, "--------------------------------------")
    print(Fore.WHITE, state.g_code_write_help_txt)
    print(Fore.RED, "--------------------------------------")

from colorama import Fore, init
init()

def g_code_start(arg2):
    state.file = arg2[0]
    pas = arg2[1]
    if pas == state.password_user:
        with open(state.file, 'r') as filer:
            content = filer.read()
            print(" Do you want to compile this file?")
            print(content)
            choise = input(" Y/n")
            if choise == "Y":
                print(Fore.GREEN + " File name set. Compile file with compile[pas]")
            else:
                print(" leaving...")
    else:
        state.file = None
        print(Fore.RED + " Wrong paswort")


def g_code_compile(arg2):
    pas = arg2[0]
    if pas == state.password_user:
        print(Fore.WHITE + "Compiling...")
    else:
        print(Fore.RED + "Wrong password")


