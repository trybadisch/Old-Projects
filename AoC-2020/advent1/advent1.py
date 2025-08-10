def get_values(file):
    line = file.readline().strip()
    values = [int(line)]

    while line:
        line = file.readline().strip()
        if line.isdigit():
            values.append(int(line))

    values.sort()

    check_sum(values)
    check_sum2(values)

def check_sum(values):
    for i in values:
        for j in values:
            if i+j == 2020:
                print(i, j, "->", i*j)
                return

def check_sum2(values):
    for i in values:
        for j in values:
            for k in values:
                if i+j+k == 2020:
                    print(i, j, k, "->", i*j*k)
                    return

file = open('input')
get_values(file)
