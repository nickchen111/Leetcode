// TC:O(logn) SC:O(n)
class ExamTracker {
    using ll = long long;
    vector<ll> presum;
    vector<ll> allTime;
public:
    ExamTracker() {
        presum.emplace_back(0);
        allTime.emplace_back(0);
    }
    
    void record(int time, int score) {
        allTime.emplace_back(time);
        presum.emplace_back(presum.back() + score);
    }
    
    long long totalScore(int startTime, int endTime) {
        //二分查找 >= startTime, <= endTime
        auto iter1 = lower_bound(allTime.begin(), allTime.end(), startTime);
        auto iter2 = upper_bound(allTime.begin(), allTime.end(), endTime);
        if (iter2 == allTime.begin() || iter1 == allTime.end()) return 0;
        return presum[iter2 - allTime.begin() - 1] - presum[iter1 - allTime.begin() - 1];
    }
};

/**
 * Your ExamTracker object will be instantiated and called as such:
 * ExamTracker* obj = new ExamTracker();
 * obj->record(time,score);
 * long long param_2 = obj->totalScore(startTime,endTime);
 */
