from colorama import Fore
import state
import pasword_gen_sys
import getpass
from pathlib import Path
import os

print(r"""
 ____ ___      .__                   _________       _____  __                                                                           
│    │   ╲____ │__│ ____   ____     ╱   _____╱ _____╱ ____╲╱  │___  _  _______ _______   ____                                            
│    │   ╱    ╲│  │╱  _ ╲ ╱    ╲    ╲_____  ╲ ╱  _ ╲   __╲╲   __╲ ╲╱ ╲╱ ╱╲__  ╲╲_  __ ╲_╱ __ ╲                                           
│    │  ╱   │  ╲  (  <_> )   │  ╲   ╱        (  <_> )  │   │  │  ╲     ╱  ╱ __ ╲│  │ ╲╱╲  ___╱                                           
│______╱│___│  ╱__│╲____╱│___│  ╱  ╱_______  ╱╲____╱│__│   │__│   ╲╱╲_╱  (____  ╱__│    ╲___  >                                          
             ╲╱               ╲╱           ╲╱                                 ╲╱            ╲╱                                           
   _____   ____  __.    ___ ___                               _________                           _________            .__               
  ╱     ╲ │    │╱ _│   ╱   │   ╲   ____ _____ ___  _____.__.  ╲_   ___ ╲  ___________   ____     ╱   _____╱ ___________│__│ ____   ______
 ╱  ╲ ╱  ╲│      <    ╱    ~    ╲_╱ __ ╲╲__  ╲╲  ╲╱ <   │  │  ╱    ╲  ╲╱ ╱  _ ╲_  __ ╲_╱ __ ╲    ╲_____  ╲_╱ __ ╲_  __ ╲  │╱ __ ╲ ╱  ___╱
╱    Y    ╲    │  ╲   ╲    Y    ╱╲  ___╱ ╱ __ ╲╲   ╱ ╲___  │  ╲     ╲___(  <_> )  │ ╲╱╲  ___╱    ╱        ╲  ___╱│  │ ╲╱  ╲  ___╱ ╲___ ╲ 
╲____│__  ╱____│__ ╲   ╲___│_  ╱  ╲___  >____  ╱╲_╱  ╱ ____│   ╲______  ╱╲____╱│__│    ╲___  >  ╱_______  ╱╲___  >__│  │__│╲___  >____  >
        ╲╱        ╲╱         ╲╱       ╲╱     ╲╱      ╲╱               ╲╱                   ╲╱           ╲╱     ╲╱              ╲╱     ╲╱
""")

print(" This is your folder now is it right?: ")
print(os.getcwd())


def startup_fc():
    folder_name = input(Fore.GREEN + " Pleas enter your specific folder with the code!: ").strip()

    if not os.path.isdir(folder_name):
        print(Fore.RED + " Folder not found.")
        return False

    os.chdir(folder_name)

    files = [
        "console_user.py",
        "functions.py",
        "G_Code_Editer.py",
        "G_Code_starter_functions.py",
        "G_Code_starter.py",
        "interpreter.py",
        "pasword_gen_sys.py",
        "Startup.py",
        "state.py",
        "the_great_kinematics.py",
        "UI_handler.py",
    ]

    print(Fore.GREEN + " Searching Files...")

    if any(not Path(f).exists() for f in files):
        print(Fore.RED + " Attention .py file is not existing E:0001")
        return False

    print(Fore.GREEN + " All .py file are here...")
    print(Fore.LIGHTRED_EX + " Welcome User")

    pasword_gen_sys.sys_pas()
    state.password_user = getpass.getpass(" Enter your password: ")

    print(Fore.BLUE + " Starting MK1 Software")

    state.console_user_running = True
    state.g_code_editor_running = False

    from console_user import main
    main()
    return True


# ---- Start ----
try:
    ok = startup_fc()

    if not ok:
        choice = input("Do you want to start without?: ").strip().lower()
        if choice == "y":
            print(Fore.LIGHTRED_EX + " Welcome User")

            pasword_gen_sys.sys_pas()
            state.password_user = getpass.getpass(" Enter your password: ")

            print(Fore.BLUE + " Starting MK1 Software")

            state.console_user_running = True
            state.g_code_editor_running = False

            from console_user import main
            main()
        else:
            startup_fc()

except Exception as e:
    print(Fore.RED + str(e))