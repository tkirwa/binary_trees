#include "binary_trees.h"
#include <stdlib.h>
#include <stdio.h>

/**
 * tree_size - Computes the size of a binary tree
 * @tree: Pointer to the root node of the tree
 * Return: Size of the tree
 */
size_t tree_size(const binary_tree_t *tree)
{
if (tree == NULL)
return (0);
return (1 + tree_size(tree->left) + tree_size(tree->right));
}

/**
 * get_last_node - Gets the last node in level-order traversal
 * @root: Pointer to the root node of the heap
 * Return: Pointer to the last node
 */
heap_t *get_last_node(heap_t *root)
{
heap_t *queue[1000];
heap_t *node;
size_t rear = 0, front = 0;

if (root == NULL)
return (NULL);

queue[rear++] = root;
while (front < rear)
{
node = queue[front++];
if (node->left)
queue[rear++] = node->left;
if (node->right)
queue[rear++] = node->right;
}

return (node);
}

/**
* heapify_down - Restores the heap property by moving down the tree
* @node: Pointer to the current node
*/
void heapify_down(heap_t *node)
{
heap_t *largest = node;
heap_t *left = node->left;
heap_t *right = node->right;

if (left != NULL && left->n > largest->n)
largest = left;
if (right != NULL && right->n > largest->n)
largest = right;

if (largest != node)
{
int temp = node->n;
node->n = largest->n;
largest->n = temp;
heapify_down(largest);
}
}

/**
* heap_extract - Extracts the root node of a Max Binary Heap
* @root: Double pointer to the root node of the heap
* Return: Value stored in the root node, or 0 on failure
*/
int heap_extract(heap_t **root)
{
if (root == NULL || *root == NULL)
return (0);

int extracted_value = (*root)->n;

size_t size = tree_size(*root);
heap_t *last_node = get_last_node(*root);

if (size == 1)
{
free(*root);
*root = NULL;
return (extracted_value);
}

(*root)->n = last_node->n;

if (last_node->parent->left == last_node)
last_node->parent->left = NULL;
else
last_node->parent->right = NULL;

free(last_node);

heapify_down(*root);

return (extracted_value);
}
