from colorama import Fore
import state

def help_txt_write(arg2):
    print(Fore.RED, "--------------------------------------")
    print(Fore.WHITE, state.g_code_write_help_txt)
    print(Fore.RED, "--------------------------------------")

def g_code_start():
    print(Fore.WHITE + " Which file do you want to start on the arm.")
    filename = input("Filename: ")

