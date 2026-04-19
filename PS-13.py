#a
#N = int(input("Enter N: "))

#for i in range(1, N+1):
    #for j in range(1, i+1):
        #print(chr(64 + j), end='')
    #print()
   
#b
N = int(input("Enter N: "))
for i in range(1, N+1):
    for j in range(i, 0, -1):
        print(chr(64 + j), end='')
    print()
#c
#K = int(input("Enter K: "))
#print(chr(64 + K))