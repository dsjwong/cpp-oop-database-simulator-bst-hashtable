/* TODO: Implement the functions for the class Table and Table::Filter */
/* Write your code below */

template <typename T>
void Table::addPrimitiveColumn(string name, const T& default_value) {
    // Add the default field to default_field
    default_fields.insert(name, new PrimitiveField<T>(name, default_value));
    // Add the index tree for this field
    index_trees.insert(name, new BST<T, HashTable<Entry*>>());
}

template <typename T>
void Table::addListColumn(string name, const vector<T>& default_value) {
    // Add the default field to default_fields
    default_fields.insert(name, new ListField<T>(name, default_value));
    // Add the index tree for this field
    index_trees.insert(name, new BST<T, HashTable<Entry*>>());
}

void Table::addEntry(const Entry& entry) {
    // Add the entry pointer to entries
    Entry* entry_ptr = new Entry(entry);
    entries.insert(entry_ptr);
    // Store a copy of the fields BST for safe pointer access
    BST<string, BaseField*> entry_fields = entry_ptr->getFields();
    // For each field in default_fields
    vector<BaseField*> fields_vec = default_fields.getInorder();
    for (size_t i = 0; i < fields_vec.size(); ++i) {
        string field_name = fields_vec[i]->getName();
        BaseField** entry_field_ptr = entry_fields.get(field_name);
        BaseField* field_to_use = nullptr;
        if (entry_field_ptr) {
            field_to_use = *entry_field_ptr;
        } else {
            field_to_use = fields_vec[i]; 
        }
        // Update the index tree for this field
        BaseBST** index_tree_ptr = index_trees.get(field_name);
        if (index_tree_ptr && field_to_use) {
            field_to_use->handleAddEntryToIndexTree(*index_tree_ptr, entry_ptr);
        }
    }
}

Table& Table::operator=(const Table& other) {
    if (this != &other) {
        // Clean up current contents 
        for (BaseField* field : default_fields.getInorder()) delete field;
        for (BaseBST* tree : index_trees.getInorder()) delete tree;
        // Delete all Entry* in entries
        vector<Entry*> entry_vec = entries.to_vector();
        for (Entry* entry : entry_vec) {
            delete entry;
        }
        default_fields = BST<string, BaseField*>();
        index_trees = BST<string, BaseBST*>();
        entries = HashTable<Entry*>();

        // Deep copy entries 
        vector<Entry*> other_entries = other.entries.to_vector();
        for (Entry* entry : other_entries) {
            entries.insert(new Entry(*entry));
        }
        // Deep copy default_fields
        vector<BaseField*> other_fields = other.default_fields.getInorder();
        for (size_t i = 0; i < other_fields.size(); ++i) {
            BaseField* field = other_fields[i];
            default_fields.insert(field->getName(), field->clone());
        }
        // Deep copy index_trees 
        for (size_t i = 0; i < other_fields.size(); ++i) {
            BaseField* field = other_fields[i];
            string key = field->getName();
            BaseBST** tree_ptr = other.index_trees.get(key);
            if (tree_ptr) {
                index_trees.insert(key, (*tree_ptr)->clone());
            }
        }
    }
    return *this;
}

Table::Table(const Table& other) {
    // Deep copy entries 
    entries = HashTable<Entry*>();
    vector<Entry*> other_entries = other.entries.to_vector();
    for (Entry* entry : other_entries) {
        entries.insert(new Entry(*entry));
    }
    // Deep copy default_fields 
    vector<BaseField*> other_fields = other.default_fields.getInorder();
    for (size_t i = 0; i < other_fields.size(); ++i) {
        BaseField* field = other_fields[i];
        default_fields.insert(field->getName(), field->clone());
    }
    // Deep copy index_trees 
    for (size_t i = 0; i < other_fields.size(); ++i) {
        BaseField* field = other_fields[i];
        string key = field->getName();
        BaseBST** tree_ptr = other.index_trees.get(key);
        if (tree_ptr) {
            index_trees.insert(key, (*tree_ptr)->clone());
        }
    }
}

Table::~Table() {
    // Delete all Entry* in entries
    vector<Entry*> entry_vec = entries.to_vector();
    for (Entry* entry : entry_vec) {
        delete entry;
    }
    // Delete all BaseField* in default_fields
    vector<BaseField*> fields_vec = default_fields.getInorder();
    for (BaseField* field : fields_vec) {
        delete field;
    }
    // Delete all BaseBST* in index_trees
    vector<BaseBST*> trees_vec = index_trees.getInorder();
    for (BaseBST* tree : trees_vec) {
        delete tree;
    }
}

template <typename T>
Table Table::Filter<T>::operator==(const T& value) const {
    Table result(*table); // Deep copy the table structure
    // Delete all Entry* in result.entries before clearing
    vector<Entry*> old_entries = result.entries.to_vector();
    for (Entry* entry : old_entries) {
        delete entry;
    }
    result.entries = HashTable<Entry*>();
    // Use index tree for fast lookup
    BaseBST** index_tree_ptr = table->index_trees.get(field_name);
    if (index_tree_ptr) {
        BST<T, HashTable<Entry*>>* tree = dynamic_cast<BST<T, HashTable<Entry*>>*>(*index_tree_ptr);
        if (tree) {
            HashTable<Entry*>* hashTable = tree->get(value);
            if (hashTable) {
                vector<Entry*> entries_vec = hashTable->to_vector();
                for (Entry* entry : entries_vec) {
                    result.entries.insert(new Entry(*entry));
                }
            }
        }
    }
    return result;
}