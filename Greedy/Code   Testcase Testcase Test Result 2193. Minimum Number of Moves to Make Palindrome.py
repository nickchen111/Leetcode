# TC:O(n * n) SC:O(1)
class Solution:
    def minMovesToMakePalindrome(self, s: str) -> int:
        '''
        可以任意swap兩個相鄰的元素，問說最少swap多少次可以讓他變回文串
        會想到兩點切入 1. 回文串性質 2. 最少?
        如果想讓某元素當頭，就會耗費他要走到的位置到他之前的cost去翻他
        ex: aabb 想讓pos = 2 到pos = 0 需要翻轉兩次，翻完後其他元素相對位置保持不變
        因為題目可以接受n^2 會讓我想到可以去直接枚舉要修改的點在最右側的哪 根據臨項交換法可以證明每次都修改最左側與最右側的點即可
        '''
        n = len(s)
        s = list(s)
        res = 0
        while s:
            i = s.index(s[-1])
            if i==len(s)-1: res+=i//2
            else:
                res+=i
                s.pop(i)
            s.pop()
        return res
        '''
        以下是自己實作寫法 上面是可以直接call python api 
        i, j = 0, n - 1
        ans = 0
        while i < j:
            k = j
            while k != i and s[k] != s[i]:
                k -= 1
            if k != i and s[i] == s[k]:
                while k < j:
                    ans += 1
                    s[k], s[k + 1] = s[k + 1], s[k]
                    k += 1
                j -= 1
            else:
                ans += n // 2 - i
            # j -= 1
            i += 1
        return ans
        '''
