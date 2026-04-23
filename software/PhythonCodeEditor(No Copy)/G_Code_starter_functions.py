from colorama import Fore, init
import re
import os
import state

init()


def set_file(arg2):
    pas = arg2[0]
    state.file = arg2[1]
    if pas == state.password_user:
        print(" Set file name")
    else:
        print(" Wrong paswort")
        state.file = None

def validate_gcode(arg2):

    pas = arg2[0]

    if pas != state.password_user:
        print(Fore.RED + "Error: Wrong password")
        return {"ok": False, "errors": ["Error: Wrong password"]}

    print("Compiling...")

    COMMANDS = {
        "G0": ["X", "Y", "Z"],
        "G1": ["X", "Y", "Z", "F"],
        "G78": ["X", "Y", "F", "S"]
    }

    errors = []

    path = state.file

    print("Looking for file:", path)
    print("Exists:", os.path.exists(path))

    try:
        with open(path, "r") as f:
            lines = f.readlines()
    except Exception as e:
        print(Fore.RED + f"File error: {e}")
        return {"ok": False, "errors": [f"File error: {e}"]}

    print("Lines read:", len(lines))

    for line_number, line in enumerate(lines, start=1):
        original_line = line
        line = line.strip().upper()

        print(f"LINE {line_number}: '{line}'")

        line = re.sub(r"\(.*?\)", "", line)
        line = line.split(";")[0]

        if not line:
            continue

        parts = line.split()
        cmd = parts[0]

        
        if cmd not in COMMANDS:
            err_msg = f"Line {line_number}: Unknown command '{cmd}'"
            print(Fore.RED + err_msg)
            errors.append(err_msg)
            continue

        allowed = COMMANDS[cmd]

        
        for part in parts[1:]:
            if len(part) < 2:
                err_msg = f"Line {line_number}: Invalid parameter '{part}'"
                print(Fore.RED + err_msg)
                errors.append(err_msg)
                continue

            key = part[0]

            try:
                value = float(part[1:])
            except:
                err_msg = f"Line {line_number}: Invalid number in '{part}'"
                print(Fore.RED + err_msg)
                errors.append(err_msg)
                continue

            if key not in allowed:
                err_msg = f"Line {line_number}: Parameter '{key}' not allowed in {cmd}"
                print(Fore.RED + err_msg)
                errors.append(err_msg)

    if not errors:
        print(Fore.GREEN + "No errors found")
        return {"ok": True, "errors": ["No errors found"]}
    else:
        print(Fore.RED + f" {len(errors)} error(s) found")
        return {"ok": False, "errors": errors}
    
def recive_save(arg2):# execute.dev is not here

    import socket
    import state

    pas = arg2[0]
    HOST = str(arg2[1])        
    PORT = int(arg2[2])

    if pas == state.password_user:
        print(" RECIVING MODE ENABLED - CONECT CONTROL PAD")
        input(" Press enter when ready to Conect")

        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind((HOST, PORT))
        server.listen(1)

        print(f"Warte auf Verbindung auf Port {PORT}...")

        conn, addr = server.accept()
        print(f"Verbunden mit {addr}")

        buffer = ""

        while True:
            
            if state.clear_buffer:
                open("buffer.txt", "w").close()
                buffer = "" # clear input in ram
                state.clear_buffer = False

            data = conn.recv(1024)

            if not data:
                break

            text = data.decode("utf-8")
            buffer += text

            while ";" in buffer:
                part, buffer = buffer.split(";", 1)

                with open("buffer.txt", "a") as f:
                    f.write(part + "\n")

                print(part)

        conn.close()
        server.close()

    else:
        print(" Wrong paswort")

def recive_live(arg2):# not finished
    import socket
    import state

    pas = arg2[0]
    HOST = str(arg2[1])        
    PORT = int(arg2[2])

    if pas == state.password_user:
        state.execute_live = True
        print(" Live recive started")
        input(" Press enter when ready to connect - CONNECT CONTROLPAD")
        server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        server.bind((HOST, PORT))

        print(" conecting...")

        conn, addr = server.accept()

        print(f" Connected to {addr}")

        while True:           
            def reciving_data():
                data = conn.recv(1024)
                g_code_data = data.decode()

            if state.execute_live == True:
                reciving_data()
    else:
        print(" Wrong password")
    