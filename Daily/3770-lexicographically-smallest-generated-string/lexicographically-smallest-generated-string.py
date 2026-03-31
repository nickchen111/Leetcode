class Solution:
    def calc_z(self, s: str) -> List[int]:
        n = len(s)
        z = [0] * n
        box_l, box_r = 0, 0  # z-box 左右边界（闭区间）
        for i in range(1, n):
            if i <= box_r:
                z[i] = min(z[i - box_l], box_r - i + 1)
            while i + z[i] < n and s[z[i]] == s[i + z[i]]:
                box_l, box_r = i, i + z[i]
                z[i] += 1
        z[0] = n
        return z

    def generateString(self, s: str, t: str) -> str:
        n, m = len(s), len(t)
        ans = ['?'] * (n + m - 1)

        # 处理 T
        z = self.calc_z(t)
        pre = -m
        for i, b in enumerate(s):
            if b != 'T':
                continue
            size = max(pre + m - i, 0)
            # t 的长为 size 的前后缀必须相同
            if size > 0 and z[m - size] < size:
                return ""
            # size 后的内容都是 '?'，填入 t
            ans[i + size: i + m] = t[size:]
            pre = i

        # 计算 <= i 的最近待定位置
        pre_q = [-1] * len(ans)
        pre = -1
        for i, c in enumerate(ans):
            if c == '?':
                ans[i] = 'a'  # 待定位置的初始值为 a
                pre = i
            pre_q[i] = pre

        # 找 ans 中的等于 t 的位置，可以用 KMP 或者 Z 函数
        z = self.calc_z(t + ''.join(ans))

        # 处理 F
        i = 0
        while i < n:
            if s[i] != 'F':
                i += 1
                continue
            # 子串必须不等于 t
            if z[m + i] < m:
                i += 1
                continue
            # 找最后一个待定位置
            j = pre_q[i + m - 1]
            if j < i:  # 没有
                return ""
            ans[j] = 'b'
            i = j + 1  # 直接跳过 j

        return ''.join(ans)