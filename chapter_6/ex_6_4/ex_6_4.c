#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ex_6_1/get_word.h"

static const int kMaxWord = 100;
static const int kMaxNumDistWord = 1000;

struct TreeNode {
  char *word;
  int count;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct TreeNode TreeNode;

/* Adds a node in BST, if it is alreay in, update its count;
 * also counts the number of nodes in BST.
 *
 * @param root root pointer of the binary search tree
 * @param word word to be added into tree
 * @param word_num[out] the number of node in the tree.
 * @return the new node's pointer if the word is not in the tree,
 *         else return the root.
 */
static TreeNode *AddTreeNode(TreeNode *root, char *word, int *word_num);

/* Transfers the BST structure to a list inorder.
 *
 * @param root root pointer of the binary search tree.
 * @param list pointer array of tree node
 * @param index previous node's index in the list.
 */
static void TreeToList(TreeNode *root, TreeNode **list, int *index);

/* Compares two node of tree according the count member.
 *
 * @param node1
 * @param node2
 * @return an integer less than, equal to, or greater than zero
 *         if node1' count member is found, respectively, to be
 *         less than, to match, or be greater than node2's.
 */
static int CompareNode(const TreeNode **node1, const TreeNode **node2);

/* Prints distinct words sorted in decreasing order of frequency. */
int main() {
  TreeNode *root = NULL;
  char word[kMaxWord];
  TreeNode **word_list;
  int word_num = 0, i = 0;

  while (GetWord(word, kMaxWord) != EOF) {
    if (isalpha(word[0]) || word[0] == '_') {
      root = AddTreeNode(root, word, &word_num);
    }
  }
  word_list = (TreeNode **) malloc(word_num * sizeof(TreeNode *));
  TreeToList(root, word_list, &i);

  qsort(word_list, word_num, sizeof(TreeNode *),
        (int (*)(const void *, const void *)) CompareNode);

  for (i = word_num - 1; i >= 0; --i) {
    printf("%2d: %20s\n", word_list[i]->count, word_list[i]->word);
  }

  return 0;
}

static TreeNode *AddTreeNode(TreeNode *root, char *word, int *word_num) {
  int cond;

  if (!root) {
    root = (TreeNode *) malloc(sizeof(TreeNode));
    root->word = strdup(word);
    root->count = 1;
    root->left = root->right = NULL;
    ++*word_num;
  } else if ((cond = strcmp(word, root->word)) == 0) {
    root->count++;
  } else if (cond < 0) {
    root->left = AddTreeNode(root->left, word, word_num);
  } else {
    root->right = AddTreeNode(root->right, word, word_num);
  }

  return root;
}

static void TreeToList(TreeNode *root, TreeNode **list, int *index) {

  if (root) {
    TreeToList(root->left, list, index);
    list[(*index)++] = root;
    TreeToList(root->right, list, index);
  }
}

static int CompareNode(const TreeNode **node1, const TreeNode **node2) {
  return  ((TreeNode *)*node1)->count - ((TreeNode *)*node2)->count;
}
