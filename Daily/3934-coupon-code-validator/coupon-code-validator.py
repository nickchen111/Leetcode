class Solution:
    def validateCoupons(self, code: List[str], businessLine: List[str], isActive: List[bool]) -> List[str]:
        arr = []
        n = len(code)
        for i in range(n):
            if not isActive[i] or businessLine[i] not in {"electronics", "grocery", "pharmacy", "restaurant"} or not code[i]:
                continue
            flag = True
            for j in range(len(code[i])):
                if not ("a" <= code[i][j] <= "z" or "A" <= code[i][j] <= "Z" or '0' <= code[i][j] <= "9" or code[i][j] == '_'):
                    flag = False
                    break
            if flag:
                arr.append((businessLine[i], code[i]))
        arr.sort(key=lambda x: (x[0], x[1]))
        return [y for x, y in arr]
                