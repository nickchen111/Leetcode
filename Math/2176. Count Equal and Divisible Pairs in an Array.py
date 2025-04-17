# TC:O(n * lgk) SC:O(n)
k_max = 101
divisors = [[] for _ in range(k_max)]
for i in range(1, k_max): # 調和級數因式分解 nlgn
    for j in range(i, k_max, i):
        divisors[j].append(i)
class Solution:
    def countPairs(self, nums: List[int], k: int) -> int:
        '''
        之前有出現過 並且 i * j == k
        如果是這樣的話 j 與 k公因數是 g 
        那麼i 一定要是可以 k // g的倍數!?
        ex: k = 6, j = 2, 公因數 = 2, -> k // g = 3 -> 3, 6, 9...
        那麼就可以用map key = number
        key : value -> number 與他各自會是哪些因數的倍數!?
        '''
        cnt = defaultdict(lambda: defaultdict(int)) #某個val的因式分解後該因數有多少次出現頻率
        n = len(nums)
        k_divisor = divisors[k]
        ans = 0
        for i,val in enumerate(nums):
            ans += cnt[val][k // gcd(i, k)]
            for d in k_divisor:
                if not i % d:
                    cnt[val][d] += 1
        return ans
