# TC:O(sqrt3(n) * sqrt3(n)) SC:O(sqrt3(n) * sqrt3(n))
class Solution:
    def findGoodIntegers(self, n: int) -> list[int]:
        '''
        用3次方去枚舉看有哪些數字可以達到
        '''
        limit = int(n ** (1/3)) + 2
        cnt = Counter()
        for i in range(1, limit):
            x = i ** 3
            if x > n:
                break
            for j in range(i, limit):
                val = x + j ** 3
                if val > n:
                    break
                cnt[val] += 1
        ans = [x for x in cnt if cnt[x] >= 2]
        return sorted(ans)
                
                
            
