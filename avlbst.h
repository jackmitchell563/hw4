#ifndef AVLBST_H
#define AVLBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include "bst.h"

struct KeyError { };

/**
* A special kind of node for an AVL tree, which adds the balance as a data member, plus
* other additional helper functions. You do NOT need to implement any functionality or
* add additional data members or helper functions.
*/
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int8_t getBalance () const;
    void setBalance (int8_t balance);
    void updateBalance(int8_t diff);

    // Getters for parent, left, and right. These need to be redefined since they
    // return pointers to AVLNodes - not plain Nodes. See the Node class in bst.h
    // for more information.
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int8_t balance_;    // effectively a signed char
};

/*
  -------------------------------------------------
  Begin implementations for the AVLNode class.
  -------------------------------------------------
*/

/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), balance_(0)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the balance of a AVLNode.
*/
template<class Key, class Value>
int8_t AVLNode<Key, Value>::getBalance() const
{
    return balance_;
}

/**
* A setter for the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setBalance(int8_t balance)
{
    balance_ = balance;
}

/**
* Adds diff to the balance of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::updateBalance(int8_t diff)
{
    balance_ += diff;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that our node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


/*
  -----------------------------------------------
  End implementations for the AVLNode class.
  -----------------------------------------------
*/


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);

    // Add helper functions here
    virtual void insertFix(AVLNode<Key, Value>* p, AVLNode<Key,Value>* n);
    virtual void removeFix(AVLNode<Key, Value>* n, int diff);
    virtual void rotateRight(AVLNode<Key, Value>* n);
    virtual void rotateLeft(AVLNode<Key, Value>* n);

};

/*
 * Recall: If key is already in the tree, you should 
 * overwrite the current value with the updated value.
 */
template<class Key, class Value>
void AVLTree<Key, Value>::insert(const std::pair<const Key, Value> &new_item)
{
    // TODO

    // // // vvv old code, don't want to delete the it because i wanted to document my struggle
    // AVLNode<Key, Value>* newnode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    // // AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);
    // // Node<Key, Value>* curr = this->root_;
    // Node<Key, Value>* n1 = BinarySearchTree<Key, Value>::internalFind(new_item.first);
    // int alreadyexisted = 0;
    // if(n1) alreadyexisted = 1;
    // this->BinarySearchTree<Key, Value>::insert(new_item);
    // Node<Key, Value>* n = this->BinarySearchTree<Key, Value>::internalFind(new_item.first);
    // if(!alreadyexisted){
    //     if(n->getParent()){
    //         if(abs(static_cast<AVLNode<Key, Value>*>(n)->getParent()->getBalance()) == 1) static_cast<AVLNode<Key, Value>*>(n)->getParent()->setBalance(0);
    //         else if(!static_cast<AVLNode<Key, Value>*>(n)->getParent()->getBalance()){
    //             if(n->getParent()->getRight() == n) static_cast<AVLNode<Key, Value>*>(n)->getParent()->setBalance(1);
    //             else if(n->getParent()->getLeft() == n) static_cast<AVLNode<Key, Value>*>(n)->getParent()->setBalance(-1);
    //             insertFix(static_cast<AVLNode<Key, Value>*>(n)->getParent(), static_cast<AVLNode<Key, Value>*>(n));
    //         }
    //     }
    // }
        // Node<Key, Value>* n1 = BinarySearchTree<Key, Value>::internalFind(new_item.first);
        // int alreadyexisted = 0;
        // if(n1) alreadyexisted = 1;
        // std::cout << "Existed: " << alreadyexisted << std::endl;
        // BinarySearchTree<Key, Value>::insert(new_item);
        // AVLNode<Key, Value>* n = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::internalFind(new_item.first));
        // if(!alreadyexisted){
        //     n->setBalance(10);
        //     std::cout << n->getBalance() << std::endl;
        //     std::cout << 123456789 << std::endl;
        //     if(n->getParent()){
        //         std::cout << 987654321 << std::endl;
        //         if(abs(n->getParent()->getBalance()) == 1) n->getParent()->setBalance(0);
        //         else if(!n->getParent()->getBalance()){
        //             if(n->getParent()->getRight() == n) n->getParent()->setBalance(1);
        //             else if(n->getParent()->getLeft() == n) n->getParent()->setBalance(-1);
        //             std::cout << n->getBalance() << " " << n->getParent()->getBalance() << std::endl;
        //             insertFix(n->getParent(), n);
        //         }
        //     }
        // }
        // std::cout << "Reached end of insert function" << std::endl;
    
    /*
    i'm super stuck, so i'm just gonna write out my thoughts
    since the root_ is a Node*, it should be able to point to AVLNodes
    the question is, how do you have the root_ point to an AVLNode and then get AVLNode functionality like getBalance?

    
    edit: finally got it, and it turned out it was an issue with my rotations (static casting was the way to go after all)
    */

    AVLNode<Key, Value>* newnode = new AVLNode<Key, Value>(new_item.first, new_item.second, nullptr);
    AVLNode<Key, Value>* curr = static_cast<AVLNode<Key, Value>*>(this->root_);

    if(this->empty()){
        this->root_ = newnode;
        return;
    }
    while(1){
        if(curr->getKey() == new_item.first){ // if key already exists
            curr->setValue(new_item.second);
            delete newnode;
            return;
        } else if(curr->getKey() < new_item.first){ // current node's key is less than held key, so go to higher-value position
            if(curr->getRight()) curr = curr->getRight();
            else{
                // std::cout << "Trying to insert right: " << newnode->getKey() << std::endl;
                // this->print();
                curr->setRight(newnode);
                newnode->setParent(curr);
                if(abs(curr->getBalance()) == 1) curr->setBalance(0);
                else if(!curr->getBalance()){
                    curr->setBalance(1);
                    insertFix(curr, newnode);
                }
                return;
            }
        } else if(curr->getKey() > new_item.first){ // current node's key is greater than held key, so go to lower-value position
            if(curr->getLeft()) curr = curr->getLeft();
            else{
                // std::cout << "Trying to insert Left: " << newnode->getKey() << std::endl;
                // this->print();
                curr->setLeft(newnode);
                newnode->setParent(curr);
                // this->print();
                // std::cout << std::to_string(curr->getBalance()) << " is the balance of the parent" << std::endl;
                if(abs(curr->getBalance()) == 1){
                    curr->setBalance(0);
                    // std::cout << std::to_string(curr->getBalance()) << " is the balance of the parent after it was 1 or -1 (should be 0)" << std::endl;
                }
                else if(!curr->getBalance()){
                    curr->setBalance(-1);
                    // std::cout << "insert fix called" << std::endl;
                    insertFix(curr, newnode);
                }
                return;
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::insertFix(AVLNode<Key, Value>* p, AVLNode<Key, Value>* n){
    if(!p or !p->getParent()){
        // std::cout << "aborting insert fix" << std::endl;
        return;
    }
    AVLNode<Key, Value>* g = p->getParent();
    // std::cout << g->getKey() << " " << p->getKey() << " " << n->getKey() << std::endl;
    if(g->getLeft() == p){ // p is left child of g
        g->updateBalance(-1);
        if(!g->getBalance()) return;
        else if(g->getBalance() == -1) insertFix(g, p);
        else if(g->getBalance() == -2){
            if(p->getLeft() and p->getLeft() == n){ // zig-zig left
                rotateRight(g);
                p->setBalance(0);
                g->setBalance(0);
            } else if(p->getRight() and p->getRight() == n){ // zig-zag left-right
                rotateLeft(p);
                rotateRight(g);
                if(n->getBalance() == -1){
                    p->setBalance(0);
                    g->setBalance(1);
                    n->setBalance(0);
                } else if(!n->getBalance()){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                } else if(n->getBalance() == 1){
                    p->setBalance(-1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    } else{ // p is right child of g
        g->updateBalance(1);
        if(!g->getBalance()) return;
        else if(g->getBalance() == 1) insertFix(g, p);
        else if(g->getBalance() == 2){
            if(p->getRight() and p->getRight() == n){ // zig-zig right
                rotateLeft(g);
                p->setBalance(0);
                g->setBalance(0);
            } else if(p->getLeft() and p->getLeft() == n){ // zig-zag right-left
                rotateRight(p);
                rotateLeft(g);
                if(n->getBalance() == 1){
                    p->setBalance(0);
                    g->setBalance(-1);
                    n->setBalance(0);
                } else if(!n->getBalance()){
                    p->setBalance(0);
                    g->setBalance(0);
                    n->setBalance(0);
                } else if(n->getBalance() == -1){
                    p->setBalance(1);
                    g->setBalance(0);
                    n->setBalance(0);
                }
            }
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateRight(AVLNode<Key,Value>* n){
    if(!n->getLeft()) return;
    AVLNode<Key,Value>* lc = n->getLeft();
    if(n->getParent()){
        // std::cout << "g has parent" << std::endl;
        lc->setParent(n->getParent());
        if(n->getParent()->getLeft() == n) n->getParent()->setLeft(lc);
        else if(n->getParent()->getRight() == n) n->getParent()->setRight(lc);
    } else{
        lc->setParent(nullptr);
        this->root_ = lc;
    }
    n->setParent(lc);
    if(lc->getRight()){
        // std::cout << "p has right child" << std::endl;
        n->setLeft(lc->getRight());
        lc->getRight()->setParent(n);
    } else n->setLeft(nullptr);
    lc->setRight(n);
    // std::cout << "finished rotating right" << std::endl;
    // this->print();
}

template<class Key, class Value>
void AVLTree<Key, Value>::rotateLeft(AVLNode<Key,Value>* n){
    if(!n->getRight()) return;
    AVLNode<Key,Value>* rc = n->getRight();
    if(n->getParent()){
        rc->setParent(n->getParent());
        if(n->getParent()->getLeft() == n) n->getParent()->setLeft(rc);
        else if(n->getParent()->getRight() == n) n->getParent()->setRight(rc);
    } else{
        rc->setParent(nullptr);
        this->root_ = rc;
    }
    n->setParent(rc);
    if(rc->getLeft()){
        n->setRight(rc->getLeft());
        rc->getLeft()->setParent(n);
    } else n->setRight(nullptr);
    rc->setLeft(n);
    // std::cout << "finished rotating left" << std::endl;
    // this->print();
}

/*
 * Recall: The writeup specifies that if a node has 2 children you
 * should swap with edecessor and then remove.
 */
template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    // TODO
    AVLNode<Key, Value>* toremove = static_cast<AVLNode<Key, Value>*>(this->internalFind(key));
    if(!toremove) return;
    if(toremove->getLeft() and toremove->getRight()) nodeSwap(toremove, static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(toremove)));
    int diff = 0;
    AVLNode<Key, Value>* p = toremove->getParent();
    if(p){
      if(p->getLeft() == toremove) diff = 1;
      else if(p->getRight() == toremove) diff = -1;
    }
    if(toremove->getLeft() and toremove->getRight()){ // 2 children
        // nodeSwap(toremove, static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key, Value>::predecessor(toremove)));
        if(toremove->getLeft()){
            if(toremove->getParent() and toremove->getParent()->getLeft() == toremove) toremove->getParent()->setLeft(toremove->getLeft()); // if toremove is left child of its parent
            else if(toremove->getParent() and toremove->getParent()->getRight() == toremove) toremove->getParent()->setRight(toremove->getLeft()); // if toremove is right child of its parent
            else this->root_ = toremove->getLeft(); // no parent
            if(toremove->getParent()) toremove->getLeft()->setParent(toremove->getParent()); // update promoted child's parent
            else toremove->getLeft()->setParent(nullptr); // toremove has no parent, so the promoted child is also an orphan
        } else if(toremove->getRight()){
            if(toremove->getParent() and toremove->getParent()->getLeft() == toremove) toremove->getParent()->setLeft(toremove->getRight()); // if toremove is left child of its parent
            else if(toremove->getParent() and toremove->getParent()->getRight() == toremove) toremove->getParent()->setRight(toremove->getRight()); // if toremove is right child of its parent
            else this->root_ = toremove->getRight(); // no parent
            if(toremove->getParent()) toremove->getRight()->setParent(toremove->getParent()); // update promoted child's parent
            else toremove->getRight()->setParent(nullptr); // toremove has no parent, so the promoted child is also an orphan
        } else{ // no children
            if(toremove->getParent() and toremove->getParent()->getLeft() == toremove) toremove->getParent()->setLeft(nullptr); // if toremove is left child of its parent
            else if(toremove->getParent() and toremove->getParent()->getRight() == toremove) toremove->getParent()->setRight(nullptr); // if toremove is right child of its parent
            else this->root_ = nullptr; // no parent and no children, so it's the last node
        }
    } else if(toremove->getLeft()){ // same logic as above
        if(toremove->getParent() and toremove->getParent()->getLeft() == toremove) toremove->getParent()->setLeft(toremove->getLeft());
        else if(toremove->getParent() and toremove->getParent()->getRight() == toremove) toremove->getParent()->setRight(toremove->getLeft());
        else this->root_ = toremove->getLeft();
        if(toremove->getParent()) toremove->getLeft()->setParent(toremove->getParent());
        else toremove->getLeft()->setParent(nullptr);
    } else if(toremove->getRight()){
        if(toremove->getParent() and toremove->getParent()->getLeft() == toremove) toremove->getParent()->setLeft(toremove->getRight());
        else if(toremove->getParent() and toremove->getParent()->getRight() == toremove) toremove->getParent()->setRight(toremove->getRight());
        else this->root_ = toremove->getRight();
        if(toremove->getParent()) toremove->getRight()->setParent(toremove->getParent());
        else toremove->getRight()->setParent(nullptr);
    } else{
        if(toremove->getParent() and toremove->getParent()->getLeft() == toremove) toremove->getParent()->setLeft(nullptr);
        else if(toremove->getParent() and toremove->getParent()->getRight() == toremove) toremove->getParent()->setRight(nullptr);
        else this->root_ = nullptr;
    }
    delete toremove;
    removeFix(p, diff);
}

template<class Key, class Value>
void AVLTree<Key, Value>::removeFix(AVLNode<Key, Value>* n, int diff){
    // std::cout << "removefix called" << std::endl; // dead end; it's being called fine
    if(!n) return;
    int ndiff = 0;
    AVLNode<Key, Value>* p = n->getParent();
    if(p){
      if(p->getLeft() == n) ndiff = 1;
      else if(p->getRight() == n) ndiff = -1;
    }
    if(diff == -1){
        AVLNode<Key, Value>* c = n->getLeft();
        if(n->getBalance() + diff == -2){
            if(c->getBalance() == -1){ // zig-zig
                rotateRight(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            } else if(!c->getBalance()){ // zig-zig
                rotateRight(n);
                n->setBalance(-1);
                c->setBalance(1);
            } else if(c->getBalance() == 1){ // zig-zag
                AVLNode<Key, Value>* g = c->getRight();
                rotateLeft(c);
                rotateRight(n);
                if(g->getBalance() == 1){
                    n->setBalance(0);
                    c->setBalance(-1);
                    g->setBalance(0);
                } else if(!g->getBalance()){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                } else if(g->getBalance() == -1){
                    n->setBalance(1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        } else if(n->getBalance() + diff == -1){
            n->setBalance(-1);
        } else if(n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    } else if(diff == 1){
        AVLNode<Key, Value>* c = n->getRight();
        if(n->getBalance() + diff == 2){
            if(c->getBalance() == 1){ // zig-zig
                rotateLeft(n);
                n->setBalance(0);
                c->setBalance(0);
                removeFix(p, ndiff);
            } else if(!c->getBalance()){ // zig-zig
                rotateLeft(n);
                n->setBalance(1);
                c->setBalance(-1);
            } else if(c->getBalance() == -1){ // zig-zag
                AVLNode<Key, Value>* g = c->getLeft();
                rotateRight(c);
                rotateLeft(n);
                if(g->getBalance() == -1){
                    n->setBalance(0);
                    c->setBalance(1);
                    g->setBalance(0);
                } else if(!g->getBalance()){
                    n->setBalance(0);
                    c->setBalance(0);
                    g->setBalance(0);
                } else if(g->getBalance() == 1){
                    n->setBalance(-1);
                    c->setBalance(0);
                    g->setBalance(0);
                }
                removeFix(p, ndiff);
            }
        } else if(n->getBalance() + diff == 1){
            n->setBalance(1);
        } else if(n->getBalance() + diff == 0){
            n->setBalance(0);
            removeFix(p, ndiff);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int8_t tempB = n1->getBalance();
    n1->setBalance(n2->getBalance());
    n2->setBalance(tempB);
}


#endif
