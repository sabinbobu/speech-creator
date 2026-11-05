import sys
import re
import copy
import datetime

DEBUG = False
OPTION_USE_OWN_DATA_STRUCTURE = False

TYPE = "" #original
#TYPE = "_REDUCED"
#TYPE = "_TEST"


if len(sys.argv) != 7:
    print("Parameter error: ", sys.argv[0], "  tricore_tasking.map  output_file  sql|csv  platform  project  githash")
    sys.exit(-1)

if DEBUG:
    OPTION_USE_OUTPUT_FILE   = True #Configure for debugging
    OPTION_OUTPUT_FORMAT_SQL = True #Configure for debugging
    #MAP_FILENAME             = r"c:\Users\f79382b\workspace\hdecua\Build\Bin\In00In000_App_default\In00In000_App_default.map"
    MAP_FILENAME             = r"C:\Users\f79382b\workspace\_python\CI\CI_parse_tricore_map\Support\In00In000_App_default"+ TYPE + ".map"
    OUT_FILEEXT              = "sql" if OPTION_OUTPUT_FORMAT_SQL else "csv"
    OUT_FILENAME             = r"C:\Users\f79382b\workspace\_python\CI\CI_parse_tricore_map\Tmp\map_parser_LINK_RESULT"+ TYPE
    CONFIG_PLATFORM          = "Dlc00"
    CONFIG_PROJECT           = "Dlc00Dl006_App_default"
    CONFIG_GITHASH           = "3cae818b6fe822c5d088eff4da9514a1ec88ede1"
else:
    OUT_FILEEXT              = sys.argv[3].lower() # 'sql' XOR 'csv'
    OPTION_OUTPUT_FORMAT_SQL = (OUT_FILEEXT == 'sql')
    MAP_FILENAME             = sys.argv[1]
    OUT_FILENAME             = sys.argv[2]
    OPTION_USE_OUTPUT_FILE   = (OUT_FILENAME != 'stdout')
    CONFIG_PLATFORM          = sys.argv[4]
    CONFIG_PROJECT           = sys.argv[5]
    CONFIG_GITHASH           = sys.argv[6]


CONFIG_DATE = datetime.datetime.now().strftime("%Y-%m-%d")
CONFIG_TIME = datetime.datetime.now().strftime("%H:%M:%S")

SECTION_START_PATTERN = r"\**  Link Result  \**"
SECTION_DATA_START_PATTERN = r"\|=*\|"
SECTION_RECORD_PATTERN = r"\| (.*?) \| (.*?) \| (.*?) \| (.*?) \| (.*?) \| (.*?) \|"
SECTION_RECORD_SEPARATOR_PATTERN = r"\|-+\|"
SECTION_TABLE_END_PATTERN = r"\** [a-zA-Z ]* \**"

temp_entry = ['', '', '', '', '', ''] #temp record taken from the parsed line
list_entry = ['', '', '', '', '', ''] #prepared line for storing
found_list = []                       #stored final list
linenum = 0
local_line_counter = 0


f = open(MAP_FILENAME, 'r')
for line in f:
    linenum += 1
    if re.search(SECTION_START_PATTERN, line):
        break

for line in f:
    linenum += 1
    if re.search(SECTION_DATA_START_PATTERN, line):
        break

#print('"debug","lines","[in] File","[in] Section","[in] Size (MAU)","[out] Offset","[out] Section","[out] Size (MAU)"')
#print('"[in] File","[in] Section","[in] Size (MAU)","[out] Offset","[out] Section","[out] Size (MAU)"')

def do_store_record():
    global list_entry, local_line_counter
    if (list_entry[0] != '') and (list_entry[1] != '') and (list_entry[2] != ''):
        if DEBUG: print('ADDING  :,', end = '')
        if DEBUG: print('"' + list_entry[0] + '","' + list_entry[1] + '","' + list_entry[2] + '","' + list_entry[3] + '","' + list_entry[4] + '","' + list_entry[5] + '"')
        found_list.append(copy.deepcopy(list_entry))
        for i in range(0, 4):
            list_entry[i] = ''
        list_entry[5] = '0x00000000'

        local_line_counter = 0

for line in f:
    line = line.rstrip('\n')
    linenum += 1
    if DEBUG: print('ORIGINAL: (' + str(linenum) + ') "' + line + '"')
    match = re.search(SECTION_RECORD_PATTERN, line)
    if match:
        local_line_counter += 1
        temp_entry = [ match.group(1).strip(), match.group(2).strip(), match.group(3).strip(), match.group(4).strip(), match.group(5).strip(), match.group(6).strip() ]
        if DEBUG: print('FOUND   : "' + temp_entry[0] + '"|"' + temp_entry[1] + '"|"' + temp_entry[2] + '"|"' + temp_entry[3] + '"|"' + temp_entry[4] + '"|"' + temp_entry[5] + '"')
        if DEBUG: print('LINES   : ' + str(local_line_counter))
        if temp_entry[0] != "":
            do_store_record()

        for i in range(len(temp_entry)):
            if temp_entry[i][0:1] == '(':
                temp_entry[i] = ' ' + temp_entry[i]
        
        for i in range(len(temp_entry)):
            list_entry[i] = list_entry[i] + temp_entry[i]
        #list_entry = list(map(lambda s1, s2: s1 + s2, list_entry, temp_entry))
        pass
    else:
        match = re.search(SECTION_RECORD_SEPARATOR_PATTERN, line)
        if match:
            if DEBUG: print('SEPARATOR DETECTED -> storing.')
            do_store_record()
            for i in range(len(list_entry)):
                list_entry[i] = ''

        else:
            match = re.search(SECTION_TABLE_END_PATTERN, line)
            if match:
                if DEBUG: print('TABLE END DETECTED -> exiting.')
                break

f.close

for i in found_list:
    match = re.search(r'(.*)(?: )\((.*)\)', i[1])
    if match:
        i[1] = match.group(1)
        i.insert(2, match.group(2))

    if i[3][0:2] == '0x':
        size_dec = str(int(i[3],16))
    else:
        size_dec = ''
    i.insert(4, size_dec)

    match = re.search(r'(.*)(?: )\((.*)\)', i[6])
    if match:
        i[6] = match.group(1)
        i.insert(7, match.group(2))

    if i[8][0:2] == '0x':
        size_dec = str(int(i[8],16))
    else:
        size_dec = ''
    i.insert(9, size_dec)


if OPTION_USE_OWN_DATA_STRUCTURE:
    if OPTION_USE_OUTPUT_FILE:
        with open(OUT_FILENAME + '.' + OUT_FILEEXT, 'w') as f:
            if OPTION_OUTPUT_FORMAT_SQL:
                f.write('PRAGMA foreign_keys = off;\n')
                f.write('BEGIN TRANSACTION;\n')
                f.write('CREATE TABLE IF NOT EXISTS link_result (inFile, in_Section, in_Section_ID, in_Size_MAU_HEX, in_Size_MAU_DEC INT, out_Offset, out_Section, out_Section_ID, out_Size_MAU_HEX, out_Size_MAU_DEC INT);' + '\n')
                for i in found_list:
                    f.write('INSERT INTO link_result (inFile, in_Section, in_Section_ID, in_Size_MAU_HEX, in_Size_MAU_DEC, out_Offset, out_Section, out_Section_ID, out_Size_MAU_HEX, out_Size_MAU_DEC) VALUES (')
                    f.write('"' + i[0] + '", "' + i[1] + '", "' + i[2] + '", "' + i[3] + '", "' + i[4] + '", "' + i[5] + '", "' + i[6] + '", "' + i[7] + '", "' + i[8] + '", "' + i[9] + '"' + ');' + '\n')
                f.write('COMMIT TRANSACTION;\n')
            else:
                f.write('"inFile","in_Section","in_Section_ID","in_Size_MAU_HEX","in_Size_MAU_DEC","out_Offset","out_Section","out_Section_ID","out_Size_MAU_HEX","out_Size_MAU_DEC"' + '\n')
                for i in found_list:
                    f.write('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '"' + '\n')
    else:
        if OPTION_OUTPUT_FORMAT_SQL:
            print('PRAGMA foreign_keys = off;')
            print('BEGIN TRANSACTION;')
            print('CREATE TABLE IF NOT EXISTS link_result (inFile, in_Section, in_Section_ID, in_Size_MAU_HEX, in_Size_MAU_DEC INT, out_Offset, out_Section, out_Section_ID, out_Size_MAU_HEX, out_Size_MAU_DEC INT);')
            for i in found_list:
                print('INSERT INTO link_result (inFile, in_Section, in_Section_ID, in_Size_MAU_HEX, in_Size_MAU_DEC, out_Offset, out_Section, out_Section_ID, out_Size_MAU_HEX, out_Size_MAU_DEC) VALUES (', end = '')
                print('"' + i[0] + '", "' + i[1] + '", "' + i[2] + '", "' + i[3] + '", "' + i[4] + '", "' + i[5] + '", "' + i[6] + '", "' + i[7] + '", "' + i[8] + '", "' + i[9] + '");')
            print('COMMIT TRANSACTION;')
        else:
            #           0            1               (2)               3                (4)           5             6               (7)                 8                 (9)
            print('"inFile","in_Section","in_Section_ID","in_Size_MAU_HEX","in_Size_MAU_DEC","out_Offset","out_Section","out_Section_ID","out_Size_MAU_HEX","out_Size_MAU_DEC"')
            for i in found_list:
                print('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '"')
else:
    if OPTION_USE_OUTPUT_FILE:
        with open(OUT_FILENAME + '.' + OUT_FILEEXT, 'w') as f:
            if OPTION_OUTPUT_FORMAT_SQL:
                f.write('PRAGMA foreign_keys = off;\n')
                f.write('BEGIN TRANSACTION;\n')
                f.write('CREATE TABLE IF NOT EXISTS compiler_map (platform, project, githash, date, time, originhex, origindec INT, sizehex, sizedec INT, section, filename);' + '\n')
                for i in found_list:
                    f.write('INSERT INTO compiler_map (platform, project, githash, date, time, originhex, origindec, sizehex, sizedec, section, filename) VALUES (')
                    f.write(f'"{CONFIG_PLATFORM}", "{CONFIG_PROJECT}", "{CONFIG_GITHASH}", "{CONFIG_DATE}", "{CONFIG_TIME}", "00000000", "0", "{i[3]}", "{i[4]}", "{i[1]}", "{i[0]}"' + ');' + '\n')
                f.write('COMMIT TRANSACTION;\n')
            else:
                f.write('"platform","project","githash","date","time","originhex","origindec","sizehex","sizedec","section","filename"' + '\n')
                for i in found_list:
                    #f.write('"' + i[0] + '","' + i[1] + '","' + i[2] + '","' + i[3] + '","' + i[4] + '","' + i[5] + '","' + i[6] + '","' + i[7] + '","' + i[8] + '","' + i[9] + '"' + '\n')
                    f.write(f'"{CONFIG_PLATFORM}","{CONFIG_PROJECT}","{CONFIG_GITHASH}","{CONFIG_DATE}","{CONFIG_TIME}","00000000","0","{i[3]}","{i[4]}","{i[1]}","{i[0]}"' + '\n')
    else:
        if OPTION_OUTPUT_FORMAT_SQL:
            print('PRAGMA foreign_keys = off;')
            print('BEGIN TRANSACTION;')
            print('CREATE TABLE IF NOT EXISTS compiler_map (platform, project, githash, date, time, originhex, origindec INT, sizehex, sizedec INT, section, filename);')
            for i in found_list:
                print('INSERT INTO compiler_map (platform, project, githash, date, time, originhex, origindec, sizehex, sizedec, section, filename) VALUES (', end = '')
                print(f'"{CONFIG_PLATFORM}", "{CONFIG_PROJECT}", "{CONFIG_GITHASH}", "{CONFIG_DATE}", "{CONFIG_TIME}", "00000000", "0", "{i[3]}", "{i[4]}", "{i[1]}", "{i[0]}");')
            print('COMMIT TRANSACTION;')
        else:
            print('"platform","project","githash","date","time","originhex","origindec","sizehex","sizedec","section","filename"')
            for i in found_list:
                print(f'"{CONFIG_PLATFORM}","{CONFIG_PROJECT}","{CONFIG_GITHASH}","{CONFIG_DATE}","{CONFIG_TIME}","00000000","0","{i[3]}","{i[4]}","{i[1]}","{i[0]}"')
