# TC:O(n) SC:O(n)
class Solution:
    def majorityFrequencyGroup(self, s: str) -> str:
        mp = Counter(s)
        groups = defaultdict(list)
        mx = 0
        for ch, cnt in mp.items():
            groups[cnt].append(ch)
            if (len(groups[cnt]), cnt) > (len(groups[mx]), mx): # tuple 好用
                mx = cnt
        return "".join(groups[mx])
        
                
