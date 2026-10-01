class Solution:
    def isValid(self, s: str) -> bool:
        st = []
        mp = {}
        mp[')'] = '('
        mp['}'] = '{'
        mp[']'] = '['
        for ch in s:
            if ch in ')]}':
                if not st or st[-1] != mp[ch]:
                    return False
                st.pop()
            else:
                st.append(ch)
        return True if not st else False
