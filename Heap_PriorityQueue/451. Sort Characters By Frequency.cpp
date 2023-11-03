/*
451. Sort Characters By Frequency
*/

// TC:O(nlgn) SC:O(n) 11/3
class Solution {
public:
    string frequencySort(string s) {
        unordered_map<char,int> map;
        for(auto ch:s){
            map[ch]+=1;
        }

        auto cmp = [](pair<int,char>& a, pair<int,char>& b){
            if(a.first != b.first){
                return a.first < b.first;
            }
            else return a.second > b.second;
        };

        priority_queue<pair<int,char>, vector<pair<int,char>>, decltype(cmp)> pq;

        for(auto p:map){
            pq.push({p.second,p.first});
        }

        string res;
        while(!pq.empty()){
            auto cur = pq.top();
            int freq = cur.first;
            while(freq > 0){
                res.push_back(cur.second);
                freq-=1;
            }
            pq.pop();
        }

        return res;
    }
};

//"tc: o(nlgn) sc: o(n) 但如果是在頻率一樣的字很多的時候 用string(3, 'a')這種操作可以大幅降低時間複雜度"
// pq+hash table 但沒有用string(3, 'a');
class Solution {
public:
    string frequencySort(string s) {
        int n = s.size();
        if(n == 1) return s;

        unordered_map<char, int> map;
        for(const char c:s){
            map[c]++;
        }

        auto cmp = [](const pair<char, int>& a, const pair<char, int>& b) {
            if(a.second == b.second){
                return a.first>b.first; //隨意 題目沒要求 但為了避免兩個不同的字元排在一起才寫
            }

            return a.second < b.second;
        };
        //由小到大 大堆頂
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> pq(cmp);

        for(int i = 0; i < n; i++){
            pq.push({s[i], map[s[i]]});
        }

        string ans;

        while(!pq.empty()){
            ans+=pq.top().first;
            pq.pop();
        }
        return ans;

    }
};

//不用pq 直接sort改定義
class Solution {
public:
//可以不用pq 直接在 sort裡面自定義即可
    string frequencySort(string s) {
        int n = s.size();
        if(n == 1) return s;

        unordered_map<char, int> f; //sc:o(n)
        for(const char c:s){ //tc: o(n)
            f[c]++;
        }

        sort(s.begin(), s.end(), [&f](char a, char b){
            return f[a] > f[b] || (f[a] == f[b] && a > b);
        });
        
        return s;

    }
};

//加上string 操作 labuladong
class Solution {
public:
    string frequencySort(string s) {
        vector<char> chars(s.begin(), s.end());
        // s 中的字符 -> 该字符出现的频率
        unordered_map<char, int> charToFreq;
        for (char ch : chars) {
            charToFreq[ch]++;
        }

        auto cmp = [](pair<char, int>& entry1, pair<char, int>& entry2) {
            return entry1.second < entry2.second;
        };
        // 队列按照键值对中的值（字符出现频率）从大到小排序
        priority_queue<pair<char, int>, vector<pair<char, int>>, decltype(cmp)> pq(cmp);

        // 按照字符频率排序
        for (auto& entry : charToFreq) {
            pq.push(entry);
        }

        string res = "";
        while (!pq.empty()) {
            // 把频率最高的字符排在前面
            pair<char, int> entry = pq.top();
            pq.pop();
            res += string(entry.second, entry.first);
        }

        return res;
    }
};
