#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ex_6_1/get_word.h"

struct TreeNode {
  char *word;
  int match;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct TreeNode TreeNode;

static const int kMaxWord = 100;

/* Adds a node in the BST and marks the matched
 * nodes that their first num characters are equal,
 * if it is already in, do nothing.
 *
 * @param root root pointer of the binary search tree
 * @param word word to be added into tree
 * @param num first num characters will be used for matching.
 * @param match_found[out] 1 for at least one word matched is found
 *                         0 for no word matched is found.
 * @return the new node's pointer if the word is not in the tree,
 *         else return the root.
 */
static TreeNode *AddTreeNode(TreeNode *root, char *word,
                             int num, int *match_found);

/* Prints the tree inorder
 *
 * @param root root pointer of the binary search tree
 * @param pre_node_match[out] previous node's match element.
 *                            used to control new line.
 */
static void PrintTree(TreeNode *root, int *pre_node_match);

/* Prints the variable names in alphabetic order,
 * where each group of names are identical in
 * the first num characters (default 6).
 */
int main(int argc, char *argv[]) {
  TreeNode *root;
  char word[kMaxWord];
  int match_found = 0;
  int num = 0;

  if (--argc == 1) {
    if ((num = atoi(*++argv)) == 0) {
        printf("Warning: invalid argument, using default.\n");
        num = 6;
    }
  } else if (argc > 1){
    printf("Error: too many arguments\n");
  } else {
    printf("Warning: missing argument, using default.\n");
    num = 6;
  }

  root = NULL;
  while (GetWord(word, kMaxWord) != EOF) {
    if ((isalpha(word[0]) || word[0] == '_' || word[0] == '#')
        && strlen(word) >= num)  {
      root = AddTreeNode(root, word, num, &match_found);
    }
    match_found = 0;
  }
  PrintTree(root, &match_found);
  return 0;
}

static TreeNode *AddTreeNode(TreeNode *root, char *word,
                             int num, int *match_found) {
  if (root == NULL) {
    root = (TreeNode *) malloc(sizeof(TreeNode));
    root->word = strdup(word);
    root->match = *match_found;
    root->left = root->right = NULL;
  } else {
    int n = strcmp(word, root->word);

    if (n != 0 && !strncmp(root->word, word, num)) {
      root->match = 1;
      *match_found = 1;
    }
    if (n < 0) {
      root->left = AddTreeNode(root->left, word, num, match_found);
    } else if (n > 0) {
      root->right = AddTreeNode(root->right, word, num, match_found);
    }
  }
  return root;
}

static void PrintTree(TreeNode *root, int *pre_node_match) {
  if (root != NULL) {
    PrintTree(root->left, pre_node_match);

    if(*pre_node_match != root->match || *pre_node_match == 0) {
      putchar('\n');
    }

    printf("%s ", root->word);

    *pre_node_match = root->match;

    PrintTree(root->right, pre_node_match);
  }
}
