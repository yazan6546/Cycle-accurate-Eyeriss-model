import re

def add_tracker_assignments(input_file_path, output_file_path):
    """
    Adds 'PE_X_Y->tracker = tracker;' for each PE instance before the closing brace.
    
    Parameters:
    - input_file_path: Path to the original PE_array.h file.
    - output_file_path: Path to save the updated PE_array.h file.
    """
    # Regular expression to match PE instantiation lines
    # Example: PE_0_0 = new PE("PE_0_0");
    pe_instantiation_pattern = re.compile(r'^\s*(PE_\d+_\d+)\s*=\s*new\s+PE\("PE_\d+_\d+"\);')

    # Read the original file and collect all PE names
    pe_names = set()
    with open(input_file_path, 'r') as infile:
        for line in infile:
            match = pe_instantiation_pattern.match(line)
            if match:
                pe_name = match.group(1)
                pe_names.add(pe_name)

    if not pe_names:
        print("No PE instances found in the file.")
        return

    # Read all lines from the original file
    with open(input_file_path, 'r') as infile:
        lines = infile.readlines()

    # Find the index of the last closing brace '}'
    # This assumes that the closing brace is on its own line
    closing_brace_index = None
    for i in range(len(lines)-1, -1, -1):
        if re.match(r'^\s*\}\s*$', lines[i]):
            closing_brace_index = i
            break

    if closing_brace_index is None:
        print("No closing brace '}' found in the file.")
        return

    # Prepare tracker assignment lines with proper indentation
    # Assuming the indentation is the same as the closing brace line
    closing_brace_line = lines[closing_brace_index]
    indentation_match = re.match(r'^(\s*)\}\s*$', closing_brace_line)
    if indentation_match:
        indent = indentation_match.group(1)
    else:
        indent = ''

    tracker_lines = [f"{indent}{pe}->tracker = tracker;\n" for pe in sorted(pe_names)]

    # Insert tracker assignments before the closing brace
    updated_lines = lines[:closing_brace_index] + tracker_lines + lines[closing_brace_index:]

    # Write the updated lines to the output file
    with open(output_file_path, 'w') as outfile:
        outfile.writelines(updated_lines)

    print(f"Tracker assignments added successfully. Updated file saved as '{output_file_path}'.")
    print(f"Total PEs updated: {len(pe_names)}")

if __name__ == "__main__":
    # Define the input and output file paths
    input_file = 'PE_array.h'              # Path to your original PE_array.h
    output_file = 'PE_array_updated.h'     # Path to save the updated PE_array.h

    add_tracker_assignments(input_file, output_file)