# TC:O(nlogn) SC:O(n)
class Solution:
    def makeParityAlternating(self, nums: List[int]) -> List[int]:
        n = len(nums)
        if n == 1: # edge case 只有一個數字
            return [0,0]
        ops_a, ops_b = 0, 0 # 偶奇, 奇偶
        for i, x in enumerate(nums):
            if x % 2 != i % 2:
                ops_a += 1
            if x % 2 != (1 - i % 2):
                ops_b += 1
        
        min_ops = min(ops_a, ops_b)
        
        def solve(target_fn) -> int:
            items = []
            for i, x in enumerate(nums):
                parity = target_fn(i)
                if x % 2 == parity:
                    items.append([x])
                else:
                    items.append([x - 1, x + 1])
            
            cands = []
            for i, vals in enumerate(items):
                for v in vals:
                    cands.append((v, i))
            cands.sort()
            
            count = defaultdict(int)
            covered = 0
            mn = inf
            left = 0
            
            for right in range(len(cands)):
                v_r, idx_r = cands[right]
                if count[idx_r] == 0:
                    covered += 1
                count[idx_r] += 1
                
                while covered == n:
                    mn = min(mn, cands[right][0] - cands[left][0])
                    v_l, idx_l = cands[left]
                    count[idx_l] -= 1
                    if count[idx_l] == 0:
                        covered -= 1
                    left += 1
            
            return mn
        
        results = []
        if ops_a == min_ops:
            results.append(solve(lambda i: i % 2))
        if ops_b == min_ops:
            results.append(solve(lambda i: 1 - i % 2))
        
        return [min_ops, min(results)]
