// TC:O(1) SC:O(n)
class TaskManager {
private:
    // 儲存任務信息：{priority, taskId} -> userId
    map<pair<int,int>, int> tasks;
    // 儲存每個taskId對應的優先級
    unordered_map<int, int> taskPriorities;
    
public:
    TaskManager(vector<vector<int>>& tasks) {
        for(const auto& task : tasks) {
            add(task[0], task[1], task[2]);
        }
    }
    
    void add(int userId, int taskId, int priority) {
        tasks[{priority, taskId}] = userId;
        taskPriorities[taskId] = priority;
    }
    
    void edit(int taskId, int newPriority) {
        int oldPriority = taskPriorities[taskId];
        auto it = tasks.find({oldPriority, taskId});
        int userId = it->second;
        tasks.erase(it);
        
        tasks[{newPriority, taskId}] = userId;
        taskPriorities[taskId] = newPriority;
    }
    
    void rmv(int taskId) {
        int priority = taskPriorities[taskId];
        tasks.erase({priority, taskId});
        taskPriorities.erase(taskId);
    }
    
    int execTop() {
        if(tasks.empty()) return -1;
        
        auto it = tasks.rbegin();
        int userId = it->second;
        int taskId = it->first.second;
        // 刪除該任務
        rmv(taskId);
        
        return userId;
    }
};
