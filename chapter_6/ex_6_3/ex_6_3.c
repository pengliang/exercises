#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "ex_6_1/get_word.h"

static const kMaxWord = 100;

struct LinkNode {
  int line_num;
  struct LinkNode *next;
};

typedef struct LinkNode LinkNode;

struct TreeNode {
  char *word;
  LinkNode *lines;
  struct TreeNode *left;
  struct TreeNode *right;
};

typedef struct TreeNode TreeNode;

/* Adds a node in BST, if it is already in, then
 * appends the line number to its lines list
 * if the number is new.
 *
 * @param root root pointer of the binary search tree
 * @param word word to be added into tree
 * @param line_num the line number that the word appears in.
 * @return the new node's pointer if the word is not in the tree,
 *         else return the root.
 */
static TreeNode *AddTreeNode(TreeNode *root,
                             const char *word,
                             int line_num);

/* Appends a node on the link list, if it is not already in.
 *
 * @param head head node's pointer of the link list
 * @param line_num new node's content
 */
static void AppendLinkList(LinkNode *head, int line_num);

/* Checks the word is noise word or not.
 *
 * @param word string of letters, digits and underscores
 *             begin with alpha or '_'
 * @param return an integer >= 0 for it is a noise word
 *               -1 for other
 */
static int IsNoiseWord(char *word);

/* Prints the tree inorder.
 *
 * @param root root node's pointer of the BST.
 */
static void PrintTree(TreeNode *root);

/* Cross referencer, prints all words and its line number */
int main() {
  TreeNode *root;
  char word[kMaxWord];
  int line_num = 1;

  root = NULL;
  while (GetWord(word, kMaxWord) != EOF) {
    if (isalpha(word[0]) && IsNoiseWord(word) == -1) {
      root = AddTreeNode(root, word, line_num);
    } else if (word[0] == '\n') {
      ++line_num;
    }
  }
  PrintTree(root);
  return 0;
}

TreeNode *AddTreeNode(TreeNode *root, const char *word, int line_num) {
  int i = 0;

  if (root == NULL) {
    root = (TreeNode *) malloc(sizeof(TreeNode));
    root->word = strdup(word);
    // Null head of LinkNode
    root->lines = (LinkNode *) malloc(sizeof(LinkNode));
    root->lines->line_num = 0;
    root->lines->next = (LinkNode *) malloc(sizeof(LinkNode));
    root->lines->next->line_num = line_num;
    root->lines->next->next = NULL;
    root->left = root->right = NULL;
  } else if ((i = strcmp(word, root->word)) == 0) {
    AppendLinkList(root->lines, line_num);
  } else if (i < 0) {
    root->left = AddTreeNode(root->left, word, line_num);
  } else {
    root->right = AddTreeNode(root->right, word, line_num);
  }
  return root;
}

void AppendLinkList(LinkNode *head, int line_num) {
  LinkNode *p = head->next;

  while (p->next && p->line_num != line_num) {
    p = p->next;
  }

  if (p->line_num != line_num) {
    p->next = (LinkNode *)malloc(sizeof(LinkNode));
    p->next->line_num = line_num;
    p->next->next =NULL;
  }
}

void PrintTree(TreeNode *root) {
  if (root != NULL) {
    LinkNode *p = root->lines;

    PrintTree(root->left);
    printf("%15s: ", root->word);

    while (p = p->next) {
      printf("%4d ", p->line_num);
    }
    putchar('\n');
    PrintTree(root->right);
  }
}

int IsNoiseWord(char *word) {
  static char *noise_word[] = {
    "a", "an", "and", "are", "in", "is",
    "of", "or", "that", "the", "this", "to"
  };

  int low = 0, cond = 0, mid = 0;
  int high = sizeof(noise_word) / sizeof(char *) - 1;

  while (low < high) {
    mid = (low + high) / 2;

    if ((cond = strcmp(word, noise_word[mid])) < 0) {
      high = mid -1;
    } else if (cond > 0) {
      low = mid + 1;
    } else {
      return mid;
    }
  }
  return -1;
}
