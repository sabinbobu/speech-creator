rem echo SearchFiles.py
rem "D:\Program Files (x86)\Python_27\python.exe" SearchFlashFilesInArtifactory.py

echo execute the "real" test
call startEXAM_automated.bat


echo copy_test_xml.py
"C:\Program Files (x86)\Python_27\python.exe" copy_test_xml.py


echo Convert.py
"C:\Program Files (x86)\Python_27\python.exe" Convert.py

rem echo cleanup.bat
rem call cleanup.bat