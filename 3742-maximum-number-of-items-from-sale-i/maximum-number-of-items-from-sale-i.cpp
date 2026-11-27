
class Solution {
public:
    int maximumSaleItems(vector<vector<int>>& items, int budget) {
        int n = items.size();
        int min_price = 1e9;
        
        // Sabse sasta item ka price nikalo
        for (const auto& item : items) {
            min_price = min(min_price, item[1]);
        }

        // Har item ko pehli baar kharidne par kitne total items milenge (1 khud + free wale)
        vector<int> gains(n, 0);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (items[j][0] % items[i][0] == 0) {
                    gains[i]++;
                }
            }
        }

        // 0/1 Knapsack DP pehli purchase ke liye
        vector<int> dp(budget + 1, 0);
        for (int i = 0; i < n; ++i) {
            int price = items[i][1];
            int gain = gains[i];
            for (int b = budget; b >= price; --b) {
                dp[b] = max(dp[b], dp[b - price] + gain);
            }
        }

        // Bache hue budget se sabse sasta item (min_price) kharid lo
        int ans = 0;
        for (int b = 0; b <= budget; ++b) {
            ans = max(ans, dp[b] + (budget - b) / min_price);
        }

        return ans;
    }
};