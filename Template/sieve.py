MAX_NUMBER = 10 ** 5 + 1
is_prime = [False] * 2 + [True] * (MAX_NUMBER - 2)
for i in range(2, int(MAX_NUMBER ** 0.5) + 1):
    if not is_prime[i]:
        continue
    for j in range(i * i, MAX_NUMBER, i):
        is_prime[j] = False
