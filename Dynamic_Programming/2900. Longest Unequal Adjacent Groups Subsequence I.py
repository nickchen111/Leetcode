# TC:O(n) SC:O(1)
class Solution:
    def getLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:
        '''
        只有 0 or 1 選出最長子序列 相鄰元素不相同
        '''
        # 貪心
        n = len(groups)
        ans = []
        for i, g in enumerate(groups):
            if i == n - 1 or g != groups[i + 1]: 
                ans.append(words[i])
        return ans

        '''
        n = len(words)
        nxt = [-1] * n
        len_end = [0, 0]  # [以 0 結尾的長度, 以 1 結尾的長度]
        pos = [n, n]      # [以 0 結尾的起始 index, 以 1 結尾的起始 index]
        best_len, start = 0, n

        for i in reversed(range(n)):
            g = groups[i]
            alt = 1 - g
            if 1 + len_end[alt] > len_end[g]:
                len_end[g] = 1 + len_end[alt]
                nxt[i] = pos[alt]
                pos[g] = i
                if len_end[g] > best_len:
                    best_len = len_end[g]
                    start = i
        ans = []
        while start != n:
            ans.append(words[start])
            start = nxt[start]
        return ans
        '''
