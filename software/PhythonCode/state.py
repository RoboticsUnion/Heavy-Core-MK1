# state.py

password_user = None
sys_password = None

console_user_running = True
g_code_editor_running = False
g_code_starter_running = False


file = None

# state.py

execute_live = None #set to False when in use

commands_text = "Here you see all existing commands in all cmd outlets"

basic_text = "Here you can get an basic overview of the Heavy Core cmd-control Program"

help_text = "Here you can get an help overview of the whole project"

gui_text = "Here you can get an overview of our GUI-System"

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
    " This is the help page, you can use the following commands:\n"
    " pip: packet\n"
    " pas: password\n"
    " ser: serial\n"
    " help: help_functions\n"
    " cal: calibrate\n"
    " stat: statistics\n"
    " g-e: G Code editor\n"
    " g-s: G code start\n"
    " helpGUI: GUI Window help"
)

cal_help_txt = (
    " This is the calibrating page\n"
    " man = l1 l2 l3 r1 r2 w1 w2 w3 tool_x tool_y\n"
    " auto = l1 l2 l3\n"
    " dumb = (deleting values)\n"
    " tl = l (tool length)\n"
    " help = (help page)"
)

ser_help_txt = (
    " This is the serial page\n"
    " ser - set/help - pas - ser - baud - timeout"
)

editor_help_txt = (
    " This is the editor page\n"
)


g_code_write_help_txt = (
    "This is the G-Code start page. Learn how to use the g-start software\n"
    " G0 - Drive the arm at max speed to a position(x/y/z)\n"
    " G1 - Drive the arm at a fixed speed to a position(x/y/z)\n"
    " G1-s - Fix the speed for G1\n"
    " GD - Drive every axe to a position(R1/W1/W2/R2/W3/W(x/y) example: GD R1 num W2 num W num(x) num(y)\n"
)

help_g_code_starter = (
    "This is the help page for the recive/start section\n"
)

