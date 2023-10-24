/*
692. Top K Frequent Words
Follow-up: Could you solve it in O(n log(k)) time and O(n) extra space?
*/


//用hassh table+ priority_queue 就要 o(nlgn)太慢了 所以需要給pq設限制 用min heap 不超過k個就可以在nlgk內達成
class Solution {
    struct state{
        string word;
        int freq;
        state(int freq, string word){
            this->word = word;
            this->freq = freq;
        }

        bool operator< (const state& other) const{
            if(freq == other.freq){
                for(int i = 0; i<word.size(); i++){
                    if(word[i] != other.word[i]){
                        return word[i] > other.word[i];
                    }
                }
            }
            return freq < other.freq;
        }
    };
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> map;
        for(auto word:words){
            map[word]++;
        }

        priority_queue<state, vector<state>, less<state> > pq;
        for(auto &[word, freq]:map){
            pq.push({freq,word});
        }

        vector<string> ans;
        while(k--){
            state cur = pq.top(); pq.pop();
            ans.push_back(cur.word);
        }

        return ans;
    }
};

//改成tc:o(nlgk) sc: o(n)
class Solution {
    struct state{
        string word;
        int freq;
        state(int freq, string word){
            this->word = word;
            this->freq = freq;
        }

        bool operator> (const state& other) const{
            if(freq == other.freq){
                return word < other.word;
            }
            return freq > other.freq;
        }
    };
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> map;
        for(auto word:words){
            map[word]++;
        }

        priority_queue<state, vector<state>, greater<state> > pq;
        for(auto &[word, freq]:map){
            pq.push(state(freq,word));
            if(pq.size() > k){
                pq.pop();//確保tc可以在nlgk完成
            }
        }

        vector<string> ans;
        
        while(!pq.empty()){
            ans.push_back(pq.top().word);
            pq.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};

//priority queue用自定義函式lamda比較  甚至還可以直接寫在pq裡呵呵
class Solution {
    //用lamda比較
public:
    vector<string> topKFrequent(vector<string>& words, int k) {
        unordered_map<string, int> map;
        for(auto word:words){
            map[word]++;
        }

        auto cmp = [](const pair<string,int>& a, const pair<string,int>& b) {
            if(a.second == b.second){
                return a.first < b.first;
            }
            else return a.second > b.second;
        };
        priority_queue<pair<string, int>, vector<pair<string, int>>, decltype(cmp) > pq(cmp);//用lamda寫的方式
        for(auto &[word, freq]:map){
            pq.push({word,freq});
            if(pq.size() > k){
                pq.pop();//確保tc可以在nlgk完成
            }
        }

        vector<string> ans;
        
        while(!pq.empty()){
            ans.push_back(pq.top().first);
            pq.pop();
        }

        reverse(ans.begin(), ans.end());

        return ans;
    }
};
