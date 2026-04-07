class Robot:
    def __init__(self, width: int, height: int) -> None:
        self.w = width
        self.h = height
        self.s = 0

    def step(self, num: int) -> None:
        # 由于机器人只能走外圈，那么走 (w+h-2)*2 步后会回到起点
        # 把 s 取模调整到 [1, (w+h-2)*2]，这样不需要特判 s == 0 时的方向
        self.s = (self.s + num - 1) % ((self.w + self.h - 2) * 2) + 1

    def _getState(self) -> Tuple[int, int, str]:
        w, h, s = self.w, self.h, self.s
        if s < w:
            return s, 0, "East"
        if s < w + h - 1:
            return w - 1, s - w + 1, "North"
        if s < w * 2 + h - 2:
            return w * 2 + h - s - 3, h - 1, "West"
        return 0, (w + h) * 2 - s - 4, "South"

    def getPos(self) -> List[int]:
        x, y, _ = self._getState()
        return [x, y]

    def getDir(self) -> str:
        return self._getState()[2]
