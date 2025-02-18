import subprocess
import os

count = 0
def compile_java(name):
    print("Compiling", name)
    java_file_path = f"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/{name}.java"
    result = subprocess.run(
        ["javac", java_file_path],
        capture_output=True,
        text=True
    )
    if result.returncode != 0:
        print(f"Error compiling {name}.java:\n{result.stderr}")
        exit(1)
    else:
        print(f"{name}.java compiled successfully.")
def compile_cpp(name):
    print("compiling", name)
    result = subprocess.run(["g++", "C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/"+name+".cpp", "-o", name+".exe"], capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Error compiling {name}.cpp:\n{result.stderr}")
        exit(1)

# compile_java("correct")
compile_cpp("correct")
compile_cpp("wrong")
compile_cpp("gen")
def files_are_identical(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        content1 = f1.read().strip()  # Strip whitespace
        content2 = f2.read().strip()  # Strip whitespace
        print("LINE 19",content1)
    return content1 == content2
def are_floats_close():
    # Read the float from wrong_output.txt
    with open('wrong_output.txt', 'r') as f:
        wrong_float = float(f.read().strip())
    
    # Read the float from correct_output.txt
    with open('correct_output.txt', 'r') as f:
        correct_float = float(f.read().strip())
    
    # Check if the floats differ by less than 10^-6
    return abs(wrong_float - correct_float) < 1e-6

correct_file = r"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct_output.txt"
wrong_file = r"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/wrong_output.txt"
while True:
    # Generate input
    with open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt", "w") as f:
        subprocess.run(["C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/gen.exe"], stdout=f)
    files_are_identical(r"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt", r"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt")
    # command = ["python3", "C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct.py"]   
    # # Run correct and wrong solutions
    with open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt", "r") as fin, open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct_output.txt", "w") as fout:
        subprocess.run(["C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct.exe"], stdin=fin, stdout=fout)
    input_path = "C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt"
    output_path = "C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct_output.txt"
    classpath = "correct"

    # Run the Java program
    # with open(input_path, "r") as fin, open(output_path, "w") as fout:
    #     subprocess.run(
    #         ["java", classpath],
    #         stdin=fin,
    #         stdout=fout,
    #         text=True
    #     )
    # with open("input.txt", "r") as input_file, open("correct_output.txt", "w") as output_file:
    #     # Run the command with input redirection and output redirection
    #     subprocess.run(command, stdin=input_file, stdout=output_file)
    with open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt", "r") as fin, open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/wrong_output.txt", "w") as fout:
        subprocess.run(["C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/wrong.exe"], stdin=fin, stdout=fout)

    # Compare outputs using subprocess
    
    # Check if there was any difference
    if not files_are_identical(correct_file, wrong_file):
        print(f"Test failed on test case {count}. Check input.txt")
        break

    # Print progress every 100,000 test cases
    count += 1
    if count % 25 == 0:
        print(f"Tested {count} cases.")
