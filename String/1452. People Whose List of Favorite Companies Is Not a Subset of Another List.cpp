/*
1452. People Whose List of Favorite Companies Is Not a Subset of Another List
*/
 
// BitMask  TC:O(n*m) SC:O(n*m*100)
class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        int n = favoriteCompanies.size();
        unordered_map<string, bitset<100>> c2p; // company to person
        for(int i = 0; i < n; i++){
            for(int j = 0; j < favoriteCompanies[i].size(); j++){
                c2p[favoriteCompanies[i][j]][i] = 1;
            }
        }

        vector<int> res;
        for(int i = 0; i < n; i++){
            bitset<100> bs;
            bs.set(); // 先全部置為1 然後去&其他跟我喜歡的東西一樣的公司 如果剩下的人超過2就代表我不是唯一有我這個set的人
            for(auto str : favoriteCompanies[i]){
                bs &= c2p[str];
            }

            if(bs.count() == 1) res.push_back(i);
        }

        return res;
    }
};

// 優化資料結構
class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& favoriteCompanies) {
        int n = favoriteCompanies.size();
        vector<unordered_set<string>> arr;

        for(int i = 0; i < n; i++){
            unordered_set<string> set(favoriteCompanies[i].begin(), favoriteCompanies[i].end());
            arr.push_back(set);
        }

        vector<int> res;
        for(int i = 0; i < n; i++){
            bool flag = 1;
            for(int j = 0; j < n; j++){
                if(i == j) continue;
                bool included = true;
                for(auto str : arr[i]){
                    if(arr[j].find(str) == arr[j].end()){
                        included = false;
                        break;
                    }
                }

                if(included){
                    flag = 0;
                    break;
                }
            }
            if(flag) res.push_back(i);
        }

        return res;
    }
};

// TC:O(n^2*m) SC:O(n*m)
class Solution {
public:
    vector<int> peopleIndexes(vector<vector<string>>& arr) {
        map<int, unordered_set<string>> map;
        for(int i = 0; i < arr.size(); i++){
            map[i].insert(arr[i].begin(), arr[i].end());   
        }

        vector<int> res;
        for(int i = 0; i < arr.size(); i++){
            bool flag = 1;
            for(int j = 0; j < arr.size(); j++){
               if(i == j) continue;
               int count = 0;
               for(string str: map[i]){
                   if(map[j].find(str) != map[j].end()){
                       count++;
                   }
                   else break;
               }
               if(count == map[i].size()){
                    flag = false;
                    break;
               }
            }
            
            if(flag) res.push_back(i);
        }

        return res;
    }
};
