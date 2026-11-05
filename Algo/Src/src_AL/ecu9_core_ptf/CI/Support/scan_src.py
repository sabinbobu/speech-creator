import os
import sys
import re

#if len(sys.argv) < 2:
#  print("Parameter error: " + sys.argv[0] + "  project_directory")
#  sys.exit(-1)

#project_dir = str(sys.argv[1])

#debug:
print(os.getcwd())
project_dir = os.path.join(os.getcwd(), '../../src').replace('/', os.sep)
filesearch = re.compile(r'.*\b(Src_AL|Src_ALComponent)\b(.*\.c)')
#filesearch = re.compile(r'.*(Src_AL)(.*\.c)')
#filesearch = re.compile(r'.*\.c')

for root, dirs, files in os.walk(project_dir):
    for file in files:
        fullpath = os.path.join(root, file)
        m = filesearch.match(fullpath)
        if m:
            print('{},{},{}'.format(m.group(0), m.group(1), m.group(2)))
