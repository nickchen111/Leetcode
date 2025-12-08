class Solution:
    def countTriples(self, n: int) -> int:
        '''
        可以用st 讓他n^2解
        '''
        st = set()
        for i in range(1, n + 1):
            st.add(i * i)
        ans = 0
        # print(st)
        for i in st:
            for j in st:
                if i - j in st and (i - j) < i and j < i:
                    ans += 1
                    # print(i, i - j, j)
        return ans