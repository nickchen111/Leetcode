class Solution:
    def pyramidTransition(self, bottom: str, allowed: List[str]) -> bool:
        mp = defaultdict(list)
        for allow in allowed:
            mp[allow[:2]].append(allow[2])

        def dfs(prev:List[str], i:int, cur:List[str]) -> bool:
            if len(cur) == 1 and len(prev) == 2:
                return True
            if i == len(prev) - 1:
                if dfs(cur, 0, []):
                    return True
                return False
            for cand in mp[prev[i] + prev[i + 1]]:
                cur.append(cand)
                if dfs(prev, i + 1, cur):
                    return True
                cur.pop()
            return False
        return dfs(list(bottom), 0, [])