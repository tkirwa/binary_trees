#include "binary_trees.h"
#include <stdlib.h>
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
heap_t *last_node = NULL;
heap_t *temp = *root;
if (size == 1)
*root = NULL;
free(temp);
return (extracted_value);
while (temp->left != NULL || temp->right != NULL)
{
if (temp->right == NULL)
last_node = temp->left;
break;
if (temp->left->n >= temp->right->n)
temp = temp->left;
else
temp = temp->right;
}
if (last_node == NULL)
{
last_node = temp;
temp = temp->parent;
if (temp->left == last_node)
temp->left = NULL;
else
temp->right = NULL;
}
else
{
if (temp->left == last_node)
temp->left = NULL;
else
temp->right = NULL;
}
(*root)->n = last_node->n;
free(last_node);
heapify_down(*root);
return (extracted_value);
}
