#ifndef TREEMAP_H
#define TREEMAP_H

template <typename K, typename V>
struct treemap_t
{

  // Pair_t structure
  struct pair_t
  {
    K key;
    V value;
  };

  // Node_t structure (child of Pair_t)
  struct node_t : pair_t
  {
    node_t *parent;
    node_t *left;
    node_t *right;

    node_t(node_t *parent)
        : parent{parent}, left{nullptr}, right{nullptr} {};
  };

  // Fields and constructor for treemap
  node_t *root;
  treemap_t()
      : root{nullptr} {};

  node_t *lookup(node_t **pcur, node_t *parent, const K *key, bool create)
  {
    if (*pcur == nullptr)
    {
      if (create)
      {
        *pcur = new node_t(parent);
        (*pcur)->key = *key;
        return *pcur;
      }
      return nullptr;
    }
    if (*key < (*pcur)->key)
    {
      return lookup(&(*pcur)->left, *pcur, key, create);
    }
    else if (*key > (*pcur)->key)
    {
      return lookup(&(*pcur)->right, *pcur, key, create);
    }
    else
    {
      return *pcur;
    }
  }

  void set_at(const K key, const V value)
  {
    node_t *node = lookup(&root, nullptr, &key, true);
    if (node != nullptr)
    {
      node->value = value;
    }
  };

  V at(const K key)
  {
    node_t *node = lookup(&root, nullptr, &key, false);

    if (node != nullptr)
    {
      return node->value;
    }
    else
    {
      std::cout << "Key not in tree" << std::endl;
      exit(-1);
    }
  };

  void display()
  {
    display_helper(root, 0);
  }

  void display_helper(node_t *current, int depth)
  {
    if (current == nullptr)
    {
      return;
    }

    display_helper(current->left, depth + 1);

    for (int i = 0; i < depth; i++)
    {
      std::cout << " ";
    }
    std::cout << "(" << current->key << "," << current->value << ")" << std::endl;

    display_helper(current->right, depth + 1);
  }

  struct iterator_t
  {
    node_t *cur;

    iterator_t(node_t *root)
    {
      cur = root;
      while (cur != nullptr && cur->left != nullptr)
      {
        cur = cur->left;
      }
    }

    void next()
    {
      if (cur->right)
      {
        cur = cur->right;
        while (cur->left)
        {
          cur = cur->left;
        }
      }
      else
      {
        while (cur->parent && cur == cur->parent->right)
        {
          cur = cur->parent;
        }
        cur = cur->parent;
      }
    }
  };

  iterator_t begin()
  {
    return iterator_t(root);
  }
};

#endif