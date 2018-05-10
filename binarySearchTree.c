#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

struct tree
{
	int item;
	struct tree *right;
	struct tree *left;
	struct tree *parent;
};
typedef struct tree node;


int search_tree(node *l, int x)
{
	if(l == NULL)
	{
		return 0;
	}

	if(l->item == x)
	{
		return 1;
	}

	if(x < l->item)
	{
		return (search_tree(l->left, x));
	}
	else
	{
		return (search_tree(l->right, x));
	}
}

int find_minimum(node *t1)
{
	node *min;

	if(t1 == NULL)
	{
		return -1;
	}

	min = t1;
	while(min->left != NULL)
	{
		min = min->left;
	}
	return min->item;
}

int find_maximum(node *t2)
{
	node *max;

	if(t2 == NULL)
	{
		return -1;
	}

	max = t2;
	while(max->right != NULL)
	{
		max = max->right;
	}
	return max->item;
}

int insert_tree(node **l, int x, node *parent)
{
	node *p;

	if(*l == NULL)
	{
		p = malloc(sizeof(node));
		p->item = x;
		p->left = p->right = NULL;
		p->parent = parent;
		*l = p;
		return p->item;
	}

	if(x < (*l)->item)
	{
		return (insert_tree(&((*l)->left), x, *l));
	}
	else
	{
		return (insert_tree(&((*l)->right), x, *l));
	}
}

int find_successor(node *l, int x)
{
	if(l == NULL)
	{
		return -1;
	}

	if(l->item == x)
	{
		if(l->right != NULL)
		{
			l = l->right;
			while(l->left != NULL)
			{
				l = l->left;
			}
			if(l->item == x)
			{
				return l->parent->item;
			}
			else
			{
				return l->item;
			}
		}
		else if(l->right == NULL)
		{
			while(l->parent != NULL)
			{
				if(l->parent->left == l)
				{
					return l->parent->item;
				}
				l = l->parent;
			}
			return -1;
		}
	}

	if(x < l->item)
	{
		return (find_successor(l->left, x));
	}
	else
	{
		return (find_successor(l->right, x));
	}
}

int find_predecessor(node *l, int x)
{
	if(l == NULL)
	{
		return -1;
	}

	if(l->item == x)
	{
		if(l->left != NULL)
		{
			l = l->left;
			while(l->right != NULL)
			{
				l = l->right;
			}
			if(l->item == x)
			{
				return l->parent->item;
			}
			else
			{
				return l->item;
			}
		}
		else if(l->left == NULL)
		{
			while(l->parent != NULL)
			{
				if(l->parent->right == l)
				{
					return l->parent->item;
				}
				l = l->parent;
			}
			return -1;
		}
	}

	if(x < l->item)
	{
		return (find_predecessor(l->left, x));
	}
	else
	{
		return (find_predecessor(l->right, x));
	}
}

int find_height(node *l)
{
	if(l == NULL)
	{
		return -1;
	}
	else
	{
		int lDepth = find_height(l->left);
		int rDepth = find_height(l->right);
		
		if(lDepth > rDepth)
		{
			return (lDepth+1);
		}
		else
		{
			return (rDepth+1);
		}
	}
}

int delete_tree(node *l, int x, int count)
{
	if(l == NULL)
	{
		//return count;
	}

	if(l->item == x)
	{
		if((l->parent != NULL) && (l->right == NULL && l->left == NULL))
		{
			if(l->parent->right == l)
			{
				l->parent->right = NULL;
			}
			if(l->parent->left == l)
			{
				l->parent->left = NULL;
			}
			free(l);
			count = count + 1;
		}
		if((l->parent != NULL) && ((l->right != NULL && l->left == NULL) || (l->right == NULL && l->left != NULL)))
		{
			int delKey = l->item;
			node *p;
			p = l->parent;
			if((l->right != NULL && l->left == NULL))
			{
				if(p->right == l)
				{
					while(l->item == delKey)
					{
						if(l == NULL)
						{
							break;
						}
						l = l->right;
						free(l->parent);
						count = count + 1;
					}
					p->right = l;
					if(l != NULL)
					{
						l->parent = p;
					}
				}
				if(p->left == l)
				{
					while(l->item == delKey)
					{
						if(l == NULL)
						{
							break;
						}
						l = l->right;
						free(l->parent);
						count = count + 1;
					}
					p->left = l;
					if(l != NULL)
					{
						l->parent = p;
					}
				}
			}
			if((l->right == NULL && l->left != NULL))
			{
				if(p->right == l)
				{
					l = l->left;
					free(l->parent);
					count = count + 1;
					p->right = l;
					l->parent = p;
				}
				if(p->left == l)
				{
					l = l->left;
					free(l->parent);
					count = count + 1;
					p->left = l;
					l->parent = p;
				}
			}
		}
		if((l->parent != NULL) && (l->right != NULL && l->left != NULL))
		{
			node *p;
			p = l->parent;
			node* s = l;
			if(p->right == l)
			{
				l = l->right;
				while(l->left != NULL)
				{
					l = l->left;
				}
				if(l->item == s->item)
				{
					p->right = l;
					if(l->item != s->right->item)
					{
						l->parent->left = NULL;
						l->right = s->right;
						s->right->parent = l;
					}
					l->parent = p;
					l->left = s->left;
					s->left->parent = l;
					free(s);
					count = count + 1;
				}
				else
				{
					p->right = l;
					if(l->item != s->right->item)
					{
						l->parent->left = NULL;
						l->right = s->right;
						s->right->parent = l;
					}
					l->parent = p;
					l->left = s->left;
					s->left->parent = l;
					free(s);
					count = count + 1;
				}
			}
			if(p->left == l)
			{
				l = l->right;
				while(l->left != NULL)
				{
					l = l->left;
				}
				if(l->item == s->item)
				{
					p->left = l;
					if(l->item != s->right->item)
					{
						l->parent->left = NULL;
						l->right = s->right;
						s->right->parent = l;
					}
					l->parent = p;
					l->left = s->left;
					s->left->parent = l;
					free(s);
					count = count + 1;
				}
				else
				{
					p->left = l;
					if(l->item != s->right->item)
					{
						l->parent->left = NULL;
						l->right = s->right;
						s->right->parent = l;
					}
					l->parent = p;
					l->left = s->left;
					s->left->parent = l;
					free(s);
					count = count + 1;
				}
			}
		}
		if((l->parent == NULL) && ((l->right != NULL && l->left == NULL) || (l->right == NULL && l->left != NULL)))
		{
			node *s;
			s = l;
			printf("%d\n", s->item);
			if((l->right != NULL && l->left == NULL))
			{
				l = l->right;
				free(s);
				count = count + 1;
				l->parent = NULL;
			}
			if((l->right == NULL && l->left != NULL))
			{
				l = l->left;
				free(s);
				count = count + 1;
				l->parent = NULL;
			}
		}
		if((l->parent == NULL) && ((l->right != NULL) && (l->left != NULL)))
		{
			node* s = l;
			l = l->right;
			while(l->left != NULL)
			{
				l = l->left;
			}
			if(l->item == s->item)
			{
				if(l->item != s->right->item)
				{
					l->parent->left = l->right;
					if(l->right != NULL)
					{
						l->right->parent = l->parent;
					}
					l->right = s->right;
					s->right->parent = l;
				}
				l->left = s->left;
				s->left->parent = l;
				free(s);
				count = count + 1;
				l->parent = NULL;
			}
			else
			{
				if(l->item != s->right->item)
				{
					l->parent->left = l->parent;
					if(l->right != NULL)
					{
						l->right->parent = l->parent;
					}
					l->right = s->right;
					s->right->parent = l;
				}
				l->left = s->left;
				s->left->parent = l;
				free(s);
				count = count + 1;
				l->parent = NULL;
			}
		}
	}

	if(x < l->item)
	{
		return (delete_tree(l->left, x, count));
	}
	else if(x == l->item)
	{
		return (delete_tree(l, x, count));
	}
	else
	{
		return (delete_tree(l->right, x, count));
	}
}	

void main(int argc, char *argv[])
{
	printf("%d\n", 575);
	node *root = NULL;

	FILE *input;
	char temp[100];
	char line[30];
	int listchar;
	input = fopen(argv[1], "r");

	while(!feof(input))
	{
		fgets(temp, sizeof(temp), input);
		sscanf(temp, "%s %d", line, &listchar);

   		if(strcmp(line, "INS") == 0)
   		{
   			printf("%d\n", insert_tree(&root, listchar, NULL));
   		}
   		if(strcmp(line, "DEL") == 0)
   		{
   			printf("%d\n", delete_tree(root, listchar, 0));
   		}
   		if(strcmp(line, "SEA") == 0)
   		{
   			printf("%d\n", search_tree(root, listchar));
   		}
   		if(strcmp(line, "MIN") == 0)
   		{
   			printf("%d\n", find_minimum(root));
   		}
   		if(strcmp(line, "MAX") == 0)
   		{
   			printf("%d\n", find_maximum(root));
   		}
   		if(strcmp(line, "PRE") == 0)
   		{
   			printf("%d\n", find_predecessor(root, listchar));
   		}
   		if(strcmp(line, "SUC") == 0)
   		{
   			printf("%d\n", find_successor(root, listchar));
   		}
   		if(strcmp(line, "HEI") == 0)
   		{
   			printf("%d\n", find_height(root)-1);
   		}
	}

	//printf("%d\n", root->item);
	//printf("%d\n", root->parent->item);

   	/*insert_tree(&root, 6, NULL);
   	insert_tree(&root, 7, NULL);
   	insert_tree(&root, 15, NULL);
   	insert_tree(&root, 5, NULL);
   	insert_tree(&root, 6, NULL);
   	insert_tree(&root, 6, NULL);
   	insert_tree(&root, 6, NULL);

   	printf("%d\n", delete_tree(root, 6, 0));
   	//printf("%d\n", delete_tree(root, 15, 0));
   	printf("%d\n", find_height(root));

   	//printf("%d\n", root->parent->item);
   	//printf("%d\n", find_height(root));*/
}

