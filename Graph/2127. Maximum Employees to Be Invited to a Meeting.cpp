/*
2127. Maximum Employees to Be Invited to a Meeting
*/

// TC:O(n) SC:O(n)
class Solution {
public:
    int maximumInvitations(vector<int>& favorite) {
        int n = favorite.size();
        vector<int> indegree(n,0);
        vector<int> depth(n,1);
        for(int i = 0; i < n; i++){
            indegree[favorite[i]] += 1;
        }
        
        queue<int> q;
        vector<bool> visited(n,0);
        for(int i = 0; i < n; i++){
            if(indegree[i] == 0){
                visited[i] = 1;
                q.push(i);
            }
        }

        while(!q.empty()){
            int cur = q.front();
            q.pop();
            int nxt = favorite[cur];
            indegree[nxt] -= 1;
            if(indegree[nxt] == 0){
                visited[nxt] = 1;
                q.push(nxt);
            }
            depth[nxt] = depth[cur] + 1;
        }

        int max_multi_node_circle = 0;
        int max_link = 0;

        for(int i = 0; i < n; i++){
            if(visited[i]) continue;
            int count = 0;
            int j = i;
            while(visited[j] == 0){
                visited[j] = 1;
                j = favorite[j];
                count += 1;
            }

            if(count >= 3){
                max_multi_node_circle = max(max_multi_node_circle, count);
            }
            else if(count == 2){
                max_link += depth[i] + depth[favorite[i]];
            }
        }

        return max(max_multi_node_circle, max_link);
    }
};

/*
這題說最多可以讓多少人參加會議 每個人參加會議的條件是可以坐在他喜歡的人旁邊
這題是2360 follow up 除了比較能夠想到的答案會是一個環以外 還有可能是 喜歡的人不會是自己
x -> x -> x <-> x <- x <- x 這種狀況 並且這種的可能會有很多條二元環 都要累加起來 他們都可以一起參加會議
值得學習的是在拓墣排序indegree慢慢減少的時候就可以對每個node賦予他的深度 從他前面的節點繼承過來 深度越深的會越後後面更新所以就算一個點上連接兩條長度不同的點 越長得越會在後面更新
*/ 
