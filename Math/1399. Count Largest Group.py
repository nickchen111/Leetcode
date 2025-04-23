# TC:O(n) SC:O(n + m) m 為數字最多相加總和
class Solution:
    def countLargestGroup(self, n: int) -> int:
        '''
        自己數字相加和一樣就分在同一組 問說有多少組會有最多的數量
        '''
        cnt = [0] * 40
        rank = [0] * (n + 1)
        for i in range(1, n + 1):
            group = i % 10 + rank[i // 10]
            rank[i] = group
            cnt[group] += 1
        return cnt.count(max(cnt))
