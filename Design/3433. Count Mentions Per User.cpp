// Sort TC:O(nlgn) SC:O(n)
#include<ranges>
class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> ans(numberOfUsers, 0);
        vector<int> online(numberOfUsers, 0);
        ranges::sort(events, {}, [&](auto &e){ return pair(stoi(e[1]), e[0][2]);}); // 剛好第三個字從小到大符合離線在錢
        int cnt = 0;
        for(auto &event : events) {
            int time = stoi(event[1]);
            if(event[0][0] == 'M') {
                if(event[2][0] == 'A') {
                    cnt += 1;
                }
                else if(event[2][0] == 'H') {
                    for(int i = 0; i < numberOfUsers; i++) {
                        if(online[i] <= time) ans[i] += 1;
                    }
                }
                else {
                    for(const auto &part : event[2] | ranges::views::split(' ')) {
                        string s(part.begin()+2, part.end());
                        ans[stoi(s)] += 1; 
                    }
                }
            }
            else if(event[0][0] == 'O') {
                online[stoi(event[2])] = time + 60;
            }
        }
        
        if(cnt) {
            for(int i = 0; i < numberOfUsers; i++) ans[i] += cnt;
        }
        return ans;
    }
};

// PQ TC:O(mlgm) m = n* numberofuser SC:O(m)
class Solution {
public:
    vector<int> countMentions(int numberOfUsers, vector<vector<string>>& events) {
        vector<int> ans(numberOfUsers, 0);
        vector<bool> online(numberOfUsers, true);
        
        auto cmp = [&](const tuple<int,int,int>& a, const tuple<int,int,int>& b) {
            if(get<0>(a) != get<0>(b)) return get<0>(a) > get<0>(b);
            return get<2>(a) < get<2>(b);
        };
        // 0 -> 指定id++, 1:所有人 2:上線的 3:有人下線 4:有人上線
        priority_queue<tuple<int,int,int>, vector<tuple<int,int,int>>, decltype(cmp)> pq(cmp);
        
        for(auto &event : events) {
            int time = stoi(event[1]);
            
            if(event[0][0] == 'M') {
                if(event[2][0] == 'A') {
                    pq.push({time, -1, 1});
                }
                else if(event[2][0] == 'H') {
                    pq.push({time, -1, 2});
                }
                else {
                    stringstream ss(event[2]);
                    string token;
                    while(ss >> token) {
                        if(token.substr(0, 2) == "id") {
                            int id = stoi(token.substr(2));
                            pq.push({time, id, 0});
                        }
                    }
                }
            }
            else if(event[0][0] == 'O') {
                int cur = stoi(event[2]);
                pq.push({time, cur, 3});
                pq.push({time + 60, cur, 4});
            }
        }
        
        int cnt = 0;
        while(!pq.empty()) {
            auto [time, id, e] = pq.top();
            pq.pop();
            
            if(e == 0) {
                ans[id]++;
            }
            else if(e == 1) {
                cnt++;
            }
            else if(e == 2) {
                for(int i = 0; i < numberOfUsers; i++) {
                    if(online[i]) ans[i]++;
                }
            }
            else if(e == 3) {
                online[id] = false;
            }
            else if(e == 4) {
                online[id] = true;
            }
        }
        
        for(int i = 0; i < numberOfUsers; i++) {
            ans[i] += cnt;
        }
        
        return ans;
    }
};
