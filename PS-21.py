#d
numbers = [10, 25, 60, 40, 80]

for i in range(len(numbers)):
    if numbers[i] > 50:
        print("Value:", numbers[i])
        print("Position:", i + 1)
        break