#3143. Maximum Points Inside the Square


# TC:O(nlgn) SC:O(n)
class Solution:
    def maxPointsInsideSquare(self, points: List[List[int]], s: str) -> int:
        dict_of_set = defaultdict(set) # 可以創建一個哈希表 沒有賦值的會自動value 為 set()

        for (x,y),c in zip(points, s):
            c = ord(c) - ord('a') # 將字元轉成0-25, ord 為Unicode 
            d = max(abs(x), abs(y))
            if c in dict_of_set[d]:
                dict_of_set[d].add(-1)
            else :
                dict_of_set[d].add(c)
        
        union = {-1}
        for d, st in sorted(dict_of_set.items()): # sorted 函式 
            if st & union:
                break
            union |= st
        return len(union)-1
