class Solution:
    def makeFancyString(self, s: str) -> str:
        n = len(s)
        i = 0
        ans = []
        while i < n:
            j = i + 1
            tmp = [s[i]]
            while len(tmp) < 2 and j < n and s[j] == s[j - 1]:
                tmp.append(s[j])
                j += 1  
            ans.extend(tmp)
            while j < n and s[j] == s[j - 1]:
                j += 1
            i = j
        return ''.join(ans)
            
