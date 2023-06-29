#include <bits/stdc++.h>
#include <iostream>

using namespace std ;

class SegmentTree{
    public:
    vector<int>seg ; // Segment tree size = O(4N) i.e a size of 4N is sufficient , where N = number of elements in original array 
    SegmentTree(int n){
        seg.resize(4*n + 1) ;
    }
    void build(int ind , int low , int high , int arr[]){ // TC => O(N) i.e order of total number of nodes in segment tree 
    // We have 4N nodes so TC for bui.d is O(4N) => O(N)
        if(low == high){
            seg[ind] = arr[low] ;
            return ;
        }
        int mid = low + (high - low) / 2 ;
        build(2 * ind + 1 , low , mid , arr) ;
        build(2 * ind + 2 , mid + 1 , high , arr) ;
        seg[ind] = min(seg[2*ind + 1] , seg[2 * ind + 2]) ;
    }

    int query(int ind , int low , int high , int l , int r){ // range minimum query 
        // TC = O(logn) 
        // why ? bcoz for any range we are visiting the depth of the tree only for certain nodes , and for most nodes it would be 
        // the case of no overlap or complete overlap so we would just return , so we would go the depth only for partial overlap cases ,
        //  which would be very less in number in comparison 

        if(low >= l && high <= r){ // complete overlap 
            return seg[ind];
        }
        else if(high < l || low > r){ // No overlap 
            return INT_MAX ;
        }
        else{ // partial overlap 
            int mid = low + (high - low) / 2 ;
            int left = query(2*ind + 1 , low , mid , l , r) ;
            int right = query(2*ind + 2 , mid + 1 , high , l , r) ;
            return min(left , right) ;
        }
    }

    void update(int ind , int low , int high , int updateIndex , int val){
        // TC => O(logn)
        if(low == high){
            seg[ind] = val ;
            return ;
        }
        int mid = low + (high - low) / 2 ;
        // we search whether the index we are looking for is in the left or right subtree
        if(updateIndex <= mid){
            update(2 * ind + 1  , low , mid , updateIndex , val) ;
        }
        else{
            update(2 * ind + 2 , mid + 1 , high , updateIndex , val) ;
        }
        // While returning we recalculate the minimums 
        seg[ind] = min(seg[2*ind + 1] , seg[2*ind + 2]) ;
    }
};




int main(){
    int arr[] = {2 , 1 , 3 , 5 , 6 , -1};
    int n = 6 ;
    SegmentTree s(n) ; 
    s.build(0 , 0 , n - 1 , arr);
    int T ;
    cin >> T ;
    while(T--){
        int type , first , second ; 
        cin >> type >>  first >> second ;
        if(type == 1){ // Query 
            int l = first , r = second ;
            if(l < 0 || r > n || l > r) cout << "Invalid range \n";
            else cout << "Min in range " << l << " to " << r << " = " << s.query(0 , 0 , n - 1 , l , r) << "\n" ; 
        }else{ // type == 2 is point update
            int index = first;
            int val = second ;
            s.update(0 , 0 , n - 1 , index , val ) ; 
            cout << "\n" ;
        }
        
    }
    return 0 ;
}
