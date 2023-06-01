#include "binary_trees.h"

/**
 * binary_tree_size - Measures the size of a binary tree
 * @tree: Pointer to the root node of the tree to measure
 *
 * Return: Size of the tree
 */
size_t binary_tree_size(const binary_tree_t *tree)
{
if (tree == NULL)
return (0);

return (1 + binary_tree_size(tree->left) + binary_tree_size(tree->right));
}

/**
 * sift_up - Moves a node up in the heap to restore the max heap property
 * @node: Pointer to the node to sift up
 */
void sift_up(heap_t **node)
{
heap_t *current = *node;
int temp;

while (current->parent != NULL && current->n > current->parent->n)
{
temp = current->n;
current->n = current->parent->n;
current->parent->n = temp;
current = current->parent;
}
}

/**
 * heap_insert - Inserts a value in a max binary heap
 * @root: Double pointer to the root node of the heap
 * @value: Value to insert
 *
 * Return: Pointer to the created node, or NULL on failure
 */
heap_t *heap_insert(heap_t **root, int value)
{
heap_t *new_node, *current;
size_t size, index;

if (root == NULL)
return (NULL);

size = binary_tree_size(*root);
index = size + 1;
current = *root;

while (index > 1)
{
if (index % 2 == 0)
{
current = current->left;
}
else
{
current = current->right;
}
index /= 2;
}

new_node = binary_tree_node(current, value);
if (new_node == NULL)
return (NULL);

if (current == NULL)
*root = new_node;
else if (current->left == NULL)
current->left = new_node;
else
current->right = new_node;

sift_up(&new_node);

return (new_node);
}

