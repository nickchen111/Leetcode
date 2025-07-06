# TC:O(Llogn) L為code[i]長度之和 SC:O(L or n) 取決於語言是用引用or拷貝
class Solution:
    def validateCoupons(self, code: List[str], businessLine: List[str], isActive: List[bool]) -> List[str]:
        ans = []
        checkBusiness = ["electronics", "grocery", "pharmacy", "restaurant"]
        for i in range(len(code)):
            if businessLine[i] not in checkBusiness or not isActive[i] or not code[i]:
                continue
            valid = True
            for ch in code[i]:
                if not (ch.isalnum() or ch == '_'):
                    valid = False
                    break
            if valid:
                ans.append((businessLine[i], code[i]))
        ans.sort()
        return [code for _, code in ans]
