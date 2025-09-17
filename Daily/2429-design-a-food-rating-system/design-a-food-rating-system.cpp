class FoodRatings {
    /*
    需要一種可以支援排序的資料結構 並且可以任意修改其中一種type的某種食物rating
    */
    unordered_map<string, string> f2c;
    unordered_map<string, int> f2r;
    unordered_map<string, set<pair<int, string>>> mp;
    vector<string> foods, cuisines;
    vector<int> ratings;
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        this -> foods = foods;
        this -> cuisines = cuisines;
        this -> ratings = ratings;
        for (int i = 0; i < foods.size(); i++) {
            mp[cuisines[i]].insert({-ratings[i], foods[i]});
            f2c[foods[i]] = cuisines[i];
            f2r[foods[i]] = ratings[i];
        }
    }
    
    void changeRating(string food, int newRating) {
        string c = f2c[food];
        int r = f2r[food];
        mp[c].erase({-r, food});
        f2r[food] = newRating;
        mp[c].insert({-newRating, food});
    }
    
    string highestRated(string cuisine) {
        return mp[cuisine].begin()->second;
    }
};

/**
 * Your FoodRatings object will be instantiated and called as such:
 * FoodRatings* obj = new FoodRatings(foods, cuisines, ratings);
 * obj->changeRating(food,newRating);
 * string param_2 = obj->highestRated(cuisine);
 */