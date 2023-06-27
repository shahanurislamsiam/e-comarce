#include <stdio.h>
#include <stdlib.h>

struct Node {
  int data;
  struct Node *left;
  struct Node *right;
};

struct Node *replace_cousins_values(struct Node *root) {
  if (root == NULL) {
    return NULL;
  }

  // Get the list of all cousins of the current node.
  struct Node *cousins = get_cousins(root);

  // Calculate the sum of all cousins' values.
  int sum = 0;
  for (struct Node *c = cousins; c != NULL; c = c->next) {
    sum += c->data;
  }

  // Replace the value of the current node with the sum of all cousins' values.
  root->data = sum;

  // Recursively replace the values of all cousins' nodes.
  replace_cousins_values(cousins);

  return root;
}

struct Node *get_cousins(struct Node *node) {
  if (node == NULL) {
    return NULL;
  }

  // Get the list of all children of the current node's parent.
  struct Node *children = node->parent->children;

  // Create a list of all cousins of the current node.
  struct Node *cousins = NULL;
  for (struct Node *c = children; c != NULL; c = c->next) {
    if (c != node && c != node->sibling) {
      cousins = add_node(cousins, c);
    }
  }

  return cousins;
}

struct Node *add_node(struct Node *head, struct Node *node) {
  if (head == NULL) {
    return node;
  }

  node->next = head;
  return node;
}

int main() {
  // Create a tree
  struct Node *root = (struct Node *)malloc(sizeof(struct Node));
  root->data = 5;
  root->left = (struct Node *)malloc(sizeof(struct Node));
  root->left->data = 4;
  root->left->left = NULL;
  root->left->right = NULL;
  root->right = (struct Node *)malloc(sizeof(struct Node));
  root->right->data = 9;
  root->right->left = (struct Node *)malloc(sizeof(struct Node));
  root->right->left->data = 1;
  root->right->left->left = NULL;
  root->right->left->right = NULL;
  root->right->right = (struct Node *)malloc(sizeof(struct Node));
  root->right->right->data = 10;
  root->right->right->left = NULL;
  root->right->right->right = NULL;

  // Replace the value of each node in the tree with the sum of all its cousins' values.
  root = replace_cousins_values(root);

  // Print the tree
  printf("The tree with cousins' values replaced:\n");
  print_tree(root);

  return 0;
}

void print_tree(struct Node *node) {
  if (node == NULL) {
    return;
  }

  printf("%d ", node->data);
  print_tree(node->left);
  print_tree(node->right);
}
