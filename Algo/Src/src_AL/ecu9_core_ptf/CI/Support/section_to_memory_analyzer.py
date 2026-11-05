#import pandas as pd
from IPython.display import display
import sys
import csv

DEBUG = False
VERBOSE = False

print("\n\nAnalyzing the configuration of SECTION to MEMORY")

if DEBUG:
    CSV_INFILE_NAME  = r'C:\Users\f79382b\workspace\stdt\CI\Tmp\NEW_section_to_memory.csv'
    CSV_RULES_NAME   = r'C:\Users\f79382b\workspace\stdt\CI\Config\section_to_memory_rules.csv'
    CSV_OUTFILE_NAME = r'C:\Users\f79382b\workspace\stdt\CI\Testresults\NEW_section_to_memory.csv'
else:
    if len(sys.argv) != 4:
        print("Argument count: ", len(sys.argv))
        print("Parameter error: ", sys.argv[0], "  Tmp/NEW_section_to_memory.csv  Config/section_to_memory_rules.csv  Testresults/NEW_section_to_mmory.csv")
        sys.exit(-1)
    CSV_INFILE_NAME  = sys.argv[1]
    CSV_RULES_NAME   = sys.argv[2]
    CSV_OUTFILE_NAME = sys.argv[3]

if VERBOSE:
    print(f"CSV_INFILE_NAME:  {CSV_INFILE_NAME}")
    print(f"CSV_RULES_NAME:   {CSV_RULES_NAME}")
    print(f"CSV_OUTFILE_NAME: {CSV_OUTFILE_NAME}")


UNKNOWN    = "UNKNOWN"
OK_NO_RULE = "OK_NO_RULE"
NEW        = "NEW"
OK         = "OK"
CONFLICT   = "CONFLICT"
ERROR      = "ERROR"

configDict = {}
final_list = []
colwidth = [0, 0, 0, 0, 0]

#df = pd.DataFrame(columns = ['section', 'calculated_memory', 'final_memory', 'status'])

def memory_by_section(section):
    retVal = UNKNOWN
    #print(f"searching: '{section}'")
    if "." in section:
        search = "." + section.split(".")[1]
        if(search in configDict):
            pass
            #print(f"{section},{configDict[search]}")
            retVal = configDict[search]
        else:
            pass
            #print(f"{section},UNKNOWN")
    else:
        pass
        #print(f"{section},UNKNOWN")
    #print(f"{section},{retVal}")
    return retVal


with open(CSV_RULES_NAME) as csvrules:
    reader = csv.DictReader(csvrules)
    for row in reader:
        if(row["section"] in configDict):
            pass
            #print(f"ERROR duplicate entry: {row['section']}")
        else:
            #print(f"adding: {row['section']}, {row['memory']}")
            configDict[row["section"]] = row["memory"]

with open(CSV_INFILE_NAME) as csvinfile:
    reader = csv.DictReader(csvinfile)
    for row in reader:
        #if DEBUG: print(f'checking {row["section"]:40}: ', end="")
        #if not DEBUG: print(f'{row["section"]},', end="")
        original_memory = row["memory"]
        calculated_memory = memory_by_section(row["section"])
        final_memory = row["memory"]
        if row["memory"] == UNKNOWN and calculated_memory == UNKNOWN:
            status = UNKNOWN
        elif row["memory"] != UNKNOWN and calculated_memory == UNKNOWN:
            status = OK_NO_RULE
            final_memory = original_memory
        elif row["memory"] == UNKNOWN and calculated_memory != UNKNOWN:
            status = NEW
            final_memory = calculated_memory
        elif row["memory"] != "ROM" and row["memory"] != "RAM":
            if calculated_memory != UNKNOWN:
                status = NEW
                final_memory = calculated_memory
            else:
                status = ERROR
                final_memory = UNKNOWN
        elif row["memory"] != UNKNOWN and calculated_memory != UNKNOWN:
            if row["memory"] == calculated_memory:
                status = OK
            else:
                status = CONFLICT

        #if DEBUG: print(f'Current memory: {row["memory"]:7}  Calculated memory: {calculated_memory:7}  New memory: {final_memory:7}  Status: {status}')
        #if not DEBUG: print(f'{final_memory}')

        new_elem = {'section': row["section"], 'original_memory': original_memory, 'calculated_memory': calculated_memory, 'final_memory': final_memory, 'status': status}
        colwidth = [max(colwidth[0], len(new_elem["section"])),
                    max(colwidth[1], len(new_elem["original_memory"])),
                    max(colwidth[2], len(new_elem["calculated_memory"])),
                    max(colwidth[3], len(new_elem["final_memory"])),
                    max(colwidth[4], len(new_elem["status"]))]
        final_list.append(new_elem)

    def printelem(elem):
        print(f'Section: {elem["section"]:{colwidth[0]}}: '
              f'Original memory: {elem["original_memory"]:{colwidth[1]}}  '
              f'Calculated memory: {elem["calculated_memory"]:{colwidth[2]}}  '
              f'Final memory: {elem["final_memory"]:{colwidth[3]}}  '
              f'Status: {elem["status"]:{colwidth[4]}}')

    def print_list_of(status):
        print(f'\nList of {status}')
        for elem in final_list:
            if elem['status'] == status:
                printelem(elem)

    #print_list_of(OK)
    #print_list_of(OK_NO_RULE)
    print_list_of(UNKNOWN)
    print_list_of(NEW)
    print_list_of(CONFLICT)
    print_list_of(ERROR)

    with open(CSV_OUTFILE_NAME, 'w', newline='') as csv_outfile:
        csvwriter = csv.DictWriter(csv_outfile, fieldnames = reader.fieldnames, delimiter=',')
        csvwriter.writeheader()
        for elem in final_list:
            csvwriter.writerow({'section':elem['section'], 'memory':elem['final_memory']})

pass
