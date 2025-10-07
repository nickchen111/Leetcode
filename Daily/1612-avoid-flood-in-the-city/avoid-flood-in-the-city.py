class Solution:
    def avoidFlood(self, rains: List[int]) -> List[int]:
        '''
        將這些機會存起來 當有個湖被flood時 找一個在他之前 但是在第一個位置之後的dry
        '''
        mp = defaultdict(int)
        st = []
        ans = [-1] * len(rains)
        for i, r in enumerate(rains):
            if r == 0:
                st.append(i)
                ans[i] = 1
            else:
                if r in mp:
                    prev_pos = mp[r] # 找他之後的第一個位置
                    idx = bisect_left(st, prev_pos)
                    if idx < len(st):
                        ans[st[idx]] = r
                        st.remove(st[idx])
                        mp[r] = i
                    else:
                        return [] 
                else:
                    mp[r] = i
        return ans
                    

