from time import sleep
import state
from colorama import Fore

# ready
def password(args):
    import state
    print(Fore.RED, "--------------------------------------")
    pas = args[0]
    if pas == state.sys_password:
        print("", state.password_user)

# ready
def packet(args):
    password_u = str(args[0])
    import state
    from colorama import Fore

    print(Fore.RED, "--------------------------------------")

    if password_u == state.password_user:
        import sys
        import subprocess

        import requests

        response = requests.get("https://example.com")
        print(" Status:", response.status_code)

        pack = str(args[1])

        def ensure_package(package_name):
            try:
                try:
                    __import__(package_name)
                    print("checking package FOUND no need for install", package_name)
                    return True
                except ImportError:
                    from colorama import Fore
                    print(Fore.RESET + "package not found", package_name)
                    print(f"Library '{package_name}' Installing ...")
                    subprocess.check_call([
                        sys.executable,
                        "-m",
                        "pip",
                        "install",
                        package_name
                    ])
                    return True

            except Exception as e:
                from colorama import Fore
                print(Fore.RED + "Something went wrong:", e)

        ensure_package(pack)


    else:
        from colorama import Fore
        print(Fore.LIGHTRED_EX, Fore.RED + "Wrong Password")

# ready
def serial(args):
    password_u = str(args[1])
    set_help = str(args[0])
    from colorama import Fore

    import state
    print(Fore.RED, "--------------------------------------")
    if password_u == state.password_user:
        from colorama import Fore

        if set_help == "set":
            state.s_port1 = str(args[2])
            state.baud_rate = int(args[3])
            state.timeout = int(args[4])

            try:
                import serial
                serial.Serial(port=state.s_port1, baudrate=state.baud_rate, timeout=state.timeout)

            except Exception as e:
                print(Fore.RED + " Something went wrong:", e)

        elif set_help == "help":
            from state import ser_help_txt
            print(Fore.RED, "--------------------------------------")
            print(Fore.WHITE, ser_help_txt)
            print(Fore.RED, "--------------------------------------")


    else:
        from colorama import Fore
        print(Fore.RED + " Wrong Password")

# ready
def help_functions(args):
    from state import help_txt
    from colorama import Fore

    print(Fore.RED, "--------------------------------------")

    print(Fore.RED, "--------------------------------------")
    print(Fore.WHITE, help_txt)
    print(Fore.RED, "--------------------------------------")

# ready
def calibrate(args):
    from colorama import Fore
    import state

    print(Fore.RED, "--------------------------------------")

    set_value = str(args[0])
    password_u1 = str(args[1])

    if password_u1 == state.password_user:
        if set_value == "man":
            import state
            state.l1 = int(args[2])
            state.l2 = int(args[3])
            state.l3 = int(args[4])
            state.r1 = int(args[5])
            state.r2 = int(args[6])
            state.w1 = int(args[7])
            state.w2 = int(args[8])
            state.w3 = int(args[9])
            state.tool_x = int(args[10])
            state.tool_y = int(args[11])

            print(Fore.WHITE +
                f" Setting(length) l1 to {state.l1}mm, l2 to {state.l2}mm, l3 to {state.l3}mm, "
                f" Setting(rotate) r1 to {state.r1}°, r2 to {state.r2}°\n"
                f" Setting(angle) w1 to {state.w1}°, w2 to {state.w2}°, w3 to {state.w3}° \n"
                f" Setting(tool head) tool_x to {state.tool_x}°, tool_y to {state.tool_y}° \n"
            )
            sleep(1)
            print(" Setting finished!")

        elif set_value == "auto":
            state.l1 = int(args[2])
            state.l2 = int(args[3])
            state.l3 = int(args[4])

            print(Fore.WHITE +f" Setting l1 to {state.l1}mm, l2 to {state.l2}mm, l3 to {state.l3}mm...")
            sleep(1)
            print(" Setting finished!")

        elif set_value == "dump":
            state.l1 = state.l2 = state.l3 = state.r1 = state.r2 = state.w1 = state.w2 = state.w3 =\
                state.tool_y = state.tool_x = state.tool_length = None
            print(Fore.RED + "Values dumbed")

        elif set_value == "help":
            from state import cal_help_txt
            print(Fore.RED, "--------------------------------------")
            print(Fore.WHITE, cal_help_txt)
            print(Fore.RED, "--------------------------------------")

        elif set_value == "tl":
            state.tool_length = int(args[2])
            print(Fore.WHITE + f" Setting l1 to {state.tool_length}mm")
            sleep(1)
            print(" Setting finished!")

    else:
        print(Fore.RED, " Wrong Password")

# ready
def stats(args):
    from colorama import Fore
    print(Fore.RED, "--------------------------------------")
    print(Fore.WHITE,f"Terminal lines: {state.L2}")
    print(f" l1: {state.l1}mm, l2: {state.l2}mm, l3: {state.l3}mm")
    print(f" r1: {state.r1}°, r2: {state.r2}°")
    print(f" w1: {state.w1}°, w2: {state.w2}°, w3: {state.w3}°")
    print(f" tool_x: {state.tool_x}°, tool_y: {state.tool_y}°")
    print(f" tool_length: {state.tool_length}mm")
    print(f" Compliler name set: {state.file}")
    print(f" Arg test (args are the attributes from the main commands:")
    print(f" {args}")
    print(f" Slices Args (enter number):")
    try:
        arg_test = int(input(" ~"))
        print(args[arg_test])
    except ValueError:
        print(" Please enter a number")

# ready?
def g_code_editor(args):
    from colorama import Fore
    print(Fore.RED, "--------------------------------------")

    from colorama import Fore

    editor_mode = str(args[0])
    password_u1 = str(args[1])

    if password_u1 == state.password_user:
        if editor_mode == "help":
            print(Fore.RED, "--------------------------------------")
            print(Fore.WHITE + state.editor_help_txt)
            print(Fore.RED, "--------------------------------------")
        elif editor_mode == "write":
            state.console_user_running = False
            state.g_code_editor_running = True
            state.g_code_starter_running = False
            from G_Code_Editer import g_code_writer
            g_code_writer()
        elif editor_mode == "edit":
            state.console_user_running = False
            state.g_code_editor_running = True
            state.g_code_starter_running = False
            from G_Code_Editer import g_code_editor
            g_code_editor()
        elif editor_mode == "make":
            state.console_user_running = False
            state.g_code_editor_running = True
            state.g_code_starter_running = False
            from G_Code_Editer import g_code_file_maker
            g_code_file_maker()
        elif editor_mode == "delete":
            state.console_user_running = False
            state.g_code_editor_running = True
            state.g_code_starter_running = False
            from G_Code_Editer import g_code_deleter
            g_code_deleter()

    else:

        print(Fore.RED, " Wrong Password")



def g_code_start(args):
    print(Fore.RED, "--------------------------------------")
    password_u1 = str(args[0])

    if password_u1 == state.password_user:
        print(Fore.WHITE + " Do you want to continue? (Y/n)")
        choice = (input(" (Y/n)~"))
        if choice == "Y":
            state.console_user_running = False
            state.g_code_editor_running = False
            state.g_code_starter_running = True
            from G_Code_starter import g_starter
            g_starter()
        elif choice == "n":
            print(" Goodbye!")
        else:
            print(Fore.RED + " Please enter Y or N")
    else:
        print(Fore.RED, " Wrong Password")

