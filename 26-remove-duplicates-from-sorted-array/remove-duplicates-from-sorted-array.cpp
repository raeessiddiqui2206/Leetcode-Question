class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int count = 1;
        vector<int> f; 
        f.push_back(nums[0]);
        for(int i = 0 ; i < nums.size() ; i++){
            if(i!=0 && nums[i]!=nums[i-1]){
                f.push_back(nums[i]);
                count++;
            }
        }
        for(int i=0; i < f.size(); i++){
            nums[i] = f[i];
        }
        return count;
    }
};