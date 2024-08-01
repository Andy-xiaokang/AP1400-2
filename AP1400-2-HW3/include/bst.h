#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>


class BST
{
public:
    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;
    };
    BST();
    ~BST();
    BST(const BST & bst);
    BST(BST&& bst);
    BST& operator=(const BST & other);
    BST& operator=(BST && other);
    BST(std::initializer_list<int> init);
    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func) const;
    size_t length() const;
    bool add_node(int value);
    Node** find_node(int value) ;
    Node** find_parrent(int value) ;
    Node** find_successor(int value) ;
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os, const BST & bst);
    BST& operator++();
    BST operator++(int);

private:
    Node* root;

};

std::ostream& operator<<(std::ostream& os, const BST::Node& node);

bool operator>(const BST::Node& node, int value);
bool operator>(int value, const BST::Node& node);

bool operator<(int value, const BST::Node& node);
bool operator<(const BST::Node& node, int value);

bool operator>=(const BST::Node& node, int value);
bool operator>=(int value, const BST::Node& node);

bool operator<=(int value, const BST::Node& node);
bool operator<=(const BST::Node& node, int value);

bool operator==(int value, const BST::Node& node);
bool operator==(const BST::Node& node, int value);

#endif //BST_H