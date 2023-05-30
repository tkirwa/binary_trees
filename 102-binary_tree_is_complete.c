#include "binary_trees.h"
#include <stdlib.h>

/**
 * link_t - A linked list node to store binary tree nodes
 * @node: Pointer to the binary tree node
 * @next: Pointer to the next linked list node
 */
typedef struct link_s
{
	binary_tree_t *node;
	struct link_s *next;
} link_t;

/**
 * new_link - Creates a new linked list node
 * @node: Pointer to the binary tree node
 *
 * Return: The created linked list node
 */
link_t *new_link(binary_tree_t *node)
{
	link_t *new_node = malloc(sizeof(link_t));
	if (new_node == NULL)
		return NULL;

	new_node->node = node;
	new_node->next = NULL;

	return new_node;
}

/**
 * free_q - Frees the linked list nodes
 * @head: The head of the linked list
 */
void free_q(link_t *head)
{
	link_t *temp;

	while (head)
	{
		temp = head;
		head = head->next;
		free(temp);
	}
}

/**
 * push - Pushes a binary tree node to the queue (linked list)
 * @node: The binary tree node to push
 * @head: The head of the linked list
 * @tail: The tail of the linked list
 *
 * Return: The new tail of the linked list
 */
link_t *push(binary_tree_t *node, link_t *head, link_t **tail)
{
	link_t *new_link_node = new_link(node);
	if (new_link_node == NULL)
	{
		free_q(head);
		exit(1);
	}

	(*tail)->next = new_link_node;
	*tail = new_link_node;
	return new_link_node;
}

/**
 * pop - Pops a binary tree node from the queue (linked list)
 * @head: The head of the linked list
 */
void pop(link_t **head)
{
	link_t *temp;

	if (*head == NULL)
		return;

	temp = *head;
	*head = (*head)->next;
	free(temp);
}

/**
 * binary_tree_is_complete - Checks if a binary tree is complete
 * @tree: Pointer to the root node of the tree
 *
 * Return: 1 if the tree is complete, 0 otherwise
 */
int binary_tree_is_complete(const binary_tree_t *tree)
{
	link_t *head, *tail;
	int flag = 0;

	if (tree == NULL)
		return (0);

	head = tail = new_link((binary_tree_t *)tree);
	if (head == NULL)
		exit(1);

	while (head != NULL)
	{
		if (head->node->left != NULL)
		{
			if (flag == 1)
			{
				free_q(head);
				return (0);
			}
			tail = push(head->node->left, head, &tail);
		}
		else
			flag = 1;

		if (head->node->right != NULL)
		{
			if (flag == 1)
			{
				free_q(head);
				return (0);
			}
			tail = push(head->node->right, head, &tail);
		}
		else
			flag = 1;

		pop(&head);
	}

	return (1);
}
