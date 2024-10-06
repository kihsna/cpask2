#include <stdio.h>
#include <stdlib.h>


struct Node {
    int key;
    struct Node* left;
    struct Node* right;
};


struct Node* newNode(int key) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->key = key;
    node->left = node->right = NULL;
    return node;
}


void inOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    inOrderTraversal(root->left);    
    printf("%d ", root->key);        
    inOrderTraversal(root->right);   
}


void preOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->key);        
    preOrderTraversal(root->left);   
    preOrderTraversal(root->right);  
}


void postOrderTraversal(struct Node* root) {
    if (root == NULL) return;
    postOrderTraversal(root->left);  
    postOrderTraversal(root->right); 
    printf("%d ", root->key);        
}


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


void enqueue(struct Node *tNode) {
    struct QNode* qNode = newQNode(tNode);
    if (rear == NULL) {
        front = rear = qNode;
    } else {
        rear->next = qNode;
        rear = qNode;
    }
}


struct Node* dequeue() {
    if (front == NULL) return NULL;
    struct Node* tNode = front->tNode;
    struct QNode* temp = front;
    front = front->next;
    if (front == NULL) rear = NULL;
    free(temp);
    return tNode;
}


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


struct Node* insert(struct Node* node, int key) {
    if (node == NULL) return newNode(key); 
    if (node->key == key) return node;     
    if (node->key < key)
        node->right = insert(node->right, key);  
    else
        node->left = insert(node->left, key);    
    return node;
}


struct Node* search(struct Node* root, int key) {
    if (root == NULL || root->key == key) return root;
    if (root->key < key)
        return search(root->right, key);   
    return search(root->left, key);        
}


struct Node* getSuccessor(struct Node* curr) {
    curr = curr->right;
    while (curr != NULL && curr->left != NULL)
        curr = curr->left;
    return curr;
}


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


void depthFirstSearch(struct Node* root) {
    if (root == NULL) return;
    printf("%d ", root->key);  
    depthFirstSearch(root->left);   
    depthFirstSearch(root->right);  
}


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

    printf("Depth First Search (DFS): ");
    depthFirstSearch(root);
    printf("\n");

    
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

    return 0;
}
