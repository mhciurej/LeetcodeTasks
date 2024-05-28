//https://leetcode.com/problems/binary-tree-maximum-path-sum/submissions/1268722334/

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */

struct info 
{
    int inner_path;
    int to_the_root;
};

info get_info(TreeNode* root)
{
    if(!root) { return {0, 0}; }
    info left = get_info(root -> left);
    info right = get_info(root -> right);
    
    int inner[] = {
        0,
        left.inner_path,
        right.inner_path,
        left.to_the_root + root -> val + right.to_the_root,
        root -> val,
    };

    return { 
        *std::max_element(std::begin(inner), std::end(inner)),
        std::max(0, std::max(left.to_the_root + root -> val, root -> val + right.to_the_root))
    }; 
}

int maximal_node(TreeNode* root)
{
    if(!root) { return std::numeric_limits<int>::min(); }
    return std::max(root->val, std::max(maximal_node(root->left), maximal_node(root->right)));
}

class Solution {
public:
    int maxPathSum(TreeNode* root) {
        info result = get_info(root);
        int max = std::max(result.inner_path, result.to_the_root);
        if(max == 0) { return maximal_node(root); }
        return max;
    }
};