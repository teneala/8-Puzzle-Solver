//
//  search.cpp
//  8 Puzzle Solver
//
//  Created by Teneala Spencer on 10/28/17.
//  Copyright © 2017 Teneala Spencer. All rights reserved.
//

#include "search.hpp"
#include <iostream>
#include <chrono>
#include <algorithm>
#include <map>
#include <array>
using namespace std;

string val;
string genState[9];
string goal[9] = {"1", "2", "3", "4", "5", "6", "7", "8", "0"};
string temparr[9];


bool flag = true;
bool caught = false;

int counter = 0;
int sitch = 0;
int l = 0;
int j = 0;
int test = 1;



map<int , array<string, 9>> map1;




struct node
{
    string state[9];
    string path;
   
    node * next = NULL;
    
};

node * n = NULL;
node * head = NULL;
node * temp = NULL;
node * current = NULL;
node * check = NULL;
node * previous = NULL;


struct vis
{

    string map[9];

};

vis * vap = new vis[181440];

void puzzler:: inquire()
{
    int j = 0;

    cout << "Please enter numbers 0 - 8 for your puzzle. When finished please type 'done'. " << endl;
 
    
    
    while(cin>>val)
    {
        if(val == "done")
        {
            break;
        }
        
        else
            genState[j] = val;
            j++;
        
    }
 
    cout << endl << "You chose your intial state as the following: " << endl << endl;
 
    for( int i = 0; i < 9; i++)
        {
           cout << genState[i]; 
        }
 
    cout << endl << endl; 
    cout << "Please chose which search you would like to perform: " << endl << endl;
    cout << "1. Breadth First" << endl << "2. Depth First" << endl << endl;
    
    cin >> val;
    
    if(val == "1")
    {
        breadth();
    }
    
}



void puzzler::breadth()
{
   

    while(flag != false)
        
    {

        
        if((std::equal(std::begin(genState), std::end(genState), std::begin(goal))))
        {
            tell();
            break;
        }


        
    if( head == NULL)
    {
        n = new node;
        head = n;
        current = n;
        temp = n;
        previous = n;
        
        memcpy(n->state, genState, sizeof(n->state));
        
        for(int i = 0; i < 9; i++)
        {
            n -> path = n -> path + n -> state[i];
        }
        
        n -> path = n -> path + "\n";
        
        memcpy(vap[l].map, n->state, sizeof(vap[l].map));
      
        l++;
        counter++;
   
      
        swap();
        
        delete previous;
        previous = current ->next;
       
    }
    
        
    else if ( head != NULL)
        {
            
            
            current = current -> next;
         
            swap();
            
            delete previous;
            previous = current->next;


       
        }
        
 
    }
    

}

    
        
void puzzler::swap()
{
    for(sitch = 0; sitch < 9; sitch++)
    {
        if (current -> state[sitch] == "0")
        {
    
    switch(sitch)
            {
                case 0:
                    right();
                    down();
                    break;
                case 1:
                    down();
                    right();
                    left();
                    break;
                case 2:
                    down();
                    left();
                    break;
                case 3:
                    up();
                    down();
                    right();
                    break;
                case 4:
                    down();
                    up();
                    left();
                    right();
                    break;
                case 5:
                    down();
                    up();
                    left();
                    break;
                case 6:
                    up();
                    right();
                    break;
                case 7:
                    up();
                    left();
                    right();
                    break;
                case 8:
                    up();
                    left();
                    break;
            }
        }
    }
    

}

    
void puzzler::right()
{
    int i = 0;
    
    memcpy(temparr, current->state, sizeof(temparr));
    
    temparr[sitch] = temparr[sitch + 1];
    
    temparr[sitch + 1] = "0";
    
    if((std::equal(std::begin(temparr), std::end(temparr), std::begin(goal))))
    {
        tell();
        flag = false;
        
    }
    
    while( i <= l && caught != true)
    {
        if(std::equal(std::begin(temparr), std::end(temparr), std::begin(vap[i].map)))
        {
            caught = true;
            
        }
        
        
        i++;
        
    }
    

    

    if(caught == false)
        
    {
        memcpy(vap[l].map, temparr, sizeof(vap[l].map));
        l++;
        
        n = new node;
        memcpy(n->state, temparr, sizeof(n->state));
        n -> path = current -> path;
        for(int i = 0; i < 9; i++)
        {
            n -> path = n->path + n->state[i];
        }
        
        n -> path = n -> path + "\n";
        temp -> next = n;
        temp = n;
        counter++;
        
    }
    

    
    
    
    caught = false;
}



void puzzler::left()
{
    int i = 0;
    memcpy(temparr, current->state, sizeof(temparr));
  
    temparr[sitch] = temparr[sitch - 1];
    temparr[sitch - 1] = "0";
    
    if((std::equal(std::begin(temparr), std::end(temparr), std::begin(goal))))    {
        tell();
        flag = false;
        
    }
    
    
    while( i <= l && caught != true)
    {
        if(std::equal(std::begin(temparr), std::end(temparr), std::begin(vap[i].map)))
        {
            caught = true;
            
        }
        
        
        i++;
        
    }
    
    if(caught != true)
        
    {
        memcpy(vap[l].map, temparr, sizeof(vap[l].map));
        l++;
        
        n = new node;
        memcpy(n->state, temparr, sizeof(n->state));
        n -> path = current -> path;
        for(int i = 0; i < 9; i++)
        {
            n -> path = n->path +  n->state[i];
        }
        n -> path = n -> path + "\n";
        temp -> next = n;
        temp = n;
        counter++;
    
    }

    caught = false;
}


void puzzler::down()
{
    memcpy(temparr, current->state, sizeof(temparr));
    temparr[sitch] = temparr[sitch + 3];
    temparr[sitch + 3] = "0";
    int i = 0;
    
    if((std::equal(std::begin(temparr), std::end(temparr), std::begin(goal))))    {
        tell();
        flag = false;
        
    }
    
    
    
    while( i <= l && caught != true)
    {
        if(std::equal(std::begin(temparr), std::end(temparr), std::begin(vap[i].map)))
        {
            caught = true;
            
        }
        
    
        i++;
        
    }

        
    
    

    
    if(caught != true)
        
    {
        memcpy(vap[l].map, temparr, sizeof(vap[l].map));
        l++;
        
        n = new node;
        memcpy(n->state, temparr, sizeof(n->state));
        n -> path = current -> path;
        for(int i = 0; i < 9; i++)
        {
            n -> path = n->path +  n->state[i];
        }
        n -> path = n -> path + "\n";
        temp -> next = n;
        temp = n;
        counter++;
    
    }
    

    
    caught = false;
}
        
        
        
        
void puzzler::up()
{
    int i = 0;
    
    memcpy(temparr, current->state, sizeof(temparr));
    temparr[sitch] = temparr[sitch - 3];
    temparr[sitch - 3] = "0";
    
    if((std::equal(std::begin(temparr), std::end(temparr), std::begin(goal))))    {
        
        tell();
        flag = false;
        
    }
    
    while( i <= l && caught != true)
    {
        if(std::equal(std::begin(temparr), std::end(temparr), std::begin(vap[i].map)))
        {
            caught = true;
            
        }
        
        
        i++;
        
    }

    
    if(caught == false)
        
    {
        memcpy(vap[l].map, temparr, sizeof(vap[l].map));
        l++;
        
        n = new node;
        memcpy(n->state, temparr, sizeof(n->state));
        
        
        n -> path = current -> path;
        
        for(int i = 0; i < 9; i++)
        {
            n -> path = n->path + n->state[i];
        }
        n -> path = n -> path + "\n";
        temp -> next = n;
        temp = n;
        counter++;
        
    }
    
    

    
    caught = false;
}


void puzzler::tell()
{
    cout << endl << endl << "The computer found a solution!" << endl << endl;
    cout << "Number of nodes generated: " << counter << endl;

    

    cout << endl << endl << "The path it traveled to find the goal state is as follows: " << endl << endl << n->path;
    
    

    
   }
    
        

puzzler::puzzler()
{
    
}

puzzler::~puzzler()
{
    
}


      
        
        

