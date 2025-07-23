class Solution:
    def maximumGain(self, s: str, x: int, y: int) -> int:
        '''
        一律抓ab 如果 x < y -> reverse(s), swap(x, y)
        後續就可以用stack做消消樂 最後再看有多少個ba即可
        '''
        if x < y:
            s = reversed(s)
            x, y = y, x
        st = [] # 模擬stack
        ans = 0
        for ch in s:
            if len(st) > 0 and st[-1] + ch == 'ab':
                ans += x
                st.pop()
                continue
            st.append(ch)
        st2 = []
        for ch in st:
            if len(st2) > 0 and st2[-1] + ch == 'ba':
                ans += y
                st2.pop()
                continue
            st2.append(ch)
        return ans