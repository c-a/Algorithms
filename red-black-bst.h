/* -*- Mode: C; indent-tabs-mode: nil; c-basic-offset: 2; tab-width: 2 -*-  */
/*
 * red-black-bst.h
 * Copyright (C) 2013 Carl-Anton Ingmarsson <c-a@boxen>
   *
 * Algorithms is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
   * 
 * Algorithms is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef _RED_BLACK_BST_H_
#define _RED_BLACK_BST_H_

#include <queue>
#include <ostream>
#include <sstream>

template<typename K, typename V, typename Compare>
class RedBlackBST
{
private:
  class Iterator;

public:
  typedef K value_type;
  typedef V keytype;
  typedef Compare keycompare;

  typedef Iterator const_iterator;

  explicit RedBlackBST(Compare compare = Compare()) : root_(0), compare_(compare) {}

  const_iterator begin() {
    return Iterator(this, min(root_));
  }

  const_iterator end() {
    return Iterator(this, 0);
  }

  void put(const keytype& key, const value_type& value) {
    root_ = put(root_, key, value);
    root_->color = BLACK;
  }

  const_iterator get(const keytype& key) {
    Node* x = root_;

    while (x)
    {
      int cmp = compare_(key, x->key);
      if (cmp < 0)
        x = x->left;
      else if (cmp > 0)
        x = x->right;
      else
        return Iterator(this, x);
    }

    return Iterator(this, 0);
  }

  void remove(const keytype& key) {
    if (root_ == 0)
      return;

    if (!isRed(root_->left) && !isRed(root_->right))
      root_->color = RED;
    root_ = remove(root_, key);
    if (root_ != 0)
      root_->color = BLACK;
  }

  void print(std::ostream& out) {

    std::queue<DFSNode> q;
    unsigned int current_depth = 0;

    if (root_ == 0)
      return;

    q.push(DFSNode(root_, 0));
    while (!q.empty()) {
      DFSNode n = q.front();
      Node* x = n.node;
      q.pop();

      if (n.depth > current_depth) {
        current_depth = n.depth;
        out << std::endl;
      }

      if (isRed(x->left)) {
        out << x->left->toString() << "|" << x->toString() << " ";
        if (x->left->left) {
          q.push(DFSNode(x->left->left, n.depth + 1));
          if (x->left->right)
            q.push(DFSNode(x->left->right, n.depth + 1));
        }
      }
      else {
        out << x->toString() << " ";
        if (x->left)
          q.push(DFSNode(x->left, n.depth + 1));
      }

      if (x->right)
        q.push(DFSNode(x->right, n.depth + 1));
    }
    out << std::endl;
  }

  bool isRedBlackBST() {
    return is23(root_) && isBalanced();
  }

private:

  enum
  {
    BLACK = 0,
    RED   = 1
  };

  class Node
  {
    public:
      keytype key;
      value_type value;
      Node *left, *right;
      unsigned int color : 1;

      Node(const keytype& key, const value_type& value, unsigned int color) :
        key(key), value(value), left(0), right(0), color(color) {}

      void flipColors() {
        unsigned int child_color;

        if (color == BLACK) {
          color = RED;
          child_color = BLACK;
        }
        else {
          color = BLACK;
          child_color = RED;
        }

        if (left)
          left->color = child_color;
        if (right)
          right->color = child_color;
      }

      Node* rotateLeft() {
        Node* x = right;
        right = x->left;
        x->left = this;
        x->color = color;
        color = RED;
        return x;
      }

      Node* rotateRight() {
        Node* x = left;
        left = x->right;
        x->right = this;
        x->color = color;
        color = RED;
        return x;
      }

      Node* moveRedLeft() {

        flipColors();
        if (isRed(right->left)) {
          right = right->rotateRight();
          return rotateLeft();
        }
        else
          return this;
      }

      Node* moveRedRight() {

        flipColors();
        if (isRed(left->left)) {
          return rotateRight();
        }
        else
          return this;
      }

      bool isLeaf() {
        return this->left == 0;
      }

      std::string toString() {
        std::stringstream str;

        str << key;
        if (color == BLACK)
          str << "b";
        else
          str << "r";
        return str.str();
      }

    private:

      Node(const Node& a);
  };

  class Iterator
  {
    public:
      Iterator() : bst_(0), node_(0) {};
      Iterator(RedBlackBST *bst, Node* node) : bst_(bst), node_(node) {};

      const value_type& operator*() {
        return node_->value;
      }

      bool operator!=(const Iterator& rhs) const {
        return node_ != rhs.node_;
      }

      Iterator& operator++() {
        node_ = bst_->greater(node_->key);
        return *this;
      }

    private:
      RedBlackBST* bst_;
      Node* node_;
  };
  friend class Iterator;

  struct DFSNode {
    DFSNode(Node* n, unsigned int d) : node(n), depth(d) {};

    Node* node;
    unsigned int depth;
  };

  Node* root_;
  keycompare compare_;

  static bool isRed(Node* x) {
    if (!x)
      return false;

    return x->color == RED;
  }

  static bool isTwoNode(Node* x) {
    if (!x)
      return false;

    return !isRed(x) && !isRed(x->left);
  }

  static Node* min(Node*x) {
    while (x->left != 0)
      x = x->left;

    return x;
  }

  Node* greater(const keytype& key) {
    return greater(root_, key);
  }

  Node* greater(Node* x, const keytype& key) {
    if (!x)
      return 0;

    int cmp = compare_(key, x->key);
    if (cmp < 0) {
      Node* g = greater(x->left, key);
      if (g)
        x = g;
    }
    else
      x = greater(x->right, key);

    return x;
  }

  Node* put(Node* x, const keytype& key, const value_type& value) {
    if (!x)
      return new Node(key, value, RED);

    int cmp = compare_(key, x->key);
    if (cmp < 0)
      x->left = put(x->left, key, value);
    else if (cmp > 0)
      x->right = put(x->right, key, value);
    else
      x->value = value;

    /* Right leaning red link and black left link */
    if (!isRed(x->left) && isRed(x->right)) {
      x =  x->rotateLeft();
    }

    /* Two left leaning red links in a row */
    if (isRed(x->left) && isRed(x->left->left)) {
      x =  x->rotateRight();
    }

    /* Split four nodes on the way up */
    if (isRed(x->left) && isRed(x->right)) {
      x->flipColors();
    }

    return x;
  }

  Node* remove(Node* x, const keytype& key) {
    if (!x)
      return 0;

    if (compare_(key, x->key) < 0) {

      if (isTwoNode(x->left)) {
        /* Move  into left child */
        x = x->moveRedLeft();
      }

      x->left = remove(x->left, key);
    }
    
    else {

      if (compare_(key, x->key) == 0 && x->right == 0) {
        if (x->left != 0)
          x->left->color = x->color;
        delete x;
        return x->left;
      }

      /* Can't remove black node */
      if (!isRed(x))
        x = x->rotateRight();

      /* Right child can't be two node since we're either going to remove
         key from there or the minimum value */
      if (isTwoNode(x->right)) {
        x = x->moveRedRight();
      }

      if (compare_(key, x->key) == 0) {
        Node *m = min(x->right);
        x->value = m->value;
        x->key = m->key;
        x->right = remove(x->right, m->key);
      }
      else
        x->right = remove(x->right, key);
    }

    if (isRed(x->right))
      x = x->rotateLeft();

    /* Right leaning red link and black left link */
    if (!isRed(x->left) && isRed(x->right))
      x =  x->rotateLeft();

    /* Two left leaning red links in a row */
    if (isRed(x->left) && isRed(x->left->left))
      x =  x->rotateRight();

    /* Split four nodes on the way up */
    if (isRed(x->left) && isRed(x->right))
      x->flipColors();

    return x;
  }

  bool is23(Node* x) {
    if (!x)
      return true;

    if (isRed(x->left) && isRed(x->left->left))
      return false;

    if (isRed(x->right))
      return false;

    return is23(x->left) && is23(x->right);
  }

  bool isBalanced() {
    return depth(root_) >= 0;
  }

  int depth(Node* x) {
    if (!x)
      return 0;

    int l = depth(x->left);
    if (l < 0)
      return l;
    int r = depth(x->right);
    if (r < 0)
      return r;
    if (l != r)
      return -1;

    return l + (x->color == BLACK ? 1 : 0);
  }
};

#endif // _RED_BLACK_BST_H_
