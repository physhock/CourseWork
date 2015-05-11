#pragma once

#include <iostream>
#include <string>



template <class T> 
class IQueue 
{
public:
// добавить в хвост
virtual void put(const T& elem) = 0;
// взять из головы
virtual T take() = 0;
// получить элемент по номеру 0...size-1,
// 0 это голова, size-1 это хвост
virtual T get(int i) const = 0;
// узнать размер очереди
virtual int size() const = 0;
};

template<class T>
class Queue:
	public IQueue<T>
{
	Queue():head(0), tail(0), count(0) {} //Constructor 
 
    ~Queue() //Destructor
        {
             while(head)
             {
                 tail=head->next;
                 delete head;
                 head=tail;
             }
        }	

        void put(T val) //Add element
        {
                Node *Temp=new Node;
                Temp->elem=val;
                if(head==0)
                {
                        head=Temp;
                        tail=Temp;
                        return;
                }
                tail->next=Temp;
                tail=Temp;
				size ++;
        }
 
        void take() //Delete element
        {
                Node *delPtr=head;
                head=head->next;
                delete delPtr;
        }
 
		const T& get(int i) const
		{
			if (i > count)
				return tail->elem;
			else
				return head->elem;
		}

		int size() const
		{
			return (count+1);
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
		int count;
		

};
