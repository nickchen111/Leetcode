# TC:O(L) SC:O(n)
class Solution:
    def longestCommonPrefix(self, words: List[str]) -> List[int]:
        '''
        頭尾比較需要特判
        '''
        n = len(words)
        ans = [0] * n
        if n <= 2:
            return ans
        def lcp(s:str, t:str):
            l, r = 0, 0
            while l < len(s) and r < len(t):
                if s[l] == t[r]:
                    l += 1
                    r += 1
                else:
                    break
            return l
        suf = [0] * n
        for i in range(n - 2, -1, -1):
            suf[i] = max(suf[i + 1], lcp(words[i], words[i + 1]))
        ans[0] = suf[1]
        pre_max = 0
        for i in range(1, n - 1):
            ans[i] = max(suf[i + 1], lcp(words[i - 1], words[i + 1]), pre_max)
            pre_max = max(pre_max, lcp(words[i - 1], words[i]))
        ans[-1] = pre_max
        return ans
        
        '''
        預處理順著iterate解法
        mp = defaultdict(int)
        record_len = [0] * n
        prev = 0
        for i in range(0, n):
            # 比較這兩字串
            l = 0
            if i + 1 < n:
                r = 0
                while l < len(words[i]) and r < len(words[i + 1]):
                    if words[i][l] == words[i + 1][r]:
                        l += 1
                        r += 1
                    else:
                        break
                if l >= mxLen:
                    mx2Len, mxLen = mxLen, l
                elif l > mx2Len:
                    mx2Len = l
                mp[l] += 1
            record_len[i] = max(l, prev)
            prev = l
        record_pass_len = [0] * n
        for i in range(n):
            if i + 2 < n:
                l, r = 0, 0
                while l < len(words[i]) and r < len(words[i + 2]):
                    if words[i][l] == words[i + 2][r]:
                        l += 1
                        r += 1
                    else:
                        break
                record_pass_len[i + 1] = l
        # print(record_len, record_pass_len)
        ans = []
        for i in range(n):
            # 如果當下去掉的長度是最大長度 並且最大長度只有一個 就是比次大與新增的長度
            if record_len[i] == mxLen and mp[mxLen] == 1:
                ans.append(max(mx2Len, record_pass_len[i]))
            else:
                ans.append(max(mxLen, record_pass_len[i]))
        return ans
        '''
