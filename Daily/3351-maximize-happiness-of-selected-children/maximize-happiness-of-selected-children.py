class Solution:
    def maximumHappinessSum(self, happiness: List[int], k: int) -> int:
        happiness.sort(reverse = True)
        cnt = ans = 0
        for i, x in enumerate(happiness):
            ans += x - cnt if x - cnt >= 0 else 0
            cnt += 1
            if cnt == k:
                break
        return ans