import os
import subprocess

os.system("ls")
subprocess.run(["ls", "-l"])

command = "uname"
commandArgument = "-a"

print(f'Gathering system information with command: {command} {commandArgument}')
subprocess.run([command, commandArgument])

command2 = "df"
commandArgument2 = "-h"

print(f'Gathering diskspace information with command: {command2} {commandArgument2}')
subprocess.run([command2, commandArgument2])
