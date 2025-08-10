import re

valid=valxor=0

def get_values(file):
    while True:
        line = re.split("-| |: ",file.readline().strip())
        if len(line) != 4:
            break

        min, max, char, pwd = line  # unpack list
        check(int(min), int(max), char, pwd)

    print("Pt1: ", valid, "\nPt2: ", valxor)

def check(min, max, char, pwd):
    c=xor=0; global valid; global valxor
    for i in pwd:
        if i is char:
            c+=1

        if (pwd[min-1] is char) ^ (pwd[max-1] is char):
            xor = 1

    if c >= min and c <= max:
        valid+=1
    if xor == 1:
        valxor += 1;

file = open('input')
get_values(file)
