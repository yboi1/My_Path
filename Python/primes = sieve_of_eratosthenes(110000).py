def sieve_of_eratosthenes(n):
    prime = [True for i in range(n+1)]
    p = 2
    while p*p <= n:
        if prime[p] == True:
            for i in range(p*p,n,p):
                prime[i] = False
        p += 1
    return [p for p in range(2,n+1) if prime[p]]
prime = sieve_of_eratosthenes(11000000)
sum = 0
n = 0
while prime[n] < 2000000:
    n += 1
    sum += prime[n]
print(sum)