MOD = 1_000_000_007

class Fancy:
    def __init__(self):
        self.vals = []
        self.add = 0
        self.mul = 1

    def append(self, val: int) -> None:
        self.vals.append((val - self.add) * pow(self.mul, -1, MOD) % MOD)

    def addAll(self, inc: int) -> None:
        self.add += inc

    def multAll(self, m: int) -> None:
        self.mul = self.mul * m % MOD
        self.add = self.add * m % MOD

    def getIndex(self, idx: int) -> int:
        if idx >= len(self.vals):
            return -1
        return (self.vals[idx] * self.mul + self.add) % MOD