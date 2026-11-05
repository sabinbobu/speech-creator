from JUnitXml_Generator import Testsuites, Testsuite, Testcase, Failure, Error, InfoSubEl, ET

def convertExamDurationInJunit(duration_in):
    #example string 00:00:00:00 (days:hours:minutes:seconds)
    time_str    = duration_in.split(":")
    days        = int(time_str[0])
    hours       = int(time_str[1])
    minutes     = int(time_str[2])
    seconds     = int(time_str[3])

    duration_out = (days*86400) + (hours*3600) + (minutes*60) + seconds
    return str(duration_out)

tree_input                      = ET.parse(".\\reports\\exam_test-report.xml")
root                            = tree_input.getroot()
testname                        = root.attrib['testsuite']
teststart                       = root.attrib['starttime']
numberOfTest                    = root.find("statisticData[@label='number of executed tests:']").attrib['value']
numberOfScriptswithouterrors    = root.find("statisticData[@label='number of tests without script-errors:']").attrib['value'] 
numberwitherrors                = root.find("statisticData[@label='number of tests with detected script-errors:']").attrib['value']
testtime_whole                  = root.find("statisticData[@label='complete test-time: ']").attrib['value']

test_grps = root.findall("resultData/grp")

MyConvertedTestSuites       = Testsuites(testname)
MyConvertedTestSuites.time  = convertExamDurationInJunit(testtime_whole)


for grp in test_grps:
    testgrpName             = grp.attrib['name']
    temp_suite              = Testsuite(testgrpName)
    
    if testgrpName == "initialization" or testgrpName == "deInitialization":
        temp_suite.tests    = root.find("statisticData[@label='number of executed administrativeCases:']").attrib['value']
    else:
        temp_suite.tests    = root.find("statisticData[@label='number of executed testCases: ']").attrib['value']
        
    temp_suite.id           = grp.attrib['id']
    temp_suite.time         = convertExamDurationInJunit(grp.attrib['executionTime'])
    temp_suite.timestamp    = grp.attrib['starttime']
    
    for tc_el in grp.findall("testCase"):
        tc_name             = tc_el.attrib['name']
        temp_tc             = Testcase(tc_name)
        if tc_name != 'restart_pRunner':
            temp_tc.id          = tc_el.attrib['testCaseId']
            temp_tc.time        = convertExamDurationInJunit(tc_el.attrib['executionTime'])
            temp_tc.valuation   = tc_el.attrib['valuation'].lower()
            for subTest in tc_el.findall("subtests"):
                if subTest.attrib["subTestValuation"] == "FAIL":
                    subEl = Failure()
                elif subTest.attrib["subTestValuation"] == "ERROR":
                    subEl = Error()
                elif subTest.attrib["subTestValuation"] == "INFO":
                    subEl = InfoSubEl()
                else:
                    subEl = InfoSubEl()
                El_message = ""
                for subItem in subTest.findall("subTestItem"):
                    El_message += subItem.attrib["label"] + " " + subItem.attrib["value"] + "\n"
                subEl.message = El_message
                temp_tc.addSubElement(subEl)
                
        
        temp_suite.addTestcase(temp_tc)
        
    MyConvertedTestSuites.testsuites.append(temp_suite)

MyConvertedTestSuites.generateJunitXML(".\\reports\\junit-test-report.xml")