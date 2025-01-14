# TC:O(n) SC:O(n)
class Solution:
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        ans = [0] * len(A)
        mpB = defaultdict(int)
        cnt = 0
        for i,ch in enumerate(B):
            mpB[B[i]] += 1
            if mpB[B[i]] == 0:
                cnt += 1
            mpB[A[i]] -= 1
            if mpB[A[i]] == 0:
                cnt += 1
            ans[i] = cnt
        return ans
