#include "binary_trees.h"

/**
 * height - Measures the height of a tree
 *
 * @tree: Tree root
 * Return: Height
 */
int height(const binary_tree_t *tree)
{
int left = 0;
int right = 0;

if (tree == NULL)
return (-1);

left = height(tree->left);
right = height(tree->right);

if (left > right)
return (left + 1);

return (right + 1);
}

/**
 * binary_tree_is_perfect - Checks if a binary tree is perfect
 *
 * @tree: Tree root
 * Return: 1 if the tree is perfect, 0 otherwise
 */
int binary_tree_is_perfect(const binary_tree_t *tree)
{
if (tree && height(tree->left) == height(tree->right))
{
if (height(tree->left) == -1)
return (1);
if ((tree->left && !tree->left->left && !tree->left->right)
&&(tree->right && !tree->right->left && !tree->right->right))
return (1);
if (tree && tree->left && tree->right)
return (binary_tree_is_perfect(tree->left)
&& binary_tree_is_perfect(tree->right));
}

return (0);
}

/**
* swap - Swaps nodes when the child is greater than the parent
*
* @arg_node: Parent node
* @arg_child: Child node
* Return: No return
*/
void swap(heap_t **arg_node, heap_t **arg_child)
{
heap_t *node, *child, *node_child, *node_left, *node_right, *parent;
int left_right;

node = *arg_node;
child = *arg_child;

if (child->n > node->n)
{
if (child->left)
child->left->parent = node;
if (child->right)
child->right->parent = node;

if (node->left == child)
node_child = node->right, left_right = 0;
else
node_child = node->left, left_right = 1;

node_left = child->left, node_right = child->right;

if (left_right == 0)
{
child->right = node_child;
if (node_child)
node_child->parent = child;
child->left = node;
}
else
{
child->left = node_child;
if (node_child)
node_child->parent = child;
child->right = node;
}

if (node->parent)
{
if (node->parent->left == node)
node->parent->left = child;
else
node->parent->right = child;
}

parent = node->parent;
child->parent = parent;
node->parent = child;
node->left = node_left;
node->right = node_right;

*arg_node = child;
}
}

/**
* heap_insert - Inserts a value in a Max Binary Heap
* @root: Double pointer to the root node of the heap
* @value: Value to be inserted
*
* Return: Pointer to the created node, or NULL on failure.
*/
heap_t *heap_insert(heap_t **root, int value)
{
heap_t *new_node;

if (*root == NULL)
{
*root = binary_tree_node(NULL, value);
return (*root);
}

if (binary_tree_is_perfect(*root) || !binary_tree_is_perfect((*root)->left))
{
if ((*root)->left)
{
new_node = heap_insert(&((*root)->left), value);
swap(root, &((*root)->left));
return (new_node);
}
else
{
new_node = (*root)->left = binary_tree_node(*root, value);
swap(root, &((*root)->left));
return (new_node);
}
}

if ((*root)->right)
{
new_node = heap_insert(&((*root)->right), value);
swap(root, (&(*root)->right));
return (new_node);
}
else
{
new_node = (*root)->right = binary_tree_node(*root, value);
swap(root, &((*root)->right));
return (new_node);
}

return (NULL);
}
