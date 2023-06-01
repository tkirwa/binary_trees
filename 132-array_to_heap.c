#include "binary_trees.h"

/**
 * array_to_heap - builds a Max Binary Heap tree from an array
 * @array: pointer to the first element of the array
 * @size: number of elements in the array
 *
 * Return: pointer to the root node...
 * of the created Binary Heap, or NULL on failure
 */
heap_t *array_to_heap(int *array, size_t size)
{
heap_t *root = NULL;
size_t i;

if (array == NULL || size == 0)
return (NULL);

for (i = 0; i < size; i++)
{
heap_t *new_node = binary_tree_node(NULL, array[i]);

if (new_node == NULL)
{
binary_tree_delete(root);
return (NULL);
}

if (root == NULL)
root = new_node;
else
heap_insert(&root, array[i]);
}

return (root);
}

/**
 * binary_tree_delete - deletes an entire binary tree
 * @tree: pointer to the root node of the tree to delete
 */
void binary_tree_delete(heap_t *tree)
{
if (tree == NULL)
return;

binary_tree_delete(tree->left);
binary_tree_delete(tree->right);
free(tree);
}
