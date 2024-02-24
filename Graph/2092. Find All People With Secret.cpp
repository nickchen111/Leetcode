/*
2092. Find All People With Secret
*/

// Union_Find TC:O(nlgn + n) SC:O(n)
class Solution {
    vector<int> parent;
    int find(int x){
        if(x != parent[x]){
            parent[x] = find(parent[x]);
        }

        return parent[x];
    }
    void union_(int x,int y){
        x = parent[x];
        y = parent[y];
        if(x < y){
            parent[y] = x;
        }
        else parent[x] = y;
    }
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {
        parent.resize(n);
        for(int i = 0; i < n; i++){
            parent[i] = i;
        }
        union_(0,firstPerson);
        unordered_set<int> set;
        set.insert(0);
        set.insert(firstPerson);
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            return a[2] < b[2];
        };
        sort(meetings.begin(), meetings.end(), cmp);

        for(int i = 0; i < meetings.size(); i++){
            unordered_set<int> person;
            int j;
            for(j=i; j < meetings.size() && meetings[j][2] == meetings[i][2]; j++){
                int a = meetings[j][0], b = meetings[j][1];
                person.insert(a);
                person.insert(b);
                if(find(a) != find(b)){
                    union_(a,b);
                }
            }
            for(auto x : person){
                if(find(x) == 0){
                    set.insert(x);
                }
                else parent[x] = x;
            }
            i = j-1;
        }

        vector<int> res(set.begin(), set.end());

        return res;
    }
};

// BFS TC:O(n^2) SC:O(n^2) 免強能過 數據感覺沒有設計的太好 n 都是10^5級別 但因為人不會每個時間點都在開會所以免強過關
class Solution {
public:
    vector<int> findAllPeople(int n, vector<vector<int>>& meetings, int firstPerson) {

        unordered_set<int> Know;
        Know.insert(0);
        Know.insert(firstPerson);

        map<int, unordered_map<int,vector<int>>> graph; // time -> person1 <-> person2,3,4,.....
        for(auto m : meetings){
            graph[m[2]][m[0]].push_back(m[1]);
            graph[m[2]][m[1]].push_back(m[0]);
        }

        for(auto p : graph){
            vector<bool> visited(n,0);
            //時間點
            for(auto x : p.second){
                if(visited[x.first]) continue;
                if(Know.find(x.first) != Know.end()){
                    queue<int> q;
                    q.push(x.first);
                    while(!q.empty()){
                        int sz = q.size();
                        while(sz--){
                            int cur = q.front();
                            q.pop();
                            if(visited[cur]) continue;
                            Know.insert(cur);
                            visited[cur] = 1;
                            for(auto nxt : p.second[cur]){
                                if(visited[nxt]) continue;
                                q.push(nxt);
                            }
                        }
                    }
                }   
            }
        }
        vector<int> res(Know.begin(), Know.end());

        return res;

    }
};


/*
問說 從person 0 開始傳播秘密 每開一個兩人會議 如果其中一人知道秘密 那他就會告訴另外一個人
最後有哪些人知道秘密
起初想法因為會議的大小是 10^5 會想到用遍歷時間的方式將所有會議按照順序遍歷 每當遍歷到的時候就確認是否這兩個人其中一人知道秘密
這招 不行 因為會議不一定在同一個時間只有一場 可能有人當場知道在馬上告知另一場同時間的人
次佳解: BFS 設計一個資料結構 某個時間點 哪些點之間是否有連結 unordered_map<int, unordered_,map<int, vector<int>>> graph;  time -> person1 -> person2, 3, 4 ...
最佳解:改成用UF 要去思考說 某個時間有哪些人在開會 先將他們都Union再一起 然後去看哪些是有在set集合裡代表他會指向0 沒有的將它改回指向自己
*/
