# TC:O(nlogn) SC:O(n)
class Solution:
    def maxTotal(self, value: List[int], limit: List[int]) -> int:
        # 全貪心寫法
        groups = defaultdict(list)
        for l, v in zip(limit, value):
            groups[l].append(v)
        ans = 0
        for lim, v in groups.items():
            ans += sum(nlargest(lim, v))
        return ans

        '''
        heap
        # not_choose: (limit, -value)  => 按 limit 小到大，value 大到小
        not_choose = []
        for v, l in zip(value, limit):
            heapq.heappush(not_choose, [l, -v])
        active = []
        total = 0
        cnt = 0
        while not_choose:
            limit_val, neg_val = heappop(not_choose)
            val = -neg_val
            if cnt < limit_val:
                # print(total, val)
                total += val
                cnt += 1
                heappush(active, limit_val)
            
                while active and active[0] <= cnt:
                    l = heappop(active)
                    
                while not_choose and not_choose[0][0] <= cnt:
                    heappop(not_choose)
                    
                cnt = len(active)
        return total
        '''
