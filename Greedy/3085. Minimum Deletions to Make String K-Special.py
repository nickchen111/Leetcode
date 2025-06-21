# TC:O(n + m * m + mlgm) max m = 26 SC:O(n)
class Solution:
    def minimumDeletions(self, word: str, k: int) -> int:
        '''
        greedy 因為只能做刪除操作
        看是要把多的降低 還是把低的全部砍掉
        多的降低就要看有多少組是在某個頻率
        '''
        freq = sorted(Counter(word).values())
        n = len(freq)
        ans = inf
        for i in range(n):
            base = freq[i]
            target = base + k
            cur_cnt = 0
            for j in range(i):
                cur_cnt += freq[j]
            for j in range(i, n):
                if freq[j] > target:
                    cur_cnt += freq[j] - target
            ans = min(ans, cur_cnt)
        return ans
