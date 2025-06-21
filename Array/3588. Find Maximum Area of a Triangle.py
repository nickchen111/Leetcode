# TC:O(n) SC:O(n)
class Solution:
    def maxArea(self, coords: List[List[int]]) -> int:
        '''
        將點x軸分類 然後找出最高的y在哪就可以得到最大三角形
        '''
        x_base, y_base = defaultdict(list), defaultdict(list)
        y_high, x_high = 0, 0
        x_low, y_low = inf, inf
        for x,y in coords:
            x_base[x].append(y)
            y_base[y].append(x)
            x_high = max(x_high, x)
            y_high = max(y_high, y)
            x_low = min(x, x_low)
            y_low = min(y, y_low)
        # 判斷哪個x_base可以有最大底
        ans = -1
        for x, arr in x_base.items():
            if len(arr) <= 1:
                continue
            arr.sort()
            base = arr[-1] - arr[0]
            if x < x_high:
                ans = max(ans, base * (x_high - x))
            if x > x_low:
                ans = max(ans, base * (x - x_low))
        for y, arr in y_base.items():
            if len(arr) <= 1:
                continue
            arr.sort()
            base = arr[-1] - arr[0]
            if y < y_high:
                ans = max(ans, base * (y_high - y))
            if y > y_low:
                ans = max(ans, base * (y - y_low))
        return ans
            
        
