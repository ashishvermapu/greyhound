/* 
 * File:   linkstore.h
 * Author: ashish
 *
 * Created on 6 July, 2011, 5:20 PM
 */

#ifndef _LINKSTORE_H
#define	_LINKSTORE_H

#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

struct linkqueue
{
    char addr[500];
    struct linkqueue *link;
};
struct linkqueue *start = NULL;
struct linkqueue *next = NULL;
struct linkqueue *end = NULL;

void insert(struct linkqueue **s, struct linkqueue **e, char addr[])
{
    struct linkqueue *start;
    struct linkqueue *end;
    struct linkqueue *temp;
    string strtoins = (string)addr;
    string strtocom;
    start = *s;
    end = *e;
    temp = (struct linkqueue *) malloc (sizeof(struct linkqueue));
    
    strcpy(temp->addr, addr);
    temp->link = NULL;
    
    if(*s == NULL)
    {
        *s = temp;
        *e = temp;
    }
    else
    {
        while(start != NULL)
        {
            strtocom = (string)start->addr;
            if(strtoins.compare(strtocom) == 0)
            {
                return;
            }
            start = start->link;
        }
        end->link = temp;
        *e = temp;
    }
}
void linkstore (char addr[])
{
    /*
    string check = (string)addr;
    if(check == "http://ssl.gstatic.com" || check == "http://maps.gstatic.com")
    {
        return;
    }*/
    insert(&start, &end, addr);
}

void displaylinks()
{
    struct linkqueue *s;
    s = start;
    int count = 1;
    while (s != NULL)
    {
        cout<<"\n"<<count<<" ";
        ++count;
        int i = 0;
        while(s->addr[i] != '\0')
        {
            cout<<s->addr[i];
            ++i;
        }
        s = s->link;
    }
}
#endif	/* _LINKSTORE_H */

