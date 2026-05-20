class Solution:
    def findThePrefixCommonArray(self, A: List[int], B: List[int]) -> List[int]:
        cnt = defaultdict(int)
        cur = 0
        ans = [0] * len(A)
        for i in range(len(A)):
            cnt[B[i]] += 1
            cnt[A[i]] += 1
            if cnt[A[i]] == 2:
                cur += 1
            if cnt[B[i]] == 2 and A[i] != B[i]:
                cur += 1
            ans[i] = cur
        return ans