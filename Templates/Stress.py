import subprocess
import os

count = 0
def compile_cpp(name):
    print("compiling", name)
    result = subprocess.run(["g++", "C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/"+name+".cpp", "-o", name+".exe"], capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Error compiling {name}.cpp:\n{result.stderr}")
        exit(1)

compile_cpp("correct")
compile_cpp("wrong")
compile_cpp("gen")
def files_are_identical(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        content1 = f1.read().strip()  # Strip whitespace
        content2 = f2.read().strip()  # Strip whitespace
    return content1 == content2

correct_file = r"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct_output.txt"
wrong_file = r"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/wrong_output.txt"
while True:
    # Generate input
    with open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt", "w") as f:
        subprocess.run(["C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/gen.exe"], stdout=f)
    
    # Run correct and wrong solutions
    with open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt", "r") as fin, open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct_output.txt", "w") as fout:
        subprocess.run(["C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct.exe"], stdin=fin, stdout=fout)
    
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
