import state
from colorama import Fore

#ready?
def g_code_writer():
    print(Fore.RED, "--------------------------------------")
    x = 1
    filename = input(Fore.WHITE + " Enter file name: ")
    while state.g_code_editor_running:

        line_text = input(f" {x}")

        if line_text.lower() == "exit":
            state.g_code_editor_running = False
            state.console_user_running = True
            state.g_code_starter_running = False
            from console_user import main
            main()

        def write_to_line(line_number, text):


            with open(filename, "r") as file:
                lines = file.readlines()

            while len(lines) < line_number:
                lines.append("\n")

            lines[line_number - 1] = text + "\n"

            with open(filename, "w") as file:
                file.writelines(lines)

        write_to_line(x, line_text)
        x = x + 1

#ready?
def g_code_editor():
    print(Fore.RED, "--------------------------------------")
    import os

    filename = input(Fore.WHITE + " File name for editing: ")

    if not os.path.exists(filename):
        print(f" No file name: {filename} exists.")
        state.g_code_editor_running = False
        state.console_user_running = True
        state.g_code_starter_running = False
        from console_user import main
        main()

    while state.g_code_editor_running:
        choice = input("\n Type 'edit' to edit a line, 'show' to view file, 'exit' to quit: ").lower()

        if choice == "exit":
            print(" Editor closed")
            state.g_code_editor_running = False
            state.console_user_running = True
            state.g_code_starter_running = False
            from console_user import main
            main()
            break
        elif choice == "show":
            with open(filename, "r") as f:
                lines = f.readlines()
            if not lines:
                print(" File is empty")
            else:
                for i, line in enumerate(lines, start=1):
                    print(f"{i}: {line.rstrip()}")
        elif choice == "edit":
            with open(filename, "r") as f:
                lines = f.readlines()

            if not lines:
                print(" File is empty, will create lines automatically.")

            try:
                line_num = int(input(" Which line do you want to edit? "))
            except ValueError:
                print(Fore.RED + " Please enter a valid number")
                continue

            while len(lines) < line_num:
                lines.append("\n")

            new_text = input(" New text: ")
            lines[line_num - 1] = new_text + "\n"

            with open(filename, "w") as f:
                f.writelines(lines)

            print(Fore.GREEN + f" Line {line_num} updated!")
        else:
            print(" Invalid choice, type 'edit', 'show', or 'exit'")

#ready?
def g_code_file_maker():
    print(Fore.RED, "--------------------------------------")
    filename = input(Fore.WHITE + " Enter file name: ")

    with open(filename, "a") as file:
        pass

    print(" File made")

    state.g_code_editor_running = False
    state.console_user_running = True
    state.g_code_starter_running = False
    from console_user import main
    main()

#ready?
def g_code_deleter():
    print(Fore.RED, "--------------------------------------")
    import os

    filename = input(Fore.WHITE + " Which file do you want to delete: ")

    if os.path.exists(filename):
        os.remove(filename)
        print(f" {filename} deleted!")
    else:
        print(Fore.RED + f" {filename} not found.")

    state.g_code_editor_running = False
    state.console_user_running = True
    state.g_code_starter_running = False
    from console_user import main
    main()









