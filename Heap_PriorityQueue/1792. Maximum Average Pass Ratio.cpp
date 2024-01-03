/*
1792. Maximum Average Pass Ratio
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
