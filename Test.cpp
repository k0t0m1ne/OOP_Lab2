#include "Test.h"


#include "BinaryTree.h"
#include <cassert>
void Test() {
    BinaryTree<int, string> emptytree;
    assert(emptytree.getSize() == 0);

    BinaryTree<int, string> tree1;
    tree1.insertItem(12, "12");
    tree1.insertItem(4, "4");
    tree1.insertItem(6, "6");
    tree1.insertItem(9, "9");
    tree1.insertItem(17, "17");
    tree1.insertItem(14, "14");
    int size = 6, wrongkey = 0;
    assert(tree1.getSize() == size);

    string strs[6] = { "4", "6", "9", "12", "14", "17" };
    auto lst = tree1.lst();
    int i = 0;
    for (auto& v : lst) {
        assert(v == strs[i++]);
    }

    tree1.deleteItem(wrongkey);
    assert(tree1.getSize() == size);


    assert(tree1.find(4) == true);
    assert(tree1.find(wrongkey) == false);


    std::string path = "text.txt";
    tree1.write(path);
    BinaryTree<int, string> tree2;
    tree2.read(path);
    assert(tree1 == tree2);
    tree1.deleteItem(6);
    assert(tree1.getSize() == size - 1);
    assert(tree1 != tree2);
    tree1.clear();
    assert(emptytree == tree1);

    std::cout << "all tests are passed sucessfull";
}
