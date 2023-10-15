import sys
import re

# Python script to convert comments in a header file to Doxygen format
# The script takes a single command-line argument, which is the name of the file to convert
# The script will write the converted file to a new file with the same name, but with ".converted" appended to the end
# it reads a line and checks if it has a comment appended to it, if it does then it converts it to a doxygen comment

# Regular expression to match comments
comment_regex = r"^\s*#define\s+(\w+)\s+(.+?)\s*//(.*)$"

# Get the filename from the command-line arguments
if len(sys.argv) < 2:
    print("Usage: python format.py <filename>")
    sys.exit(1)
filename = sys.argv[1]

# Read the contents of the file
with open(filename, "r") as f:
    text = f.read()

# Split the text into lines
lines = text.splitlines()

# Initialize the new text
new_text = ""

# Loop through the lines
for line in lines:
    # Check if the line contains a comment
    match = re.match(comment_regex, line)
    if match:
        # If it's a comment, add it to the new text
        new_text += "/*!\n"
        new_text += f" * @brief {match.group(3).strip()}\n"
        new_text += " */\n"
        new_text += f"#define {match.group(1)} {match.group(2)}\n"
    else:
        # If it's not a comment, add the line to the new text
        new_text += line + "\n"

# Write the new text to a new file
new_filename = filename + ".converted"
with open(new_filename, "w") as f:
    f.write(new_text)

print(f"Converted file written to {new_filename}")