/*
767. Reorganize String
*/

// TC:O(n + n*lg26) SC:O(n)
class Solution {
public:
    string reorganizeString(string s) {
        int n = s.size();
        unordered_map<char, int> map;
        priority_queue<pair<int, char>, vector<pair<int, char>>, less<pair<int, char>>> pq;
        for(int i = 0; i < n; i++){
            map[s[i]] += 1;
        }
        for(auto p : map){
            pq.push({p.second,p.first}); // freq ch
        }

        string res;
        while(!pq.empty()){
            char ch = pq.top().second;
            int freq = pq.top().first;
            pq.pop();
            freq -= 1;
            res += ch;
            if(freq == 0) continue;
            else {
                if(pq.empty()) return "";
                else {
                    char ch2 = pq.top().second;
                    int freq2 = pq.top().first;
                    pq.pop();
                    res += ch2;
                    freq2 -= 1;
                    if(freq2 > 0) pq.push({freq2,ch2});
                    pq.push({freq, ch});
                }
            }
        }

        return res;
    }
};

/*
rearrange string 讓相鄰字不要相同 返回任意可能組合 也可能不可能達成
PQ with map 一個字排好在排下一個如果他還沒空那就加回去
*/
