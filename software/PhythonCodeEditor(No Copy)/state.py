# state.py

password_user = None
sys_password = None

console_user_running = True
g_code_editor_running = False
g_code_starter_running = False


file = None

# state.py

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
    " g-s: G code start"
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

