/*
763. Partition Labels
*/


// 最快速的方式 用陣列查找 TC:O(n) SC:O(128)
class Solution {
public:
    vector<int> partitionLabels(string s) {
        //更節省空間的做法
        int n = s.size();
        vector<int> index(128,0);//紀錄每個字元的最後位置
        for(int i = 0; i<n; i++){
            index[s[i]] = i;
        }

        int start = 0;
        int end = 0;
        vector<int> res;
        for(int i = 0; i<n; i++){
            end = max(end,index[s[i]]);
            if(i == end){
                res.push_back(end-start+1);
                start = end+1;
            }
        }

        return res;
    }
};


//用hash map TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> partitionLabels(string s) {
        //更節省空間的做法
        int n = s.size();
        unordered_map<char,int> map;//紀錄每個字元的最後位置
        for(int i = 0; i<n; i++){
            map[s[i]] = i;
        }

        int start = 0;
        int end = 0;
        vector<int> res;
        for(int i = 0; i<n; i++){
            end = max(end,map[s[i]]);
            if(i == end){
                res.push_back(end-start+1);
                start = end+1;
            }
        }

        return res;
    }
};
//另種思考方式 最一開始的做法 TC:O(n) SC:O(n)
class Solution {
public:
    vector<int> partitionLabels(string s) {
        //同種字只能出現在同一part裡面 要怎麼分出最多part 且不能斷開 要都連在一起的Split
        int n = s.size();
        unordered_map<char, int> map;
        for(int i = 0; i<n; i++){
            map[s[i]]+=1;
        }

        vector<int> res;
        int count = 0;
        unordered_map<char, int> record;
        
        for(int i = 0; i<n; i++){
            map[s[i]]-=1;
            record[s[i]]+=1;
            count+=1;

            if(map[s[i]] == 0){
                record.erase(s[i]);
                if(record.empty()){
                    res.push_back(count);
                    count = 0;
                }
            }   
        }
        return res;
    }
};

/* 
我的想法是
先將所有字算出有幾個
一開始的開始run後 就map-- 看有沒有變成0 沒有的話繼續run 途中讓run進去的map都減減
並且大家都要是0 才能擷取這段 用一個變數紀錄長度
*/
