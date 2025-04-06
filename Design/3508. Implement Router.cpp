// Segment Tree TC:O(lgn) SC:O(n)
class Router {
    using ll = long long;
private:
    struct Packet {
        int source;
        int destination;
        int timestamp;
        
        Packet(int s, int d, int t) : source(s), destination(d), timestamp(t) {}
    };
    
    // 懶惰構建的線段樹節點
    struct SegmentTreeNode {
        int count;
        SegmentTreeNode *left, *right;
        
        SegmentTreeNode() : count(0), left(nullptr), right(nullptr) {}
        
        ~SegmentTreeNode() {
            if (left) delete left;
            if (right) delete right;
        }
    };
    
    queue<Packet> q;
    int memoryLimit;
    
    // 哈希表用於檢查重複
    unordered_map<ll, bool> packetExists;
    
    // 線段樹根據目的地分離
    unordered_map<int, SegmentTreeNode*> segmentTrees;
    
    ll packToKey(int source, int destination, int timestamp) {
        ll key = 0;
        key |= (ll)source << 40;
        key |= (ll)destination << 20;
        key |= (ll)timestamp;
        return key;
    }
    
    // 懶惰更新線段樹（只有當需要時才創建節點）
    void updateSegmentTree(SegmentTreeNode* &node, int start, int end, int timestamp, int val) {
        if (!node) {
            node = new SegmentTreeNode();
        }
        
        node->count += val;
        
        if (start == end) return;
        
        int mid = start + (end - start) / 2;
        if (timestamp <= mid) {
            updateSegmentTree(node->left, start, mid, timestamp, val);
        } else {
            updateSegmentTree(node->right, mid + 1, end, timestamp, val);
        }
    }
    
    // 查詢線段樹
    int querySegmentTree(SegmentTreeNode* node, int start, int end, int queryStart, int queryEnd) {
        if (!node) return 0;
        
        if (queryStart > end || queryEnd < start) return 0;
        
        if (queryStart <= start && queryEnd >= end) {
            return node->count;
        }
        
        int mid = start + (end - start) / 2;
        return querySegmentTree(node->left, start, mid, queryStart, queryEnd) + 
               querySegmentTree(node->right, mid + 1, end, queryStart, queryEnd);
    }
    
public:
    Router(int memoryLimit) {
        this->memoryLimit = memoryLimit;
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        // 檢查數據包是否重複
        ll key = packToKey(source, destination, timestamp);
        if (packetExists[key]) {
            return false;
        }
        
        // 如果達到記憶體限制，移除最舊的數據包
        if ((int)q.size() >= memoryLimit) {
            forwardPacket();
        }
        
        // 添加新數據包
        q.push(Packet(source, destination, timestamp));
        packetExists[key] = true;
        
        // 更新線段樹
        updateSegmentTree(segmentTrees[destination], 1, 1e9, timestamp, 1);
        
        return true;
    }
    
    vector<int> forwardPacket() {
        if (q.empty()) {
            return {};
        }
        
        Packet frontPacket = q.front();
        q.pop();
        
        ll key = packToKey(frontPacket.source, frontPacket.destination, frontPacket.timestamp);
        packetExists[key] = false;
        
        
        updateSegmentTree(segmentTrees[frontPacket.destination], 1, 1e9, frontPacket.timestamp, -1);
        
        return {frontPacket.source, frontPacket.destination, frontPacket.timestamp};
    }
    
    int getCount(int destination, int startTime, int endTime) {
        if (!segmentTrees[destination]) {
            return 0;
        }
        
        return querySegmentTree(segmentTrees[destination], 1, 1e9, startTime, endTime);
    }
};


// Map + vector TC:O(lgn) SC:O(n)
class Router {
    using ll = long long;
private:
    struct Packet {
        int source;
        int destination;
        int timestamp;
        
        Packet(int s, int d, int t) : source(s), destination(d), timestamp(t) {}
    };
    
    
    queue<Packet> q;
    int memoryLimit;
    
    // 哈希表用於檢查重複
    unordered_map<ll, bool> packetExists;
    // 根據目的地分開節點
    unordered_map<int, vector<int>> dest2time;
    
    ll packToKey(int source, int destination, int timestamp) {
        ll key = 0;
        key |= (ll)source << 40;
        key |= (ll)destination << 20;
        key |= (ll)timestamp;
        return key;
    }

public:
    Router(int memoryLimit) {
        this->memoryLimit = memoryLimit;
    }
    
    bool addPacket(int source, int destination, int timestamp) {
        // 檢查數據包是否重複
        ll key = packToKey(source, destination, timestamp);
        if (packetExists[key]) {
            return false;
        }
        
        if ((int)q.size() >= memoryLimit) {
            forwardPacket();
        }
        
        q.push(Packet(source, destination, timestamp));
        packetExists[key] = true;
        
        dest2time[destination].emplace_back(timestamp);
        
        return true;
    }
    
    vector<int> forwardPacket() {
        if (q.empty()) {
            return {};
        }
        
        Packet frontPacket = q.front();
        q.pop();
        
        ll key = packToKey(frontPacket.source, frontPacket.destination, frontPacket.timestamp);
        packetExists[key] = false;
        
        
       dest2time[frontPacket.destination].erase(lower_bound(dest2time[frontPacket.destination].begin(), dest2time[frontPacket.destination].end(),frontPacket.timestamp));
        
        return {frontPacket.source, frontPacket.destination, frontPacket.timestamp};
    }
    
    int getCount(int destination, int startTime, int endTime) {
        if (dest2time[destination].empty()) {
            return 0;
        }
        // vector<int> cur = dest2time[destination];
        auto right = upper_bound(dest2time[destination].begin(), dest2time[destination].end(), endTime);
        auto left = lower_bound(dest2time[destination].begin(), dest2time[destination].end(), startTime);
        return right - left;
    }
};
