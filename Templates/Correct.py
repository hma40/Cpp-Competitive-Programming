import subprocess

count = 0

def compile_cpp(name):
    print("compiling", name)
    result = subprocess.run(["g++", f"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/{name}.cpp", "-o", f"{name}.exe"], capture_output=True, text=True)
    if result.returncode != 0:
        print(f"Error compiling {name}.cpp:\n{result.stderr}")
        exit(1)

compile_cpp("correct")
compile_cpp("wrong")
compile_cpp("gen")

def compare_files_with_details(file1, file2):
    with open(file1, 'r') as f1, open(file2, 'r') as f2:
        lines1 = f1.readlines()
        lines2 = f2.readlines()
        for i, (line1, line2) in enumerate(zip(lines1, lines2)):
            if line1.strip() != line2.strip():
                print(f"Difference found on line {i + 1}:")
                print(f"  correct_output.txt: {line1.strip()}")
                print(f"  wrong_output.txt:   {line2.strip()}")
                return False
        if len(lines1) != len(lines2):
            print(f"Files have different lengths. Additional lines found:")
            if len(lines1) > len(lines2):
                for extra_line in lines1[len(lines2):]:
                    print(f"  correct_output.txt: {extra_line.strip()}")
            else:
                for extra_line in lines2[len(lines1):]:
                    print(f"  wrong_output.txt:   {extra_line.strip()}")
            return False
    return True

correct_file = r"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct_output.txt"
wrong_file = r"C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/wrong_output.txt"

while True:
    # Run correct and wrong solutions
    with open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt", "r") as fin, open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct_output.txt", "w") as fout:
        subprocess.run(["C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/correct.exe"], stdin=fin, stdout=fout)
    print("Got to line 44")
    with open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/input.txt", "r") as fin, open("C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/wrong_output.txt", "w") as fout:
        subprocess.run(["C:/Users/vgoof/Documents/Cpp-Competitive-Programming/Templates/wrong.exe"], stdin=fin, stdout=fout)
    print("Got to line 47")
    # Compare outputs
    if not compare_files_with_details(correct_file, wrong_file):
        print(f"Test failed on test case {count}. Check input.txt for details.")
        break
    
    # Print progress every 25 test cases
    count += 1
    if count % 25 == 0:
        print(f"Tested {count} cases.")
