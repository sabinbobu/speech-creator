import xml.etree.ElementTree as ET
import sys
from xml.etree.ElementTree import Element, SubElement

class SubTestCaseEl(object):
    def __init__(self, elementName,  type_="", message="", text=""):
        super(SubTestCaseEl, self).__init__()
        self.message    = message
        self.type       = type_
        self.text       = text
        self.elName     = elementName.replace(" ", "")
    
    def setMessage(self, _message):
        self.message = _message
    
    def setType(self, _type):
        self.type = _type
        
    def setText(self, text):
        self.text = text
    
    def setElementName(self, elementName):
        self.elName     = elementName.replace(" ", "")
    
    def toSubElement(self, parent):
        self.ET_SubElement = SubElement(parent, self.elName)
        self.ET_SubElement.attrib['type']       = self.type
        self.ET_SubElement.attrib['message']    = self.message
        if self.text:
            self.ET_SubElement.text                 = self.text
    
class Failure(SubTestCaseEl):
    def __init__(self, type_="", message="", text=""):
        if sys.version[0] == '2':
            super(Failure, self).__init__("failure", type_, message, text)
        elif sys.version[0] == '3':
            super().__init__("failure", type_, message, text)
    
class Error(SubTestCaseEl):
    def __init__(self, type_="", message="", text=""):
        if sys.version[0] == '2':
            super(Failure, self).__init__("error", type_, message, text)
        elif sys.version[0] == '3':
            super().__init__("error", type_, message, text)

class InfoSubEl(SubTestCaseEl):
    def __init__(self, type_="", message="", text=""):
        if sys.version[0] == '2':
            super(InfoSubEl, self).__init__("info", type_, message, text)
        elif sys.version[0] == '3':
            super().__init__("info", type_, message, text)

class Testcase():
    def __init__(self, name, valuation="", _id="", _time=""):
        self.id             = _id
        self.setValuation(valuation)
        self.name           = name
        self.time           = _time
        self.subInfo        = []
        self.subElements    = []
    
    def addFailure(self, type_="", message="", text=""):
        tempFailure = Failure(type_, message, text)
        self.subElements.append(tempFailure)
    
    def addSubElement(self, subElement):
        self.subElements.append(subElement)
    
    def setId(self, _id):
        self.id = _id
    
    def setName(self, name):
        self.name = name
    
    def setValuation(self, valuation):
        if valuation.lower() == "fail":
            self.valuation = "failure"
        else:
            self.valuation = valuation.lower()
    
    def setTime(self, time):
        self.time = time
        
    def toSubElement(self, parent):
        self.ET_SubElement = SubElement(parent, "testcase")
        self.ET_SubElement.attrib['id']           = self.id
        self.ET_SubElement.attrib['name']         = self.name
        self.ET_SubElement.attrib['assertion']    = self.valuation
        self.ET_SubElement.attrib['time']         = self.time
        for subEl in self.subElements:
            subEl.toSubElement(self.ET_SubElement)

class Testsuite():
    def __init__(self, name, _id="", time="", failures="", errors="", tests="", timestamp="", skipped=""):
        self.id             = _id
        self.name           = name
        self.time           = time
        self.failures       = failures
        self.errors         = errors
        self.tests          = tests
        self.timestamp      = timestamp
        self.skipped        = skipped
        self.testcases      = []
    
    def addTestcase(self, testcase):
        self.testcases.append(testcase)
    
    def toSubElement(self, parent):
        testsuite_init = SubElement(parent, 'testsuite')
        testsuite_init.attrib['name']           = self.name
        testsuite_init.attrib['tests']          = str(len(self.testcases))
        testsuite_init.attrib['time']           = self.time
        testsuite_init.attrib['timestamp']      = self.timestamp
        for tc in self.testcases:
            tc.toSubElement(testsuite_init)
    
class Testsuites():
    def __init__(self, name, _id="", time="", failures=""):
        self.id             = _id
        self.name           = name
        self.time           = time
        self.failures       = failures
        self.testsuites     = []
        
    def generateJunitXML(self, path):
        testsuites      = Element('testsuites')
        for ts in self.testsuites:
            ts.toSubElement(testsuites)
        tree_output     = ET.ElementTree(testsuites)
        tree_output.write(path, encoding='utf-8')        


''' Testing stuff
suites = Testsuites("mytestsuite")
suites.testsuites.append(Testsuite("TesSuite"))
suites.testsuites[0].addTestcase(Testcase("tc"))
suites.testsuites[0].testcases[0].addFailure("ty","mes","te")
suites.generateJunitXML(".\\test1.xml")
t = 1
'''