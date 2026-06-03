class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();

        // Water rides preprocessing
        vector<pair<int, int>> water(m);
        for (int i = 0; i < m; i++) {
            water[i] = {waterStartTime[i], waterDuration[i]};
        }

        sort(water.begin(), water.end());

        vector<int> wStart(m);
        vector<long long> prefMinDurW(m);
        vector<long long> suffMinFinishW(m);

        for (int i = 0; i < m; i++) {
            wStart[i] = water[i].first;

            if (i == 0)
                prefMinDurW[i] = water[i].second;
            else
                prefMinDurW[i] =
                    min(prefMinDurW[i - 1], (long long)water[i].second);
        }

        for (int i = m - 1; i >= 0; i--) {
            long long val = (long long)water[i].first + water[i].second;

            if (i == m - 1)
                suffMinFinishW[i] = val;
            else
                suffMinFinishW[i] = min(suffMinFinishW[i + 1], val);
        }

        // Land rides preprocessing
        vector<pair<int, int>> land(n);
        for (int i = 0; i < n; i++) {
            land[i] = {landStartTime[i], landDuration[i]};
        }

        sort(land.begin(), land.end());

        vector<int> lStart(n);
        vector<long long> prefMinDurL(n);
        vector<long long> suffMinFinishL(n);

        for (int i = 0; i < n; i++) {
            lStart[i] = land[i].first;

            if (i == 0)
                prefMinDurL[i] = land[i].second;
            else
                prefMinDurL[i] =
                    min(prefMinDurL[i - 1], (long long)land[i].second);
        }

        for (int i = n - 1; i >= 0; i--) {
            long long val = (long long)land[i].first + land[i].second;

            if (i == n - 1)
                suffMinFinishL[i] = val;
            else
                suffMinFinishL[i] = min(suffMinFinishL[i + 1], val);
        }

        long long ans = LLONG_MAX;

        // Land -> Water
        for (int i = 0; i < n; i++) {

            long long t =
                (long long)landStartTime[i] + landDuration[i];

            long long best = LLONG_MAX;

            int pos = upper_bound(wStart.begin(), wStart.end(), t) -
                      wStart.begin();

            // water ride already open
            if (pos > 0) {
                best = min(best, t + prefMinDurW[pos - 1]);
            }

            // water ride opens later
            if (pos < m) {
                best = min(best, suffMinFinishW[pos]);
            }

            ans = min(ans, best);
        }

        // Water -> Land
        for (int i = 0; i < m; i++) {

            long long t =
                (long long)waterStartTime[i] + waterDuration[i];

            long long best = LLONG_MAX;

            int pos = upper_bound(lStart.begin(), lStart.end(), t) -
                      lStart.begin();

            // land ride already open
            if (pos > 0) {
                best = min(best, t + prefMinDurL[pos - 1]);
            }

            // land ride opens later
            if (pos < n) {
                best = min(best, suffMinFinishL[pos]);
            }

            ans = min(ans, best);
        }

        return ans;
        
    }
};