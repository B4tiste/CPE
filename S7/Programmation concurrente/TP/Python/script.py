import os

# Open a file for writing the Markdown output
with open("output.md", "w") as output_file:
    # Write the Markdown header
    output_file.write("# Python Files\n\n")

    # Iterate through all files in the current directory and its subdirectories
    for dir_name, subdir_list, file_list in os.walk("."):
        # Iterate through all the files
        for file_name in file_list:
            # Check if the file is a Python file
            if file_name.endswith(".py"):
                # Write the file name and path in the Markdown file
                output_file.write("## {}\n\n".format(os.path.join(dir_name, file_name)))
                # Open the Python file for reading
                with open(os.path.join(dir_name, file_name), "r") as python_file:
                    # Write the file's content in the Markdown file
                    output_file.write("```python\n")
                    output_file.write(python_file.read())
                    output_file.write("\n```\n")
