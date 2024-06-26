#include<bits/stdc++.h>
using namespace std;

class TreeNode{
    int index;
    public: 

    int val;
    TreeNode* left;
    TreeNode* right;
    
    TreeNode(int index, TreeNode* left, TreeNode* right) {
        this->index = index;
        this->left = left;
        this->right = right;
    }
    ~TreeNode(){
        delete left;
        delete right;
    }
};

TreeNode* makeSegmentTree(vector<int> &v, int start, int end,int index, bool maximum){
    TreeNode* node = new TreeNode(index, NULL, NULL);
    if(start == end) {
        node->val = v[start];
    } else {
        TreeNode* left = makeSegmentTree(v, start, (start+end)/2, 2*index + 1, maximum);
        TreeNode* right = makeSegmentTree(v, (start+end)/2 + 1, end, 2*index + 2, maximum);
        node->left = left;
        node->right = right;
        if(maximum) node->val = max(node->left->val, node->right->val);
        else  node->val = min(node->left->val, node->right->val);
    }
    return node;
}

int find(TreeNode* root, int start, int end, int actualstart, int actualend, bool maximum){
    if(actualstart > end || actualend < start) {
        if(maximum) return INT_MIN;
        else return INT_MAX;
    }
    if(actualstart <= start && actualend >= end){
        return root->val;
    } else {
        int left = find(root->left, start, (start+end)/2, actualstart, actualend, maximum);
        int right = find( root->right, (start+end)/2 + 1, end,actualstart, actualend, maximum );
        if(maximum) return max(left,right);
        else return min(left, right);
    }
}

int main(){
    vector<int> v = {8,2,5,1,4,5,3,9,6,10};
    TreeNode* root = makeSegmentTree(v, 0, v.size() -1, 0, false);
    cout<<find(root, 0,9,4,9,false);
    return 0;
}