/*
2899. Last Visited Integers
*/


// TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> lastVisitedIntegers(vector<string>& words) {
        unordered_map<int,int> map;
        int n = words.size();
        vector<int> res;
        int count = 0;//是否有任何人拿走一個數字
        int idx = 0;//總共出現的數字計算
        for(int i=0; i<n; i++){
            if(words[i] == "prev"){
                if(map[count] != 0){
                    res.push_back(map[count]);
                    count--;
                }
                else {
                    res.push_back(-1);
                }
            }
        if(words[i] != "prev"){
            map[idx] = stoi(words[i]);
            count = idx;
            idx++;
          }
        }
      
        return res;  
    }
};
