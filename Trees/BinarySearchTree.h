/*
BST HEADER FILE 
@author : jellybee @https://github.com/JellyAB
*/

//PREREQUISITES FOR INCLUDING HEADER
//#include<stdio.h>
//#include<stdlib.h>

//->Declaring a b-tree
//    Tree *tree_name_here=NULL; <-Including the NULL is important!
//    Now there's a pointer to a tree without actual data.

//->Guide to user about the functions available to use :

//    -insertNode(tree_name, data_to_insert)
//        If there's no tree available, then it creates a tree
//		  If there's a tree available, it adds nodes as per Binary Search Tree theorem
//		  Data to insert is the data of the node to be inserted

//    -deleteNode(tree_name, data_to_delete)
//        Deletes a node from the tree
//		  Data to delete is the data of the node in concern

//    -searchElement(tree_name, data_to_search);
//        Searches for a data in the tree and 
//		  Writes whether it is available or not in the tree

//    -searchElementAlgo(tree_name, data_to_search)                      
//        Searches for a data in the tree and
//		  Returns the address of the node if it's available. NULL if it's not available

//    -printInorder(tree_name)
//		  Writes the data of nodes in the tree as per in-order traversal ,which is a Depth-first traversal

//    -printPostorder(tree_name)
//		  Writes the data of nodes in the tree as per post-order traversal ,which is a Depth-first traversal

//    -printPreorder(tree_name)
//		  Writes the data of nodes in the tree as per pre-order traversal ,which is a Depth-first traversal

//    -printLevelorder(tree_name)
//		  Writes the data of nodes in the tree as per Level-order traversal ,which is a Breadth-first traversal

//	  -sizeTree(tree_name)
//		  Returns the size of the tree. In other terms, the total number of nodes in the entire tree

//	  -heightTree(tree_name)
//		  Returns the height of the entire tree. In other terms, the maximum number of nodes from root to leaf

//	  -depthNode(tree_name, data_to_find_depth_of)
//		  Returns the depth of the node. In other terms, the number of nodes passed to reach the node concerned, from root
//		  depth of root is zero

//	  -heightNode(tree_name, data_to_find_height_of)
//		  Returns the height of the node. In other terms, the mumber of nodes passed to reach the node concerned, from leaf
//		  height of leaf is zero

//	  -levelNode(tree_name, data_to_find_level_of)
//		  Returns in which level the node is in the tree
//		  level of root is zero

//    -deleteTree(tree_name)
//        Wipes out the whole tree from memory



//Structure definitions for Tree and Queue
typedef struct Tree{
	int data;
	struct Tree *left, *right;
}Tree;

typedef struct Queue{		//Needed for BFS
    int front, rear, size;
    unsigned max;
    Tree* array[100];	// the Queue stores the addresses of nodes of the tree
}Queue;


/*
CREATES A TREE || INSERT NODES TO A TREE
*/
Tree* insertNode(Tree* root,int val){
	
	if(root==NULL){		//Creates a root for a new B-tree
		root = (Tree*)malloc(sizeof(Tree));		//Allocates memory for the B-tree
		root->data = val;
		root->left = root->right = NULL;
		return root;
	}else{				//Puts value into position (BST)
		if(val<root->data){
			root->left = insertNode(root->left, val);
		}else if(val>root->data){
			root->right = insertNode(root->right, val);			
		}				//if value already exists in the tree, it doesn't count (No redundancies)
		return root;
		
		/*NB.
		If you wish to keep redundancies>>>
		Copy the following code and paste above
		
		else{
		root->right = createTree(root->right, val);
		}
		
		so that if val==root it connects to right sub tree as well.
		*/
	}
}


/*
LOCATES A GIVEN NODE - returns the address
*/
Tree* searchElementAlgo(Tree* root, int element){
	Tree* temp = root;
	if(temp==NULL){
		return NULL;
	}
	if(temp->data==element){
		return temp;
	}else if(element < temp->data){
		return searchElementAlgo(temp->left,element);
	}else{
		return searchElementAlgo(temp->right, element);
	}
}


/*
PRINTS WHETHER A GIVEN NODE EXISTS IN THE TREE
*/
void searchElement(Tree* root, int element){
	if(searchElementAlgo(root,element)){
		printf("%d is a node in the B-Tree\n",element);
	}else{
		printf("%d is not a node in the B-Tree\n",element);
	}
}

Tree* minNode(Tree* root){	//used in the deleteNode(,) func.
	
	Tree* min = root;
	while(min->left!=NULL){	//This finds the leftmost leaf in the tree
		min=min->left;
	}
	return min;
}


/*
DELETES A GIVEN SINGLE NODE FROM THE TREE
*/
Tree* deleteNode(Tree* root, int element){
	if(searchElementAlgo(root,element)){
		if(root==NULL){
			return NULL;
		}
		//Traverse to the required element
		if(element < root->data){	
			root->left = deleteNode(root->left, element); 
		}else if(element > root->data){
			root->right = deleteNode(root->right, element);
		}else{	// so the Node to be deleted is Found!
		/*
			And now for the fiddly part:
		Three possibilities arise when deleting a node...
				1- Node has no children (Node is a leaf)
				2- Node has only one child
				3- Node has two children >>>>>pain in the *neck*
		*/
		
		//1---Node has no children
			if(root->left==NULL && root->right==NULL){	
				free(root);
				return NULL;
			}
		//2---Node has only one child
			if(root->left==NULL){						
				Tree *temp = root->right;
				free(root);
				return temp;
			}else if(root->right==NULL){
				Tree *temp = root->left;
				free(root);
				return temp;
		}
		//3---Node has two children
			else{										
			/*We need to find the smallest element of the right sub tree.
			Because that element is the best candidate to fill the void 
			left by the element to be deleted.
			*/
				Tree *temp = minNode(root->right);		//Finds the minimum value  in the right sub tree
				root->data = temp->data;				//copies the min value to the root
			/*Note that still the min value exists in the tree
			we need to delete it in the same manner. 
			Although this element only has two deleting possibilities: 
					-1 Has no children OR
					-2 Has only one child.
			*/
				root->right = deleteNode(root->right,temp->data);	
			}
		}
	return root;

	}else{
		printf("ERROR : Unable to delete node. Node with requested data not found.\n");			///////DOESN'T WORK!!! BECAUSE IT'S RECURSIVE.
	}
	
	
}
	

	


/*
DEPTH FIRST TRAVERSAL (DFT)
*/
void printPreorder(Tree* node) { 	//Pre-order Traversal
     if (node == NULL) 
          return; 
  
     printf("%d ", node->data);   
     printPreorder(node->left);   
     printPreorder(node->right); 
}  

void printInorder(Tree* node) { 	//In-order Traversal
     if (node == NULL) 
          return; 
          
     printInorder(node->left); 
     printf("%d ", node->data);   
     printInorder(node->right); 
} 

void printPostorder(Tree* node) { 	//Post-order Traversal
     if (node == NULL) 
        return; 
   
     printPostorder(node->left); 
     printPostorder(node->right); 
     printf("%d ", node->data); 
} 

////*************************ALL QUEUE FUNCTIONS*************************/////
Queue* createQ(){
    Queue* q = (Queue*) malloc(sizeof(Queue));	//Allocates memory for the queue
    q->max = 100;
    q->front = q->size = 0; 
    q->rear = q->max - 1;
    return q;
}

int isEmpty(Queue* q){  
    return (q->size == 0); 
}

int isFull(Queue* q){  
    return (q->size == q->max);  
}

void enqueue(Queue* q, Tree* item){		//NB.***the data enqueued is AN ADDRESS of a node of the tree
    if (isFull(q))
        return;
    q->rear = (q->rear + 1)%q->max;
    q->array[q->rear] = item;
    q->size = q->size + 1;
 }
 
 Tree* dequeue(Queue* q){		//NB.***returns AN ADDRESS of a node of the treee
	if (isEmpty(q))
        return NULL;			//Not 0 or int_min because this is an address, therefore it should be NULL
    Tree* item = q->array[q->front];
    q->front = (q->front + 1)%q->max;
    q->size = q->size - 1;
    return item;
 }

/*
BREADTH FIRST TRAVERSAL (BFT)
*/
void printLevelorder(Tree* root){		//Level-order Traversal
	
    if(root==NULL) return;
    else
    {
        Queue* q = createQ();		//Creates a queue
		enqueue(q,root);			//Enqueue the root element
		while(!isEmpty(q)){			//Process until the queue is empty
			root = dequeue(q);		//Dequeues and prints the root
			printf("%d ", root->data);
			if(root->left!=NULL){	//if there is a left node put it to the queue,similarly to the right...
				enqueue(q,root->left);
			}if(root->right!=NULL){		// not 'else if' because there can be right node and left node as well
				enqueue(q,root->right);
			}
		}
    }
}


/*
FINDS THE SIZE OF THE TREE - total number of nodes
*/
int sizeTree(Tree* root){
	if(root==NULL){
		return 0;
	}
	else{
		return 1 + sizeTree(root->left) + sizeTree(root->right);
	}
	
}

/*
FINDS THE HEIGHT OF THE ENTIRE TREE
*/
int heightTree(Tree* root){
	int hL=0, hR=0;
	if(root==NULL){
		return 0;
	}
	else{
		if(root->left!=NULL){
			hL = 1 + heightTree(root->left);
		}
		if(root->right!=NULL){
			hR = 1 + heightTree(root->right);
		}
	}
	return (hL > hR ? hL : hR);
}


/*
FINDS THE HEIGHT OF A GIVEN NODE
*/
int heightNode(Tree* root, int node){
	Tree* temp = searchElementAlgo(root, node);
	if(temp==NULL){
		printf("ERROR : Unable to find the height of the node. Node with requested data not found.\n");
	}else{
		return heightTree(temp);
	}
}


/*
FINDS THE DEPTH OF A GIVEN NODE
*/
int depthNode(Tree* root,int node){		//Same code as the level of a node, but two concepts.
	int depth=0;
	if(root->data==node){
		return 0;
	}
	else{
		if(node < root->data){
			depth = 1 + depthNode(root->left,node);
		}
		else if(node > root->data){
			depth = 1 + depthNode(root->right,node);
		}else{
			printf("ERROR : Unable to find the depth of the node. Node with requested data not found\n");
		}
	}
	return depth;
}

/*
FINDS THE LEVEL OF A GIVEN NODE
*/
int levelNode(Tree* root, int node){	//Same code as the depth of a node, but two concepts.
	int level = 0;
	
	if(root->data==node){
		return 0;
	}else{
		if(node < root->data){
			level = 1 + levelNode(root->left,node);
		}else if(node > root->data){
			level = 1 + levelNode(root->right,node);
		}else{
			printf("ERROR : Unable to find the level of the node. Node with requested data not found\n");
		}
	}
	return level;
}

/*
DELETES THE ENTIRE TREE AND FREES ALLOCATED MEMORY
---used post-order traversal here. it frees up nodes, leaf to root.
*/
void deleteTree(Tree* root){
	
    if (root!=NULL){           
    	deleteTree(root->left); 
    	deleteTree(root->right); 
    	free(root); 	
	}else{	//Already Empty tree
        printf("Error: No tree available in memory.\n");
    }
}


