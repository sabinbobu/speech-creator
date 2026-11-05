import os
import sys
import re


if len(sys.argv) < 3:
    print("Parameter error: " + sys.argv[0] + "  project_directory  test_directory")
    sys.exit(-1)

project_dir = str(sys.argv[1])
#test_dir = str(sys.argv[2])

filesearch = re.compile(r'.*\.c')
unittest_search = re.compile(r'[ \t]*ALUnitTest_AddFunction[ ]*\( *\"(\w+)\"[ ]*, (\w+)[ ]*\)[ ]*;')
errorlist = []
errorentry = []
maxlen = [0, 0, 0, 0]

path_list = sys.argv[2].split(';')
for i in range(len(path_list)):
    test_dir = path_list[i]

    for root, dirs, files in os.walk(project_dir + test_dir):
        for file in files:
            fullpath = os.path.join(root, file)
            m = filesearch.match(fullpath)
            if m:
                file = open(fullpath, 'r')
                lines = file.readlines()
                count = 0
                linenum = 0
                for line in lines:
                    linenum += 1
                    m = unittest_search.match(line)
                    if m and m.group(1) != m.group(2):
                        thisfile = file.name[len(project_dir):].replace('\\', '/')
                        errorentry = [thisfile, str(linenum), m.group(1), m.group(2)]
                        errorlist.append(errorentry)
                        maxlen[0] = max(len(thisfile), maxlen[0])
                        maxlen[1] = max(len(str(linenum)), maxlen[1])
                        maxlen[2] = max(len(m.group(1)), maxlen[2])
                        maxlen[3] = max(len(m.group(2)), maxlen[3])

print('\n*** Test file consistency check ***')
if len(errorlist):
    print('PROBLEM: The test description does not match the called test function as in ALUnitTest_AddFunction("MT_CddExample_Init", MT_CddExample_Init);')
    print('EFFECT:  The Unit or Integration test evaluation can not be trusted.')
    print('ACTION:  Correct these parameters in the listed test file, also check the relevant DOORS specification.\n')
    print('File'.ljust(maxlen[0]) + '  ' + 'Line'.ljust(maxlen[1]) + '  ' + 'Function name'.ljust(maxlen[2]) + '    ' + 'Function pointer'.ljust(maxlen[3]))
    print('-' * maxlen[0] + '  ' + '-' * maxlen[1] + '  ' + '-' * maxlen[2] + '    ' + '-' * maxlen[3])

    for errorentry in errorlist:
        print(errorentry[0].ljust(maxlen[0]) + '  ' + errorentry[1].rjust(maxlen[1]) + '  ' + errorentry[2].ljust(maxlen[2]) + ' != ' + errorentry[3].ljust(maxlen[3]))

else:
    print('Test files have ZERO known problems.')
