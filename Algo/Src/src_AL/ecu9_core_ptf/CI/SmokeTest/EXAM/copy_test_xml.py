import os, shutil

report_dir = "D:\\EXAM44\\userData\\reports\\_05_SystemIntegrationTest\\DevicesUnderTest\\PSA\\LDM\\"
all_subdirs = [report_dir+d for d in os.listdir(report_dir) if os.path.isdir(report_dir+d)]
#get the latest sub dir
latest_subdir = max(all_subdirs, key=os.path.getmtime)

xml_report_file_name = latest_subdir.split('\\')[-1]+".xml"
pdf_report_file_name = latest_subdir.split('\\')[-1]+".pdf"

if not os.path.exists(".\\reports"):
    os.mkdir(".\\reports")
if os.path.isfile(".\\reports\\exam_test-report.xml"):
    os.remove(".\\reports\\exam_test-report.xml")
if os.path.isfile(".\\reports\\" + pdf_report_file_name):
    os.remove(".\\reports\\" + pdf_report_file_name)
    
shutil.copy2(latest_subdir + "\\" + xml_report_file_name, ".\\reports\\exam_test-report.xml")
shutil.copy2(latest_subdir + "\\" + pdf_report_file_name, ".\\reports\\" + pdf_report_file_name)
