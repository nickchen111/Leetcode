class Solution:
    def sortableIntegers(self, nums: list[int]) -> int:
        '''
        一定要是類似這種的才能rotate
        8,9,10,1,2,3,4,5,6
        也就是第二段的尾不能超過第一段的頭
        8,9,19,4,5,6,1,2,3 這樣就不行 一定要是兩段
        兩段都是non-decreasing
        解法就會是枚舉他的因數有哪些 這些因數都去跑一次拆解看是否符合狀況
        做法:
        1. 先做完因式分解
        2. 枚舉因式
            2.1取每段subarray 都是因式長度
            2.2這段subarray 要馬都是排序好的 要馬是兩段式 滿足第二段的尾不能超過第一段的頭
            2.3 記錄這段的最大數字 到時候要比下一段的頭 <=
            2.4將結果記錄下來有幾個
        每段確認 cur_head <= prev_tail;
        內部確認 1. 兩段式 or 一段 2. 兩段的話要確認 1st head >= 2nd tail
        '''

        n = len(nums)
        
        # 找所有 n 的因數
        divisors = []
        for i in range(1, isqrt(n) + 1):
            if n % i == 0:
                divisors.append(i)
                if i != n // i:
                    divisors.append(n // i)
        
        ans = 0
        for k in divisors:
            prev_max = -inf
            ok = True
            
            for start in range(0, n, k):
                end = start + k  # 這段是 nums[start:end]
                
                # 找下降點數量
                drop = -1
                for i in range(start, end - 1):
                    if nums[i] > nums[i + 1]:
                        if drop != -1:   # 已經有一個了 → 超過一個
                            ok = False
                            break
                        drop = i
                if not ok:
                    break
                
                # 有下降點時，還要確認 nums[end-1] <= nums[start]
                if drop != -1 and nums[end - 1] > nums[start]:
                    ok = False
                    break
                
                # 這段 rotate 後的 min / max
                # min 是整段最小值，max 是整段最大值
                # 但因為這段是 sorted 的 rotation，min = nums[drop+1]（若有下降點）或 nums[start]
                # max = nums[drop]（若有下降點）或 nums[end-1]
                if drop == -1:
                    seg_min = nums[start]
                    seg_max = nums[end - 1]
                else:
                    seg_min = nums[drop + 1]
                    seg_max = nums[drop]
                
                # 段間條件
                if seg_min < prev_max:
                    ok = False
                    break
                prev_max = seg_max
            
            if ok:
                ans += k
        
        return ans
                    
                    
                    
                
                