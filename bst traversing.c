
#include <bits/stdc++.h>
using namespace std;
 
/* A binary tree node has data, pointer to left child
and a pointer to right child */
class node {
public:
    int data;
    node* left;
    node* right;
};
 
// A utility function to create a node
node* newNode(int data)
{
    node* temp = new node();
 
    temp->data = data;
    temp->left = temp->right = NULL;
 
    return temp;
}
 
// A recursive function to construct Full from pre[].
// preIndex is used to keep track of index in pre[].
node* constructTreeUtil(int pre[], int* preIndex, int low,
                        int high, int size)
{
    // Base case
    if (*preIndex >= size || low > high)
        return NULL;
 
    // The first node in preorder traversal is root. So take
    // the node at preIndex from pre[] and make it root, and
    // increment preIndex
    node* root = newNode(pre[*preIndex]);
    *preIndex = *preIndex + 1;
 
    // If the current subarry has only one element, no need
    // to recur
    if (low == high)
        return root;
 
    // Search for the first element greater than root
    int i;
    for (i = low; i <= high; ++i)
        if (pre[i] > root->data)
            break;
 
    // Use the index of element found in preorder to divide
    // preorder array in two parts. Left subtree and right
    // subtree
    root->left = constructTreeUtil(pre, preIndex, *preIndex,
                                   i - 1, size);
    root->right
        = constructTreeUtil(pre, preIndex, i, high, size);
 
    return root;
}
 
// The main function to construct BST from given preorder
// traversal. This function mainly uses constructTreeUtil()
node* constructTree(int pre[], int size)
{
    int preIndex = 0;
    return constructTreeUtil(pre, &preIndex, 0, size - 1,
                             size);
}
 
// A utility function to print inorder traversal of a Binary
// Tree
void printInorder(node* node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}
 
// Driver code
int main()
{
    int pre[] = { 10, 5, 1, 7, 40, 50 };
    int size = sizeof(pre) / sizeof(pre[0]);
 
    node* root = constructTree(pre, size);
 
    cout << "Inorder traversal of the constructed tree: \n";
    printInorder(root);
 
    return 0;
}
 
// This code is contributed by rathbhupendra
Output
Inorder traversal of the constructed tree: 
1 5 7 10 40 50 
Time Complexity: O(n2)

Method 2 ( O(n) time complexity ) 
The idea used here is inspired by method 3 of this post. The trick is to set a range {min .. max} for every node. Initialize the range as {INT_MIN .. INT_MAX}. The first node will definitely be in range, so create a root node. To construct the left subtree, set the range as {INT_MIN …root->data}. If a value is in the range {INT_MIN .. root->data}, the values are part of the left subtree. To construct the right subtree, set the range as {root->data..max .. INT_MAX}. 

Below is the implementation of the above idea:


/* A O(n) program for construction
of BST from preorder traversal */
#include <bits/stdc++.h>
using namespace std;
 
/* A binary tree node has data, pointer to left child
and a pointer to right child */
class node {
public:
    int data;
    node* left;
    node* right;
};
 
// A utility function to create a node
node* newNode(int data)
{
    node* temp = new node();
 
    temp->data = data;
    temp->left = temp->right = NULL;
 
    return temp;
}
 
// A recursive function to construct
// BST from pre[]. preIndex is used
// to keep track of index in pre[].
node* constructTreeUtil(int pre[], int* preIndex, int key,
                        int min, int max, int size)
{
    // Base case
    if (*preIndex >= size)
        return NULL;
 
    node* root = NULL;
 
    // If current element of pre[] is in range, then
    // only it is part of current subtree
    if (key > min && key < max) {
        // Allocate memory for root of this
        // subtree and increment *preIndex
        root = newNode(key);
        *preIndex = *preIndex + 1;
 
        if (*preIndex < size) {
            // Construct the subtree under root
            // All nodes which are in range
            // {min .. key} will go in left
            // subtree, and first such node
            // will be root of left subtree.
            root->left = constructTreeUtil(pre, preIndex,
                                           pre[*preIndex],
                                           min, key, size);
        }
        if (*preIndex < size) {
            // All nodes which are in range
            // {key..max} will go in right
            // subtree, and first such node
            // will be root of right subtree.
            root->right = constructTreeUtil(pre, preIndex,
                                            pre[*preIndex],
                                            key, max, size);
        }
    }
 
    return root;
}
 
// The main function to construct BST
// from given preorder traversal.
// This function mainly uses constructTreeUtil()
node* constructTree(int pre[], int size)
{
    int preIndex = 0;
    return constructTreeUtil(pre, &preIndex, pre[0],
                             INT_MIN, INT_MAX, size);
}
 
// A utility function to print inorder
// traversal of a Binary Tree
void printInorder(node* node)
{
    if (node == NULL)
        return;
    printInorder(node->left);
    cout << node->data << " ";
    printInorder(node->right);
}
 
// Driver code
int main()
{
    int pre[] = { 10, 5, 1, 7, 40, 50 };
    int size = sizeof(pre) / sizeof(pre[0]);
 
    // Function call
    node* root = constructTree(pre, size);
 
    cout << "Inorder traversal of the constructed tree: \n";
    printInorder(root);
 
    return 0;
}
 
// This is code is contributed by rathbhupendra
Output
Inorder traversal of the constructed tree: 
1 5 7 10 40 50 
Time Complexity: O(n)

We will soon publish a O(n) iterative solution as a separate post.
Please write comments if you find anything incorrect, or you want to share more information about the topic discussed above.

Method 3 ( O(n2) time complexity ):  

Simply do that just by using the recursion concept and iterating through the array of the given elements like below.


/*Construct a BST from given pre-order traversal
for example if the given traversal is {10, 5, 1, 7, 40, 50},
then the output should be the root of the following tree.
     10
   /   \
  5     40
 /  \      \
1    7      50 */
 
class Node {
    int data;
    Node left, right;
    Node(int data)
    {
        this.data = data;
        this.left = this.right = null;
    }
}
 
class CreateBSTFromPreorder {
    private static Node node;
 
    // This will create the BST
    public static Node createNode(Node node, int data)
    {
        if (node == null)
            node = new Node(data);
 
        if (node.data > data)
            node.left = createNode(node.left, data);
        if (node.data < data)
            node.right = createNode(node.right, data);
 
        return node;
    }
 
    // A wrapper function of createNode
    public static void create(int data)
    {
        node = createNode(node, data);
    }
    // A function to print BST in inorder
    public static void inorderRec(Node root)
    {
        if (root != null) {
            inorderRec(root.left);
            System.out.println(root.data);
            inorderRec(root.right);
        }
    }
 
    // Driver Code
    public static void main(String[] args)
    {
        int[] nodeData = { 10, 5, 1, 7, 40, 50 };
 
        for (int i = 0; i < nodeData.length; i++) {
            create(nodeData[i]);
        }
        inorderRec(node);
    }
}