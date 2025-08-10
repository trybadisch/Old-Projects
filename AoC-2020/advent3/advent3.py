drift=trees=0

def main(file):
    slope = file.readline()

    while slope:
        slope = file.readline()
        if slope.find('.') is -1:
            break
        check_slope(slope)

def check_slope(slope):
    global drift; global trees
    drift += 3
    if drift > 30:
        drift %= 31
    if slope[drift] == '#':
        trees += 1
    print(slope[:drift]+"X"+slope[drift+1:], trees, sep="")

file = open('input')
main(file)
