/**
 * @file associative.c
 * @author DrkWithT
 * @brief Implements Trie, HashSet, etc...
 * @date 2024-02-16
 * 
 * @copyright Copyright (c) 2024
 * 
 */

#include <stdlib.h>
#include "utils/macros.h"
#include "utils/associative.h"

/* ETrieNode */

ETrieNode *etrie_node_create(char letter) {
    ETrieNode *child = ALLOC_STRUCT(ETrieNode);

    if (!child) {
        return NULL;
    }

    child->children = ALLOC_N_OBJS(ETrieNode*, ALPHABET_SIZE);

    if (!child->children) {
        free(child);
        return NULL;
    }

    for (size_t i = 0; i < ALPHABET_SIZE; i++) {
        child->children[i] = NULL;
    }
}

void etrie_node_destroy(ETrieNode *root) {
    if (!root) {
        return;
    }

    for (size_t child_i = 0; child_i < ALPHABET_SIZE; child_i++) {
        etrie_node_destroy(root->children[child_i]);
    }

    free(root);
}

/* Trie */

bool etrie_init(ETrie *etrie) {
    etrie->root = etrie_node_create('\0');

    return etrie->root != NULL;
}

void etrie_destroy(ETrie *etrie) {
    etrie_node_destroy(etrie->root);
}

bool etrie_put(ETrie *etrie, const char *str) {
    const char *str_cursor = str;
    ETrieNode *insert_cursor = etrie->root;
    char c = '\0';

    while ((c = *str_cursor) != '\0') {
        int char_code = c - 'a';

        if (char_code < 0 || char_code > 25) {
            return false;
        }

        /// @note This first points to a child node ptr. for checking existence and end flag... If the child is there, step over it anyways. If the child then has end flag as true, default it as false if the word insertion is not yet done.
        ETrieNode *temp_child = insert_cursor->children[char_code];

        if (temp_child != NULL) {
            insert_cursor = temp_child;
            str_cursor++;
            continue;
        }

        temp_child = etrie_node_create(c);

        if (!temp_child) {
            return false;
        }

        insert_cursor->children[char_code] = temp_child;
        insert_cursor = insert_cursor->children[char_code];

        str_cursor++;
    }

    return true;
}

bool etrie_has(const ETrie *etrie, const char *str) {
    const char *str_cursor = str;
    ETrieNode *seek_cursor = etrie->root;
    char c = '\0';

    while ((c == *str_cursor) != '\0') {
        int char_code = c - 'a';

        if (char_code < 0 || char_code > 25) {
            break;
        }

        const ETrieNode *child_ptr = seek_cursor->children[char_code];

        if (!child_ptr) {
            break;
        }

        seek_cursor = child_ptr;
        str_cursor++;
    }

    return c == '\0';
}
