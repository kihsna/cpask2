#include <stdio.h>
#include <stdlib.h>

// Structure for tree node
struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}

// Inorder traversal
void inOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    inOrderTraversal(root->left);    
    printf("%d ", root->key);        
    inOrderTraversal(root->right);   
}

// Preorder traversal
void preOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->key);        
    preOrderTraversal(root->left);   
    preOrderTraversal(root->right);  
}

// Postorder traversal
void postOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    postOrderTraversal(root->left);  
    postOrderTraversal(root->right); 
    printf("%d ", root->key);        
}

// Queue node for level order traversal
struct QNode {
    struct Node *tNode;
    struct QNode *next;
};

struct QNode *front = NULL;
struct QNode *rear = NULL;

struct QNode* newQNode(struct Node* tNode) {
    struct QNode* qNode = (struct QNode*)malloc(sizeof(struct QNode));
    qNode->tNode = tNode;
    qNode->next = NULL;
    return qNode;
}

// Enqueue for level order traversal
void enqueue(struct Node *tNode) {
    struct QNode* qNode = newQNode(tNode);
    if (rear == NULL) {
        front = rear = qNode;
    } else {
        rear->next = qNode;
        rear = qNode;
    }
}

// Dequeue for level order traversal
struct Node* dequeue() {
    if (front == NULL) return NULL;
    struct Node* tNode = front->tNode;
    struct QNode* temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
    return tNode;
}

// Level Order Traversal
void levelOrderTraversal(struct Node* root) {
    if (root == NULL) return; 
    enqueue(root);
    while (front != NULL) {
        struct Node* curr = dequeue();
        printf("%d ", curr->key);
        if (curr->left != NULL) enqueue(curr->left);
        if (curr->right != NULL) enqueue(curr->right);
    }
}

// Insert a new node in BST
struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key); 
    if (node->key == key) return node;     
    if (node->key < key)
        node->right = insert(node->right, key);  
    else
        node->left = insert(node->left, key);    
    return node;
}

// Search for a node in BST
struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (root->key < key)
        return search(root->right, key);   
    return search(root->left, key);        
}

// Get inorder successor
struct Node* getSuccessor(struct Node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}

// Delete a node in BST
struct Node* delNode(struct Node* root, int x) {
    if (root == NULL) return root;  
    if (root->key > x)
        root->left = delNode(root->left, x);    
    else if (root->key < x)
        root->right = delNode(root->right, x);  
    else {
        if (root->left == NULL) {
            struct Node* temp = root->right;
            free(root);
            return temp;
        }
        if (root->right == NULL) {
            struct Node* temp = root->left;
            free(root);
            return temp;
        }
        
        struct Node* succ = getSuccessor(root);
        root->key = succ->key;
        root->right = delNode(root->right, succ->key); 
    }
    return root;
}

// Depth First Search (Preorder)
void depthFirstSearch(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->key);  
    depthFirstSearch(root->left);   
    depthFirstSearch(root->right);  
}

// Calculate the height of the BST
int height(struct Node* node) {
    if (node == NULL) return -1;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Find LCA (Lowest Common Ancestor)
struct Node* findLCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;
    if (root->key > n1 && root->key > n2)
        return findLCA(root->left, n1, n2);
    if (root->key < n1 && root->key < n2)
        return findLCA(root->right, n1, n2);
    return root;
}

// Find distance from root to a node
int findDistance(struct Node* root, int a) {
    int distance = 0;
    while (root != NULL) {
        if (a < root->key) {
            root = root->left;
        } else if (a > root->key) {
            root = root->right;
        } else {
            return distance;
        }
        distance++;
    }
    return -1; 
}

// Calculate distance between two nodes
int distanceBetweenNodes(struct Node* root, int n1, int n2) {
    struct Node* lca = findLCA(root, n1, n2);
    int d1 = findDistance(lca, n1);
    int d2 = findDistance(lca, n2);
    return d1 + d2;
}

// Build tree from user input
struct Node* buildTree() {
    int n, key;
    struct Node* root = NULL;
    
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &key);
        root = insert(root, key);
    }
    
    return root;
}

// Main function
int main() {
    struct Node* root = buildTree();

    printf("Inorder Traversal: ");
    inOrderTraversal(root);
    printf("\n");

    printf("Preorder Traversal: ");
    preOrderTraversal(root);
    printf("\n");

    printf("Postorder Traversal: ");
    postOrderTraversal(root);
    printf("\n");

    printf("Level Order Traversal: ");
    levelOrderTraversal(root);
    printf("\n");

    printf("Tree Height: %d\n", height(root));

    int key;
    printf("Enter a value to search: ");
    scanf("%d", &key);
    struct Node* searchResult = search(root, key);
    if (searchResult != NULL) {
        printf("Node %d found in the tree.\n", key);
    } else {
        printf("Node %d not found in the tree.\n", key);
    }

    printf("Enter a value to delete: ");
    scanf("%d", &key);
    root = delNode(root, key);
    printf("Tree after deletion (Inorder Traversal): ");
    inOrderTraversal(root);
    printf("\n");

    int n1, n2;
    printf("Enter two values to find their LCA: ");
    scanf("%d %d", &n1, &n2);
    struct Node* lca = findLCA(root, n1, n2);
    if (lca != NULL) {
        printf("Lowest Common Ancestor of %d and %d: %d\n", n1, n2, lca->key);
    } else {
        printf("No common ancestor found.\n");
    }

    printf("Enter two values to find the distance between them: ");
    scanf("%d %d", &n1, &n2);
    int distance = distanceBetweenNodes(root, n1, n2);
    printf("Distance between %d and %d: %d\n", n1, n2, distance);

    return 0;
}
