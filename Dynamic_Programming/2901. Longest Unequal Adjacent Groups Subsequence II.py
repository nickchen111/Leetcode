# 子序列 相鄰相關 DP TC:O(n * n * l) SC:O(n) 最佳解值域DP: TC:O(nl) SC:O(nl)
class Solution:
    def getWordsInLongestSubsequence(self, words: List[str], groups: List[int]) -> List[str]:
        '''
        挑最長子序列LS 其中字串長度要一樣 並且最小distance == 1
        1. 首先先檢查 groups 是否一樣
        2. 再來檢查字串是否符合條件 ok的話加入 然後判斷當前加入後可以達到的最長字串長度
        所以dp狀態會設計成 走到i的時候 以這個字段groups作為結尾  可以達到的最長長度
        '''
        n = len(words)
        f_map = {} # 枚舉有哪些不同的字符串 他們可以達到的數值是多少以及他對應的groups數值的index
        max_len, start = 0, n
        nxt = [n] * n
        for i in range(n - 1, -1, -1):
            w, g = words[i], groups[i]
            # 31 -> 11111就用來當做 abc -> ?bc, a?c, ab? 的 ?
            hash_val = sum((ord(ch) & 31) << (k * 5) for k, ch in enumerate(w)) # 每個字母用5個比特保存 
            f = 0
            for k in range(len(w)):
                h = hash_val | 31 << (k * 5) # 覆蓋掉
                max_f, j = f_map.get(h, (0, 0)) # 之前是否有這個數值
                if max_f > f and groups[j] != g:
                    f = max_f
                    nxt[i] = j
            f += 1
            if f > max_len:
                max_len = f
                start = i
            # 將當下的可能性加進去
            for k in range(len(w)):
                h = hash_val | 31 << (k * 5) # 覆蓋掉
                if h not in f_map or f > f_map[h][0]:
                    f_map[h] = (f, i)
        ans = []
        while start != n:
            ans.append(words[start])
            start = nxt[start]
        return ans

        '''
        n = len(words)
        mx = max(groups)
        dp = [0] * n
        nxt = [n] * n
        mx_len, start = 0, n-1
        def check(s:str, t:str) -> bool:
            return len(s) == len(t) and sum(x != y for x, y in zip(s, t)) == 1
        for i in range(n-1, -1, -1):
            for j in range(i + 1, n): # 之前有哪些可以選
                if dp[j] > dp[i] and groups[i] != groups[j] and check(words[i], words[j]):
                    dp[i] = dp[j]
                    nxt[i] = j
            dp[i] += 1
            if mx_len < dp[i]:
                mx_len = dp[i]
                start = i
        ans = []
        while start != n:
            ans.append(words[start])
            start = nxt[start]
        return ans
        '''

        
