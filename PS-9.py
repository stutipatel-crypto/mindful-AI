#a
N = int(input("Enter N: "))

for i in range(1,N+1):
    for j in range(1,i+1):
        print(j, end='')
    print()
#b
N = int(input("Enter N: "))

for i in range(1,N+1):
    for j in range(1,i+1):
        print(i, end='')
    print()
   #c 
N = int(input("Enter N: "))

for i in range(1, N+1):
    for j in range(i+1, 0, -1):
        print(j, end='')
    print()
