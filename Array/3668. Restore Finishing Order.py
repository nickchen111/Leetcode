# TC:O(n) SC:O(n)
class Solution:
    def recoverOrder(self, order: List[int], friends: List[int]) -> List[int]:
        ans = []
        st = set(friends)
        for o in order:
            if o in st:
                ans.append(o)
        return ans                
