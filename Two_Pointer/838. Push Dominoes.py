# TC:O(n) SC:O(1)
class Solution:
    def pushDominoes(self, dominoes: str) -> str:
        '''
        分類討論L .. L , R ... R, L...R, R...L 狀況
        然後根據這些狀況個別處理
        '''
        s = list('L' + dominoes + 'R')  # 前後各加一哨兵
        pre = 0  # 上一個L 或 R 的位置
        for i, ch in enumerate(s):
            if ch == '.':
                continue
            if ch == s[pre]:  # L...L 或 R...R
                s[pre + 1: i] = ch * (i - pre - 1)  # 全變成 s[i]
            elif ch == 'L':  # R...L
                m = (pre + i - 1) // 2
                s[pre + 1: m + 1] = 'R' * (m - pre)  # 前一半變 R
                m = (pre + i) // 2 + 1
                s[m:i] = 'L' * (i - m)  # 後一半變 L
            pre = i
        return ''.join(s[1:-1])  # 去掉前後哨兵
