#include <iostream>
#include "Node.h"
using  namespace  std;

template <class U>
class SLL {
    
    Node<U> * headPtr;
    int size;
    
    public:
    // default constructor
    SLL()
    {
        headPtr = NULL;
        size = 0;
    }

    // destructor    
    ~SLL()
    {
        Node<U> * dest = headPtr;
        while(dest != NULL)
        {
            Node<U> * temp = dest->next;
            delete dest;
            dest = temp;
        }
    }
    
    Node<U>* getHeadPtr()
    {
        return headPtr;
    }
    
    // insert (item1, item2) to the list
    void insert(U item1, U item2)
    {
        Node<U> * newPtr = new Node<U>;
        newPtr->SSN = item1;  
        newPtr->name = item2;
        newPtr->next = NULL;   
        if(headPtr == NULL)
        {
            headPtr = newPtr;   
        }   
        else
        {     
            Node<U> * temp = headPtr;     
            while(temp->next != NULL)
            {        
                temp = temp->next;     
            }     
            temp->next = newPtr;   
        }
    }
    
    // if find the item1 value, return the pointer to the node
    // otherwise, return nullptr
    Node<U>* search(U item1)
    {
        Node<U> * temp = headPtr; 

        if(headPtr == NULL)
        {
            return NULL;
        }

        while(temp != NULL)
        {
            if(temp->SSN == item1)
            {
                return temp;
            }
            temp = temp->next; 
        }

        return NULL;
    }
    
    // remove the node with key value: item1
    bool remove(U item1)
    {
        Node<U> * temp = headPtr;

        if(headPtr == NULL)
        {
            return false;
        }

        if(temp->SSN == item1)
        {
            headPtr = headPtr->next;
            return true;
        }

        while(temp->next != NULL)
        {
            if(temp->next->SSN == item1)
            {
                temp->next = temp->next->next;
                return true;
            }
            temp = temp->next; 
        }

        return false;
    }
    
    int getSize()
    {    
        return size;
    }
    
    // display the SSN values of each node in the linked list
    void display()
    {
        Node<U>* temp;
        temp = headPtr;
        while (temp!= NULL)
        {
            cout << temp->SSN << endl;
            temp = temp->next;
        }
    }
};


