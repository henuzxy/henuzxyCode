84. 柱状图中最大的矩形
给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。

求在该柱状图中，能够勾勒出来的矩形的最大面积。

![img](..\img\histogram.png)

以上是柱状图的示例，其中每个柱子的宽度为 1，给定的高度为 [2,1,5,6,2,3]。
 

示例:

输入: [2,1,5,6,2,3]
输出: 10

```cpp
class Solution {
public:
    int largestRectangleArea(vector<int>& heights) {
        stack<int> stc;
        int res = 0;
        heights.push_back(0);//这里放0是为了能清空栈，让每个数都被计算
        for(int i=0;i<heights.size();i++){
            while(!stc.empty() && heights[i] < heights[stc.top()]){
                int h = heights[stc.top()];
                stc.pop();
                int l = stc.empty()? 0:stc.top()+1;
                int area = (i-l)*h;
                res = max(res,area);
        //        cout << area << endl;
            }
            stc.push(i);
        }
        return res;
    }
};
```

描述
给出一个整数数组 nums 和一个整数 k。划分数组（即移动数组 nums 中的元素），使得：

所有小于k的元素移到左边
所有大于等于k的元素移到右边
返回数组划分的位置，即数组中第一个位置 i，满足 nums[i] 大于等于 k。

```cpp
class Solution {
public:
    /**
     * @param nums: The integer array you should partition
     * @param k: An integer
     * @return: The index after partition
     */
    int partitionArray(vector<int> &nums, int k) {
        if(nums.size() == 0){
          return 0;
        }
        int l = 0,r = nums.size()-1;
        while(l < r){
          while(l < r && nums[l] < k){
            l += 1;
          }
          while(l < r && nums[r] >= k){
            r -= 1;
          }
          swap(nums[l],nums[r]);
        }
        if(nums[l] >= k){//这里必须要判断，因为如果数组里面的数都比target小，要输出nums.size()+1;
          return l;
        }else{
          return l+1;
        }
    }
};
```