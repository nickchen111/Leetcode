# TC:O(10^m + nlgn)  m = (n-1) / 2 SC:O(10^m * n)
class Solution:
    def countGoodIntegers(self, n: int, k: int) -> int:
        '''
        一個數字要能夠被k整除 並且要是回文串 然後長度是n會有多少種這種數字
        所以回文串枚舉一波 然後要判斷他可以被k整除 可以的話再做排列組合 看他能有多少種數字排法
        但要注意不重不漏 有可能重複 ex: 12321, 21312 可以用哈希表 紀錄排過的數字 從小到大排序
        再來就是排序了 他是有重複的排列個數 就會是n! / c0! c1! c2!...c9! 這是沒前導零的情況
        有前導零: ex: 10221 ->  4 * 5! (不考慮重複情況) 
        再除上重複的 4 * 5! / 2! * 2! * 2! 也就是 (n - c0) * (n - 1) ! / c0!...c9!
        '''
        fac = [factorial(i) for i in range(n + 1)]
        ans = 0
        vis = set()
        base = 10 ** ((n - 1) // 2)
        for i in range(base, base * 10):
            s = str(i)
            s += s[::-1][n % 2:]
            if int(s) % k:
                continue

            sorted_s = ''.join(sorted(s))
            if sorted_s in vis: 
                continue
            vis.add(sorted_s)

            cnt = Counter(sorted_s)
            res = (n - cnt['0']) * fac[n - 1]
            for c in cnt.values():
                res //= fac[c]
            ans += res
        return ans
