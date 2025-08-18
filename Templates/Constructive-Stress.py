import subprocess
import os
import shutil

# File paths
gen_cpp = "./gen.cpp"
wrong_cpp = "./wrong.cpp"
check_cpp = "./check.cpp"
gen_exe = "gen.exe"
wrong_exe = "wrong.exe"
check_exe = "check.exe"

# Compile C++ files
print("Compiling gen.cpp...")
subprocess.run(["g++", gen_cpp, "-o", gen_exe], check=True)
print("Compiling wrong.cpp...")
subprocess.run(["g++", wrong_cpp, "-o", wrong_exe], check=True)
print("Compiling check.cpp...")
subprocess.run(["g++", check_cpp, "-o", check_exe], check=True)
reps = 0
while True:
    # Generate input using gen
    if reps%25==0:
        print(reps,"test cases tested...")
    reps+=1
    # print("Generating input...")
    with open("input.txt", "w") as input_file:
        subprocess.run([f"./{gen_exe}"], stdout=input_file, check=True)

    # Run wrong with generated input
    # print("Running wrong...")
    with open("input.txt", "r") as input_file, open("wrong_output.txt", "w") as wrong_output_file:
        subprocess.run([f"./{wrong_exe}"], stdin=input_file, stdout=wrong_output_file, check=True)

    # Check the output
    # print("Checking output...")
    with open("wrong_output.txt", "r") as wrong_output_file, open("correct_output.txt", "w") as correct_output_file:
        subprocess.run([f"./{check_exe}"], stdin=wrong_output_file, stdout=correct_output_file, check=True)

    # Read the result
    with open("correct_output.txt", "r") as correct_output_file:
        result = correct_output_file.read().strip()
        if result == "OK":
            pass
            # print("Test passed. Continuing...")
        elif result == "WA":
            # print("Wrong answer detected. Exiting loop.")
            break

# Print the inputs and outputs that caused WA
print("\nInput causing WA:")
with open("input.txt", "r") as input_file:
    print(input_file.read())

print("\nWrong output:")
with open("wrong_output.txt", "r") as wrong_output_file:
    print(wrong_output_file.read())
