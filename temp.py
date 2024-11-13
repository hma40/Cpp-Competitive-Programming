with open("out.txt", "w") as f:
    # Write the total count of numbers
    f.write("200000\n")
    # Write numbers from 5 to 1,000,000 in increments of 5
    f.write("5")
    for i in range(10, 1000001, 5):
        f.write(" ")
        f.write(f"{i}")