# Documentation of HeavyMk1 Code

**Folder naming convention:**
- Main folders
- Sub folders
- Assets folders

## Functions

### Terminal
- **Terminal-IN:** Gets input from the user over the terminal
- **Terminal-OUT:** Can output things over the terminal
- **Interpret:** Interprets commands for the terminal

## Description of the functions

### Terminal

#### Terminal - IN
`terminal_read_line();` // reads a line of input from the terminal and returns it as a string.

`terminal_read_line_int();` // reads a line of input from the terminal and returns it as a string, but only if the input is an integer.

`terminal_read_password();` // reads a line of input from the terminal and returns it as a string, but hides the input from the terminal (for password input).

#### Terminal - OUT
`terminal_custom_output(std::string content, std::string color);` // gives you the custom output for the terminal, which is the content passed to the function with the color passed to the function

`terminal_standard_output();` // gives you the standard output for the terminal, which is "--> "

`terminal_error_output(std::string error_reason);` // gives you the error output for the terminal, which is the error message corresponding to the error reason passed to the function

`load_error_message(const std::string config_file_name);` // loads the error messages from the file "error_list.txt" and returns them as a vector of strings

**Terminal - OUT has special functions**
You can load an error txt for better error information:
`load_error_message(const std::string config_file_name);`

With `terminal_error_output(std::string error_reason);` you get easy control over error outputs. Just name an error reason that is configured in the `error.txt` with "Reason Reasoning".
