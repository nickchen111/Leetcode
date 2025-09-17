class FoodRatings:
    def __init__(self, foods: List[str], cuisines: List[str], ratings: List[int]):
        self.f2c = defaultdict(str)
        self.f2r = defaultdict(int)
        self.c2rf = defaultdict(lambda: SortedSet())
        
        for f, c, r in zip(foods, cuisines, ratings):
            self.f2c[f] = c
            self.f2r[f] = r
            self.c2rf[c].add((-r, f))

    def changeRating(self, food: str, newRating: int) -> None:
        c, r = self.f2c[food], self.f2r[food]
        self.f2r[food] = newRating
        self.c2rf[c].remove((-r, food))
        self.c2rf[c].add((-newRating, food))

    def highestRated(self, cuisine: str) -> str:
        return self.c2rf[cuisine][0][1]

# Your FoodRatings object will be instantiated and called as such:
# obj = FoodRatings(foods, cuisines, ratings)
# obj.changeRating(food,newRating)
# param_2 = obj.highestRated(cuisine)