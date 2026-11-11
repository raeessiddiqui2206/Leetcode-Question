class Solution {
public:
    int sumOfUnique(vector<int>& nums) {
        int sum = 0;
        int len =  nums.size();
        for(int i = 0 ; i < len ; i++){
            int k = 1;
            for(int j = 0; j < len ; j++){
                if( j != i && nums[i] == nums[j]){
                    k = 0;
                    break;
                }
            }
            if(k){
                sum += nums[i];
                }
        }
        return sum;
    }
};