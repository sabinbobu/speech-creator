import getopt
import sys
import logging
import os

#Global Variables:
misraLines=[]
hiswarnings=[]


def filterWarnings(axiviontxtfile:str):
    try:
        with open(axiviontxtfile,'r') as file:
            lines=file.readlines()

        for line in lines:
            if 'MisraC2012' in line and line.__contains__('.c'):
                misraLines.append(line)
            elif 'Metric.HIS.STMT' in line and line.__contains__('.c'):
                hiswarnings.append(line)   
    except Exception as e:
        logging.ERROR(e)
        sys.exit(1)
    finally:
        file.close()
        

    if misraLines or hiswarnings:
        parent_directory = os.path.join(os.getcwd(), os.pardir)
        target_directory_path = os.path.join(parent_directory,'Tmp')
        os.makedirs(target_directory_path, exist_ok=True)

        warningsfile= os.path.join(target_directory_path,'AXN_MISRA_HIS_Warnings.txt')
        with open(warningsfile,'w') as w:
            w.writelines(misraLines)
            w.writelines(hiswarnings)            
    else:
        logging.error('Unknown file prasing issue')
        sys.exit(1)


def parseInput(args:str):
    try:
        opts,args=getopt.getopt(args,'f:',['filename='])
    except getopt.GetoptError:
        logging.info(f'filterWarnings.py -f <filename>')
        sys.exit(1)

    for opt,arg in opts:
        if opt in ('-f','--filename'):
            filename=arg

    return filename

if __name__=='__main__':
    input=parseInput(sys.argv[1:])
    filterWarnings(input)