import re

def check_pass(file):

    pass_list = file.read().split('\n\n')

    fields = ["byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid"]
    valid_number = 0

    for i in range(len(pass_list)):
        if all(x in pass_list[i] for x in fields):
            valid_number += 1
            byr = int(re.search("(?<=byr: )\d\d\d\d", pass_list[i]).group(0))
            iyr = int(re.search("(?<=iyr: )\d\d\d\d", pass_list[i]).group(0))
            eyr = int(re.search("(?<=eyr: )\d\d\d\d", pass_list[i]).group(0))
            hgt = re.search("(?<=hgt: ).*[cm|in]", pass_list[i])
            while hgt:
                try:
                    hgt = str(hgt.group(0))
                except AttributeError:
                    print(hgt)
                    break
            if hgt and "cm" in hgt:
                try:
                    hgtcm = int(re.search(".*(?=cm|in)", hgt).group(0))
                except:
                    hgtcm = 0
            else:
                hgtcm = 0
            if hgt and "in" in hgt:
                hgtin = int(re.search(".*(?=cm|in)", hgt).group(0))
            else:
                hgtin = 0

            if byr >= 1920 and byr <= 2002 and \
            iyr >= 2010 and iyr <= 2020 and \
            eyr >= 2020 and eyr <= 2030 and \
            ((hgtcm >= 150 and hgtcm <= 193) or (hgtin >= 59 and hgtin <= 76)):

                print(True, hgtcm, hgtin)
            else:
                print(False, hgtcm, hgtin)

    print(len(pass_list))
    print(valid_number)

file = open('input')
check_pass(file)
