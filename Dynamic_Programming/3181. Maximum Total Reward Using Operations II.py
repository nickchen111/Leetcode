# 3181. Maximum Total Reward Using Operations II

# TC:O(n^2/64 + nlgn) SC:O(1)
class Solution:
    def maxTotalReward(self, rewardValues: List[int]) -> int:
        f = 1
        for v in sorted(set(rewardValues)):
            mask = (1 << v) - 1 
            f |= (f & mask) << v
        return f.bit_length()-1
