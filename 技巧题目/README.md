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