class Solution:
    def evaluate(self, s: str, knowledge: list[list[str]]) -> str:
        mp = {}
        for i in range(len(knowledge)):
            mp[knowledge[i][0]] = knowledge[i][1]
        ans = []
        j = 0
        while j < len(s):
            if s[j] == '(':
                j += 1
                word = ''
                while s[j] != ')':
                    word += s[j]
                    j += 1
                print(s[j])
                if word in mp:
                    ans += mp[word]
                else:
                    ans += "?"
            else:
                ans += s[j]
            j += 1
        return "".join(ans)
                