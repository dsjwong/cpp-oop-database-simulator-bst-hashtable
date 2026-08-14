/* TODO: Implement the functions for the class HashTable */
/* Write your code below */

template <typename T>
HashTable<T>::HashTable(int base_exponent, double max_load_factor) {
    head_node = new TableNode;
    head_node->exponent_size = base_exponent;
    head_node->table_size = 0;
    int num_buckets = 1 << base_exponent;
    head_node->table = new vector<T>[num_buckets];
    head_node->next = nullptr;
    this->max_load_factor = max_load_factor;
    total_size = 0;
    cur_node = head_node;
}

template <typename T>
HashTable<T>::~HashTable() {
    TableNode* node = head_node;
    while (node != nullptr) {
        TableNode* next = node->next;
        delete[] node->table;
        delete node;
        node = next;
    }
}

template <typename T>
HashTable<T>& HashTable<T>::operator=(const HashTable<T>& other) {
    if (this != &other) {
        // Clean up current contents
        TableNode* node = head_node;
        while (node != nullptr) {
            TableNode* next = node->next;
            delete[] node->table;
            delete node;
            node = next;
        }
        head_node = nullptr;
        cur_node = nullptr;
        total_size = 0;

        // Deep copy 
        max_load_factor = other.max_load_factor;
        TableNode* other_node = other.head_node;
        TableNode* prev_new_node = nullptr;
        while (other_node != nullptr) {
            TableNode* new_node = new TableNode;
            new_node->exponent_size = other_node->exponent_size;
            new_node->table_size = other_node->table_size;
            int num_buckets = 1 << new_node->exponent_size;
            new_node->table = new vector<T>[num_buckets];
            for (int i = 0; i < num_buckets; ++i) {
                new_node->table[i] = other_node->table[i];
            }
            new_node->next = nullptr;
            if (prev_new_node == nullptr) {
                head_node = new_node;
            } else {
                prev_new_node->next = new_node;
            }
            prev_new_node = new_node;
            other_node = other_node->next;
        }
        cur_node = prev_new_node;
        total_size = other.total_size;
    }
    return *this;
}

template <typename T>
HashTable<T>::HashTable(const HashTable<T>& other) {
    // Initialize members 
    head_node = nullptr;
    cur_node = nullptr; 
    total_size = 0;
    max_load_factor = other.max_load_factor;
    // Copy all elements from other 
    TableNode* other_node = other.head_node; 
    TableNode* prev_new_node = nullptr;
    while (other_node != nullptr) {
        TableNode* new_node = new TableNode;
        new_node->exponent_size = other_node->exponent_size;
        new_node->table_size = other_node->table_size;
        int num_buckets = 1 << new_node->exponent_size;
        new_node->table = new vector<T>[num_buckets];
        for (int i = 0; i < num_buckets; ++i) {
            new_node->table[i] = other_node->table[i];
        }
        new_node->next = nullptr;
        if (prev_new_node == nullptr) {
            head_node = new_node;
        } else { 
            prev_new_node->next = new_node;
        }
        prev_new_node = new_node;
        other_node = other_node->next;
    }
    cur_node = prev_new_node;
    total_size = other.total_size;
}

template <typename T>
bool HashTable<T>::exists(const T& value) const {
    TableNode* node = head_node;
    while (node != nullptr) {
        int num_buckets = 1 << node->exponent_size;
        int idx = pa3_hash(value) % num_buckets;
        const vector<T>& bucket = node->table[idx];
        for (size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i] == value) {
                return true;
            }
        }
        node = node->next;
    }
    return false;
}

template <typename T>
bool HashTable<T>::insert(const T& value) {
    // Check if value already exists
    if (exists(value)) return false;
    // Check load factor before insertion
    int num_buckets = 1 << cur_node->exponent_size;
    double load_factor = static_cast<double>(cur_node->table_size) / num_buckets;
    if (load_factor >= max_load_factor) {
        // Create new TableNode with double the buckets
        TableNode* new_node = new TableNode;
        new_node->exponent_size = cur_node->exponent_size + 1;
        int new_num_buckets = 1 << new_node->exponent_size;
        new_node->table = new vector<T>[new_num_buckets];
        new_node->table_size = 0;
        new_node->next = nullptr;
        // Link new node
        cur_node->next = new_node;
        cur_node = new_node;
        num_buckets = new_num_buckets;
    }
    // Insert value 
    int idx = pa3_hash(value) % num_buckets;
    cur_node->table[idx].push_back(value);
    cur_node->table_size++;
    total_size++;
    return true;
}

template <typename T>
bool HashTable<T>::remove(const T& value) {
    TableNode* node = head_node;
    TableNode* prev = nullptr;
    while (node != nullptr) {
        int num_buckets = 1 << node->exponent_size;
        int idx = pa3_hash(value) % num_buckets;
        vector<T>& bucket = node->table[idx];
        for (size_t i = 0; i < bucket.size(); ++i) {
            if (bucket[i] == value) {
                // Found value, remove it
                bucket.erase(bucket.begin() + i);
                node->table_size--;
                total_size--;
                // If node is not head_node and becomes empty, remove node from list
                if (node != head_node && node->table_size == 0) {
                    prev->next = node->next;
                    if (cur_node == node) cur_node = prev;
                    delete[] node->table;
                    delete node;
                }
                return true;
            }
        }
        prev = node;
        node = node->next;
    }
    return false;
}

template <typename T>
vector<T> HashTable<T>::to_vector() const {
    vector<T> result;
    TableNode* node = head_node;
    while (node != nullptr) {
        int num_buckets = 1 << node->exponent_size;
        for (int i = 0; i < num_buckets; ++i) {
            const vector<T>& bucket = node->table[i];
            result.insert(result.end(), bucket.begin(), bucket.end());
        }
        node = node->next;
    }
    return result;
}





