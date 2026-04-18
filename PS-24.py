

#n = int(input("Enter a number: "))

#def is_prime(n):
    #for d in range(2, n):
        #if n % d == 0:
            #return False
    #return True

##print(is_prime(n))

def is_prime(n):
    for d in range(2, n):
        if n % d == 0:
            return False
    return True


N = int(input("Enter N: "))

for num in range(2, 2*N + 1):
    if is_prime(num):
        print(num)