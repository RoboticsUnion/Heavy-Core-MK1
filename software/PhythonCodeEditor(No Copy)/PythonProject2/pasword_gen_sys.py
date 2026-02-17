# pasword_gen_sys.py

import random
import string
import state

def sys_pas():
    state.sys_password = ''.join(
        random.choices(string.ascii_lowercase + string.digits, k=5)
    )
    print(" System password:", state.sys_password)
