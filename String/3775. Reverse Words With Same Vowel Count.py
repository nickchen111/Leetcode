# TC:O(n) SC:O(1)
class Solution:
    def reverseWords(self, s: str) -> str:
        s = s.split(" ")
        n = len(s)
        cnt = 0
        st = {'a', 'e', 'i', 'o', 'u'}
        for i in range(len(s[0])):
            if s[0][i] in st:
                cnt += 1
       
        for i in range(1, n):
            cntt = 0
            for j in range(len(s[i])):
                if s[i][j] in st:
                    cntt += 1
            if cntt == cnt:
                s[i] = s[i][::-1]
        return " ".join(s)
        
            
