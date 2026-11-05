#!/usr/bin/env python3
"""
Mark duplicate failures/errors in cunit.xml as skipped if they exist in cunit_master.xml.
Generates delta_cunit.xml for Jenkins JUnit plugin without 'time' attributes and compact spacing.

Usage: python parse_cunit_delta.py cunit_master.xml cunit.xml delta_cunit.xml
"""

import logging
import sys
import xml.etree.ElementTree as ET
from typing import Set, Tuple
from pathlib import Path


logging.basicConfig(level=logging.INFO, format='%(message)s')
logger = logging.getLogger(__name__)


def get_master_failures(xml_path: str) -> Set[Tuple[str, str]]:
    """Parse cunit_master.xml and return set of failing test identifiers (classname, name)."""
    tree = ET.parse(xml_path)
    root = tree.getroot()
    failures: Set[Tuple[str, str]] = set()

    for testsuite in root.findall('.//testsuite'):
        for testcase in testsuite.findall('testcase'):
            classname = testcase.get('classname', '')
            name = testcase.get('name', '')
            if testcase.find('failure') is not None or testcase.find('error') is not None:
                failures.add((classname, name))
    return failures

def recalculate_suite_stats(testsuite: ET.Element):
    """Recalculate and update testsuite attributes based on child testcases"""
    failures = 0
    errors = 0
    skipped = 0
    total_tests = 0
    for testcase in testsuite.findall('testcase'):
        total_tests += 1
        if testcase.find('failure') is not None:
            failures += 1
        elif testcase.find('error') is not None:
            errors += 1
        elif testcase.find('skipped') is not None:
            skipped += 1
    testsuite.set('failures', str(failures))
    testsuite.set('errors', str(errors))
    testsuite.set('skipped', str(skipped))
    testsuite.set('tests', str(total_tests))
    if 'time' in testsuite.attrib:
        del testsuite.attrib['time']

def recalculate_root_stats(root_element: ET.Element):
    """Recalculate and update root testsuites attributes"""
    total_tests = 0
    total_failures = 0
    total_errors = 0
    total_skipped = 0

    for testsuite in root_element.findall('.//testsuite'):
        total_tests += int(testsuite.get('tests', '0'))
        total_failures += int(testsuite.get('failures', '0'))
        total_errors += int(testsuite.get('errors', '0'))
        total_skipped += int(testsuite.get('skipped', '0'))

    root_element.set('tests', str(total_tests))
    root_element.set('failures', str(total_failures))
    root_element.set('errors', str(total_errors))
    root_element.set('skipped', str(total_skipped))
    if 'time' in root_element.attrib:
        del root_element.attrib['time']


def process_cunit_xml(tree, master_failures):
    """Process cunit.xml: convert duplicate failures/errors to skipped."""
    root = tree.getroot()

    skipped_count = 0
    for testsuite in root.findall('.//testsuite'):
        for testcase in testsuite.findall('testcase'):
            classname = testcase.get('classname', '')
            name = testcase.get('name', '')

            failure_element = testcase.find('failure')
            error_element = testcase.find('error')

            if failure_element is not None or error_element is not None:
                identifier = (classname, name)
                if identifier in master_failures:
                    if failure_element is not None:
                        testcase.remove(failure_element)
                    if error_element is not None:
                        testcase.remove(error_element)
                    skipped = ET.SubElement(testcase, 'skipped')
                    existing_msg = ""
                    if failure_element is not None and failure_element.text:
                        existing_msg = failure_element.text.strip()
                    elif error_element is not None and error_element.text:
                        existing_msg = error_element.text.strip()
                    skipped.text = f"{existing_msg} | Skipped: duplicate failure from master build" if existing_msg else "Skipped: duplicate failure from master build"
                    skipped_count += 1
        recalculate_suite_stats(testsuite)
    recalculate_root_stats(root)
    return tree

def compact_xml(element):
    """Return compact indented XML string matching input format."""
    def _indent(element, level=0):
        i = "  " * level
        if len(element):
            if not element.text or not element.text.strip():
                element.text = '\n' + i + "  "
            if not element.tail or not element.tail.strip():
                element.tail = '\n' + i
            for subelem in element:
                _indent(subelem, level+1)
            if not element.tail or not element.tail.strip():
                element.tail = '\n' + i
        else:
            if level and (not element.tail or not element.tail.strip()):
                element.tail = '\n' + i
    _indent(element)
    lines = [line.rstrip() for line in ET.tostring(element, encoding='unicode').splitlines() if line.strip()]
    return '\n'.join(lines)

def main():
    if len(sys.argv) != 4:
        logger.error("Usage: python parse_cunit_delta.py <cunit_master.xml> <cunit.xml> <delta_cunit.xml>")
        sys.exit(1)

    master_path = sys.argv[1]
    cunit_path = sys.argv[2]
    output_path = sys.argv[3]

    if not Path(master_path).exists():
        logger.error(f"File not found: {master_path}")
        sys.exit(1)
    if not Path(cunit_path).exists():
        logger.error(f"File not found: {cunit_path}")
        sys.exit(1)

    master_failures = get_master_failures(master_path)
    tree = ET.parse(cunit_path)
    processed_tree = process_cunit_xml(tree, master_failures)

    xml_string = compact_xml(processed_tree.getroot())
    with open(output_path, 'w', encoding='utf-8') as f:
        f.write(xml_string)

    logger.info(f"Delta XML written to: {output_path}")

if __name__ == "__main__":
    main()
