import subprocess
import os

count = 0

def compile_java(name):
    print("Compiling", name)
    java_file_path = f"{name}.java"
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
    print("Compiling", name)
    result = subprocess.run(
        ["g++", f"{name}.cpp", "-o", f"{name}.exe"],
        capture_output=True,
        text=True
    )
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
        print("LINE 19", content1, content2)
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

correct_file = "correct_output.txt"
wrong_file = "wrong_output.txt"

while True:
    # Generate input
    with open("input.txt", "w") as f:
        subprocess.run(["gen.exe"], stdout=f)

    files_are_identical("input.txt", "input.txt")

    # Run correct solution
    with open("input.txt", "r") as fin, open("correct_output.txt", "w") as fout:
        subprocess.run(["correct.exe"], stdin=fin, stdout=fout)

    # Run wrong solution
    with open("input.txt", "r") as fin, open("wrong_output.txt", "w") as fout:
        subprocess.run(["wrong.exe"], stdin=fin, stdout=fout)

    # Compare outputs
    if not files_are_identical(correct_file, wrong_file):
        print(f"Test failed on test case {count}. Check input.txt")
        break

    count += 1
    if count % 25 == 0:
        print(f"Tested {count} cases.")
