# TC:O(5 * 5 * n) SC:O(n)
# array版本
class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        '''
        n = 3 * 1e4
        找出substring滿足條件 長度至少K, 兩者頻率差最大
        只會有0 - 4
        鎖定兩個以後會去找前面哪個位置可以讓目前這兩個扣掉以後最長
        用一個map紀錄這兩個數字是 odd, odd or even, even or even. odd or odd, even
        '''
        ans = -inf
        s = list(ord(ch) - ord('0') for ch in s)
        n = len(s)
        for target1 in range(5):
            for target2 in range(5):
                if target1 == target2:
                    continue
                mp = [[(inf, inf, inf)] * 2 for _ in range(2)]
                mp[0][0] = (0, 0, -1)
                i = cnt1 = cnt2 = 0
                prev1, prev2 = 0, 0
                for j in range(n):
                    if j - i >= k:
                        if s[i] == target1:
                            prev1 += 1
                        elif s[i] == target2:
                            prev2 += 1
                        odd, even = prev1 % 2, prev2 % 2
                        diff = prev1 - prev2
                        if mp[odd][even][0] - mp[odd][even][1] > diff or mp[odd][even][0] == inf:
                            mp[odd][even] = (prev1, prev2, i)
                        i += 1
                    if s[j] == target1:
                        cnt1 += 1
                    elif s[j] == target2:
                        cnt2 += 1
                    odd, even = 0 if cnt1 % 2 else 1, 0 if cnt2 % 2 == 0 else 1
                    if mp[odd][even][0] != inf:
                        if cnt1 - mp[odd][even][0] and cnt2 - mp[odd][even][1] and j - mp[odd][even][2] >= k:
                            # print(j, target1, target2, cnt1, cnt2, mp[(odd, even)][0], mp[(odd, even)][1], cnt1 - cnt2 - mp[(odd, even)][0] + mp[(odd, even)][1])
                            ans = max(ans, cnt1 - cnt2 - mp[odd][even][0] + mp[odd][even][1])
        return ans

# 最初版map
class Solution:
    def maxDifference(self, s: str, k: int) -> int:
        '''
        n = 3 * 1e4
        找出substring滿足條件 長度至少K, 兩者頻率差最大
        只會有0 - 4
        鎖定兩個以後會去找前面哪個位置可以讓目前這兩個扣掉以後最長
        用一個map紀錄這兩個數字是 odd, odd or even, even or even. odd or odd, even
        '''
        ans = -inf
        s = list(ord(ch) - ord('0') for ch in s)
        n = len(s)
        for target1 in range(5):
            for target2 in range(5):
                if target1 == target2:
                    continue
                mp = {}
                mp[(0, 0)] = (0, 0, -1)
                i = cnt1 = cnt2 = 0
                prev1, prev2 = 0, 0
                for j in range(n):
                    if j - i >= k:
                        if s[i] == target1:
                            prev1 += 1
                        elif s[i] == target2:
                            prev2 += 1
                        odd, even = prev1 % 2, prev2 % 2
                        diff = prev1 - prev2
                        if (odd, even) in mp and mp[(odd, even)][0] - mp[(odd, even)][1] > diff or (odd, even) not in mp:
                            mp[(odd, even)] = (prev1, prev2, i)
                        i += 1
                    if s[j] == target1:
                        cnt1 += 1
                    elif s[j] == target2:
                        cnt2 += 1
                    odd, even = 0 if cnt1 % 2 else 1, 0 if cnt2 % 2 == 0 else 1
                    if (odd, even) in mp:
                        if cnt1 - mp[(odd, even)][0] and cnt2 - mp[(odd, even)][1] and j - mp[(odd, even)][2] >= k and (cnt1 - mp[(odd, even)][0]) % 2 and (cnt2 - mp[(odd, even)][1]) % 2 == 0:
                            # print(j, target1, target2, cnt1, cnt2, mp[(odd, even)][0], mp[(odd, even)][1], cnt1 - cnt2 - mp[(odd, even)][0] + mp[(odd, even)][1])
                            ans = max(ans, cnt1 - cnt2 - mp[(odd, even)][0] + mp[(odd, even)][1])
        return ans


                    
