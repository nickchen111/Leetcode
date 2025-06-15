# TC:O(n) SC:O(1)
class Solution:
    def generateTag(self, s: str) -> str:
        ans = ['#']
        n = len(s)
        for i, x in enumerate(s.split()):
            x = x.capitalize() if i else x.lower()
            ans.append(x)
        return ''.join(ans)[:100]
        '''
        i = 0
        first = True
        while i < n and len(ans) < 100:
            while i < n and s[i] == ' ':
                i += 1
            j = i
            if first:
                while j < n and s[j] != ' ' and len(ans) < 100:
                    ans += s[j].lower()
                    j += 1
                first = False
            else:
                 while j < n and s[j] != ' ' and len(ans) < 100:
                    if j == i:
                        ans += s[j].upper()
                    else:
                        ans += s[j].lower()
                    j += 1
            i = j + 1
        return ans
        '''
                    
