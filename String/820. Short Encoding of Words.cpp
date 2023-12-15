/*
820. Short Encoding of Words
*/

// 最優解   TC:O(nlgn + n*m) SC:O(n)
class Solution {
    static bool cmp (const string& a, const string& b){
        return a.size() > b.size();
    };
public:
    int minimumLengthEncoding(vector<string>& words) {
      
        sort(words.begin(), words.end(), cmp);
        int n = words.size();
        string res = "";
        res = res + words[0] + "#";

        for(int i = 1; i < n; i++){
            int pos = res.find(words[i]+"#");
            if(pos < res.size()) continue;
            else res += words[i] + "#";
        }

        return res.size();
    }
};


//次佳解 TC:O(n + nlgn + n^2*m) m為平均字串長度 SC:O(n)
class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        //去重
        unordered_set<string> set;
        for(const auto& word : words){
            set.insert(word);
        }

        //排序
        vector<string> str(set.begin(), set.end());
        auto cmp = [](const string& a, const string& b){
            return a.size() > b.size();
        };
        sort(str.begin(), str.end(), cmp);

        // find ans we want
        int res = 0;
        int n = str.size();
        vector<int> visited(n,-1);
        for(int i = 0; i < n; i++){
            if(visited[i] == 1) continue;
            visited[i] = 1;
            for(int j = i + 1; j < n; j++){
                int pos = str[i].find(str[j]);//返回的是找到的index
                if(pos == -1) continue;

                if(pos != -1 && str[i].size() == str[j].size() + pos){
                    visited[j] = 1;
                }
                else {
                    //找到了但不是結尾
                    while((pos = str[i].find(str[j], pos) )!= -1){
                        if(str[i].size() == str[j].size() + pos){
                            visited[j] = 1;
                            break;
                        }
                        pos++;
                    }
                }
            }

            res += str[i].size() + 1;
        }

        return res;
    }
};

/*
此題想要將單詞盡量的頭尾相接 並且接到不能接之後加上一個# 問說最後他的長度會是多長
1.因為單詞有可能重複-> 去重
2. 排序 將較長的單詞先做他更有可能不段尾頭相連其他單詞
3. 計算答案 並且需要visited數組 做過的就不用做了
time me 
*/class Solution {
public:
    int minimumLengthEncoding(vector<string>& words) {
        //去重
        unordered_set<string> set;
        for(const auto& word : words){
            set.insert(word);
        }

        //排序
        vector<string> str(set.begin(), set.end());
        auto cmp = [](const string& a, const string& b){
            return a.size() > b.size();
        };
        sort(str.begin(), str.end(), cmp);

        // find ans we want
        int res = 0;
        int n = str.size();
        vector<int> visited(n,-1);
        for(int i = 0; i < n; i++){
            if(visited[i] == 1) continue;
            visited[i] = 1;
            for(int j = i + 1; j < n; j++){
                int pos = str[i].find(str[j]);//返回的是找到的index
                if(pos == -1) continue;

                if(pos != -1 && str[i].size() == str[j].size() + pos){
                    visited[j] = 1;
                }
                else {
                    //找到了但不是結尾
                    while((pos = str[i].find(str[j], pos) )!= -1){
                        if(str[i].size() == str[j].size() + pos){
                            visited[j] = 1;
                            break;
                        }
                        pos++;
                    }
                }
            }

            res += str[i].size() + 1;
        }

        return res;
    }
};

/*
此題想要將單詞盡量的頭尾相接 並且接到不能接之後加上一個# 問說最後他的長度會是多長
1.因為單詞有可能重複-> 去重
2. 排序 將較長的單詞先做他更有可能不段尾頭相連其他單詞
3. 計算答案 並且需要visited數組 做過的就不用做了
time me 
*/
