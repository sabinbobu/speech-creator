import sys
import re

if len(sys.argv) < 3:
  print("Parameter error: ", sys.argv[0], " input_ALSize_report_file_name  output_file")
  sys.exit(-1)

in_file = open(str(sys.argv[1]), "r")

lines = in_file.readlines()
in_file.close()

exception_list = ("ALSize", "Copyright", "ALSize Memory Report", "In \[Byte\]", "\\*\\*\\*\\*", "With 8-Bit")

def match_all(curr_line):
  for curr_exception in exception_list:
    match = re.search(curr_exception, curr_line)
    if match:
      return False
  return True

new_file = open(str(sys.argv[2]), "w")

#skip the first empty line too
empty_counter = 1

for line in lines:
  match = match_all(line)
  if match:
    if re.search("^$", line):
      empty_counter += 1
      if(empty_counter <= 1):
        new_file.write(line)
    else:
      empty_counter = 0
      new_file.write(line)

new_file.close()
