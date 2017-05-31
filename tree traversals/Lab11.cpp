#include <iostream>
#include <stack>
#include <queue>

using namespace std;

// Tree Node has data, left pointer, right pointer
struct TreeNode
{
    int datum;
    struct TreeNode* left;
    struct TreeNode* right;
};

// create a new node with given value, left and right pointers are nullptr
struct TreeNode* newTreeNode(int value)
{
    struct TreeNode* node = new struct TreeNode;
    node->datum = value;
    node->left = NULL;
    node->right = NULL;
    return(node);
}

// Non-recursive traverse a binary tree
// print out the values by inorder
// it uses stack to store the nodes 
void noRecInorder(TreeNode *root)
{
    stack<TreeNode*> noRecTree;

    while(true)
    {
        while(root != NULL)
        {
            noRecTree.push(root);
            root = root->left;
        }
                            
        if(noRecTree.empty())
        {
            break;
        }

        root = noRecTree.top();
        noRecTree.pop();

        cout << root->datum << endl;

        root = root->right;
    }
}

// level order traversal 
// It uses queue to store the values of the next level
void levelOrder(TreeNode *root)
{
    queue<TreeNode*> noRecTree;

    if(root != NULL)
    {
        noRecTree.push(root);
    }

    while(!noRecTree.empty())
    {
        TreeNode *temp;
        temp = noRecTree.front();
        noRecTree.pop();
        cout << temp->datum << endl;

        if(temp->left != NULL)
        {
            noRecTree.push(temp->left);
        }
        if(temp->right != NULL)
        {
            noRecTree.push(temp->right);
        }
    }
}


// Driver program to test above functions
int main()
{
    /* Constructed binary tree is
        100
      /     \
      9      10
     /  \    /
     9   4  7
     */
    struct TreeNode *root = newTreeNode(100);
    root->left        = newTreeNode(9);
    root->right       = newTreeNode(10);
    root->left->left  = newTreeNode(9);
    root->left->right = newTreeNode(4);
    root->right->left = newTreeNode(7);
    
    cout << "Inorder traversal result:" << endl;
    noRecInorder(root);
    cout << "Level traversal result:" << endl;
    levelOrder(root);
    
    return 0;
}
