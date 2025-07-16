// class Solution {
     

// public:
//       // declaring the global allocation.
//       vector<int> segmentTree;
//       int n;

//       void buildsegmentTree(int idx,int l,int r,vector<int> & nums){
       
//        // using the base case.
//        if(l  ==   r){
//         segmentTree[idx] = l; // storing the index at the leaf Node.
//         return;
//        }

//       // now applying as usual approach.
//       int mid = l + (r - l)/2;

//       buildsegmentTree(2*idx+1,l,mid,nums); // left call.
//       buildsegmentTree(2*idx+2,mid+1,r,nums); // right call;

//       int leftmaxIndex = segmentTree[2*idx+1];
//       int rightmaxIndex = segmentTree[2*idx+2];

//       if(nums[leftmaxIndex]>=nums[rightmaxIndex]){
//         segmentTree[idx] = leftmaxIndex;
//       }
//       else{
//         segmentTree[idx] = rightmaxIndex;
//       }

//       }


//       int RMIQ(int idx,int l,int r,int left,int right,vector<int> & heights){
//       // using the base case
//       // case 1: Non overlapping case
//       if(r<left || l>right){
//         return -1; // invalid case.
//       }

//       // case 2: total overlapping case
//       if(l>=left && r<=right){
//         return segmentTree[idx];
//       }

//       // here the case of the partial overlapping.
//        int mid = l + (r - l)/2;
//       int leftmaxIndex = RMIQ(2*idx+1,l,mid,left,right,heights);
//       int rightmaxIndex = RMIQ(2*idx+2,mid+1,r,left,right,heights);


//           if(leftmaxIndex == -1) return rightmaxIndex;
//           if(rightmaxIndex == -1) return leftmaxIndex;


//       if(heights[leftmaxIndex]>=heights[rightmaxIndex]){
//         return leftmaxIndex;
//       }
//       else{
//         return rightmaxIndex;
//       }



//       }


//     vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
          
//       // using the optimal approach.

//        n = heights.size();
//        segmentTree.resize(4*n);
//        buildsegmentTree(0,0,n-1,heights);
//       vector<int> ans;
      


//      int n1 = queries.size();

//      // traversal of the queries.
//      for(int  i = 0; i<n1; i++){
       
//            int left = min(queries[i][0],queries[i][1]);
//            int right  = max(queries[i][0],queries[i][1]);
//          if(left == right){
//             ans.push_back(left); // alice and Bob are at the same Building.
//             continue; // for next range search.
//          }

//          if(heights[left]<=heights[right]){
//             ans.push_back(right);
//             continue; // for next range search.
//          }
          
//           // now the index of the finding the rightIndex.
//           int leftIndex = right+1;
//           int rightIndex = n-1; 
          
        
//          // now apply the binary search.
//            int reqIndex = INT_MAX;
//          while(leftIndex<=rightIndex){
//             int mid = leftIndex + (rightIndex - leftIndex)/2;

          

//             int index = RMIQ(0,0,n-1,leftIndex,mid,heights);

//             if(index != -1 && ( heights[index]>heights[left] && heights[index]>heights[right] )){
                
//                     reqIndex = min(reqIndex,index);
                 
//                  rightIndex = mid - 1;
//             }
//             else{
//                 leftIndex = mid+1;
//             }

    
//     }

//          if(reqIndex == INT_MAX){
//             ans.push_back(-1);
//          }  
//          else{
//             ans.push_back(reqIndex);
//          }

//      }



//      return ans;


//     }
// };

class Solution {
public:

    vector<int> seg;
    vector<int> arr;
    vector<int> ans;
    void buildtree(int i, int left, int right){
        if(left == right){
            seg[i] = left;
            return;
        }
        int  mid = left + (right- left)/2;
        buildtree(2*i+1, left, mid);
        buildtree(2*i+2, mid+1, right);
        if(arr[seg[2*i + 1]] >= arr[seg[2*i + 2]]){
            seg[i] = seg[2*i+1];
        }
        else{
            seg[i] = seg[2*i+2];
        }
    }

    int find(int i, int left,int right, int start, int end){
        if(start > right || left > end) return -1;
        if(left>=start && right<=end) return seg[i];
        int mid = left + (right-left)/2;
        int l = find(2*i+1, left, mid, start, end);
        int r = find(2*i+2, mid+1, right, start, end);
        if(l == -1 && r != -1) return r;
        else if(l != -1 && r == -1) return l;
        if(arr[l] >= arr[r]){
            return l;
        }
        return r;
    }


    vector<int> leftmostBuildingQueries(vector<int>& heights, vector<vector<int>>& queries) {
        int n = heights.size();
        seg.resize(4*n ,0);
        arr.resize(n ,0);
        arr = heights;
        buildtree(0, 0, n-1);
        for(auto x:queries){
            int from = min(x[0],x[1]);
            int to = max(x[0],x[1]);
            int start = to+1;
            int end = n-1;
            int res = -1;
            if(from == to){
                ans.push_back(from);
                continue;
            }
            if(arr[find(0,0,n-1,start-1,start-1)] > arr[from]){
                ans.push_back(start-1);
                continue;
            }
            while(start <= end){
                int mid = start + (end -start)/2;
                int ind = find(0, 0, n-1, start, mid);
                if(arr[ind] > arr[from] && arr[ind] > arr[to]){
                    res = ind;
                    end=mid-1;
                }
                else{
                    start = mid+1;
                }
            }
            ans.push_back(res);
        }
        return ans;
    }
};