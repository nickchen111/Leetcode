# TC:O(n^3) SC:O(n) 最優解: 中心擴展法: TC:O(n^2) SC:O(n)
class Solution:
    def minOperations(self, s: str, t: str) -> int:
        n = len(s)
        def update(x:str, y:str) -> None:
            if x == y:
                return 
            if cnt[(y,x)] > 0:
                cnt[(y,x)] -= 1
            else:
                nonlocal op
                op += 1
                cnt[(x,y)] += 1
        rev_op = [[0] * n for _ in range(n)]
        for i in range(2 * n - 1): # 中心擴展法
            cnt = defaultdict(int)
            l, r = i // 2, (i + 1) // 2
            op = 1
            while l >= 0 and r < n:
                update(s[l], t[r])
                if l != r: # 同一個位置不需要計算兩次
                    update(s[r], t[l]) 
                rev_op[l][r] = op
                l -= 1
                r += 1
        f = [0] * (n + 1)
        for i in range(n):
            op = 0
            cnt = defaultdict(int)
            res = inf
            for j in range(i, -1, -1):
                x, y = s[j], t[j]
                update(s[j], t[j])
                res = min(res, f[j] + min(op, rev_op[j][i]))
            f[i + 1] = res
        return f[n]

        '''
        n^3
        for i in range(n):
            res = inf
            cnt = defaultdict(int)
            op = 0
            for j in range(i, -1, -1):
                x, y = s[j], t[j]
                if x != y:
                    if cnt[(y,x)] > 0:
                        cnt[(y,x)] -= 1
                    else:
                        cnt[(x,y)] += 1
                        op += 1
                # 開始判斷反轉狀況
                rev_cnt = defaultdict(int)
                rev_op = 1
                for p in range(j, i + 1):
                    x, y = s[p], t[i + j - p]
                    if x == y:
                        continue
                    if x != y:
                        if rev_cnt[(y,x)] > 0:
                            rev_cnt[(y,x)] -= 1
                        else:
                            rev_cnt[(x,y)] += 1
                            rev_op += 1
                res = min(res, f[j] + min(rev_op, op))
            f[i + 1] = res
        return f[n]
        '''
