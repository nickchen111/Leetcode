/*
2353. Design a Food Rating System
*/

// TC:O(N log M) SC:O(N+M)
class FoodRatings {
    map<string, pair<string,int>> food2CuisineAndRating;
    map<string, map<int, set<string>>> cuisine2RatingAndFood;
public:
    FoodRatings(vector<string>& foods, vector<string>& cuisines, vector<int>& ratings) {
        for(int i = 0; i < foods.size(); i++){
            food2CuisineAndRating[foods[i]] = {cuisines[i],ratings[i]};
            cuisine2RatingAndFood[cuisines[i]][ratings[i]].insert(foods[i]);
        }
    }
    
    void changeRating(string food, int newRating) {
        string cuisine = food2CuisineAndRating[food].first;
        int oldRating = food2CuisineAndRating[food].second;
        auto foodInfo = food2CuisineAndRating.find(food);
        foodInfo->second.second = newRating;

        cuisine2RatingAndFood[cuisine][oldRating].erase(food);
        if(cuisine2RatingAndFood[cuisine][oldRating].empty()){
            cuisine2RatingAndFood[cuisine].erase(oldRating);
        }
        cuisine2RatingAndFood[cuisine][newRating].insert(food);
        

    }
    
    string highestRated(string cuisine) {
        return *cuisine2RatingAndFood[cuisine].rbegin()->second.begin();
    }
};
/*
food -> cuisine
cuisine -> highest rating
food -> rating
*/
