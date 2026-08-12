/* TODO: Implement the functions for the subclasses of BaseField */
/* Write your code below */

template <typename T>
void PrimitiveField<T>::handleAddEntryToIndexTree(BaseBST* index_tree, Entry* entry) const {
    BST<T, HashTable<Entry*>>* tree = dynamic_cast<BST<T, HashTable<Entry*>>*>(index_tree);
    if (!tree) return;
    const T& key = this->getValue();
    HashTable<Entry*>* hashTable = tree->get(key);
    if (!hashTable) {
        HashTable<Entry*> newTable;
        newTable.insert(entry);
        tree->insert(key, newTable);
    } else {
        hashTable->insert(entry);
    }
}

template <typename T>
void ListField<T>::handleAddEntryToIndexTree(BaseBST* index_tree, Entry* entry) const {
    BST<T, HashTable<Entry*>>* tree = dynamic_cast<BST<T, HashTable<Entry*>>*>(index_tree);
    if (!tree) return;
    for (const T& key : this->values) {
        HashTable<Entry*>* hashTable = tree->get(key);
        if (!hashTable) {
            HashTable<Entry*> newTable;
            newTable.insert(entry);
            tree->insert(key, newTable);
        } else {
            hashTable->insert(entry);
        }
    }
}

