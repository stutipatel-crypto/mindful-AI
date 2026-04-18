
Numbers = [34, 78, 12, 90, 45, 67]

max_num = Numbers[0]
min_num = Numbers[0]

for Number in Numbers:
    if Number > max_num:
        max_num = Number
    if Number < min_num:
        min_num = Number

print("Maximum:", max_num)
print("Minimum:", min_num)