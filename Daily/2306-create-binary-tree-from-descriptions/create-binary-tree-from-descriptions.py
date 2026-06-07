class Solution:
    def createBinaryTree(self, descriptions: List[List[int]]) -> Optional[TreeNode]:
        nodes = {}  # val -> TreeNode
        children = set()

        # 建树
        for x, y, is_left in descriptions:
            if x not in nodes:
                nodes[x] = TreeNode(x)
            if y not in nodes:
                nodes[y] = TreeNode(y)
            if is_left:
                nodes[x].left = nodes[y]
            else:
                nodes[x].right = nodes[y]
            children.add(y)  # y 不是根节点

        for x, node in nodes.items():
            if x not in children:  # node 是根节点
                return node
        # 测试用例保证可以构造出有效的二叉树