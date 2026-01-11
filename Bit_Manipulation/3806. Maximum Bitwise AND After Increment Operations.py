# 最優解 TC:O(n * logn * logU) SC:O(n)
class Solution:
    def maximumAND(self, nums: List[int], k: int, m: int) -> int:
        ops = [0] * len(nums)  # 每个数的操作次数
        ans = 0
        max_width = (max(nums) + k).bit_length()
        for bit in range(max_width - 1, -1, -1):
            target = ans | (1 << bit)  # 注意 target 要带着 ans 已经填好的 1
            for i, x in enumerate(nums):
                j = (target & ~x).bit_length()
                # j-1 是从高到低第一个 target 是 1，x 是 0 的比特位
                # target = 10110
                #      x = 11010
                #            ^
                #           j-1
                # x 高于 j-1 的比特位不变，其余变成和 target 一样
                # 上面的例子要把 010 变成 110
                mask = (1 << j) - 1
                ops[i] = (target & mask) - (x & mask)

            # 贪心，取前 m 小的操作次数
            ops.sort()
            if sum(ops[:m]) <= k:
                ans = target  # 答案的 bit 位可以填 1
        return ans


# 比賽我的寫法 
class Solution:
    def maximumAND(self, nums: List[int], k: int, m: int) -> int:
        ans = 0
        for i in range(30, -1, -1):
            test_target = ans | (1 << i)
            
            costs = []
            for x in nums:
                y = 0
                possible_y = x | test_target
                curr_y = 0
                for bit in range(30, -1, -1):
                    t_bit = (test_target >> bit) & 1
                    x_bit = (x >> bit) & 1
                    if t_bit:
                        curr_y |= (1 << bit)
                        if not x_bit:
                            for low_bit in range(bit - 1, -1, -1):
                                if (test_target >> low_bit) & 1:
                                    curr_y |= (1 << low_bit)
                            possible_y = curr_y
                            break
                    else:
                        if x_bit:
                            curr_y |= (1 << bit)
                
                costs.append(possible_y - x)
            
            costs.sort()
            if sum(costs[:m]) <= k:
                ans = test_target
                
        return ans
