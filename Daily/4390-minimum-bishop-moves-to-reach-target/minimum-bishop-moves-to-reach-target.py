class Solution:
    def minBishopMoves(self, source: list[int], target: list[int]) -> int:
        sr, sc = source
        tr, tc = target

        # 已經在 target
        if source == target:
            return 0

        # 不同顏色，永遠到不了
        if (sr + sc) % 2 != (tr + tc) % 2:
            return -1

        # 同一條 diagonal
        if abs(sr - tr) == abs(sc - tc):
            return 1

        # 同色但不同 diagonal
        return 2