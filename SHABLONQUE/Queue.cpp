#include <iostream>
 
#include "Queue.h"
 
//Shkolnikov Fedor
//13501/4 11.04.2015
//The task was to create a template of queue without using STL libiary.
//Unfortunately i maked this one a bit later than i have to,hope that this will not the point to refuse you check my work :333
int main()
{
        try
        {
        Queue<int> Queue;
        Queue.enqueue(1);
        Queue.enqueue(1488);
		Queue.enqueue(2);
        Queue.enqueue(228);
		Queue.enqueue(3);
		std::cout<<"Default queue: ";
        Queue.print();
		std::cout<<"First element: "<<Queue.front()<<'\n';
		std::cout<<"Last element: "<<Queue.back()<<'\n';
        Queue.dequeue();
		std::cout<<"After action: ";
        Queue.print();
		std::cout<<"First element: "<<Queue.front()<<'\n';
		std::cout<<"Last element: "<<Queue.back()<<'\n';
        }
        catch(const std::string& e)
        {
             std::cout<<e<<'\n';
        }
		system("pause");
}