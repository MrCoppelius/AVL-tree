#include "TAVLtree.h"
#include <iostream>
#include <cstdio>
#include <string>


int main() {

    unsigned long long data;
    //std::ios::sync_with_stdio(false); 
    //std::cin.tie(0);
    char key[257];
    TAVLtree* tree = new TAVLtree;
    while (std::cin >> key) {
        switch (key[0]) {
        case '+':
            std::cin >> key;
            std::cin >> data;
            tree->SetRoot(tree->Insert(tree->GetRoot(),key, data));
            break;
        case '-':
            std::cin >> key;
            tree->SetRoot(tree->Remove(tree->GetRoot(),key));
            break;
        case '!':
            std::cin >> key;
            if (key[0] == 'S' || key[0] == 's') {
                std::cin >> key;
                tree->Serialization(key);
            }
            else if (key[0] == 'L' || key[0] == 'l') {
                std::cin >> key;
                TAVLtree *newtree = new TAVLtree();
                if (newtree->DeSerialization(key)){
                    delete tree;
                    tree = newtree;
                }
                else{
                    delete newtree;
                }
            }
            break;
        case '`':
            tree->Print(tree->GetRoot(), 0);
            break; 
        default:
            tree->FindKey(tree->GetRoot(), key);
        }
    }
delete tree;    
}
