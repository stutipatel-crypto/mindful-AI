#N = 5

#print("    ", end="")

#for j in range(1, N+1):
    #print(j, end="    ")

#print()
N = 5

print("  +" + "-" * (5*N))

for i in range(1, N+1):
    print(i, "|", end=" ")
    
    for j in range(1, N+1):
        print(i*j, end="   ")
    
    print()
    