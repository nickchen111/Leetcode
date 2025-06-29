# TC:O(n^2) SC:O(n)
class Solution:
    def findCoins(self, numWays: List[int]) -> List[int]:
        '''
        有多少方法可以獲取某個數值 類似背包求方法數量 現在倒過來去選擇有哪些
        每個都去做背包 如果遇到某一個少1 就把自己新增上去
        '''
        n = len(numWays)
        dp = [0] * (n + 1)
        dp[0] = 1
        mx = max(numWays)
        ans = []
        for i, way in enumerate(numWays, 1):
            if way == dp[i]:
                continue
            if way != dp[i] + 1:
                return []
            ans.append(i)
            for c in range(i, n + 1): # 這裡隱含了多次使用物品
                dp[c] += dp[c - i] 
                if dp[c] > mx + 1: # 這段可略 但如果是其他語言可能會溢出
                    return []
        return ans

# 比䈢時寫法:
class Solution:
    def findCoins(self, numWays: List[int]) -> List[int]:
        '''
        有多少方法可以獲取某個數值 類似背包求方法數量 現在倒過來去選擇有哪些
        每個都去做背包 如果遇到某一個少1 就把自己新增上去
        '''
        st = set()
        n = len(numWays)
        for i, way in enumerate(numWays):
            num = i + 1
            dp = [0] * (num + 1)
            dp[0] = 1
            for x in st:
                for c in range(1, num + 1):
                    if x > c:
                        continue
                    dp[c] += dp[c - x]
            if dp[num] + 1 == way:
                st.add(num)
            elif dp[num] != way:
                return []
        return list(sorted(st))
                    
                
            
