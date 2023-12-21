/*
1942. The Number of the Smallest Unoccupied Chair
*/

// TC:O(nlgn + n) SC:O(n)
class Solution {
    using PII = pair<int,int>;
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        priority_queue<PII, vector<PII>, greater<PII>> used; // endTime, person
        priority_queue<int, vector<int>, greater<int>> empty;

        for(int i = 0; i < times.size(); i++){
            empty.push(i);//需要的椅子數量
            times[i].push_back(i);//紀錄每個時間點是誰
        }

        sort(times.begin(), times.end());
        for(auto &time : times){
            int start = time[0], leave = time[1], person = time[2];

            while(!used.empty() && start >= used.top().first){
                empty.push(used.top().second);
                used.pop();
            }
            int chair = empty.top();
            empty.pop();
            used.push({leave, chair});
            if(person == targetFriend) return chair;
        }

        return -1;
    }
};

// TC:O(2*nlg2*n) SC:O(3*n + n)
class Solution {
public:
    int smallestChair(vector<vector<int>>& times, int targetFriend) {
        //先將抵達時間排序
        int number = 0;
        auto cmp = [](const vector<int>& a, const vector<int>& b){
            if(a[0] != b[0]){
                return a[0] > b[0];
            }
            else return a[2] > b[2];
        };
        priority_queue<vector<int>, vector<vector<int>>, decltype(cmp)> pq;
        priority_queue<int, vector<int>, greater<int>> chair;
        unordered_map<int, int> man2chair;
        int n = times.size();
        
        for(int i = 0; i < n; i++){
            int arrive = times[i][0], leave = times[i][1];
            pq.push({arrive,i,1});
            pq.push({leave,i,-1});
        }

        while(!pq.empty()){
            int flag = pq.top()[2];
            int time = pq.top()[0];
            int person = pq.top()[1];
            pq.pop();
            if(flag == 1){
                if(chair.empty()){
                    man2chair[person] = number;
                    if(person == targetFriend) return number;
                    number++;
                }
                else {
                    man2chair[person] = chair.top();
                    if(person == targetFriend) return chair.top();
                    chair.pop();
                }
            }
            else {
                chair.push(man2chair[person]);
                man2chair.erase(person);
            }
        }

        return -1;

    }
};

/*
此題說每個人進來都會挑最小數字椅子坐 人來來去去 問某個人會坐到的椅子編號
我最一開始寫的思維 一個ＰＱ裝模擬的過程 人來人往 是誰走是誰來  一個PQ裝 目前有沒有之前走掉的人留下的椅子 map那些要走掉的人之前是做哪個椅子
TC:O(2*nlg2*n) SC:O(3*n + n)
更好的想法可以直接用PQ裝可以做的椅子 另外再用一個PQ裝 被借走的椅子他的歸還時間與數字
*/
