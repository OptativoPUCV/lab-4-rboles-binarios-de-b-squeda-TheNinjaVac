#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"

typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
    TreeMap * new = (TreeMap *)malloc(sizeof(TreeMap));
    if (new == NULL) return NULL;
    new->root = NULL;
    new->current = NULL;
    new->lower_than = lower_than;
    return new;

}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
    if (tree == NULL) return;
    TreeNode * new = createTreeNode(key, value);
    if (new == NULL) return;
    if (tree->root == NULL) {
        tree->root = new;
        tree->current = new;
        return;
    }

    TreeNode * current = tree->root;
    while (1) {
        if (tree->lower_than(new->pair->key, current->pair->key)) {
            if (current->left == NULL) {
                current->left = new;
                new->parent = current;
                tree->current = new;
                break;
            } else {
                current = current->left;
            }
        } else if (tree->lower_than(current->pair->key,new->pair->key)) {
            if (current->right == NULL) {
                current->right = new;
                new->parent = current;
                tree->current = new;
                break;
            } else {
                current = current->right;
            }
        } else {
            free(new);
            return;
        }
    }
}

TreeNode * minimum(TreeNode * x){
    if (x == NULL) return NULL;
    if (x->left == NULL) return x;
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}


void removeNode(TreeMap * tree, TreeNode* node) {
    if (node == NULL) return;

    // Caso 1: Nodo sin hijos
    if (node->left == NULL && node->right == NULL) {
        if (node->parent != NULL) {
            if (node->parent->left == node) {
                node->parent->left = NULL;
            } else {
                node->parent->right = NULL;
            }
        }
        free(node->pair);
        free(node);
        return;
    }
    // Caso 2: Nodo con un hijo
    if (node->left == NULL || node->right == NULL) {
        TreeNode * child;
        if (node->left != NULL) {
            child = node->left;
        } else {
            child = node->right;
        }
        if (node->parent != NULL) {
            if (node->parent->left == node) {
                node->parent->left = child;
            } else {
                node->parent->right = child;
            }
        }
        child->parent = node->parent;
        free(node->pair);
        free(node);
        return;
    }
    
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}




Pair * searchTreeMap(TreeMap * tree, void* key) {
    if (tree == NULL || tree->root == NULL) return NULL;
    TreeNode * current = tree->root;
    while (current != NULL) {
        if (tree->lower_than(key, current->pair->key)) {
            current = current->left;
        }
        else if (tree->lower_than(current->pair->key, key)) {
            current = current->right;
        } else {
            tree->current = current;
            return current->pair;
        }
    }
    return NULL;
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
