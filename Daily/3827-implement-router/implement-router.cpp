class Router {
    using ll = long long;
    struct Packet {
        int source;
        int destination;
        int timestamp;
        Packet(int s, int d, int t) : source(s), destination(d), timestamp(t){}
    };
    unordered_map<int, vector<int>> d2t;
    queue<Packet> q;
    unordered_map<ll, bool> mp;
    int memoryLimit;

    ll packTokey(int source, int destination, int timestamp) {
        return  ((ll) source << 50) | ((ll) destination << 30) | (ll) timestamp;
    }
public:
    Router(int memoryLimit) {
        this -> memoryLimit = memoryLimit;
    }

    bool addPacket(int source, int destination, int timestamp) {
        ll key = packTokey(source, destination, timestamp);
        if (mp[key]) return false;
        if (q.size() == memoryLimit) {
            forwardPacket();
        }
        mp[key] = true;
        q.push(Packet(source, destination, timestamp));
        d2t[destination].emplace_back(timestamp);
        return true;
    }

    vector<int> forwardPacket() {
        if (q.empty()) return {};
        Packet frontPacket = q.front();
        q.pop();
        ll key = packTokey(frontPacket.source, frontPacket.destination, frontPacket.timestamp);
        mp[key] = false;
        d2t[frontPacket.destination].erase(lower_bound(d2t[frontPacket.destination].begin(), d2t[frontPacket.destination].end(), frontPacket.timestamp));
        return {frontPacket.source, frontPacket.destination, frontPacket.timestamp};
    }

    int getCount(int destination, int startTime, int endTime) {
        if (d2t[destination].empty()) {
            return 0;
        }

        auto right = upper_bound(d2t[destination].begin(), d2t[destination].end(), endTime);
        auto left = lower_bound(d2t[destination].begin(), d2t[destination].end(), startTime);
        return right - left;
    }
};



/**
 * Your Router object will be instantiated and called as such:
 * Router* obj = new Router(memoryLimit);
 * bool param_1 = obj->addPacket(source,destination,timestamp);
 * vector<int> param_2 = obj->forwardPacket();
 * int param_3 = obj->getCount(destination,startTime,endTime);
 */