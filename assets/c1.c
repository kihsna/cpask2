#include <stdio.h>
#include <stdlib.h>



// Structure for tree node
struct Node {
    int data;
    struct Node* left;
    struct Node* right;
};

// Create a new node
struct Node* newNode(int data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Insert a new node in BST
struct Node* insert(struct Node* node, int data) {
    if (node == NULL) return newNode(data);
    if (node->data == data) return node;
    if (node->data < data)
        node->right = insert(node->right, data);
    else
        node->left = insert(node->left, data);
    return node;
}

// Build tree from user input
struct Node* buildTree() {
    int n, data;
    struct Node* root = NULL;
    
    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    printf("Enter the node values:\n");
    for (int i = 0; i < n; i++) {
        scanf("%d", &data);
        root = insert(root, data);
    }
    
    return root;
}






// Inorder traversal
void inOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    inOrderTraversal(root->left);
    printf("%d ", root->data);
    inOrderTraversal(root->right);
}

// Preorder traversal
void preOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
}

// Postorder traversal
void postOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    printf("%d ", root->data);
}






// Search for a node in BST
struct Node* search(struct Node* root, int data) {
    if (root == NULL || root->data == data) return root;
    if (root->data < data)
        return search(root->right, data);
    return search(root->left, data);
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
    if (root->data > x)
        root->left = delNode(root->left, x);
    else if (root->data < x)
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
        root->data = succ->data;
        root->right = delNode(root->right, succ->data);
    }
    return root;
}

// Depth First Search (Preorder)
void depthFirstSearch(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->data);
    depthFirstSearch(root->left);
    depthFirstSearch(root->right);
}


////SIMPLE LEVEL ORDER


// Calculate the height of the tree
int height(struct Node* node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Print nodes at a given level
void printLevel(struct Node* root, int level) {
    if (root == NULL) return;
    if (level == 1) {
        printf("%d ", root->data);
    } else if (level > 1) {
        printLevel(root->left, level - 1);
        printLevel(root->right, level - 1);
    }
}

// Simplified Level Order Traversal using recursion
void levelOrder(struct Node* root) {
    int h = height(root);
    for (int i = 1; i <= h; i++) {
        printLevel(root, i);
    }
}


///// LEVEL  ORDER  USING  QNODE


// Queue node for level order traversal (alternative implementation)
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

// Alternative Level Order Traversal using Queue
void levelOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    enqueue(root);
    while (front != NULL) {
        struct Node* curr = dequeue();
        printf("%d ", curr->data);
        if (curr->left != NULL) enqueue(curr->left);
        if (curr->right != NULL) enqueue(curr->right);
    }
}





//// DISTANCE BETWEEN  NODES


// Find LCA (Lowest Common Ancestor)
struct Node* findLCA(struct Node* root, int n1, int n2) {
    if (root == NULL) return NULL;
    if (root->data > n1 && root->data > n2)
        return findLCA(root->left, n1, n2);
    if (root->data < n1 && root->data < n2)
        return findLCA(root->right, n1, n2);
    return root;
}

// Find distance from root to a node
int findDistance(struct Node* root, int a) {
    int distance = 0;
    while (root != NULL) {
        if (a < root->data) {
            root = root->left;
        } else if (a > root->data) {
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

    printf("Level Order Traversal (Recursive): ");
    levelOrder(root);
    printf("\n");

    // Uncomment this line if you want to use the queue-based level order traversal instead
    // printf("Level Order Traversal (Queue-based): ");
    // levelOrderTraversal(root);
    // printf("\n");

    printf("Tree Height: %d\n", height(root));

    int data;
    printf("Enter a value to search: ");
    scanf("%d", &data);
    struct Node* searchResult = search(root, data);
    if (searchResult != NULL) {
        printf("Node %d found in the tree.\n", data);
    } else {
        printf("Node %d not found in the tree.\n", data);
    }

    printf("Enter a value to delete: ");
    scanf("%d", &data);
    root = delNode(root, data);
    printf("Tree after deletion (Inorder Traversal): ");
    inOrderTraversal(root);
    printf("\n");

    int n1, n2;
    printf("Enter two values to find their LCA: ");
    scanf("%d %d", &n1, &n2);
    struct Node* lca = findLCA(root, n1, n2);
    if (lca != NULL) {
        printf("Lowest Common Ancestor of %d and %d: %d\n", n1, n2, lca->data);
    } else {
        printf("No common ancestor found.\n");
    }

    printf("Enter two values to find the distance between them: ");
    scanf("%d %d", &n1, &n2);
    int distance = distanceBetweenNodes(root, n1, n2);
    printf("Distance between %d and %d: %d\n", n1, n2, distance);

    return 0;
}
