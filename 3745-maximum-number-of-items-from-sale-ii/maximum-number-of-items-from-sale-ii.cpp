class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        vector<int> freq(n + 1, 0);
        long long minPrice = LLONG_MAX;

        for (const auto& item : items) {
            freq[item[0]]++;
            minPrice = min(minPrice, (long long)item[1]);
        }

        // Precompute total items whose factor is a multiple of f
        vector<int> multCount(n + 1, 0);
        for (int f = 1; f <= n; ++f) {
            if (freq[f] == 0) continue;
            for (int m = f; m <= n; m += f) {
                multCount[f] += freq[m];
            }
        }

        // Collect (price, max_double_copies) for items cheaper than 2 * minPrice
        vector<pair<long long, long long>> deals;
        for (const auto& item : items) {
            int f = item[0];
            long long p = item[1];
            int freeCap = multCount[f] - 1;
            if (freeCap > 0 && p < 2 * minPrice) {
                deals.push_back({p, freeCap});
            }
        }

        sort(deals.begin(), deals.end());

        long long ans = 0;
        long long remBudget = budget;

        for (auto& [price, cap] : deals) {
            if (remBudget < price) break;
            long long take = min(cap, remBudget / price);
            ans += take * 2;
            remBudget -= take * price;
        }

        ans += remBudget / minPrice;
        return (int)ans;
    }
};