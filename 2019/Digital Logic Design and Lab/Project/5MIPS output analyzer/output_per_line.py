import os

with open("output_result.txt", 'r') as f:
    lines = f.readlines()
    line = lines[0]
    idx = 0;
    while line.find("0 : ") != -1:
        idx += 1


    while idx < len(lines):
        os.system("clear")
        print(lines[0])
        print(lines[1])
        print(lines[2])
        print("")
        print(lines[idx])
        print("")
        idx += 1
        input()
