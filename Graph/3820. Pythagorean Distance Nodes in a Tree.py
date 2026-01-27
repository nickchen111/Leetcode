# TC:O(n) SC:O(n)
class Solution:
    def specialNodes(self, n: int, edges: List[List[int]], x: int, y: int, z: int) -> int:
        g = [[] for _ in range(n)]
        for u, v in edges:
            g[u].append(v)
            g[v].append(u)
        def cal_dist(start_node:int) -> List[int]:
            dist = [-1] * n
            dist[start_node] = 0
            queue = deque([start_node])
            while queue:
                u = queue.popleft()
                for v in g[u]:
                    if dist[v] == -1:
                        dist[v] = dist[u] + 1
                        queue.append(v)
            return dist
        dx = cal_dist(x)
        dy = cal_dist(y)
        dz = cal_dist(z)
        ans = 0
        for i in range(n):
            arr = sorted([dx[i], dy[i], dz[i]])
            a,b,c = arr[0], arr[1], arr[2]
            if a * a + b * b == c * c:
                ans += 1
        return ans
        
            
