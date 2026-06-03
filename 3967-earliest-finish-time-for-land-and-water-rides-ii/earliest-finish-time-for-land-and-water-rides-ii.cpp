class Solution {
public:
    int earliestFinishTime(vector<int>& landStartTime, vector<int>& landDuration, vector<int>& waterStartTime, vector<int>& waterDuration) {
        int n = landStartTime.size();
        int m = waterStartTime.size();
        vector<pair<int, int>> water(m);

        for (int i = 0; i < m; i++) {
            water[i] = {waterStartTime[i], waterDuration[i]};
        }

        sort(water.begin(), water.end());

        vector<int> wStart(m);
        vector<int> prefMinDurW(m);
        vector<int> suffMinFinishW(m);

        for (int i = 0; i < m; i++) {

            wStart[i] = water[i].first;

            if (i == 0)
                prefMinDurW[i] = water[i].second;
            else
                prefMinDurW[i] = min(prefMinDurW[i - 1], water[i].second);
        }

        for (int i = m - 1; i >= 0; i--) {

            int finish =
                water[i].first + water[i].second;

            if (i == m - 1)
                suffMinFinishW[i] = finish;
            else
                suffMinFinishW[i] = min(suffMinFinishW[i + 1], finish);
        }
        vector<pair<int, int>> land(n);

        for (int i = 0; i < n; i++) {
            land[i] = {landStartTime[i], landDuration[i]};
        }

        sort(land.begin(), land.end());

        vector<int> lStart(n);
        vector<int> prefMinDurL(n);
        vector<int> suffMinFinishL(n);

        for (int i = 0; i < n; i++) {

            lStart[i] = land[i].first;

            if (i == 0)
                prefMinDurL[i] = land[i].second;
            else
                prefMinDurL[i] = min(prefMinDurL[i - 1], land[i].second);
        }

        for (int i = n - 1; i >= 0; i--) {

            int finish =
                land[i].first + land[i].second;

            if (i == n - 1)
                suffMinFinishL[i] = finish;
            else
                suffMinFinishL[i] = min(suffMinFinishL[i + 1], finish);
        }

        int ans = INT_MAX;
        for (int i = 0; i < n; i++) {

            int landFinish =
                landStartTime[i] + landDuration[i];

            int pos =
                upper_bound(wStart.begin(),
                            wStart.end(),
                            landFinish) -
                wStart.begin();

            int best = INT_MAX;

            // Water ride already open
            if (pos > 0) {

                best =
                    min(best,
                        landFinish +
                        prefMinDurW[pos - 1]);
            }

            // Water ride opens later
            if (pos < m) {

                best =
                    min(best,
                        suffMinFinishW[pos]);
            }

            ans = min(ans, best);
        }
        for (int i = 0; i < m; i++) {

            int waterFinish =
                waterStartTime[i] + waterDuration[i];

            int pos =upper_bound(lStart.begin(),lStart.end(),waterFinish) - lStart.begin();

            int best = INT_MAX;

            // Land ride already open
            if (pos > 0) {

                best =
                    min(best,
                        waterFinish +
                        prefMinDurL[pos - 1]);
            }

            // Land ride opens later
            if (pos < n) {

                best =
                    min(best,
                        suffMinFinishL[pos]);
            }

            ans = min(ans, best);
        }

        return ans;
        
    }
};