class Solution:
    def maxIceCream(self, costs: List[int], coins: int) -> int:
        costs.sort()

        # 按照价格从低到高买
        for i, cost in enumerate(costs):
            if coins < cost:  # 钱不够
                return i  # 买 [0, i-1] 一共 i 根雪糕
            coins -= cost

        # 可以买所有雪糕
        return len(costs)

