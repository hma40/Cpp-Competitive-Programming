with open("out.txt", "w") as f:
    # Write 1000 on the first line
    f.write("1000\n")
    
    # Write 1000 lines, each containing the number 4
    for _ in range(1000):
        f.write("4\n")