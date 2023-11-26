/*
729. My Calendar I
*/

// TC:O(nlgn) SC:O(n)
class MyCalendar {
    set<pair<int,int>> set;// start,end
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        for(auto &x:set){
            if(!(x.first >= end || x.second <= start)) return false;
        }
        set.insert({start,end});
        return true;
    }
};
