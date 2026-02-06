# TC:O(n) SC:O(n)
class Solution:
    def reverseByType(self, s: str) -> str:
        alpha = []
        non_alpha = []
        for ch in s:
            if ch.isalpha():
                alpha.append(ch)
            else:
                non_alpha.append(ch)
        alpha = alpha[::-1]
        non_alpha = non_alpha[::-1]
        ans = []
        i = j = 0
        for ch in s:
            if ch.isalpha():
                ans.append(alpha[i])
                i += 1
            else:
                ans.append(non_alpha[j])
                j += 1
        return "".join(ans)
                
