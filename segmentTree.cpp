#include <bits/stdc++.h>
#include <iostream>

using namespace std ;

class SegmentTree{
    public:
    vector<int>seg ; // Segment tree size = O(4N) i.e a size of 4N is sufficient , where N = number of elements in original array 
    vector<int>lazy ;
    SegmentTree(int n){
        seg.resize(4*n + 1) ;
        lazy.resize(4*n + 1 , 0) ;
    }
    void build(int ind , int low , int high , int arr[]){ // TC => O(N) i.e order of total number of nodes in segment tree 
    // We have 4N nodes so TC for build is O(4N) => O(N)
        if(low == high){
            seg[ind] = arr[low] ;
            return ;
        }
        int mid = low + (high - low) / 2 ;
        build(2 * ind + 1 , low , mid , arr) ;
        build(2 * ind + 2 , mid + 1 , high , arr) ;
        seg[ind] = seg[2*ind + 1] + seg[2 * ind + 2];
    }
    /*
    ind => index for the node in the seg array 
    low , high => node's range 
    l , r => query range 
    */
    int query(int ind , int low , int high , int l , int r){ // range sum query 
        // TC = O(logn) 
        // why ? bcoz for any range we are visiting the depth of the tree only for certain nodes and depth == O(logn) , and for most nodes it would be 
        // the case of no overlap or complete overlap so we would just return , so we would go the depth only for partial overlap cases ,
        //  which would be very less in number in comparison 

        if(low >= l && high <= r){ // complete overlap 
            return seg[ind];
        }
        else if(high < l || low > r){ // No overlap 
            return 0 ;
            // return INT_MAX ;
        }
        else{ // partial overlap 
            int mid = low + (high - low) / 2 ;
            int left = query(2*ind + 1 , low , mid , l , r) ;
            int right = query(2*ind + 2 , mid + 1 , high , l , r) ;
            // For range sum query instead of min(left , right) we just return left + right 
            return left + right ;
            // return min(left ,right) ;
        }
    }

    // Point Update 
    // TC => O(logn)
    void pointUpdate(int ind , int low , int high , int updateIndex , int val){
        
        if(low == high){
            seg[ind] = val ;
            return ;
        }
        int mid = low + (high - low) / 2 ;
        // we search whether the index we are looking for is in the left or right subtree
        if(updateIndex <= mid){
            pointUpdate(2 * ind + 1  , low , mid , updateIndex , val) ;
        }
        else{
            pointUpdate(2 * ind + 2 , mid + 1 , high , updateIndex , val) ;
        }
        // While returning we recalculate the minimums 
        seg[ind] = seg[2*ind + 1] + seg[2*ind + 2];
    }

    // Range update with lazy 
    // TC => O(logn)
    void rangeUpdate(int ind , int low ,int high , int l , int r , int val){
        // upon reaching a node first clear all the pending lazy updates of that node 
        if(lazy[ind] != 0){
            seg[ind] += (high - low + 1) * lazy[ind] ; // clear lazy updates of that node

            // in case of range minimum query (RMQ) => seg[ind] += lazy[ind]

            // if it is not a leaf node then further propagate the lazy update downwards 
            if(low != high){
                lazy[2 * ind + 1] = lazy[ind] ;
                lazy[2 * ind + 2] = lazy[ind] ;
            }
            // lazy of current node has been cleared 
            lazy[ind] = 0 ;
        }

        // if the node lies completely out of the update range i.e. no overlap case then simply return 
        if(high < l || low > r) return ;
        
        // if node lies completely inside update range then update the node with appropriate value 
        // ex -> if node i has value 3 and has low = 2 and high = 6 and val = 5 
        // then this node is responsible for 6 - 2 + 1 = 5 nodes , so we increment the node's value by 5 * val i.e. 5 * 5 = 25 
        // the update => 3 ----> 25
        // and we lazily propagate the update of "val" to the children 
        if(l >= low && high <= r){
            seg[ind] += (high - low + 1) * val ; // update current node 

            // in case of range minimum query (RMQ) => seg[ind] += val

            // lazy propagate to children 
            if(low != high){
                lazy[2 * ind + 1] += val ;
                lazy[2 * ind + 2] += val ;
            }
            return ;
        }

        // otherwise in case of partial overlap we go to both left and right children and retrieve the value 
        int mid = low + (high - low) / 2 ;
        rangeUpdate(2 * ind + 1 , low , mid , l , r , val) ;
        rangeUpdate(2 * ind + 2 , mid + 1 , high , l , r , val) ;
        // and revaulate all nodes while backtracking 
        seg[ind] = seg[2 * ind + 1 ] + seg[2 * ind + 2] ;
        // seg[ind] = min(seg[2 * ind + 1 ] , seg[2 * ind + 2]) ;
    }
    
    // TC => O(logn)
    int querySumLazy(int ind , int low , int high , int l , int r){
        // upon reaching a node first clear all the pending lazy updates of that node 
        if(lazy[ind] != 0){
            seg[ind] += (high - low + 1) * lazy[ind] ; 
            // seg[ind] += lazy[ind]
            if(low != high){
                lazy[2 * ind + 1] = lazy[ind] ;
                lazy[2 * ind + 2] = lazy[ind] ;
            }
            lazy[ind] = 0 ;
        }

        // no overlap 
        if(high < l || low > r){
            return 0 ;
            // return INT_MAX ;
        }

        // complete overlap
        if(l >= low && high <= r){
            return seg[ind] ;
        }
        // partial overlap 
        int mid = low + (high - low) / 2 ;
        int left = querySumLazy(2 * ind + 1 , low , mid , l , r) ;
        int right = querySumLazy(2 * ind + 2 , mid + 1 , high , l , r) ;
        return left + right ;
        // return min(left ,right)
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
            else cout << "Sum in range " << l << " to " << r << " = " << s.querySumLazy(0 , 0 , n - 1 , l , r) << "\n" ; 
        }else if(type == 2){ // type == 2 is point update
            int index = first;
            int val = second ;
            s.pointUpdate(0 , 0 , n - 1 , index , val ) ; 
            cout << "\n" ;
        }
        else if(type == 3){ // type == 3 is range update
            int l = first ; 
            int r = second ; 
            int val ; 
            cin >> val ;
            s.rangeUpdate(0 , 0 , n - 1 , l , r , val) ;
        }
    }
    return 0 ;
}
