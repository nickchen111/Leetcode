# TC:O(n) SC:O(n)
class Solution:
    def processStr(self, s: str, k: int) -> str:
        ops = []
        length = 0
        for ch in s:
            if ch.islower():
                ops.append(('add', ch, length))
                length += 1
            elif ch == '*':
                if length > 0:
                    ops.append(('pop', '', length))
                    length -= 1
                else:
                    ops.append(('nop', '', length))
            elif ch == '#':
                ops.append(('#', '', length))
                length *= 2
            elif ch == '%':
                ops.append(('%', '', length))

        if k >= length:
            return '.'
        for i in range(len(ops) - 1, -1, -1):
            op, val, prev_len = ops[i]
            if op == 'add':
                if k == prev_len:
                    return val
            elif op == 'pop':
                if k == prev_len:
                    return '.'
            elif op == '#':
                if k >= prev_len:
                    k -= prev_len
            elif op == '%':
                '''
                k = 5
                prev_len = 6
                x x x x x x
                '''
                k = prev_len - 1 - k
        return '.'
