#ifndef ASSOCIATIVE_H
#define ASSOCIATIVE_H

#include <stddef.h>
#include <stdbool.h>

/// @note Denotes English alphabet size for trie
#define ALPHABET_SIZE 26

/* English word Trie */

typedef struct etrie_node_t {
    struct etrie_node_t **children;
} ETrieNode;

ETrieNode *etrie_node_create();

void etrie_node_destroy(ETrieNode *root);

#define ETRIE_NODE_IS_ROOT(node_ptr) (node_ptr->letter == '\0')

typedef struct trie_t {
    ETrieNode *root;
} ETrie;

bool etrie_init(ETrie *etrie);

void etrie_destroy(ETrie *etrie);

bool etrie_put(ETrie *etrie, const char *str);

bool etrie_has(const ETrie *etrie, const char *str);

#endif