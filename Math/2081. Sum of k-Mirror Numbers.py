# TC:O(1) SC:O(1)
MAX_N = 30
ans = [[] for _ in range(10)]
def is_k_palindrome(x:int, k:int) -> bool:
    if x % k == 0:
        return False # no leading zero
    rev = 0
    while rev < x // k:
        rev = rev * k + x % k
        x //= k
    return rev == x or rev == x // k
def do_palindrome(x:int) -> bool:
    done = True
    for k in range(2, 10):
        if len(ans[k]) < MAX_N and is_k_palindrome(x, k):
            ans[k].append(x)
        if len(ans[k]) < MAX_N:
            done = False
    if not done:
        return False
    for k in range(2, 10):
        ans[k] = list(accumulate(ans[k]))
    return True
def init() -> None:
    base = 1
    while True:
        # odd
        for i in range(base, base * 10):
            x = str(i)
            x = int(x + x[::-1][1:])
            if do_palindrome(x):
                return
        # even
        for i in range(base, base * 10):
            x = str(i)
            x = int(x + x[::-1])
            if do_palindrome(x):
                return
        base *= 10
init()
class Solution:
    def kMirror(self, k: int, n: int) -> int:
        return ans[k][n-1]
