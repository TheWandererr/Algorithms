if __name__ == '__main__':
    with open('input.txt', 'r', encoding='utf-8') as inFile:
        num = inFile.readline()
        binNum = bin(int(num))[2:]
    arr = list(binNum)
    arr.reverse()
    degreesTree = []
    treesCount = 0
    degree = 0
    for el in arr:
        if el == '0':
            degreesTree += [-1]
        else:
            degreesTree += [degree]
            treesCount += 1
        degree += 1
    with open('output.txt', 'w', encoding='utf-8') as outFile:
            for el in degreesTree:
                if el != -1:
                    outFile.write(str(el) + '\n')

