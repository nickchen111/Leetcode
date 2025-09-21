class MovieRentingSystem {
    unordered_map<long long, int> shop_movie_to_price;
    unordered_map<int, set<pair<int, int>>> unrented_movie_to_price_shop;// price, shops
    set<tuple<int,int,int>> rented_movies;
public:
    MovieRentingSystem(int n, vector<vector<int>>& entries) {
        for (auto & e : entries) {
            shop_movie_to_price[1LL * e[0] << 32 | e[1]] = e[2];
            unrented_movie_to_price_shop[e[1]].insert({e[2], e[0]});
        }
    }
    
    vector<int> search(int movie) {
        /*
        尚未租借的某movie 5個 price -> shop return shops
        */
        auto it = unrented_movie_to_price_shop.find(movie);
        if (it == unrented_movie_to_price_shop.end()) {
            return {};
        }
        vector<int> ans;
        for (auto& [_, shop] : it->second) {
            ans.push_back(shop);
            if (ans.size() == 5) {
                break;
            }
        }
        return ans;
    }
    
    void rent(int shop, int movie) {
        /*
        借電影出去
        */
        int price = shop_movie_to_price[1LL * shop << 32 | movie];
        unrented_movie_to_price_shop[movie].erase({price, shop});
        rented_movies.emplace(price, shop, movie);
    }
    
    void drop(int shop, int movie) {
        /*
        還電影
        */
        int price = shop_movie_to_price[1LL * shop << 32 | movie];
        // 从 rented_movies 移到 unrented_movie_to_price_shop
        rented_movies.erase({price, shop, movie});
        unrented_movie_to_price_shop[movie].emplace(price, shop);
    }
    
    vector<vector<int>> report() {
        /*
        五個最便宜已租借電影 price -> shop, movie
        */
        vector<vector<int>> ans;
        for (auto& [_, shop, movie] : rented_movies) {
            ans.push_back({shop, movie});
            if (ans.size() == 5) {
                break;
            }
        }
        return ans;
    }
};

/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */