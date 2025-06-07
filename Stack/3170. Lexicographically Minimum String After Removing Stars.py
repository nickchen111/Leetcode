# TC:O(26*n) SC:O(26 + n) Bit: TC:O(n) SC:O(n + 26)
class Solution:
    def clearStars(self, s: str) -> str:
        '''
        將26個字母記起來，遇到*就從第一個開始判斷是否可刪除最後再搭起來
        '''
        s = list(s)
        stacks = [[] for _ in range(26)]
        mask = 0
        for i, c in enumerate(s):
            if c != '*':
                c = ord(c) - ord('a')
                stacks[c].append(i)
                mask |= 1 << c  # 標記第c個棧為非空
            else:
                lb = mask & -mask
                st = stacks[lb.bit_length() - 1]
                s[st.pop()] = '*'
                if not st:
                    mask ^= lb  # 標記棧為空
        return ''.join(c for c in s if c != '*')
      '''
      pos = [[] for _ in range(26)]
        s = list(s)
        n = len(s)
        for i, ch in enumerate(s):
            if ch == '*':
                for c in range(0, 26):
                    if len(pos[c]) > 0:
                        s[pos[c][-1]] = ''
                        pos[c].pop()
                        break
                s[i] = ''
            else:
                c = ord(ch) - ord('a')
                pos[c].append(i)
        
        # all_pos = set()
        # for c in range(0, 26):
        #     for p in pos[c]:
        #         all_pos.add(p)
        ans = []
        for i in range(n):
            # if i in all_pos:
            #     ans.append(s[i])
            if s[i]:
                ans.append(s[i])
        return ''.join(ans)
      '''
