/*
253. Meeting Rooms II
给定一系列的会议时间间隔intervals，包括起始和结束时间[[s1,e1],[s2,e2],...] (si < ei)，找到所需的最小的会议室数量。

输入: intervals = [(0,30),(5,10),(15,20)]
输出: 2
解释:
需要两个会议室
会议室1:(0,30)
会议室2:(5,10),(15,20)

输入: intervals = [(2,7)]
输出: 1
解释:
只需要1个会议室就够了
*/

// sweeping line  TC:O(nlgn) SC:O(n)
class Solution {
public:
    int minMeetingRooms(vector<Interval> &intervals) {
        //尋找同一時間最多人開會的會議次數 就是本題答案
        //先用sweeping line的方式做
        vector<pair<int,int>> q;
        for(int i = 0; i < intervals.size(); i++){
            q.push_back({intervals[i].start, +1});
            q.push_back({intervals[i].end, -1});
        }
        sort(q.begin(), q.end());

        int res = 0;
        int sum = 0;
        for(int i = 0; i<q.size(); i++){
            sum +=q[i].second;
            res = max(res, sum);
        }
        return res;
    }
};


//sort + pq TC:O(nlgn) SC:O(n)
class Solution {
public:
    static bool cmp1(Intereval& a, Interval& b){
        return a.start < b.start;
    }
    struct cmp2{
        bool operator()(Interval& a, Interval& b){
            return a.end > b.end;
        }
    };
    int minMeetingRooms(vector<Interval> &intervals) {
        sort(intervals.begin(), intervals.end(), cmp1);
        priority_queue<Interval, vector<Interval>, decltype(cmp2)> pq(cmp2);

        int count = 0;
        while(i < intervals.size()){
            while(pq.empty() || i < intervals.size() && pq.top().end > intervals[i].start){
                pq.push(intervals[i]);
                i++;
            }
            int n = pq.size();
            count = max(count, n);
            pq.pop();
        }

        return count;
    }
};

/*
解法1:
此题用到了sort和pq的组合拳，是一类题目的典型。
先将intervals按照start进行从先到后排序。注意，这是解此类问题的一个常见步骤。
然后我们构建一个pq，这个队列里按照end自动排序，end小的排在栈顶。我们令pq里面存装的是当前正在同时进行的会议。
在遍历intervals元素的过程中，如果pq.top().end>intervals[i].start，说明正在进行的会议里，即使最早结束的那个，也都晚于当前考虑的会议intervals[i]的开始时间。
没办法，但当前会议必须开，所以要将intervals[i]加入pq里面。pq的size因此变大。然后考虑下一个i，直至pq.top().end<=intervals[i].start。
然后将pq弹出最早结束的一个会议，重复之前的操作，会有新的会议加入需要同时举行。
输出结果就是pq在整个遍历过程中的最大size。
对于pq的数据结构，我们在C++中还可以用multiset来实现，因为它也是自动有序的。

解法2: 扫描线
本题和732一模一样。将所有{startTime,1}和{endTime,-1}加入一个数组,然后将这个数组按照时间戳排序.注意,本题中所有的有效区间的长度必须大于0,所以,{time,-1}要比{time,1}排序更靠前.
使用一个count依时间顺序将所有的+1/-1进行累加.当count>0的时候标志着一个会议的开始,重新归为0的时候标着一个会议的结束.
*/
