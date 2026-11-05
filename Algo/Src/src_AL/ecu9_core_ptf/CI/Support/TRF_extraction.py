from sqlite3 import connect
import sys

def trf_analyzer(trf):
    """
    This function analyzes a .trf file and extracts relevant information.
    :param trf: path to the .trf file
    :return: list of tuples (item_name, item_result, Marelli_status)
    """
    result_dict = []
    FAIL = ['ERROR', 'FAILED', 'INCONCLUSIVE']
    conn = connect(trf)
    cursor = conn.cursor()
    cursor.execute("SELECT * FROM reportitem_data")
    r = cursor.fetchall()

    # todo manage NONE case properly


    for i in range(len(r)):
        if r[i][2] == 'PROJECT' and r[i][13] != '' and r[i][13].startswith('ALD'):
            if r[i][8] != "NONE":
                result_dict.append((r[i][13], r[i][8], "FAIL" if r[i][8] in FAIL else "PASS"))
        elif r[i][2] == 'PACKAGE' and (r[i][3] is None or r[i][3] == 'STIMULATION' or r[i][3] == 'ANALYSIS') and r[i][13] != '':
            if r[i][8] != "NONE":
                result_dict.append((r[i][13], r[i][8], "FAIL" if r[i][8] in FAIL else "PASS"))
    conn.close()
    return result_dict

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Usage: python script_name.py path_to_trf_file")
        sys.exit(1)
    trf_file_path = sys.argv[1]
    d = trf_analyzer(trf_file_path)
    # Define column widths
    col1_width = 55
    col2_width = 20
    col3_width = 10

    # Print table header
    print("\n" + "=" * (col1_width + col2_width + col3_width + 4))
    print(f"{'Test Name':<{col1_width}} | {'Result':<{col2_width}} | {'Status':<{col3_width}}")
    print("=" * (col1_width + col2_width + col3_width + 4))

    # Print table rows
    for k in d:
        print(f"{k[0]:<{col1_width}} | {k[1]:<{col2_width}} | {k[2]:<{col3_width}}")

    # Print table footer
    print("=" * (col1_width + col2_width + col3_width + 4))
    print(f"\nTotal Tests: {len(d)}")
    
    has_failures = any(k[2] == 'FAIL' for k in d)
    if has_failures:
      print("\n SMOKE TEST FAILED! Please refer to the table above for failed test cases")
      sys.exit(1) #exit code to indicate failure
    else:
      sys.exit(0)
    
    
    