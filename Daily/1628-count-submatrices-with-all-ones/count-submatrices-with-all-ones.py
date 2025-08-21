class Solution:
    def numSubmat(self, mat: List[List[int]]) -> int:
        m, n = len(mat), len(mat[0])
        ans = 0
        cnt = [0] * (n + 1)
        def cal(cnt: List[int]) -> int:
            st = []
            st.append(0)
            tot = ret = 0
            for i in range(1, len(cnt)):
                while st and cnt[st[-1]] > cnt[i]:
                    h = cnt[st[-1]] - cnt[i]
                    w1 = st[-1]
                    st.pop()
                    w2 = st[-1]
                    tot -= h * (w1 - w2)
                st.append(i)
                tot += cnt[i]
                ret += tot
            return ret
        for i in range(m):
            for j in range(n):
                if mat[i][j]:
                    cnt[j + 1] += 1
                else:
                    cnt[j + 1] = 0
            ans += cal(cnt)
        return ans