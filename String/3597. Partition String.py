# 字符串哈希 TC:O(n) SC:O(n)
MOD = 10 ** 9 + 7
HASH = 31
class Solution:
    def partitionString(self, s: str) -> List[str]:
        ans = []
        n = len(s)
        st = set()
        i = 0
        ss = []
        while i < n:
            tmp = ord(s[i])
            ss.append(s[i])
            j = i + 1
            while j < n and tmp in st:
                tmp = (tmp * HASH + ord(s[j])) % MOD
                ss.append(s[j])
                j += 1
            if tmp not in st: 
                ans.append(''.join(ss))
                ss = []
                st.add(tmp)
            i = j
        return ans
# Brute TC:O(n * sqrt(n)) SC:O(n)
class Solution:
    def partitionString(self, s: str) -> List[str]:
        s = list(s)
        ans = []
        n = len(s)
        st = set()
        i = 0
        while i < n:
            tmp = s[i]
            j = i + 1
            while j < n and tmp in st:
                tmp += s[j]
                j += 1
            if tmp not in st: ans.append(tmp)
            st.add(tmp)
            i = j
        return ans
                
