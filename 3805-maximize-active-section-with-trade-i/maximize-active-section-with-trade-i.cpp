class Solution {
public:
    int maxActiveSectionsAfterTrade(string s) {
        string t = "1" + s + "1";
        int n = t.size();
        
        vector<char> btype;
        vector<int> blen;
        int i = 0;
        while (i < n) {
            int j = i;
            while (j < n && t[j] == t[i]) j++;
            btype.push_back(t[i]);
            blen.push_back(j - i);
            i = j;
        }
        int m = btype.size();
        
        long long ones = 0;
        for (char c : s) if (c == '1') ones++;
        
        // Find top-3 zero-blocks (len, idx) via a single linear scan — O(n)
        // top1 >= top2 >= top3
        pair<int,int> top1 = {-1,-1}, top2 = {-1,-1}, top3 = {-1,-1};
        for (int k = 0; k < m; k++) {
            if (btype[k] != '0') continue;
            pair<int,int> cur = {blen[k], k};
            if (cur.first > top1.first) {
                top3 = top2;
                top2 = top1;
                top1 = cur;
            } else if (cur.first > top2.first) {
                top3 = top2;
                top2 = cur;
            } else if (cur.first > top3.first) {
                top3 = cur;
            }
        }
        
        long long best = 0; // "do nothing" option always available
        
        for (int k = 1; k < m - 1; k++) { // skip augmented boundary blocks
            if (btype[k] != '1') continue;
            
            int x = blen[k];
            int leftIdx = k - 1, rightIdx = k + 1;
            int L = blen[leftIdx], R = blen[rightIdx];
            
            long long mergeGain = (long long)L + R;
            
            long long otherGain = LLONG_MIN;
            if (top1.second != -1 && top1.second != leftIdx && top1.second != rightIdx) {
                otherGain = (long long)top1.first - x;
            } else if (top2.second != -1 && top2.second != leftIdx && top2.second != rightIdx) {
                otherGain = (long long)top2.first - x;
            } else if (top3.second != -1 && top3.second != leftIdx && top3.second != rightIdx) {
                otherGain = (long long)top3.first - x;
            }
            
            long long gain = max(mergeGain, otherGain);
            best = max(best, gain);
        }
        
        return (int)(ones + best);
    }
};