class Solution:
    def minimumScore(self, nums: List[int], edges: List[List[int]]) -> int:
        '''
        任意拿掉兩個edge 必定會有3棵tree ? => yes
        要求出拿掉以後 這三棵tree 的XOR 之中最大-最小 的最小值
        從特殊到一般:
        如果只要求拿掉一個edge 另一段就會是 all_xor ^= 被拿掉後剩餘那棵 ^ 拿掉的edge
        拿掉剩餘那棵可以預處理判斷 pre[node] = ? 以某個節點為父節點 其子樹可以形成的XOR是?
        n = 1000 可以n^2枚舉選哪兩條edge
        再來就是要判斷選擇的兩條edge 是 1. 包含 2. 不包含 的狀況 -> 時間戳來判斷是否被包含 in out
        不包含:
        1st: all_xor ^ subtree1頭 ^ subtree2頭
        2nd: subtree1尾
        3rd: subtree2尾
        包含:
        1st: all_xor ^ 最低公共祖先(subtree1頭, subtree2頭)
        2ns: 最低公共祖先(subtree1尾, subtree2尾) ^ subtree1頭 or subtree2頭
        3rd: subtree1尾 or subtree2尾
        '''
        n = len(nums)
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)

        subtree = [0] * n
        tin = [0] * n
        tout = [0] * n
        time = 0
        total_xor = 0

        def dfs(u, parent):
            nonlocal time, total_xor
            tin[u] = time
            time += 1
            xor_sum = nums[u]
            total_xor ^= nums[u]
            for v in g[u]:
                if v != parent:
                    xor_sum ^= dfs(v, u)
            subtree[u] = xor_sum
            tout[u] = time
            return xor_sum

        dfs(0, -1)

        def is_ancestor(u, v):  # 是否 u 是 v 的祖先
            return tin[u] <= tin[v] < tout[u]

        ans = float('inf')
        edge_list = []

        for u, v in edges:
            # 確保 u 是 parent
            if tin[u] < tin[v]:
                edge_list.append((u, v))
            else:
                edge_list.append((v, u))

        for i in range(len(edge_list)):
            u1, v1 = edge_list[i]
            for j in range(i + 1, len(edge_list)):
                u2, v2 = edge_list[j]

                # Case 1: 不相交子樹
                if not is_ancestor(v1, v2) and not is_ancestor(v2, v1):
                    a = subtree[v1]
                    b = subtree[v2]
                    c = total_xor ^ a ^ b
                # Case 2: v1 包含 v2
                elif is_ancestor(v1, v2):
                    a = subtree[v2]
                    b = subtree[v1] ^ subtree[v2]
                    c = total_xor ^ subtree[v1]
                # Case 3: v2 包含 v1
                else:  # is_ancestor(v2, v1)
                    a = subtree[v1]
                    b = subtree[v2] ^ subtree[v1]
                    c = total_xor ^ subtree[v2]

                vals = [a, b, c]
                ans = min(ans, max(vals) - min(vals))

        return ans