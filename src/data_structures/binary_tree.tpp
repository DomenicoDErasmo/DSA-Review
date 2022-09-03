#ifndef BINARY_TREE_TPP
#define BINARY_TREE_TPP

template <typename T>
class BinaryTree {
public:
    // Constructors
    BinaryTree(): data(T()), left(nullptr), right(nullptr) {}
    BinaryTree(T in_data): data(in_data), left(nullptr), right(nullptr) {}
    BinaryTree(T in_data, BinaryTree* in_left, BinaryTree* in_right): data(in_data), left(in_left), right(in_right) {}
    BinaryTree(const BinaryTree& other): data(other.data), left(other.left), right(other.right) {}
    ~BinaryTree() {
        if (left) {delete left;}
        if (right) {delete right;}
    }
    // Getters
    T getData() const {return data;}
    BinaryTree* getLeft() const {return left;}
    BinaryTree* getRight() const {return right;}

    // Setters
    void setData(T in_data) const {data = in_data;}
    void setLeft(BinaryTree* in_left) const {left = in_left;}
    void setRight(BinaryTree* in_right) const {left = in_right;}

    // TODO:  == operator, != operator, basic functionality, unit tests
    std::string toString() const {
        std::string result = "[" + std::to_string(data);
        if (left) {result += (", " + left->toString());}
        if (right) {result += (", " + right->toString());}
        return result + "]";
    }

    friend std::ostream& operator << (std::ostream& out, const BinaryTree<int>& root) {
        out << root.toString();
        return out;
    }

private:
    T data;
    BinaryTree<T>* left;
    BinaryTree<T>* right;
};

#endif