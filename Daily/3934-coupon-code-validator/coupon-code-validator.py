BUSINESS_LINE_TO_CATEGORY = {
    "electronics": 0,
    "grocery": 1,
    "pharmacy": 2,
    "restaurant": 3,
}

class Solution:
    def validateCoupons(self, code: List[str], businessLine: List[str], isActive: List[bool]) -> List[str]:
        groups = [[] for _ in range(len(BUSINESS_LINE_TO_CATEGORY))]
        for s, bus, active in zip(code, businessLine, isActive):
            category = BUSINESS_LINE_TO_CATEGORY.get(bus, -1)
            if s and category >= 0 and active and \
               all(c == '_' or c.isalnum() for c in s):
                groups[category].append(s)

        ans = []
        for g in groups:
            g.sort()
            ans += g
        return ans
