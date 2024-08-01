#include "bst.h"
#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
using std::cout; using std::endl;
using Node = BST::Node;


BST::Node::Node(int value, Node *left, Node *right) : value(value), left(left), right(right){

}

BST::Node::Node() : value(0), left(nullptr), right(nullptr){

}

BST::Node::Node(const Node &node) : value(node.value), left(node.left), right(node.right){

}

std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << std::setw(17) << std::left << &node
       << "=> value:" << std::setw(5) << node.value
       << "left:" << std::setw(17) << node.left
       << "right:" << std::setw(17) <<  node.right
       << endl;
    return os;
}

bool operator>(const Node& node, int value) {
    return node.value > value;
}

bool operator>(int value, const Node& node) {
    return value > node.value;
}

bool operator<(int value, const Node& node) {
    return value < node.value;
}

bool operator<(const Node& node, int value) {
    return node.value < value;
}

bool operator>=(const Node& node, int value) {
    return node.value >= value;
}

bool operator>=(int value, const Node& node) {
    return value >= node.value;
}

bool operator<=(int value, const Node& node) {
    return value <= node.value;
}

bool operator<=(const Node& node, int value) {
    return node.value <= value;
}

bool operator==(int value, const Node& node) {
    return value == node.value;
}

bool operator==(const Node& node, int value) {
    return node.value == value;
}

Node*& BST::get_root() {
    return root;
}

void BST::bfs(std::function<void(Node *&)> func) const {
    std::queue<Node *> q;
    Node* curr = root;
    if (curr == nullptr) return;
    q.push(curr);
    while (!q.empty()) {
        curr = q.front();
        func(curr);
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
}

bool BST::add_node(int value) {
    Node *node = new Node(value, nullptr, nullptr);
    if (get_root() == nullptr) {
        root = node;
        return true;
    }
    Node *curr = get_root();
    Node *prev;
    while (curr != nullptr) {
        if (*curr == value) {
            return false;
        } else if (value > *curr) {
            prev = curr;
            curr = curr->right;
        } else if (value < *curr) {
            prev = curr;
            curr = curr->left;
        }
    }
    if (value > *prev) {
        prev->right = node;
    } else if (value < *prev) {
        prev->left = node;
    }
    return true;
}

size_t BST::length() const{
    std::queue<Node*> q;
    std::vector<Node*> v;
    Node* curr = root;
    q.push(curr);
    while (!q.empty()) {
        curr = q.front();
        v.push_back(curr);
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    return v.size();
}

std::ostream& operator<<(std::ostream& os, const BST & bst) {
    Node* curr = bst.root;
    std::queue<Node*> q;
    q.push(curr);
    os << "********************************************************************************" << endl;
    while (!q.empty()) {
        curr = q.front();
        os << *curr;
        q.pop();
        if (curr->left) q.push(curr->left);
        if (curr->right) q.push(curr->right);
    }
    os << "binary search tree size: " << bst.length() << endl;
    os << "********************************************************************************" << endl;
    return os;
}

Node** BST::find_node(int value) {
    Node* curr = root;
    Node* prev = root;
    if (curr == nullptr) return nullptr;
    if (root->value == value) return &root;
    while (curr != nullptr) {
        if (*curr == value) {
            break;
        } else if (value > *curr) {
            prev = curr;
            curr = curr->right;
        } else if (value < *curr) {
            prev = curr;
            curr = curr->left;
        }
    }
    if (curr) {
        if (value > *prev) {
            return &(prev->right);
        } else if (value < *prev) {
            return &(prev->left);
        }
    }
    return nullptr;
}

Node** BST::find_parrent(int value)  {
    Node* curr = root;
    Node* prev = root;
    if (curr == nullptr) return nullptr;
    while (curr != nullptr) {
        if (*curr == value) {
            break;
        } else if (value > *curr) {
            prev = curr;
            curr = curr->right;
        } else if (value < *curr) {
            prev = curr;
            curr = curr->left;
        }
    }
    if (curr) {
        return find_node(prev->value);
    }
    return nullptr;
}

Node** BST::find_successor(int value)  {
    Node** value_node = find_node(value);
    if (value_node == nullptr) return nullptr;
    Node* newroot = (*value_node)->left;
    Node* curr = newroot;
    Node* prev = newroot;
    if (curr == nullptr) return value_node;
    if (curr->right == nullptr) return &((*value_node)->left);
    while (curr->right != nullptr) {
        prev = curr;
        curr = curr->right;
    }
    return &(prev->right);
}

int findMax(Node* root) {
    if (root->right == nullptr) {
        return root->value;
    }
    return findMax(root->right);
}

void deleteHelper(Node*& root, int value) {
    if (root == nullptr) return;
    if (root->value < value) {
        deleteHelper(root->right, value);
    } else if (root->value > value) {
        deleteHelper(root->left, value);
    } else {
        if (root->left == nullptr && root->right == nullptr) {
            delete root;
            root = nullptr;
        } else if (root->left == nullptr) {
            Node* tmp = root->right;
            delete root;
            root = tmp;
        } else if (root->right == nullptr) {
            Node* tmp = root->left;
            delete root;
            root = tmp;
        } else {
            root->value = findMax(root->left);
            deleteHelper(root->left, root->value);
        }
    }
}

bool BST::delete_node(int value) {
    if (find_node(value) == nullptr) return false;
    deleteHelper(root, value);
    return true;
}

BST::BST() {
    get_root() = nullptr;
}

BST::~BST() {
    std::vector<Node*> nodes;
    this->bfs([&nodes](BST::Node*& node) { nodes.push_back(node); });
    for (auto& node : nodes)
        delete node;
}

BST::BST(const BST & bst) : BST(){
    std::vector<Node*> nodes;
    bst.bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
    for (Node* node : nodes) {
        this->add_node(node->value);
    }
}

BST::BST(BST&& bst) {
    this->root = bst.root;
    bst.root = nullptr;
}

BST::BST(std::initializer_list<int> init) {
    root = nullptr;
    for (int value : init) {
        add_node(value);
    }
}

BST& BST::operator=(const BST & other){
    if (this != &other) {
        this->~BST();
        std::vector<Node *> nodes;
        other.bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
        for (Node *node: nodes) {
            this->add_node(node->value);
        }
    }
    return *this;
}

BST& BST::operator=(BST && other) {
    this->~BST();
    root = other.root;
    other.root = nullptr;
    return *this;
}

BST& BST::operator++() {  // ++bst
    std::vector<Node *> nodes;
    bfs([&nodes](BST::Node *&node) { nodes.push_back(node); });
    for (Node* node : nodes) {
        node->value++;
    }
    return *this;
}

BST BST::operator++(int) {
    auto copy = (*this); // copy constructor
    ++(*this);
    return copy;
}