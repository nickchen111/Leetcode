# TC:O(MlgM) M = nm3^m SC:O(M)
class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        u = 1 << n
        max_time = [0] * u
        for i in range(n):
            j = 1 << i
            for mask in range(j):
                max_time[mask| j] = max(max_time[mask], time[i])
        sub_mask = [[] for _ in range(u)]
        for i in range(u):
            sub = i
            while sub:
                if sub.bit_count() <= k:
                    sub_mask[i].append(sub)
                sub = (sub - 1) & i
        h = []
        minCost = [[inf] * u for _ in range(m)]
        def push(cost:float, stage:int, mask:int) -> None: # cost, mask, stage
            if cost < minCost[stage][mask]:
                minCost[stage][mask] = cost
                heappush(h, (cost, stage, mask))
        push(0, 0, u - 1)
        while h:
            cost, stage, left = heappop(h)
            # 先判斷是否已經沒人要送
            if left == 0:
                return cost
            if cost > minCost[stage][left]:
                continue
            # 有人要送 去枚舉子集
            for sub in sub_mask[left]:
                nxt_cost = max_time[sub] * mul[stage]
                nxt_stage = (stage + floor(nxt_cost)) % m 
                if sub == left: # 送完
                    push(nxt_cost + cost, nxt_stage, 0)
                # 沒送完 枚舉目前要送回來的人與後續stage
                s = (u - 1) ^ left ^ sub
                while s:
                    lb = s & -s # lowbit
                    return_time = max_time[lb] * mul[nxt_stage]
                    push(cost + nxt_cost + return_time, (nxt_stage + floor(return_time)) % m, left ^ sub ^ lb)
                    s ^= lb
        return -1
#可以多加一個狀態direction 降低n的時間複雜度 TC:O(MlgM) M = m3^m SC:O(M)
class Solution:
    def minTime(self, n: int, k: int, m: int, time: List[int], mul: List[float]) -> float:
        u = 1 << n
        max_time = [0] * u
        for i, t in enumerate(time):
            high_bit = 1 << i
            for mask in range(high_bit):
                max_time[high_bit | mask] = max(max_time[mask], t)

        sub_masks = [[] for _ in range(u)]
        for i in range(u):
            sub = i
            while sub:
                if sub.bit_count() <= k:
                    sub_masks[i].append(sub)
                sub = (sub - 1) & i

        dis = [[[inf, inf] for _ in range(u)] for _ in range(m)]
        h = []

        def push(d: float, stage: int, mask: int, direction: int) -> None:
            if d < dis[stage][mask][direction]:
                dis[stage][mask][direction] = d
                heappush(h, (d, stage, mask, direction))

        push(0, 0, u - 1, 0)

        while h:
            d, stage, left, direction = heappop(h)
            if left == 0:
                return d
            if d > dis[stage][left][direction]:
                continue
            if direction == 0:
                for sub in sub_masks[left]:
                    cost = max_time[sub] * mul[stage]
                    push(d + cost, (stage + floor(cost)) % m, left ^ sub, 1)
            else:
                s = (u - 1) ^ left
                while s:
                    lb = s & -s
                    cost = max_time[lb] * mul[stage]
                    push(d + cost, (stage + floor(cost)) % m, left ^ lb, 0)
                    s ^= lb
        return -1

            
