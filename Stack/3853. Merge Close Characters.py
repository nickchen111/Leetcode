# TC:O(n) SC:O(M) M <= 26
class Solution:
    def mergeCharacters(self, s: str, k: int) -> str:
        last_pos = {}
        ans = []
        
        for ch in s:
            if ch not in last_pos or len(ans) - last_pos[ch] > k:
                last_pos[ch] = len(ans)
                ans.append(ch)
        return "".join(ans)
                    
