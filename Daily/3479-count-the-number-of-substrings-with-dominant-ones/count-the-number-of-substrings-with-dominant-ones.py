# 手写 max 更快
max = lambda a, b: b if b > a else a

class Solution:
    def numberOfSubstrings(self, s: str) -> int:
        pos0 = [-1]  # 哨兵，方便处理 cnt0 达到最大时的计数
        total1 = 0  # [0,r] 中的 1 的个数
        ans = 0

        for r, ch in enumerate(s):
            if ch == '0':
                pos0.append(r)  # 记录 0 的下标
            else:
                total1 += 1
                ans += r - pos0[-1]  # 单独计算不含 0 的子串个数

            # 倒着遍历 pos0，就相当于在从小到大枚举 cnt0
            for i in range(len(pos0) - 1, 0, -1):
                cnt0 = len(pos0) - i
                if cnt0 * cnt0 > total1:
                    break
                p, q = pos0[i - 1], pos0[i]
                cnt1 = r - q + 1 - cnt0  # [q,r] 中的 1 的个数 = [q,r] 的长度 - cnt0
                ans += max(q - max(cnt0 * cnt0 - cnt1, 0) - p, 0)

        return ans
