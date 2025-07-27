class Solution:
    def numOfSubsequences(self, s: str) -> int:
        n = len(s)
        t = s.count('T')
        l = lc = ct = c = lt = lct = 0
        ans = 0
        for ch in s:
            if ch == 'L':
                l += 1
            elif ch == 'C':
                lc += l
                c += 1
            elif ch == 'T':
                lct += lc
                ct += c
                t -= 1
            lt = max(lt, l * t)
        return lct + max(lt, ct, lc)

        '''
        SC:O(n)做法
        preL = [0] * (n + 1)
        preLC = [0] * (n + 1)
        totalL = totalLC = 0
        total = 0

        for i in range(n):
            if s[i] == 'L':
                totalL += 1
            elif s[i] == 'C':
                totalLC += totalL
            elif s[i] == 'T':
                total += totalLC
            preL[i + 1] = totalL
            preLC[i + 1] = totalLC

        sufT = [0] * (n + 1)
        sufCT = [0] * (n + 1)
        totalT = totalCT = 0
        for i in reversed(range(n)):
            if s[i] == 'T':
                totalT += 1
            elif s[i] == 'C':
                totalCT += totalT
            sufT[i] = totalT
            sufCT[i] = totalCT

        max_add = 0
        for i in range(n + 1):
            max_add = max(max_add, sufCT[i])
            max_add = max(max_add, preL[i] * sufT[i])
            max_add = max(max_add, preLC[i])

        return total + max_add
        '''