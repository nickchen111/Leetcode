# TC:O(divisor) SC:O(divisor)
class Solution:
    def fractionToDecimal(self, numerator: int, denominator: int) -> str:
        if numerator == 0:
            return "0"
        fraction = []
        if (numerator < 0) ^ (denominator < 0):
            fraction.append("-")
        dividend = abs(numerator)
        divisor = abs(denominator)
        fraction.append(str(dividend // divisor))
        remainder = dividend % divisor
        if remainder == 0:
            return "".join(fraction)
        
        fraction.append(".")
        mp = {}
        while remainder != 0:
            if remainder in mp:
                fraction.insert(mp[remainder], "(")
                fraction.append(")")
                break
            mp[remainder] = len(fraction)
            remainder *= 10
            fraction.append(str(remainder // divisor))
            remainder %= divisor
        return "".join(fraction)
