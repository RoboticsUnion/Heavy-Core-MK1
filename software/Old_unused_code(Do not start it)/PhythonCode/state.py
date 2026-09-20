# state.py

password_user = None
sys_password = None

console_user_running = True
g_code_editor_running = False
g_code_starter_running = False


file = None

# state.py

execute_live = None #set to False when in use

commands_text = """
ALL COMMANDS OF THE SOFTWARE

MAIN CONSOLE COMMANDS

help
Shows the main help page.
Usage:
help

exit
Closes the main console and stops the software.
Usage:
exit

pas
Shows the user password, but only if the generated system password is correct.
The system password is printed at startup.
Usage:
pas <system_password>

pip
Checks if a Python package exists. If it is missing, the software tries to install it with pip.
Usage:
pip <user_password> <package_name>
Example:
pip mypass colorama

ser
Serial configuration command.
Usage for setting serial:
ser set <user_password> <port> <baud_rate> <timeout>
Example:
ser set mypass COM3 9600 1

Usage for serial help:
ser help <user_password>

cal
Calibration command for robot arm values.

Manual calibration:
cal man <user_password> <l1> <l2> <l3> <r1> <r2> <w1> <w2> <w3> <tool_x> <tool_y>
Example:
cal man mypass 100 120 80 0 0 45 45 45 0 0

Automatic basic length calibration:
cal auto <user_password> <l1> <l2> <l3>
Example:
cal auto mypass 100 120 80

Tool length:
cal tl <user_password> <tool_length>
Example:
cal tl mypass 50

Delete all calibration values:
cal dump <user_password>

Calibration help:
cal help <user_password>

stat
Shows current statistics and stored state values:
terminal lines, arm lengths, rotation values, angle values, tool values and selected compiler file.
Usage:
stat

g-e
Opens the G-Code editor functions.
Usage:
g-e <mode> <user_password>

Modes:
g-e help <user_password>
Shows editor help.

g-e make <user_password>
Creates a new empty G-Code file. The program asks for the file name.

g-e write <user_password>
Opens write mode. The program asks for the file name, then you write line 1, line 2, line 3, etc.
Type exit inside the writer to return to the main console.

g-e edit <user_password>
Opens edit mode for an existing file.
Inside edit mode:
show = display the file with line numbers
edit = edit one selected line
exit = return to main console

g-e delete <user_password>
Deletes a selected file. The program asks for the file name.

g-s
Starts the G-Code starter section.
Usage:
g-s <user_password>
After that the program asks:
Do you want to continue? (Y/n)
Enter Y to start, n to cancel.

helpGUI
Opens the manual GUI window.
Usage:
helpGUI <user_password>

clock
Shows a live clock in the console.
Hold q to close the clock.
Usage:
clock <user_password>


G-CODE STARTER COMMANDS

These commands are only available after starting the starter with:
g-s <user_password>

exit
Leaves the G-Code starter and returns to the main console.
Usage:
exit

file
Sets the G-Code file that should be used by the compiler.
Usage:
file <user_password> <filename>
Example:
file mypass test.gcode

compile
Checks the selected G-Code file for syntax errors.
You must set a file first with the file command.
Usage:
compile <user_password>

recive
Starts TCP receive mode and saves received data into buffer.txt.
Data is split by semicolons. Every part before a semicolon becomes one line in buffer.txt.
Usage:
recive <user_password> <host> <port>
Example:
recive mypass 0.0.0.0 5000

recive_live
Starts live receive mode.
This function exists in the code but is marked as unfinished.
Use carefully.
Usage:
recive_live <user_password> <host> <port>
Example:
recive_live mypass 0.0.0.0 5000

help
Shows the G-Code starter help text.
Usage:
help <user_password>


SUPPORTED G-CODE COMMANDS IN THE COMPILER

The compiler currently accepts these G-Code commands:

G0
Fast movement to a position.
Allowed parameters:
X, Y, Z
Example:
G0 X100 Y50 Z20

G1
Movement to a position with feed/speed value.
Allowed parameters:
X, Y, Z, F
Example:
G1 X100 Y50 Z20 F1500

G78
Special command with X, Y, feed and S value.
Allowed parameters:
X, Y, F, S
Example:
G78 X10 Y20 F500 S1

G-Code comments:
Text inside round brackets is ignored.
Example:
G0 X10 Y20 Z30 (this is a comment)

Everything after a semicolon is ignored by the compiler.
Example:
G1 X10 Y20 Z30 F1000 ; comment

Note:
The old help text mentions GD and G1-s, but these commands are not implemented in the current compiler command list.
"""


basic_text = """
HEAVY CORE MK1 CMD-CONTROL - BASIC OVERVIEW

This software is a command line control system for a robot arm.

Start the program with Startup.py.
At startup the program asks for the folder that contains the project files.
After that it generates a system password and asks the user for a user password.

The user password is needed for most control commands.
The system password can be used with the pas command to show the user password again.

Main workflow:
1. Start Startup.py.
2. Enter the project folder.
3. Enter your user password.
4. Use help to show the command overview.
5. Calibrate the robot arm with cal.
6. Create or edit G-Code with g-e.
7. Start the G-Code starter with g-s.
8. In the starter, select a file with file and check it with compile.

Important states:
console_user_running controls the main terminal.
g_code_editor_running controls the G-Code editor.
g_code_starter_running controls the G-Code starter.
state.file stores the selected G-Code file.
"""


help_text = """
HELP OVERVIEW

This project contains a terminal based robot arm control system.

Important files:
Startup.py starts the whole software.
console_user.py runs the main command input loop.
interpreter.py connects main console commands to their functions.
functions.py contains the main command functions.
G_Code_Editer.py contains file creation, writing, editing and deleting.
G_Code_starter.py runs the G-Code starter command loop.
G_Code_starter_functions.py contains compile, file selection and receive functions.
manual.py opens the graphical manual window.
state.py stores shared variables and manual texts.

Recommended use:
Start with Startup.py.
Use help to see the command list.
Use cal help to see calibration help.
Use g-e make or g-e write to create G-Code.
Use g-s to enter the G-Code starter.
Use file to select a G-Code file.
Use compile to check the selected file.

Safety:
Always calibrate the arm before movement or file execution.
Check all length, angle and tool values with stat.
Use the correct password for control commands.
Do not run unfinished live receive functions on real hardware without testing.
"""


gui_text = """
GUI BASIC OVERVIEW

The manual GUI is opened with:
helpGUI <user_password>

The window title is User Manual.
It contains five pages:

cmd-basics
Basic overview of the command control software.

cmd-commands
Complete command list for the main console, G-Code editor and G-Code starter.

cmd-help
General help and recommended workflow.

GUI-basics
Explanation of the manual GUI.

Content-Creation
Rules for creating or changing GUI content.

The manual.py file reads the text from state.py:
state.basic_text
state.commands_text
state.help_text
state.gui_text
state.content_text

The current GUI uses labels with centered text.
For short text this is fine.
For long text, especially commands_text, a scrollable text widget is recommended.
A scrollbar makes it possible to show all commands without cutting off text.

The GUI should only display information and forward user input.
Core logic, safety logic, passwords, calibration and robot control should stay in the backend files.
"""


content_text = (
"CONTENT CREATION GUIDELINES FOR THE PROJECT\n"
"\n"
"Content creation is allowed within this project, but strictly limited to the graphical user interface (GUI). "
"The GUI layer may be modified, redesigned, extended, and visually improved as needed. "
"Developers are encouraged to adapt layouts, enhance usability, and create custom user experiences, as long as the core system integrity remains untouched.\n"
"\n"
"The GUI can be developed using the following libraries:\n"
"import os\n"
"import PySide6.QtWidgets as qw\n"
"import PySide6.QtCore as qc\n"
"import PySide6.QtGui as qg\n"
"\n"
"These libraries provide the standard foundation for building modern desktop interfaces. "
"QtWidgets (qw) contains essential UI elements such as windows, buttons, labels, layouts, and input fields. "
"QtCore (qc) handles the application logic, signals and slots, timers, threading, and core functionality. "
"QtGui (qg) is responsible for graphical rendering, fonts, icons, and advanced visual components. "
"Together, they allow the creation of structured, responsive, and customizable graphical interfaces.\n"
"\n"
"The GUI is only responsible for displaying information and forwarding user input. "
"All processing, control logic, and hardware interaction are handled in separate files. "
"The GUI must therefore only pass predefined variables and states to the backend system without modifying core behavior.\n"
"\n"
"Custom GUIs may be shared, published, and distributed freely. "
"In contrast, all other parts of the codebase are strictly protected. "
"The main system code must not be shared, modified versions must not be distributed, and no part of the backend logic may be republished, not even privately.\n"
"\n"
"The GUI is fully customizable and can be built from scratch using the provided libraries. "
"Developers have full freedom in layout design, structure, and visual style, as long as required system variables and controls remain accessible.\n"
"\n"
"SECURITY NOTICE\n"
"\n"
"No responsibility is taken if critical safety elements are removed or altered within the GUI. "
"The interface plays a direct role in system monitoring and control, and removing essential indicators or controls can lead to serious risks. "
"For safety reasons, the following elements MUST be included in any GUI implementation:\n"
"\n"
"- Digital emergency stop (dedicated variable)\n"
"- Temperature monitoring (voltage converter and motors 1-9)\n"
"- Load / utilization display\n"
"- Current / power consumption display\n"
"- Overload protection indicator\n"
"- Motor overview and status display\n"
"- Cooling system control (model dependent: fan on/off or water cooling)\n"
"\n"
"It is strongly recommended to treat the GUI not only as a visual layer, but as a critical safety interface. "
"Removing or hiding safety-relevant information can result in loss of control, hardware damage, or unsafe operating conditions. "
"Even if customization is allowed, safety visibility and control must always have highest priority!\n"
"\n"
"By contributing GUI content, you agree to follow these guidelines and ensure that usability, clarity, and system safety are maintained at all times!\n"
)


clear_buffer = None #set to False when in use
live_recive_on = None #set to true when in use
live_recive_while = None #while loop stop

l1 = None
l2 = None
l3 = None
r1 = None
r2 = None
w1 = None
w2 = None
w3 = None
tool_x = None
tool_y = None
tool_length = None

s_port1 = None
baud_rate = None
timeout = None

L1 = None # not full terminal lines
L2 = None # terminal lines

raw = None


help_txt = (
    "AVAILABLE COMMANDS:\n\n"

    "pip <user_password> <package_name>\n"
    "Example: pip mypass numpy\n"
    "Installs a Python package.\n\n"

    "pas <system_password>\n"
    "Example: pas admin123\n"
    "Shows the user password.\n\n"

    "ser set <user_password> <port> <baudrate> <timeout>\n"
    "Example: ser set mypass COM3 9600 1\n"
    "Sets serial connection.\n\n"

    "ser help <user_password>\n"
    "Shows serial help.\n\n"

    "help\n"
    "Shows all commands.\n\n"

    "cal <mode> <password> ...\n"
    "Robot calibration commands.\n\n"

    "stat\n"
    "Shows system stats.\n\n"

    "g-e <mode> <password>\n"
    "Opens G-Code editor.\n\n"

    "g-s <password>\n"
    "Starts G-Code execution.\n\n"

    "helpGUI <password>\n"
    "Opens GUI manual.\n"

    "clock <password>\n"
    "shows the clock"
)

cal_help_txt = (
    "CALIBRATION COMMANDS:\n\n"

    "cal man <password> l1 l2 l3 r1 r2 w1 w2 w3 tool_x tool_y\n"
    "Example:\n"
    "cal man mypass 500 400 300 90 180 45 60 90 10 20\n\n"

    "l1/l2/l3 = arm lengths in mm\n"
    "r1/r2 = rotation values in degrees\n"
    "w1/w2/w3 = wrist angles\n"
    "tool_x/tool_y = tool head offset\n\n"

    "cal auto <password> l1 l2 l3\n"
    "Example:\n"
    "cal auto mypass 500 400 300\n\n"

    "cal tl <password> tool_length\n"
    "Example:\n"
    "cal tl mypass 150\n\n"

    "cal dump <password>\n"
    "Deletes all calibration values\n\n"

    "cal help\n"
)

ser_help_txt = (
    " This is the serial page\n"
    " ser - set/help - pas - ser - baud - timeout"
)

editor_help_txt = (
    "G-CODE EDITOR COMMANDS:\n\n"

    "g-e write <password>\n"
    "Creates new G-Code lines\n\n"

    "g-e edit <password>\n"
    "Edits existing file\n\n"

    "g-e make <password>\n"
    "Creates new G-Code file\n\n"

    "g-e delete <password>\n"
    "Deletes G-Code file\n\n"

    "g-e help <password>\n"
)


g_code_write_help_txt = (
    "This is the G-Code start page. Learn how to use the g-start software\n"
    " G0 - Drive the arm at max speed to a position(x/y/z)\n"
    " G1 - Drive the arm at a fixed speed to a position(x/y/z)\n"
    " G1-s - Fix the speed for G1\n"
    " GD - Drive every axe to a position(R1/W1/W2/R2/W3/W(x/y) example: GD R1 num W2 num W num(x) num(y)\n"
)

help_g_code_starter = (
    "========== G CODE STARTER COMMANDS ==========\n\n"

    "1. set_file\n"
    "Command:\n"
    "g-s set_file <password> <file_path>\n\n"
    
    "Purpose:\n"
    "Selects the G-Code file that should be used.\n\n"
    
    "Arguments:\n"
    "<password>   = your user password\n"
    "<file_path>  = path or name of the gcode file\n\n"
    
    "Example:\n"
    "g-s set_file mypass test.nc\n\n"

    "-------------------------------------------\n\n"

    "2. validate_gcode\n"
    "Command:\n"
    "g-s validate <password>\n\n"
    
    "Purpose:\n"
    "Checks the selected G-Code file for errors.\n"
    "It verifies:\n"
    "- unknown commands\n"
    "- wrong parameters\n"
    "- invalid numbers\n\n"
    
    "Supported commands:\n"
    "G0 -> X Y Z\n"
    "G1 -> X Y Z F\n"
    "G78 -> X Y F S\n\n"

    "Example:\n"
    "g-s validate mypass\n\n"

    "-------------------------------------------\n\n"

    "3. recive_save\n"
    "Command:\n"
    "g-s recive_save <password> <host_ip> <port>\n\n"
    
    "Purpose:\n"
    "Starts network receive mode.\n"
    "Receives incoming G-Code from another device\n"
    "and saves it into buffer.txt\n\n"
    
    "Arguments:\n"
    "<password> = user password\n"
    "<host_ip>  = your PC IP address\n"
    "<port>     = connection port\n\n"

    "Example:\n"
    "g-s recive_save mypass 192.168.0.20 5000\n\n"

    "-------------------------------------------\n\n"

    "4. recive_live\n"
    "Command:\n"
    "g-s recive_live <password> <host_ip> <port>\n\n"
    
    "Purpose:\n"
    "Receives live G-Code commands from a control pad.\n"
    "Commands are executed in real time.\n\n"

    "Arguments:\n"
    "<password> = user password\n"
    "<host_ip>  = your PC IP address\n"
    "<port>     = connection port\n\n"

    "Example:\n"
    "g-s recive_live mypass 192.168.0.20 5000\n\n"

    "-------------------------------------------\n\n"

    "5. help\n"
    "Command:\n"
    "g-s help <password>\n\n"

    "Purpose:\n"
    "Shows this help menu.\n\n"

    "Example:\n"
    "g-s help mypass\n\n"

    "===========================================\n"
)
