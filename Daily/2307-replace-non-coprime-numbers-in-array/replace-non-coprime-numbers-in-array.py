class Solution:
    def replaceNonCoprimes(self, nums: List[int]) -> List[int]:
        n = len(nums)
        i = 0
        st = []
        while i < n:
            l = nums[i]
            while len(st) > 0 and gcd(st[-1], l) > 1:
                l = lcm(l, st[-1])
                st.pop()
            st.append(l)
            i += 1
        return st