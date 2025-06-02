# Greedy: TC:O(n * n) SC:O(1) BIT: TC:O(nlgn) SC:O(n)
class FenwickTree:
    def __init__(self, n: int):
        self.tree = [0] * (n + 1) 
    def update(self, i: int, val: int) -> None:
        while i < len(self.tree):
            self.tree[i] += val
            i += i & -i
    def pre(self, i: int) -> int:
        res = 0
        while i > 0:
            res += self.tree[i]
            i &= i - 1
        return res
    def query(self, l: int, r: int) -> int:
        if r < l:
            return 0
        return self.pre(r) - self.pre(l - 1)
class Solution:
    def minMovesToMakePalindrome(self, s: str) -> int:
        '''
        赤裸裸的逆序對 題型 需要相鄰兩個交換 然後按照某種規則換到希望的狀態
        1. 貪心n^2解
        2. 樹狀數組
        樹狀數組來解最難的點都是在如何找出要達到的最終型態 -> 這題來說是字串
        回文串性質 even 就兩邊match odd 放中間 所以我就是先枚舉每個字元的數量 然後去拼湊出他的左半邊
        '''
        n = len(s)
        mp = Counter(s)
        final_s = ""
        odd = ""
        for i in range(n):
            if mp[s[i]] == 0:
                continue
            if mp[s[i]] % 2 == 0 or (mp[s[i]] % 2 and mp[s[i]] >= 3):
                final_s += s[i]
                mp[s[i]] -= 2
            else:
                odd = s[i]
                mp[s[i]] -= 1
        if odd:
            final_s += odd
            final_s += ''.join(reversed(final_s[:-1]))
        else:
            final_s += ''.join(reversed(final_s[:]))
        
        # 開始比較兩個字串的不同處 轉成下標用逆序對
        idx = defaultdict(list)
        ns = ''.join(reversed(s))
        for i in range(n):
            idx[ns[i]].append(n - 1 - i) # 這樣前面的就會被取用
        tree = FenwickTree(n)
        ans = 0
        for i in range(n):
            index = idx[final_s[i]][-1]
            idx[final_s[i]].pop()
            ans += i - tree.pre(index + 1) # 找出前面有多少個比我大的 我就需要換幾次
            tree.update(index + 1, 1)
        return ans
        '''
        call api 找到下一個相同位置 效率極高
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
        '''
        以下是自己實作貪心寫法 上面是可以直接call python api 
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
