#!/usr/bin/env python3
"""
Parse CUnit execution result text files and generate combined CUnit XML report to be used by Jenkins Junit Plugin.

Author: A V Soumya

Usage: python parse_cunit_results.py <input_dir> <output_xml>
Example: python parse_cunit_results.py Build/Bin cunit.xml
"""

import logging
import re
import sys
import xml.etree.ElementTree as ET
from xml.dom import minidom
from pathlib import Path
from typing import List, Tuple, Dict, Any, Optional

logging.basicConfig(
    level=logging.INFO,
    format='%(message)s'
)
logger = logging.getLogger(__name__)


_MODULE_PATTERN = re.compile(r'(Mt_\w+)$')


def _extract_module_name(folder_name: str) -> str:
    """Extract module name from folder name using the Mt_ prefix pattern.
    
    Args:
        folder_name: The folder name to extract from (e.g., 'HDR2_AL074_Test_Mt_SwcGraphicCore').
        
    Returns:
        The extracted module name (e.g., 'Mt_SwcGraphicCore') or original folder_name if no match.
    """
    match = _MODULE_PATTERN.search(folder_name)
    return match.group(1) if match else folder_name


def find_execution_result_files(base_dir: str) -> List[Path]:
    """Find all ExecutionResult.txt files in the given directory.
    
    Args:
        base_dir: The base directory path to search for execution result files.
        
    Returns:
        List of Path objects pointing to execution result files.
    """
    result_files: List[Path] = []
    base_path = Path(base_dir)
    
    if not base_path.exists():
        logger.error(f"Directory {base_dir} does not exist hence no Test Execution report could be found")
        sys.exit(1)
    
    # Find all *_ExecutionResult.txt files recursively
    for result_file in base_path.rglob("*_ExecutionResult.txt"):
        result_files.append(result_file)
    
    return result_files


def infer_module_name_from_result(result_file: Path, base_dir: str) -> str:
    """Infer module name from the ExecutionResult.txt file path.
    
    Args:
        result_file: Path to the ExecutionResult.txt file.
        base_dir: The base directory path (unused, kept for compatibility).
        
    Returns:
        The inferred module name (e.g., 'Mt_SwcGraphicCore').
    
    Example:
        >>> infer_module_name_from_result(Path("Build/Bin/HDR2_AL074_Test_Mt_SwcGraphicCore/..."))
        'Mt_SwcGraphicCore'
    """
    # Extract the folder name that contains the result file
    folder_name = result_file.parent.name
    return _extract_module_name(folder_name)


def is_failed_suite_file(file_path: Path) -> Tuple[bool, Optional[str], Optional[str]]:
    """Check if the ExecutionResult.txt file represents a failed test module.
    
    Args:
        file_path: Path to the ExecutionResult.txt file.
        
    Returns:
        Tuple of (is_failed, suite_name, error_message).
        - is_failed: True if the file has only 1 line (indicating a failed module)
        - suite_name: Extracted suite name from the file path, or None
        - error_message: Descriptive error message, or None
    """
    try:
        with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
            lines = f.readlines()
            if len(lines) == 1:
                # Extract suite name from path: Build/Bin/HDR2_AL074_Test_Mt_SwcGraphicCore/HDR2_AL074_Test_Mt_SwcGraphicCore_ExecutionResult.txt
                folder_name = file_path.parent.name
                suite_name = _extract_module_name(folder_name)
                error_msg = "Test executable not generated due to test module failure"
                return True, suite_name, error_msg
            return False, None, None
    except Exception:
        return False, None, None


def parse_execution_result(file_path: Path) -> Dict[str, Any]:
    """Parse a single execution result text file.
    
    Args:
        file_path: Path to the ExecutionResult.txt file to parse.
        
    Returns:
        Dictionary containing:
        - suite_name: Name of the test suite
        - test_cases: List of test case dictionaries
        - run_summary: Dictionary with test run statistics
        - system_out: Standard output content (assert info)
    """
    with open(file_path, 'r', encoding='utf-8', errors='ignore') as f:
        content = f.read()
    
    # Extract suite name from the path
    suite_name = file_path.parent.name
    
    # Parse test cases
    test_cases: List[Dict[str, Any]] = []
    current_test: Optional[Dict[str, Any]] = None
    failure_message = ""
    in_failure_block = False
    
    lines = content.split('\n')
    for line in lines:
        # Match test line: "  Test: TestName ...FAILED" or "  Test: TestName ...passed" from ExecutionResult.txt file
        test_match = re.match(r'\s+Test:\s+(.+?)\s+\.\.\.(\w+)', line)
        if test_match:
            # Save previous test if exists
            if current_test:
                current_test['failure_message'] = failure_message.strip()
                test_cases.append(current_test)
            
            test_name = test_match.group(1)
            status = test_match.group(2).lower()
            
            current_test = {
                'name': test_name,
                'status': status,
                'failure_message': "",
                'time': 0.0
            }
            failure_message = ""
            in_failure_block = False
            continue
        
        # If we have a current test and it's marked as FAILED, collect failure details
        if current_test and current_test['status'] == 'failed':
            if 'FAILED' in line and not in_failure_block:
                in_failure_block = True
                failure_message += line + "\n"
                continue
            
            # Collect lines that are part of failure message
            if in_failure_block:
                if line.strip().startswith('Run Summary:'):
                    in_failure_block = False
                else:
                    failure_message += line + "\n"

    if current_test:
        current_test['failure_message'] = failure_message.strip()
        test_cases.append(current_test)
    
    # Parse run summary
    run_summary: Dict[str, Any] = {
        'total_tests': 0,
        'ran_tests': 0,
        'passed': 0,
        'failed': 0,
        'skipped': 0,
        'elapsed_time': 0.0
    }
    
    summary_match = re.search(r'Run Summary:.*?tests\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)\s+(\d+)', content, re.DOTALL)
    if summary_match:
        run_summary['total_tests'] = int(summary_match.group(1))
        run_summary['ran_tests'] = int(summary_match.group(2))
        run_summary['passed'] = int(summary_match.group(3))
        run_summary['failed'] = int(summary_match.group(4))
        run_summary['skipped'] = int(summary_match.group(5))
    
    time_match = re.search(r'Elapsed time\s*=\s*([\d.]+)\s+seconds', content)
    if time_match:
        run_summary['elapsed_time'] = float(time_match.group(1))
    
    # Parse standard output (assert info)
    system_out = ""
    stdout_match = re.search(r'(Total asserts:.*?Inactive:.*?\d+)', content, re.DOTALL)
    if stdout_match:
        system_out = stdout_match.group(1).strip()
    
    return {
        'suite_name': suite_name,
        'test_cases': test_cases,
        'run_summary': run_summary,
        'system_out': system_out
    }


def prettify_xml(elem: ET.Element) -> str:
    """Return a pretty-printed XML string for the Element.
    
    Args:
        elem: XML Element to prettify.
        
    Returns:
        Pretty-printed XML string.
    """
    rough_string = ET.tostring(elem, encoding='unicode')
    reparsed = minidom.parseString(rough_string)
    return reparsed.toprettyxml(indent="  ")


def generate_cunit_xml(results: List[Dict[str, Any]], failed_suites: List[Tuple[str, str]]) -> ET.Element:
    """Generate CUnit XML from parsed results in Jenkins JUnit format.
    
    Creates a <testsuites> root element with each module as a separate <testsuite>
    for clear visualization in Jenkins.
    
    Args:
        results: List of parsed successful test suite results.
        failed_suites: List of failed test suite info as (suite_name, error_message) tuples.
        
    Returns:
        The root XML Element containing all test suites.
    """
    # Create root element - testsuites wrapper for Jenkins JUnit format
    testsuites = ET.Element('testsuites')
    
    # Calculate overall totals
    total_tests = sum(r['run_summary']['total_tests'] for r in results)
    total_failures = sum(r['run_summary']['failed'] for r in results)
    total_skipped = sum(r['run_summary']['skipped'] for r in results)
    total_errors = len(failed_suites)
    
    testsuites.set('name', 'All_Unit_Tests')
    testsuites.set('tests', str(total_tests))
    testsuites.set('failures', str(total_failures))
    testsuites.set('errors', str(total_errors))
    testsuites.set('skipped', str(total_skipped))
    
    # Create a separate testsuite for each module/result (successful results first)
    for result in results:
        suite_name = result['suite_name']
        run_summary = result['run_summary']
        
        # Extract clean module name from suite_name (remove prefixes like W00Al074_Test_)
        clean_suite_name = _extract_module_name(suite_name)
        
        # Create testsuite element for this module
        testsuite = ET.SubElement(testsuites, 'testsuite')
        
        # Handle normal test results
        testsuite.set('name', clean_suite_name)
        testsuite.set('tests', str(run_summary['total_tests']))
        testsuite.set('failures', str(run_summary['failed']))
        testsuite.set('errors', '0')
        testsuite.set('skipped', str(run_summary['skipped']))
        
        # Sort test cases: failed first, then passed/inactive
        sorted_test_cases = sorted(result['test_cases'], key=lambda tc: 0 if tc['status'] == 'failed' else 1)
        
        # Add test cases for this module
        for tc in sorted_test_cases:
            testcase = ET.SubElement(testsuite, 'testcase')
            
            # Use the testsuite name as classname
            testcase.set('classname', clean_suite_name)
            testcase.set('name', tc['name'])
            
            # Add failure if test failed
            if tc['status'] == 'failed' and tc['failure_message']:
                failure = ET.SubElement(testcase, 'failure')
                failure.set('type', 'AssertionFailed')
                # Include the full failure message
                failure.text = re.sub(r'^.*Src[/\\\\]', 'Src/', tc['failure_message'], flags=re.MULTILINE)
            
            # Add skipped if test is inactive
            if tc['status'] == 'inactive':
                skipped = ET.SubElement(testcase, 'skipped')
                skipped.text = "Test marked as inactive"
        
        # Add system-out element for this module
        if result['system_out']:
            system_out = ET.SubElement(testsuite, 'system-out')
            system_out.text = ET.CDATA(result['system_out'])
    
    # Add failed test suites as errors (at the end)
    for suite_name, error_msg in failed_suites:
        testsuite = ET.SubElement(testsuites, 'testsuite')
        testsuite.set('name', suite_name)
        testsuite.set('tests', '1')
        testsuite.set('failures', '0')
        testsuite.set('errors', '1')
        testsuite.set('skipped', '0')

        testcase = ET.SubElement(testsuite, 'testcase')
        testcase.set('classname', suite_name)
        testcase.set('name', suite_name + '_Module_Failure')
        
        # Add error element for the failed suite
        error = ET.SubElement(testcase, 'error')
        error.set('type', 'TestSuiteFailed')
        error.text = f"Test suite failed to execute: {error_msg}"
    
    return testsuites


def main():
    if len(sys.argv) < 3:
        logger.error("Usage: python parse_cunit_results.py <input_dir> <output_xml>")
        logger.error("Example: python parse_cunit_results.py Build/Bin cunit.xml")
        sys.exit(1)
    
    input_dir = sys.argv[1]
    output_xml = sys.argv[2]
    
    # Find all ExecutionResult.txt files in Bin folder
    result_files = find_execution_result_files(input_dir)
    # Parse all result files
    all_results = []
    failed_suites = []
    
    for result_file in result_files:
        is_failed, suite_name, error_msg = is_failed_suite_file(result_file)
        
        if is_failed:
            # Add to failed suites list (will be added as errors in XML)
            failed_suites.append((suite_name, error_msg))
            logger.info(f"Failed suite: {suite_name} - {error_msg}")
            continue
        
        logger.info(f"Processing: {result_file}")
        
        # Parse the execution result file
        result = parse_execution_result(result_file)
        
        logger.info(f"  Suite: {result['suite_name']}")
        logger.info(f"  Tests: {len(result['test_cases'])}")
        logger.info(f"  Passed: {result['run_summary']['passed']}")
        logger.info(f"  Failed: {result['run_summary']['failed']}")
        all_results.append(result)
    
    # Generate combined XML with both passed and failed suites
    logger.info("Generating combined CUnit XML...")
    xml_root = generate_cunit_xml(all_results, failed_suites)
    xml_string = prettify_xml(xml_root)
    
    # Write to output file
    with open(output_xml, 'w', encoding='utf-8') as f:
        f.write(xml_string)
    
    # Calculate totals
    total_test_count = sum(r['run_summary']['total_tests'] for r in all_results)
    total_failure_count = sum(r['run_summary']['failed'] for r in all_results)
    total_passed_count = sum(r['run_summary']['passed'] for r in all_results)
    total_skipped_count = sum(r['run_summary']['skipped'] for r in all_results)
    
    logger.info(f"Combined XML report written to: {output_xml}")
    logger.info(f"Total test suites: {len(all_results) + len(failed_suites)}")
    logger.info(f"Total passed test suites: {len(all_results)}")
    logger.info(f"Total error test suites (failed to build/run): {len(failed_suites)}")
    logger.info(f"Total tests in passed suites: {total_test_count}")
    logger.info(f"Total passed tests: {total_passed_count}")
    logger.info(f"Total failed tests (asserts): {total_failure_count}")
    logger.info(f"Total skipped: {total_skipped_count}")


if __name__ == "__main__":
    main()
