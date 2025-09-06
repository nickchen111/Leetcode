class Solution:
    def gcdValues(self, nums: List[int], queries: List[int]) -> List[int]:
        mx = max(nums)
        cnt_x = [0] * (mx + 1)
        for x in nums:
            cnt_x[x] += 1
        cnt_gcd = [0] * (mx + 1)
        for i in range(mx, 0, -1):
            c = 0
            for j in range(i, mx + 1, i):
                cnt_gcd[i] -= cnt_gcd[j]
                c += cnt_x[j]
            cnt_gcd[i] += c * (c - 1) // 2
        
        s = list(accumulate(cnt_gcd))
        # print(s)
        return [bisect_right(s, q) for q in queries]
