class Solution:
    def subarrayMajority(self, nums: List[int], queries: List[List[int]]) -> List[int]:
        n, m = len(nums), len(queries)
        cnt = defaultdict(int)
        max_cnt = min_val = 0
        def add(x:int) -> None:
            nonlocal max_cnt, min_val
            cnt[x] += 1
            c = cnt[x]
            if c > max_cnt:
                max_cnt, min_val = c, x
            elif c == max_cnt:
                min_val = min(min_val, x)
        
        ans = [-1] * m
        block_size = ceil(n / sqrt(2 * m))
        qs = [] # (bid, ql, qr, threshold, qid) bid 是區塊編號 qid是index位置
        for i, (l, r, thre) in enumerate(queries):
            r += 1 # 右開區間
            if r - l > block_size:
                qs.append(((l // block_size), l, r, thre, i))
                continue
            for x in nums[l:r]:
                add(x)
            if max_cnt >= thre:
                ans[i] = min_val
            cnt.clear()
            max_cnt = 0
        qs.sort(key = lambda q: (q[0], q[2]))
        for i, (bid, ql, qr, thre, qid) in enumerate(qs):
            l0 = (bid + 1) * block_size
            if i == 0 or bid > qs[i - 1][0]: # 遍歷到一個新的塊
                r = l0 # 右端點起點 block邊界上
                cnt.clear()
                max_cnt = 0
            while r < qr:
                add(nums[r])
                r += 1
            tmp_cnt, tmp_val = max_cnt, min_val
            for x in nums[ql:l0]:
                add(x)
            if max_cnt >= thre:
                ans[qid] = min_val
            # 回滾
            max_cnt, min_val = tmp_cnt, tmp_val
            for x in nums[ql:l0]:
                cnt[x] -= 1
        return ans

