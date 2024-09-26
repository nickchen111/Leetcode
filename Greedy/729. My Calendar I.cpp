/*
729. My Calendar I
*/

// TC:O(lgn) SC:O(n)
class MyCalendar {
    map<int, int> map;
public:
    MyCalendar() {
        
    }
    
    bool book(int start, int end) {
        auto iter = map.upper_bound(start);
        if(iter != map.begin()) {
            auto iter2 = prev(iter);
            if(iter2->second > start){
                return false;
            }
        }

        if(iter != map.end() && iter->first < end) {
            return false;
        }

        map[start] = end;

        return true;
    }
};
