/* 
 * File:   main.cpp
 * Author: ashish
 *
 * Created on 4 July, 2011, 7:09 AM
 */

#include <iostream>

// Project Headers
#include </home/ashish/NetBeansProjects/greyhound1/webtalk.h>
#include </home/ashish/NetBeansProjects/greyhound1/wordbreak.h>
#include </home/ashish/NetBeansProjects/greyhound1/linkstore.h>

using namespace std;

int main()
{
    float elapTime;

    clock_t begint, endt;
    deletedb();
    char url[500];
    cout<<"\n\n Enter the URL...";
    cin>>url;
    cout<<"\n\n"<<url;
    cout<<"\n\n DOWNLOADING WEBPAGE";
    fflush(stdout);
    
    begint = clock();
    webtalk(url);
    endt = clock();
    elapTime = endt - begint;
    cout<<"\n\t[Process Time = "<<elapTime<<" ms.]";
    fflush(stdout);

    cout<<"\n\n BREAKING WEBPAGE INTO WORDS";
    fflush(stdout);

    begint = clock();
    wordbreak(url);
    endt = clock();
    elapTime =  endt - begint;
    cout<<"\n\t[Process Time = "<<elapTime<<" ms.]";
    fflush(stdout);

    //displaylinks();


    struct linkqueue *main;
    main = start;
    for(int x = 1; (x <= 500 && main != NULL) ; ++x)
    {
        int i = 0;
        while(main->addr[i] != NULL)
        {
            url[i] = main->addr[i];
            ++i;
        }
        url[i] = '\0';
        /*********************************************************/
        cout<<"\n\n"<<(x+1)<<" "<<url;
        cout<<"\n\n DOWNLOADING WEBPAGE";
    fflush(stdout);

    begint = clock();
    webtalk(url);
    endt = clock();
    elapTime = endt - begint;
    cout<<"\n\t[Process Time = "<<elapTime<<" ms.]";
    fflush(stdout);

    cout<<"\n\n BREAKING WEBPAGE INTO WORDS";
    fflush(stdout);

    begint = clock();
    wordbreak(url);
    endt = clock();
    elapTime =  endt - begint;
    cout<<"\n\t[Process Time = "<<elapTime<<" ms.]";
    fflush(stdout);
    /***********************************************************/
        main = main->link;
    }
    displaylinks();
    cout<<"\n\n";
}

