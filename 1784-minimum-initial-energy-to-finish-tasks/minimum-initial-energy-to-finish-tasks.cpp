class Solution {
public:
    int minimumEffort(vector<vector<int>>& tasks) {
        // Step 1: Sort based on (minimum - actual) descending
        sort(tasks.begin(), tasks.end(), [](auto &a, auto &b) {
            return (a[1] - a[0]) > (b[1] - b[0]);
        });

        int initialEnergy = 0;
        int currentEnergy = 0;

        // Step 2: Process tasks
        for (auto &task : tasks) {
            int actual = task[0];
            int minimum = task[1];

            if (currentEnergy < minimum) {
                initialEnergy += (minimum - currentEnergy);
                currentEnergy = minimum;
            }

            currentEnergy -= actual;
        }

        return initialEnergy;
        
    }
};