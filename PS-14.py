N = int(input("Enter N: "))

row = [1]

for i in range(N):
    # spaces for center
    print(' ' * (N - i - 1), end='')

    # print row
    for x in row:
        print(x, end=' ')
    print()

    # make next row
    new_row = [1]
    for j in range(len(row) - 1):
        new_row.append(row[j] + row[j+1])
    new_row.append(1)

    row = new_row
    print("Sum =", sum(row))