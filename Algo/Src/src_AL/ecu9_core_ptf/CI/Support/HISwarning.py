import getopt
import sys
import re
import logging

#Global Variables
fullMessages=[]
trimmedcfiles=[]

def fetchHISWarnings(HISfile:str):
    if HISfile:
        try:
            with open(HISfile,'r') as input:
                content=input.readlines()
                for line in content:
                    line=line.strip()
                    if line.__contains__('.c'):
                        match=re.search('(.*\\.[cpp|c])',line)
                        if match:
                            cfilename=match.group()
                            trimmedcfile=re.search(r'(\\Src_AL\\[^\\]+(?:\\[^\\]+)*\.(?:cpp|c))',cfilename)
                            trimmedcfile=trimmedcfile.group()
                            trimmedcfiles.append(trimmedcfile)
                        match=re.search(r'\\Src_AL\\(.*)',line)
                        if match:
                            fullMessage=match.group()
                            fullMessages.append(fullMessage)
        except Exception as e:
            logging.ERROR(e)
    else:
        logging.ERROR(f'{HISfile} does not exist')

def detailedReport(messages:list,output_file:str):
    warning={}
    for msg in messages:
        filepath, message = msg.split(':', 1)
        if filepath not in warning:
            warning[filepath] = []
        warning[filepath].append(message.strip())
    
    with open(output_file,'w') as output:
        output.write("HIS Warnings\n")
        output.write("----------------------------------------------------------------------------------------\n\n")
        for filename in sorted(warning):
            output.write("[filename]: " + filename + "\n")
            for message in warning[filename]:
                output.write(f"{filename}:{message}\n")
                pass
            output.write("\n")

def parse_input(args:str):
    try:
        opts,args=getopt.getopt(args,'w:o:',['hiswarning=','output_file='])
    except getopt.GetoptError:
        logging.info(f'HISwarning.py -w <hiswarning> -o <output_file>')
        sys.exit(2)

    for opt,arg in opts:
        if opt in ('-w','--hiswarning'):
            hiswarning=arg
        elif opt in ('-o','--output'):
            output_file=arg

    return hiswarning,output_file

if __name__=='__main__':

    HISfile, output_file=parse_input(sys.argv[1:])
    #HISfile, output_file='D:\\Users\\M10371A\\ALGitRepos\\aldoo\\CI\\Tmp\\AXN_HISWarnings.txt', 'D:\\Users\\M10371A\\ALGitRepos\\aldoo\\CI\\Tmp\\AXN_HIS_Report.txt'
    if HISfile:
        with open(HISfile,'r') as file:
            dataCheck = file.read(1)
            if dataCheck:
                fetchHISWarnings(HISfile)
                detailedReport(fullMessages,output_file)
            else:
                pass
