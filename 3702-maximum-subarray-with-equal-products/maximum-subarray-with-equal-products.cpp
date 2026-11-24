class Solution {
public:
    int maxLength(vector<int>& nums) {
        int ans = 2;
        int left = 0;
        long long prod = 1;

        for (int right = 0; right < nums.size(); ++right) {
            while (gcd(prod, (long long)nums[right]) > 1) {
                prod /= nums[left];
                left++;
            }
            prod *= nums[right];
            ans = max(ans, right - left + 1);
        }

        return ans;
    }
};
