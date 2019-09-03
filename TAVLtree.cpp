#include "TAVLtree.h"
#include <iostream>
#include <cstdio>
#include <string.h>

TAVLtree::TAVLtree():root(nullptr){}

TAVLtree::~TAVLtree(){
    DelTree(root);
}

void TAVLtree::DelTree(AVLnode* node) {
    if (node == nullptr) {
        return;
    }
    DelTree(node->left);
    DelTree(node->right);
    delete[] (node->key);
    node->key = nullptr; 
    delete node;
    node = nullptr;
}
AVLnode* TAVLtree::GetRoot(){
    return root;
}

void TAVLtree::SetRoot(AVLnode* node){
    root=node;
}

AVLnode* TAVLtree::RotateLeft(AVLnode* node) {
    AVLnode* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->balance = NewBalance(node);
    temp->balance = NewBalance(temp);
    return temp;
}

AVLnode* TAVLtree::RotateRight(AVLnode* node) {
    AVLnode* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->balance = NewBalance(node);
    temp->balance = NewBalance(temp);
    return temp;
}

int TAVLtree::Height(AVLnode* node) {
    int h = 0;
    if (node!=nullptr){
        int left_height = Height(node->left);
        int righ_height = Height(node->right);
        if (left_height >= righ_height) {
            h = left_height + 1;
        }
        else {
            h = righ_height + 1;
        }
    }
    return h;
}

short int TAVLtree::NewBalance(AVLnode* node) {
    return (Height(node->left) - Height(node->right));
}

AVLnode* TAVLtree::Balance(AVLnode* node) {
    if (node->balance == 2) {
        if (node->left->balance < 0) {
            node->left = RotateLeft(node->left);
        }
        return RotateRight(node);
    }
    if (node->balance == -2) {
        if (node->right->balance > 0) {
            node->right = RotateRight(node->right);
        }
        return RotateLeft(node);
    }
    return node;
}

AVLnode* TAVLtree::PopMin(AVLnode* node, AVLnode** min) {
    if (node->left == nullptr) {
        *min = node;
        flag = true;
        return node->right;
    }
    node->left = PopMin(node->left, min);
    if (flag) {
        node->balance--;
        node = Balance(node);
        if (node->balance) {
            flag = false;
        }
    }
    return node;
}

AVLnode* TAVLtree::Insert(AVLnode* node, char* key, unsigned long long data) {
    if (node == nullptr) {
        int len = strlen(key);
        node = new AVLnode;
        node->balance = 0;
        node->key = new char[len+1];
        strcpy(node->key, key);
        node->data = data;
        node->left = nullptr;
        node->right = nullptr;
        flag = true;
        std::cout << "OK" << std::endl;
        return node;
    }
    else if (strcasecmp(node->key, key)>0) {
        node->left = Insert(node->left, key, data);
        if (flag){
            node->balance++;
        }
        if (!node->balance) {
            flag = false;
        }
    }
    else if (strcasecmp(node->key, key)<0) {
        node->right = Insert(node->right, key, data);
        if (flag) {
            node->balance--;
        }
        if (!node->balance) {
            flag = false;
        }
    }
    else {
        std::cout << "Exist" << std::endl;
	flag = false;
    }
    if (flag) {
         node=Balance(node);
         if (!node->balance) {
             flag = false;
         }
    }
    return node;
}

AVLnode* TAVLtree::Remove(AVLnode* node, char* key){
    
    if (node==nullptr) {
        std::cout << "NoSuchWord" << std::endl;
        flag = false;
        return nullptr;
    }
    if (strcasecmp(node->key, key)>0) {
        node->left = Remove(node->left, key);
        if (flag) {
            node->balance--;
        }
        node = Balance(node);
        if (node->balance) {
            flag = false;
        }
    }
    else if (strcasecmp(node->key, key)<0) {
        node->right = Remove(node->right, key);
        if (flag) {
            node->balance++;
        }
        node = Balance(node);
        if (node->balance) {
            flag = false;
        }
    }
    else {
        AVLnode* left = node->left;
        AVLnode* right = node->right;
        short int oldBalance = node->balance;
        delete [] node->key;
        node->key = nullptr; 
        delete node;
        if (right == nullptr) {
            std::cout << "OK" << std::endl;
            flag = true;
            return left;
        }
        AVLnode *min = nullptr;
        right = PopMin(right, &min);
        min->right = right;
        min->left = left;
        min->balance = oldBalance;
        if (flag) {
            min->balance++;
            min = Balance(min);
            if (min->balance) {
                flag = false;
            }
        }
        std::cout << "OK" << std::endl;
        return min;
    }
    return node;
}

void TAVLtree::FindKey(AVLnode* node, char* key) {
    if (node == nullptr) {
        std::cout << "NoSuchWord" << std::endl;
        return;
    }
    if (strcasecmp(node->key, key)>0) {
        FindKey(node->left, key);
    }
    else if (strcasecmp(node->key, key)<0) {
        FindKey(node->right, key);
    }
    else if (!strcasecmp(node->key, key)) {
        std::cout << "OK: " << node->data << std::endl;
        return;
    }
}

void TAVLtree::Write(AVLnode* node, FILE* tree) {
    if (node == nullptr) {
        return;
    }
    bool tr = true;
    bool fl = false;
    int keyLen = strlen(node->key) + 1;
    fwrite(&keyLen, sizeof(int), 1, tree);
    fwrite(&node->balance, sizeof(short int), 1, tree);
    fwrite(&node->data, sizeof(unsigned long long), 1, tree);
    fwrite(&*node->key, keyLen, 1, tree);
    if (node->left)
        fwrite(&tr, sizeof(bool) , 1, tree);
    else
        fwrite(&fl, sizeof(bool), 1, tree);
    if (node->right)
        fwrite(&tr, sizeof(bool), 1, tree);
    else
        fwrite(&fl, sizeof(bool), 1, tree);
    Write(node->left, tree);
    Write(node->right, tree);
}

void TAVLtree::Serialization(char* path) {
    FILE* tree = fopen(path, "wb");
    if (!tree) {
        std::cout << "ERROR: Couldn't create file" << std::endl;
    }
    if (root == nullptr) {
        int empty = -2;
        fwrite(&empty, sizeof(int), 1, tree);
        std::cout << "OK" << std::endl;

    }
    else {
        Write(root, tree);
        std::cout << "OK" << std::endl;
    }
    fclose(tree);
}

bool TAVLtree::Read(AVLnode* node, FILE* tree) {
    int keyLen;
    bool left, right;
    if(fread(&keyLen, sizeof(int), 1, tree)!=1){
        return false;
    }
    if (keyLen == -2) {
        delete (node);
        root = nullptr;
        return true;
    }
    node->key = new char[keyLen];
    if(fread(&node->balance, sizeof(short int), 1, tree)!=1){
        return false;
    }
    if(fread(&node->data, sizeof(unsigned long long), 1, tree)!=1){
        return false;
    }
    if(fread(&*node->key, keyLen, 1, tree)!=1){
        return false;
    }
    
    if (fread(&left, sizeof(bool), 1, tree)!=1){
        return false;
    }
    if (fread(&right, sizeof(bool), 1, tree)!=1){
        return false;
    }
    if (left) {
        node->left = new AVLnode;
        if(!Read(node->left, tree)){
            return false;
        }
    }
    else {
        node->left = nullptr;
    }
    if (right) {
        node->right = new AVLnode;
        if (!Read(node->right, tree)){
            return false;
        }
    }
    else {
        node->right = nullptr;
    }
    return true;
}

bool TAVLtree::DeSerialization(char* path){
    FILE* tree = fopen(path, "rb");
    if (!tree) {
        std::cout << "ERROR: Couldn't create file" << std::endl;
        fclose(tree);
        return false;
    }
    else{
        root = new AVLnode;
        bool result = Read(root, tree);
        if (result) {
            std::cout << "OK" << std::endl;
            fclose(tree);
            return true;
        }
        else{
            std::cout << "ERROR: Wrong file" << std::endl;
            fclose(tree);
            return false;
        }
    }
}

void TAVLtree::Print(AVLnode *node, int h) {
    if (node) {
        Print(node->right, h + 2);
        for (int i = 0; i < h; ++i)
            std::cout << "   ";
        std::cout << node->key <<"[" << node->balance << "]" << std::endl;
        Print(node->left, h + 2);
    }
}


