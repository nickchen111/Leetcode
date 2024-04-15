/*
1792. Maximum Average Pass Ratio
*/

// 4/15  TC:O(nlgn + mlgn) SC:O(n)
class Solution {
    using PDI = pair<double, int>;
public:
    double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
        int n = classes.size(); //  class number
        priority_queue<PDI, vector<PDI>, less<PDI>> pq;
        vector<double> arr;
        for(int i = 0; i < n; i++){
            double pass = classes[i][0];
            double total = classes[i][1];
            arr.push_back(pass/total);
            pq.push({((pass+1)/(total+1)) - (pass/total), i});
        }

        while(extraStudents--){
            double increaseRate = pq.top().first;
            int need2change = pq.top().second;
            arr[need2change] += increaseRate;
            classes[need2change][0] += 1;
            classes[need2change][1] += 1;
            pq.pop();
            double pass = classes[need2change][0];
            double total = classes[need2change][1];
            pq.push({((pass+1)/(total+1)) - (pass/total), need2change});
        }

        double res = 0;
        for(int i = 0; i < n; i++){
            res += arr[i];
        }
        

        return res/n*1.0;
    }
};

/*
想將全體通過率拉高 可以加入一些必定通過的學生 問說要如何最好的安插來最大化全體通過率
全體通過率是 全部班級通過率加總/班級數量
可以知道說要想增加全體通過率 可能就是要試試看哪個能讓總和通過率更高 -> +1後拉升程度最高
*/

// TC:O(nlgn + mlgn) SC:O(n)
class Solution {
public:
double maxAverageRatio(vector<vector<int>>& classes, int extraStudents) {
	int n = classes.size();
    auto profit = [&](double pass, double total) {
        return (pass + 1) / (total + 1) - pass / total;
    };

    priority_queue<pair<double, array<double, 2>>> pq;
    for(auto &cla : classes){
        double pass = cla[0];
        double total = cla[1];
        pq.push({profit(pass,total), {pass, total}});
    }
    
    while(extraStudents--){
        double pass = pq.top().second[0];
        double total = pq.top().second[1];
        pq.pop();
        pq.push({profit(pass+1,total+1), {pass+1, total+1}});
    }

    double res = 0;
    double sum = 0;
    while(!pq.empty()){
        sum += (pq.top().second[0]) / (pq.top().second[1]);
        pq.pop();
    }

    res = sum / (double)(n);

    return res;
    }
};
