class Solution {
public:
    int smallestUniqueSubarray(vector<int>& nums) {
        int n = nums.size();
        const long long BASE1 = 1315423911LL, MOD1 = 1000000007LL;
        const long long BASE2 = 146527LL,     MOD2 = 1000000009LL;

        vector<long long> pow1(n + 1, 1), pow2(n + 1, 1);
        for (int i = 0; i < n; ++i) {
            pow1[i + 1] = (pow1[i] * BASE1) % MOD1;
            pow2[i + 1] = (pow2[i] * BASE2) % MOD2;
        }

        auto hasUnique = [&](int len) -> bool {
            long long h1 = 0, h2 = 0;
            for (int i = 0; i < len; ++i) {
                h1 = (h1 * BASE1 + nums[i]) % MOD1;
                h2 = (h2 * BASE2 + nums[i]) % MOD2;
            }

            vector<uint64_t> hashes;
            hashes.reserve(n - len + 1);
            hashes.push_back((uint64_t(h1) << 32) | uint64_t(h2));

            for (int i = len; i < n; ++i) {
                long long outVal = nums[i - len];
                long long inVal  = nums[i];

                h1 = (h1 - (outVal * pow1[len - 1]) % MOD1 + MOD1) % MOD1;
                h1 = (h1 * BASE1 + inVal) % MOD1;

                h2 = (h2 - (outVal * pow2[len - 1]) % MOD2 + MOD2) % MOD2;
                h2 = (h2 * BASE2 + inVal) % MOD2;

                hashes.push_back((uint64_t(h1) << 32) | uint64_t(h2));
            }

            // unordered_map ki jagah sort use kiya hai taaki TLE na aaye
            sort(hashes.begin(), hashes.end());
            int m = hashes.size();
            for (int i = 0; i < m; ++i) {
                bool sameLeft  = (i > 0 && hashes[i] == hashes[i - 1]);
                bool sameRight = (i + 1 < m && hashes[i] == hashes[i + 1]);
                if (!sameLeft && !sameRight) {
                    return true;
                }
            }
            return false;
        };

        int left = 1, right = n, ans = n;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (hasUnique(mid)) {
                ans = mid;
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        }

        return ans;
    }
};