print("")
print("")
print("+++++++++++++ Extract output from MIPS assembly code +++++++++++++")
print("-------------  SNU ECE Digital Logic Design and Lab  -------------")
print("-------------          made by. GangIn Park          -------------")
print("")
print("[*] Input files:")
print("    1. MIPS assembly code(.txt) or memory assignment verilog code(.v) with comments")
print("[*] Output files:")
print("    1. Analyzed result for output(output_result.txt)")
print("    2. Verilog code(out_code.v) which is useful for assignment of assembly code to the memory")
print("")
print("PLEASE MATCH THE FORM!!! Refer to the example given with this py file.")
print("")
print("You have to put one of these files below, in the same directory.")
print("[1] testcode.v (from verilog code)")
print("[2] testcode.txt (from assembly text file)")
print()
menu = int(input("Which do you want to extract?: "))

f = open("testcode.v", 'r')
f_out_v = open("out_code.v", 'w+')
f_out_txt = open("output_result.txt", 'w+')

if menu == 2:
    f.close()
    f = open("testcode.txt", 'r')
elif menu != 1:
    print("[Error] Wrong number of menu, try again!")

f_out_txt.write("-" * 50 + '\n')
f_out_txt.write("pc | WWD_EN on | WWD_EN off: reg 00 01 10 11\n")
f_out_txt.write("-" * 50 + '\n')
f_out_txt.write("  0 : 0000   0000 0000 0000 0000\n")

lines = f.readlines()

wwd_reg = 0
reg = [0] * 4
pc = 0
cnt = 0
jmp_target = -1

# out_code.v
for line in lines:
    inst_idx = line.find("ADD")
    if inst_idx != -1:
        inst_bin = '1111'
        rs = int(line[line.find(',') + 3:line.find(',', line.find(',')+1)])
        rt = int(line[line.find(',', line.find(',')+1) + 3:line.find('\n')])
        rd = int(line[line.find('$') + 1:line.find(',')])
        inst_bin += "{0:02b}".format(rs)
        inst_bin += "{0:02b}".format(rt)
        inst_bin += "{0:02b}".format(rd)
        inst_bin += "{0:06b}".format(0)

        f_out_v.write(("memory[%d] " % cnt) + "<= 16'h" + "{0:04x}".format(int(inst_bin, 2)) + ";\n")

        cnt = cnt + 1
        continue
    
    inst_idx = line.find("ADI")
    if inst_idx != -1:
        inst_bin = '0100'
        rs = int(line[line.find(',') + 3:line.find(',', line.find(',')+1)])
        rt = int(line[line.find('$') + 1:line.find(',')])
        imm = int(line[line.find('0x') + 2:line.find('\n')], 16)
        inst_bin += "{0:02b}".format(rs)
        inst_bin += "{0:02b}".format(rt)
        inst_bin += "{0:08b}".format(imm)

        f_out_v.write(("memory[%d] " % cnt) + "<= 16'h" + "{0:04x}".format(int(inst_bin, 2)) + ";\n")

        cnt = cnt + 1
        continue

    inst_idx = line.find("LHI")
    if inst_idx != -1:
        inst_bin = '0110'
        rt = int(line[line.find('$') + 1:line.find(',')])
        imm = int(line[line.find('0x') + 2:line.find('\n')], 16)
        inst_bin += "{0:02b}".format(0)
        inst_bin += "{0:02b}".format(rt)
        inst_bin += "{0:08b}".format(imm)

        f_out_v.write(("memory[%d] " % cnt) + "<= 16'h" + "{0:04x}".format(int(inst_bin, 2)) + ";\n")

        cnt = cnt + 1
        continue

    inst_idx = line.find("JMP")
    if inst_idx != -1:
        inst_bin = '1001'
        target = int(line[line.find('0x') + 2:line.find('\n')], 16)
        inst_bin += "{0:012b}".format(target)

        f_out_v.write(("memory[%d] " % cnt) + "<= 16'h" + "{0:04x}".format(int(inst_bin, 2)) + ";\n")

        cnt = cnt + 1
        continue

    inst_idx = line.find("WWD")
    if inst_idx != -1:
        inst_bin = '1111'
        rs = int(line[line.find('$') + 1:line.find('\n')])
        inst_bin += "{0:02b}".format(rs)
        inst_bin += "{0:02b}".format(0)
        inst_bin += "{0:02b}".format(0)
        inst_bin += "{0:06b}".format(28)

        f_out_v.write(("memory[%d] " % cnt) + "<= 16'h" + "{0:04x}".format(int(inst_bin, 2)) + ";\n")

        cnt = cnt + 1
        continue

    print("[Error] In a sentence ' ", line, "', nothing found")
    break

lines.append('')
line = lines[0]

# output_result.txt
while pc < len(lines) - 1:
    inst_idx = line.find("ADD")
    if inst_idx != -1:
        rs = int(line[line.find(',') + 3:line.find(',', line.find(',')+1)])
        rt = int(line[line.find(',', line.find(',')+1) + 3:line.find('\n')])
        rd = int(line[line.find('$') + 1:line.find(',')])

        if reg[rs] < pow(2, 15) and reg[rt] < pow(2, 15) and reg[rs] + reg[rt] >= pow(2, 15):
            reg[rd] = reg[rs] + reg[rt] - pow(2, 15)
        elif reg[rs] + reg[rt] >= pow(2, 16):
            reg[rd] = reg[rs] + reg[rt] - pow(2, 16)
        else:
            reg[rd] = reg[rs] + reg[rt]

        f_out_txt.write("{:3d}".format(pc+1) + " : " + "{0:04x}".format(wwd_reg) + "   " + "{0:04x}".format(reg[0]) + " " + "{0:04x}".format(reg[1]) + " " + "{0:04x}".format(reg[2]) + " " + "{0:04x}".format(reg[3]) + '\n')

        pc = pc + 1
        line = lines[pc]
        continue
    
    inst_idx = line.find("ADI")
    if inst_idx != -1:
        rs = int(line[line.find(',') + 3:line.find(',', line.find(',')+1)])
        rt = int(line[line.find('$') + 1:line.find(',')])
        imm = int(line[line.find('0x') + 2:line.find('\n')], 16)

        if imm >= pow(2, 7):
            for i in range(8, 16):
                imm += pow(2, i)

        if reg[rs] < pow(2, 15) and imm < pow(2, 15) and reg[rs] + imm >= pow(2, 15):
            reg[rt] = reg[rs] + imm - pow(2, 15)
        elif reg[rs] + imm >= pow(2, 16):
            reg[rt] = reg[rs] + imm - pow(2, 16)
        else:
            reg[rt] = reg[rs] + imm

        f_out_txt.write("{:3d}".format(pc+1) + " : " + "{0:04x}".format(wwd_reg) + "   " + "{0:04x}".format(reg[0]) + " " + "{0:04x}".format(reg[1]) + " " + "{0:04x}".format(reg[2]) + " " + "{0:04x}".format(reg[3]) + '\n')

        pc = pc + 1
        line = lines[pc]
        continue

    inst_idx = line.find("LHI")
    if inst_idx != -1:
        rt = int(line[line.find('$') + 1:line.find(',')])
        imm = int(line[line.find('0x') + 2:line.find('\n')], 16)

        for i in range(8):
            imm = imm * 2
        reg[rt] = imm

        f_out_txt.write("{:3d}".format(pc+1) + " : " + "{0:04x}".format(wwd_reg) + "   " + "{0:04x}".format(reg[0]) + " " + "{0:04x}".format(reg[1]) + " " + "{0:04x}".format(reg[2]) + " " + "{0:04x}".format(reg[3]) + '\n')

        pc = pc + 1
        line = lines[pc]
        continue

    inst_idx = line.find("JMP")
    if inst_idx != -1:
        target = int(line[line.find('0x') + 2:line.find('\n')], 16)

        pc_bin = ("{0:016b}".format(pc))[0:4]
        pc_bin += "{0:012b}".format(target)
        pc = int(pc_bin, 2)

        f_out_txt.write("{:3d}".format(pc) + " : " + "{0:04x}".format(wwd_reg) + "   " + "{0:04x}".format(reg[0]) + " " + "{0:04x}".format(reg[1]) + " " + "{0:04x}".format(reg[2]) + " " + "{0:04x}".format(reg[3]) + '\n')

        line = lines[pc]
        continue

    inst_idx = line.find("WWD")
    if inst_idx != -1:
        rs = int(line[line.find('$') + 1:line.find('\n')])

        wwd_reg = reg[rs]

        f_out_txt.write("{:3d}".format(pc+1) + " : " + "{0:04x}".format(wwd_reg) + "   " + "{0:04x}".format(reg[0]) + " " + "{0:04x}".format(reg[1]) + " " + "{0:04x}".format(reg[2]) + " " + "{0:04x}".format(reg[3]) + '\n')

        pc = pc + 1
        line = lines[pc]
        continue

    print("[Error] In a sentence ' ", line, "', nothing found")
    break

print()
f.close()
f_out_v.close()
f_out_txt.close()
