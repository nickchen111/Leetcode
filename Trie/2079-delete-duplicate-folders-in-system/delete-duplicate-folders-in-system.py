class TrieNode:
    __slots__ = 'son', 'name', 'deleted'

    def __init__(self):
        self.son = {}
        self.name = ''
        self.deleted = False


class Solution:
    def deleteDuplicateFolder(self, paths: List[List[str]]) -> List[List[str]]:
        root = TrieNode()
        for path in paths:
            cur = root
            for s in path:
                if s not in cur.son:
                    cur.son[s] = TrieNode()
                cur = cur.son[s]
                cur.name = s

        expr_to_node = {}

        def gen_expr(node: TrieNode) -> str:
            if not node.son:
                return node.name

            expr = sorted('(' + gen_expr(son) + ')' for son in node.son.values())
            sub_tree_expr = ''.join(expr)
            if sub_tree_expr in expr_to_node:
                expr_to_node[sub_tree_expr].deleted = True
                node.deleted = True 
            else:
                expr_to_node[sub_tree_expr] = node

            return node.name + sub_tree_expr

        for son in root.son.values():
            gen_expr(son)

        ans = []
        path = []

        def dfs(node: TrieNode) -> None:
            if node.deleted:
                return
            path.append(node.name)
            ans.append(path.copy())
            for child in node.son.values():
                dfs(child)
            path.pop()

        for son in root.son.values():
            dfs(son)

        return ans
