class Solution:
    def minimumPushes(self, word: str) -> int:
        mp = defaultdict(int)
        for w  in word:
            mp[w] += 1
        arr = [x for y,x in mp.items()]
        arr.sort(reverse = True)
        cnt = 1
        chance = 8
        ans = 0
        for a in arr:
            if chance == 0:
                cnt += 1
                chance = 8
            chance -= 1
            ans += cnt * a
        return ans