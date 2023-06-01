#include "binary_trees.h"

/**
 * binary_tree_height - Measure the height of a binary tree
 * @tree: Pointer to the root node of the tree
 *
 * Return: The height of the tree, or 0 if tree is NULL
 */
size_t binary_tree_height(const binary_tree_t *tree)
{
size_t left_height, right_height;

if (tree == NULL)
return (0);

left_height = binary_tree_height(tree->left);
right_height = binary_tree_height(tree->right);

return (1 + (left_height > right_height ? left_height : right_height));
}

/**
 * heapify - Restore the Max Heap property by swapping nodes
 * @node: Pointer to the node to start heapifying
 *
 * Return: The final position of the node in the Max Heap
 */
heap_t *heapify(heap_t *node)
{
heap_t *temp;
int value;

while (node->parent != NULL && node->n > node->parent->n)
{
value = node->n;
node->n = node->parent->n;
node->parent->n = value;
temp = node;
node = node->parent;
node->parent = temp;
}

return (node);
}

/**
 * heap_insert - Insert a value in a Max Binary Heap
 * @root: Double pointer to the root node of the Heap
 * @value: Value to store in the node to be inserted
 *
 * Return: Pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
heap_t *new_node, *current;

if (root == NULL)
return (NULL);

new_node = binary_tree_node(NULL, value);
if (new_node == NULL)
return (NULL);

if (*root == NULL)
{
*root = new_node;
return (new_node);
}

current = *root;
while (current->left != NULL && current->right != NULL)
{
if (binary_tree_height(current->left) <= binary_tree_height(current->right))
current = current->left;
else
current = current->right;
}

if (current->left == NULL)
{
current->left = new_node;
new_node->parent = current;
}
else
{
current->right = new_node;
new_node->parent = current;
}

return (heapify(new_node));
}
