if __name__ == '__main__':
    with open('input.txt', 'r', encoding='utf-8') as inFile:
        count = int(inFile.readline())
        arr = [int(elem) for elem in inFile.readline().split(' ')]
    flag = True
    for i in range(int(count/2)):
        if 2*i+2 != count:
            if arr[i] > arr[2*i + 1] or arr[i] > arr[2*i+2]:
                flag = False
                break
        else:
            if arr[i] > arr[2*i + 1]:
                flag = False
                break
    with open('output.txt', 'w', encoding='utf-8') as outFile:
        if flag is True:
            outFile.write('Yes')
        else:
            outFile.write('No')
