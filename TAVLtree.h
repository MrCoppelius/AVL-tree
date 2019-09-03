#pragma once
#include <iostream>
#include "AVLnode.h"
class TAVLtree{
    public:
        TAVLtree();
        AVLnode* GetRoot();
        void SetRoot(AVLnode* node);
        AVLnode* Insert(AVLnode* node, char* key, unsigned long long data);
        AVLnode* Remove(AVLnode* node, char* key);
        void FindKey(AVLnode* node, char* key);
        void Serialization(char* path);
        bool DeSerialization(char* path);
        void Print(AVLnode *node, int h);
        ~TAVLtree();
    private:
        void DelTree(AVLnode* node);
        void Write(AVLnode* node, FILE* tree);
        bool Read(AVLnode* node, FILE* tree);
        AVLnode* RotateLeft(AVLnode* node);
        AVLnode* RotateRight(AVLnode* node);
        AVLnode* Balance(AVLnode* node);
        AVLnode* PopMin(AVLnode* node, AVLnode** min);
        short int NewBalance(AVLnode* node);
        int Height(AVLnode*node);
        AVLnode *root;
        bool flag;
};    

