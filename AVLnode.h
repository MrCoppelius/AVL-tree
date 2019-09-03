#pragma once

struct AVLnode {
    char* key;
    unsigned long long data;
    short int balance;
    AVLnode *left, *right;
};
