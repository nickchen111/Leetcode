# TC:O(D^3 * logr * logr) SC:O(D^2 * logr * logr)
def is_good_val(n:int) -> bool:
    # 更偷雞的寫法 百位數最高一定是1 所以就看另外兩個數字是否相等
    if n < 100:
        return n // 10 != n % 10
    return 1 < n // 10 % 10 < n % 10

    # s = str(n)
    # if len(s) <= 1: 
    #     return True
    # inc = all(s[i] < s[i+1] for i in range(len(s)-1))
    # if inc: 
    #     return True
    # dec = all(s[i] > s[i+1] for i in range(len(s)-1))
    # return dec
is_good_sum = [is_good_val(i) for i in range(136)]
class Solution:
    def countFancy(self, l: int, r: int) -> int:
        STATE_INIT = 0
        STATE_INC = 1
        STATE_DES = 2
        STATE_NOT_GOOD = 3
        def solve(n_str: str) -> int:
            n = len(n_str)
            @cache
            def dfs(i:int, current_sum: int, last_digit: int, status, is_limit: bool, is_num: bool) -> int:
                if i == n:
                    if not is_num: 
                        return 0
                    is_self_good = (status < 3)
                    is_sum_good = is_good_sum[current_sum]
                    return 1 if (is_self_good or is_sum_good) else 0

                res = 0
                if not is_num:
                    res += dfs(i + 1, 0, -1, 0, False, False)

                up = int(n_str[i]) if is_limit else 9
                low = 0 if is_num else 1
                
                for d in range(low, up + 1):
                    if not is_num:
                        res += dfs(i + 1, current_sum + d, d, 0, is_limit and (d == up), True)
                    else:
                        new_status = STATE_NOT_GOOD # 已破壞單調性
                        if status == STATE_INIT: # 還不確定 只填了一個數字
                            if d > last_digit: 
                                new_status = STATE_INC # 遞增
                            elif d < last_digit:
                                new_status = STATE_DES # 遞減
                        elif status == STATE_INC:
                            if d > last_digit: 
                                new_status = STATE_INC
                        elif status == STATE_DES:
                            if d < last_digit: 
                                new_status = STATE_DES
                        res += dfs(i + 1, current_sum + d, d, new_status, is_limit and (d == up), True)
                return res
            return dfs(0, 0, -1, 0, True, False)
        return solve(str(r)) - solve(str(l - 1))

# 預處理預處理枚舉子及優化: TC:O(D^2 * logr * logr) SC:O(D * logr * logr)
# 判断数位和 s 是否为好数
def is_good(s: int) -> bool:
    if s < 100:  # s 是个位数或者两位数
        return s // 10 != s % 10  # 十位和个位不相等即为好数
    # s 是三位数，其百位一定是 1
    return 1 < s // 10 % 10 < s % 10  # 只能严格递增


# 预处理数位和不是好数的好数（只有 139 个）
good_nums = []

# 枚举 {0,1,2,...,9} 的非空子集
for mask in range(1, 1 << 10):
    # 构造严格递减好数
    x = s = 0
    for i in range(9, -1, -1):  # 从大到小遍历子集中的元素
        if mask >> i & 1:
            x = x * 10 + i
            s += i
    if not is_good(s):
        good_nums.append(x)

    # 构造严格递增好数
    if mask & 1:  # 不能包含 0
        continue
    x = s = 0
    for i in range(1, 10):  # 从小到大遍历子集中的元素
        if mask >> i & 1:
            x = x * 10 + i
            s += i
    if not is_good(s):
        good_nums.append(x)

good_nums.sort()  # 方便二分求个数


class Solution:
    def countFancy(self, l: int, r: int) -> int:
        # 计算 [l, r] 内的数位和不是好数的好数的个数
        ans = bisect_right(good_nums, r) - bisect_left(good_nums, l)

        # 计算 [l, r] 内的数位和是好数的数的个数（这个数是不是好数都可以）
        low_s = list(map(int, str(l)))  # 避免在 dfs 中频繁调用 int()
        high_s = list(map(int, str(r)))
        n = len(high_s)
        diff_lh = n - len(low_s)

        @cache
        def dfs(i: int, digit_sum: int, limit_low: bool, limit_high: bool) -> int:
            if i == n:
                return 1 if is_good(digit_sum) else 0

            lo = low_s[i - diff_lh] if limit_low and i >= diff_lh else 0
            hi = high_s[i] if limit_high else 9

            res = 0
            start = lo

            # 通过 limit_low 和 i 可以判断能否不填数字，无需 is_num 参数
            if limit_low and i < diff_lh:
                # 不填数字，上界不受约束
                res = dfs(i + 1, 0, True, False)
                start = 1  # 下面填数字，从 1 开始填

            for d in range(start, hi + 1):
                res += dfs(i + 1,
                           digit_sum + d,
                           limit_low and d == lo,
                           limit_high and d == hi)

            return res

        return ans + dfs(0, 0, True, True)
