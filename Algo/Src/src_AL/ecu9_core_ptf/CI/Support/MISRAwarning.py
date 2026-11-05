import getopt
import sys
import re
import logging

# Global Variables
fullMessages = []
trimmedcfiles = []

def fetchMISRAWarnings(MISRAfile: str):
    if MISRAfile:
        try:
            with open(MISRAfile, 'r') as input:
                content = input.readlines()
                for line in content:
                    line = line.strip()
                    if line.__contains__('.c'):
                        match = re.search(r'(.*\\.[cpp|c])', line)
                        if match:
                            cfilename = match.group()
                            trimmedcfile = re.search(r'(\\Src_AL\\[^\\]+(?:\\[^\\]+)*\.(?:cpp|c))', cfilename)
                            if trimmedcfile:
                                trimmedcfiles.append(trimmedcfile.group())
                        match = re.search(r'\\Src_AL\\(.*)', line)
                        if match:
                            fullMessage = match.group()
                            fullMessages.append(fullMessage)
        except Exception as e:
            logging.error(e)
    else:
        logging.error(f'{MISRAfile} does not exist')

def detailedReport(messages: list, output_file: str):
    warnings = {}
    for msg in messages:
        filepath, message = msg.split(':', 1)
        if filepath not in warnings:
            warnings[filepath] = []
        warnings[filepath].append(message.strip())
    
    with open(output_file, 'w') as output:
        output.write("MISRA Warnings\n")
        output.write("----------------------------------------------------------------------------------------\n\n")
        for filename in sorted(warnings):
            output.write("[filename]: " + filename + "\n")
            for message in warnings[filename]:
                output.write(f"{filename}:{message}\n")
            output.write("\n")

def parse_input(args: str):
    try:
        opts, args = getopt.getopt(args, 'w:o:', ['misrawarning=', 'output_file='])
    except getopt.GetoptError:
        logging.info(f'MISRAwarning.py -w <misrawarning> -o <output_file>')
        sys.exit(2)

    for opt, arg in opts:
        if opt in ('-w', '--misrawarning'):
            misrawarning = arg
        elif opt in ('-o', '--output'):
            output_file = arg

    return misrawarning, output_file

if __name__ == '__main__':
    MISRAfile, output_file = parse_input(sys.argv[1:])
    if MISRAfile:
        with open(MISRAfile, 'r') as file:
            dataCheck = file.read(1)
            if dataCheck:
                fetchMISRAWarnings(MISRAfile)
                detailedReport(fullMessages, output_file)