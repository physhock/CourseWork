#pragma once

#include <iostream>
#include <string>

template<class T>

class Queue
{

public:
	Queue():head(0), tail(0) {} //Constructor 
 
    ~Queue() //Destructor
        {
             while(head)
             {
                 tail=head->next;
                 delete head;
                 head=tail;
             }
        }	
 
        void enqueue(T val) //Add element
        {
                Node* Temp=new Node;
                Temp->elem=val;
                if(head==0)
                {
                        head=Temp;
                        tail=Temp;
                        return;
                }
                tail->next=Temp;
                tail=Temp;
        }
 
        void dequeue() //Delete element
        {
                if (empty())
                {
                        throw std::string("Queue is empty");
                }
                Node* delPtr=head;
                std::cout<<"Element "<< head->elem <<" is deleted from the queue\n";
                head=head->next;
                delete delPtr;
        }
 
        const T& front() const //Taking first el
        {
                if (empty())
                {
                        throw std::string("Queue is empty");
                }
                return head->elem;
        }
		 const T& back() const //Taking last one
        {
                if (empty())
                {
                        throw std::string("Queue is empty");
                }
                return tail->elem;
        }
 
        void print() const //Printing queue
        {
                if (empty())
                {
                        throw std::string("Queue is empty");
                }
                for(Node* ptr=head; ptr!=0; ptr=ptr -> next)
                        std::cout << ptr -> elem << ' ';
                std::cout << '\n';
        }
 
        bool empty() const //Check que 
        {
                return head==0;
        }
private:
        struct Node // Making struct 4 list
        {
			Node():next(0), elem(0) {}
                Node *next;
                T elem;
        };

        Node *head;
        Node *tail;

};
