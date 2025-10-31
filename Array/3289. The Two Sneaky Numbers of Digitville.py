# TC:O(n) SC:O(n)
class Solution:
    def getSneakyNumbers(self, nums: List[int]) -> List[int]:
        st = set()
        ans = []
        for x in nums:
            if x in st:
                ans.append(x)
            st.add(x)
        return ans
