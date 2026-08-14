/* TODO: Implement the functions for the class BST */
/* Write your code below */

template <typename K, typename V>
vector<V> BST<K, V>::getInorder(Node* node) const {
    vector<V> result;
    if (node == nullptr) return result;
    // Traverse left subtree
    vector<V> left = getInorder(node->left);
    result.insert(result.end(), left.begin(), left.end());
    // Visit current node
    result.push_back(node->value);
    // Traverse right subtree
    vector<V> right = getInorder(node->right);
    result.insert(result.end(), right.begin(), right.end());
    return result;
}

template <typename K, typename V>
vector<V> BST<K, V>::getInorderWithUpperBound(Node* node, const K& upper_bound) const {
    vector<V> result;
    if (node == nullptr) return result;
    if (node->key < upper_bound) {
        // Traverse left subtree
        vector<V> left = getInorderWithUpperBound(node->left, upper_bound);
        result.insert(result.end(), left.begin(), left.end());
        // Visit current node
        result.push_back(node->value);
        // Traverse right subtree
        vector<V> right = getInorderWithUpperBound(node->right, upper_bound);
        result.insert(result.end(), right.begin(), right.end());
    } else {
        // Only need to check left subtree
        vector<V> left = getInorderWithUpperBound(node->left, upper_bound);
        result.insert(result.end(), left.begin(), left.end());
    }
    return result;
}

template <typename K, typename V>
vector<V> BST<K, V>::getInorderWithLowerBound(Node* node, const K& lower_bound) const {
    vector<V> result;
    if (node == nullptr) return result;
    if (node->key > lower_bound) {
        // Traverse left subtree
        vector<V> left = getInorderWithLowerBound(node->left, lower_bound);
        result.insert(result.end(), left.begin(), left.end());
        // Visit current node
        result.push_back(node->value);
        // Traverse right subtree
        vector<V> right = getInorderWithLowerBound(node->right, lower_bound);
        result.insert(result.end(), right.begin(), right.end());
    } else {
        // Only need to check right subtree
        vector<V> right = getInorderWithLowerBound(node->right, lower_bound);
        result.insert(result.end(), right.begin(), right.end());
    }
    return result;
}

