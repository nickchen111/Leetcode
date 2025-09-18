class TaskManager {
    unordered_map<int,int> t2p;
    unordered_map<int,int> t2u;
    set<pair<int,int>> pq;
    unordered_map<int, unordered_set<int>> u2t;
public:
    TaskManager(vector<vector<int>>& tasks) {
        for (auto &t : tasks) {
            pq.insert({t[2], t[1]});
            t2p[t[1]] = t[2];
            u2t[t[0]].insert(t[1]);
            t2u[t[1]] = t[0];
        }
    }
    
    void add(int userId, int taskId, int priority) {
        pq.insert({priority, taskId});
        t2p[taskId] = priority;
        t2u[taskId] = userId;
        u2t[userId].insert(taskId);
    }
    
    void edit(int taskId, int newPriority) {
        int prevP = t2p[taskId];
        pq.erase({prevP, taskId});
        pq.insert({newPriority, taskId});
        t2p[taskId] = newPriority;
    }
    
    void rmv(int taskId) {
        int prevP = t2p[taskId];
        pq.erase({prevP, taskId});
        int user = t2u[taskId];
        u2t[user].erase(taskId);
        t2u.erase(taskId);
        t2p.erase(taskId);
    }
    
    int execTop() {
        if (pq.size() == 0) return -1;
        int t = (--pq.end())->second;
        int ans = t2u[t];
        rmv(t);
        return ans;
    }
};

/**
 * Your TaskManager object will be instantiated and called as such:
 * TaskManager* obj = new TaskManager(tasks);
 * obj->add(userId,taskId,priority);
 * obj->edit(taskId,newPriority);
 * obj->rmv(taskId);
 * int param_4 = obj->execTop();
 */