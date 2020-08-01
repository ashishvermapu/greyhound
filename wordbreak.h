/* 
 * File:   wordbreak.h
 * Author: ashish
 *
 * Created on 4 July, 2011, 7:18 AM
 */

#ifndef _WORDBREAK_H
#define	_WORDBREAK_H
/*General C++ Headers */

#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <sstream>
#include <memory>
#include <string>
#include <stdexcept>

/* MySQL Connector/C++ specific headers */

#include <driver.h>
#include <connection.h>
#include <statement.h>
#include <prepared_statement.h>
#include <resultset.h>
#include <metadata.h>
#include <resultset_metadata.h>
#include <exception.h>
#include <warning.h>

#include </home/ashish/NetBeansProjects/greyhound1/linkstore.h>

#define DBHOST "tcp://127.0.0.1:3306"
#define USER "ashish"
#define PASSWORD "guwardoo"
#define DATABASE "test"

#define NUMOFFSET 100
#define COLNAME 200




using namespace std;
using namespace sql;

long int words = 0;
long int freq_total = 0;

/*******************************STRUCTURE DEFINATIONS*******************************/

//This is a structure defined for a word (linked list).

struct word
{
    char value;
    struct word *link;
};

//Following is the defination of the file Tee
//This tree will store all the words on the file.

struct filetree
{
    struct word *word;
    int asciisum;
    int frequency;
    struct filetree *leftlink;
    struct filetree *rightlink;
};

/******************************STRUCTURE DEFINATIONS END HERE***********************/




/**********************************FUNCTION DEFINATIONS*****************************/
void linkdetector (char ch);
void deletedb ();
void dbinsert (struct word *start, struct filetree *tree, char url[500]);
int ascii (struct word *q); // Programmed to calculate the ascii sum of the word.
void createword (struct word **start, char value); // Programmed to create a word.
void word_display(struct word *start); // Programmed to display a single word.
int word_comp(struct word *word1, struct word *word2); // Programmed to compare two words.
void tree_insert (struct filetree **q, struct word *word, int asciisum); // Programmed ot insert the word into the file tree.
void tree_display (struct filetree *start, char url[500]); // Programmed to display the file tree.
/*******************************FUNCTION DEFINATIONS OVER***************************/





    char charlink[500];
    int pass1, pass2, pass3, pass4, pass5, pass6, pass7, pass0;
    int looplink = 7;
    


/***********************************CLASS DEFINATIONS*******************************/

//This class reads a file form the disk.
class file
{
private:
    FILE *fp;
public:
    file (const char *name, const char *mode)
    {
        fp = fopen (name, mode);
        if (fp==NULL)
        {
            printf("\nCannot open file: %s", name);
            exit(1);
        }
    }

    ~file ()
    {
        fclose(fp);
    }

    FILE *getfilepointer()
    {
        return fp;
    }
};


/*********************************CLASS DEFINATIONS OVER****************************/

/****************************************WORDBREAK**********************************/

void wordbreak(char url[500])
{
    //Test Code Starts
    //string stringlink;
    pass1 = pass2 = pass3 = pass4 = pass5 = pass6 = pass7 = 0;
    //TestCode Ends
    cout<<"\n\t Breaking WebPage.";
    fflush(stdout);
    //deletedb();
    struct word *start = NULL;
    struct filetree *tree = NULL;
    int a;
    char ch;
    file f ("test.txt", "r");
    while ((ch = fgetc(f.getfilepointer())) != EOF)
    {
        a = ((int)ch);

        //Checking weather the letter is in desired limit or not.
        //ascii value of charcter fecthed from file must be 33 <= letter <=126.
        if((a>=97 && a <=122)||(a>=65 && a <= 90))
        {
            //We will have to create word here
            //This letter will be included in the word being created.
            createword(&start, ch);
        }
        else if (start != NULL)
        {
            //This will end up this word.
            //This word will be stored in the tee.
            //Calculating ascii sum for this word.
            //Test Code
            int asciisum = 0;
            asciisum = ascii(start);
            //cout<<"\nThe ASCII sum [";
            //word_display(start);
            //cout<<"] is\t"<<asciisum;
            tree_insert(&tree, start, asciisum);
            start = NULL;
            //Test Code Ends
        }
        linkdetector(ch);
    }
    cout<<"\n\t Writing to Database.";
    fflush(stdout);
    tree_display(tree, url);
    cout<<"\n\t "<<freq_total<<" WORDS PRESENT.";
    freq_total = 0;
    cout<<"\n\t "<<words<<" WORDS REPEATED.";
    words = 0;
    free(tree);
}
/*****************************************END***************************************/


/*********************************FUNCTION DEFINATIONS******************************/

// This function claculates the ascii sum of a word.

int ascii (struct word *q)
{
    int ascii = 0;
    struct word *start;
    start = q;
    while(start != NULL)
    {
        ascii += ((int) start->value);
        start = start -> link;
    }
    return ascii;
}


/**************************************************************************************************************/


//This function creates a linked list of a word according to the algo.
//CreateWord Fucntion
/*
 * This function takes two arguments.
 * 1. Address to the pointer containing start adress of word being created.
 * 2. Value (New Character) to be inserted at the end of the current word.
 */
void createword (struct word **q, char value)
{
    try
    {
    struct word *start;
    struct word *temp;

    start = *q;

    temp = (struct word *) malloc (sizeof(struct word));

    temp->value = value;
    temp->link = NULL;

    if(*q == NULL)
    {
        *q = temp;
    }
    else
    {
        while(start->link != NULL)
        {
            start = start->link;
        }
        start->link = temp;
    }
    }
    catch(exception e)
    {
        cout<<"\n\nCreate Word\n\n";
    }

}

//This Function is programmed to display a word.
/*
 * This function takes only one argument.
 * 1. the start pointers value of the word to be displayd.
 * */
void word_display(struct word *start)
{
    while(start != NULL)
    {
        cout<<start->value;
        start = start->link;
    }
}

/************************************************************************************************************************/

//This Functoin Compares two words.
/* This function takes two arguments/
 * 1. Word 1
 * 2. Word 2
 *
 * This function returns on value
 *
 * 1. returns 1 if words are same and
 * 2. returns 0 of words are not same.
 */
int word_comp(struct word *word1, struct word *word2)
{
    while(word1 != NULL || word2 != NULL)
    {
        if(word1->value != word2->value)
            break;
        word1 = word1->link;
        word2 = word2->link;
    }

    if(word1 == NULL && word2 == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

/*****************************************************************************************************/

// Following function inserts a new node into FILE TREE
//this function intakes three arguments
/* 1. It takes the start address of the file tree.
 * 2. It takes the start address of the word being insterted.
 * 3. It takes the ascii sum of all the characters in the word.
 */

void tree_insert (struct filetree **q, struct word *word, int asciisum)
{
    //cout<<"\nWE ARE NOW INSERTING [";
    //word_display(word);
    //cout<<"] INTO THE FILE TREE.\n";
    struct filetree *temp;  // Variable to insert new node into.
    struct filetree *start;
    struct filetree *nextchk;
     // Start address (variable) of the file tree.
    start = *q;
    temp = (struct filetree *) malloc (sizeof(struct filetree )); // Memory allocation to the temp.
    temp->frequency = 1;

    temp->leftlink = NULL;
    temp->rightlink = NULL;

    temp->word = word;
    temp->asciisum = asciisum;
    if(*q == NULL)
    {
        *q = temp;
    }

    else
    {
        while((asciisum > start->asciisum && start->rightlink != NULL ) || (asciisum < start->asciisum && start->leftlink != NULL ))
        {
            if (asciisum > start->asciisum)

                start = start->rightlink;
            else

                start = start->leftlink;
        }

        if(asciisum < start->asciisum)
        {
            start->leftlink = temp;
        }
        else if(asciisum > start->asciisum)
        {
            start->rightlink = temp;
        }
        else if(asciisum == start->asciisum)
        {
            while(1)
            {
                int word_compare = word_comp(start->word, word);
                if(word_compare == 1)
                {
                    start->frequency += word_compare;
                    break;
                }
                else if(word_compare == 0 && start->leftlink != NULL)
                {
                    nextchk = start->leftlink;
                    if(nextchk->asciisum == asciisum)
                    {
                        start = start->leftlink;
                        continue;
                    }
                    else
                    {
                        struct filetree *temp_addr = start->leftlink;
                        start->leftlink = temp;
                        temp->leftlink = temp_addr;
                        break;
                    }
                }
                else
                {
                    start->leftlink = temp;
                    break;
                }
            }
        }
    }
}


//This Function displays the current tree.

/*
 * This function takes one argument.
 *
 * 1. Start adress of the file tree.
 *
 */
void tree_display (struct filetree *start, char url[500])
{
    try
    {
    if(start != NULL)
    {
        tree_display(start->leftlink, url);
        dbinsert(start->word, start, url);
        ++words;
        freq_total += start->frequency;
        //printf("\t %d \t %u \n\n", start->asciisum, start->frequency);
        tree_display(start->rightlink, url);
    }
    }
    catch(exception e)
    {
        cout<<"\n\nTree Display\n\n";
    }
}

void dbinsert (struct word *start, struct filetree *tree, char web[500])
{
    Driver *driver;
    Connection *con;
    Statement *stmt;
    ResultSet *res;
    PreparedStatement *prep_stmt;
    Savepoint *savept;

    int updatecount = 0;

    string url = DBHOST;
    const string user = USER;
    const string password = PASSWORD;
    const string database = DATABASE;

    driver = get_driver_instance();
    con = driver -> connect (url, user, password);
    con->setAutoCommit(0);
    con->setSchema(database);

    prep_stmt = con -> prepareStatement ("INSERT INTO test (word, web, asciisum, frequency) VALUES (?,?,?,?)");
    string wordtoinsertstring;
    string webtoinsert;
    char wordtoinsert[200];
    int asciisumtoinsert;
    int frequencytoinsert;
    int i=0;
    while(start != NULL)
    {
        wordtoinsert[i] = start->value;
        start = start->link;
        ++i;
    }
    wordtoinsert[i] = '\0';
    wordtoinsertstring = (string) wordtoinsert;
    webtoinsert = (string)web;
    asciisumtoinsert = (int) tree->asciisum;
    frequencytoinsert = (int) tree->frequency;
    prep_stmt -> setString (1, wordtoinsertstring);
    prep_stmt -> setString (2, web);
    prep_stmt -> setInt (3, asciisumtoinsert);
    prep_stmt -> setInt (4, frequencytoinsert);
    prep_stmt -> executeUpdate();
    con->close();
    con-> ~Connection();
    free(start);
}

void deletedb ()
{
    Driver *driver;
    Connection *con;
    Statement *stmt;
    string url = DBHOST;
    const string user = USER;
    const string password = PASSWORD;
    const string database = DATABASE;

    driver = get_driver_instance();
    con = driver -> connect (url, user, password);
    con->setAutoCommit(0);
    con->setSchema(database);

    stmt = con -> createStatement();
    stmt -> executeUpdate("DELETE FROM test");
    con->close();
    con-> ~Connection();
}

void linkdetector (char ch)
{
        if (ch == 'h')
        {
            charlink[0] = ch;
            charlink[1] = NULL;
            //stringlink = (string)charlink;
            //pass0 = 0;
            pass1 = 1;
            return;
        }
        else if (ch == 't' && pass1 == 1)
        {
            charlink[1] = ch;
            charlink[2] = '\0';
            //stringlink = (string)charlink;
            pass1 = 0;
            pass2 = 1;
            return;
        }
        else if (ch == 't' && pass2 == 1)
        {
            charlink[2] = ch;
            charlink[3] = '\0';
            //stringlink = (string)charlink;
            pass2 = 0;
            pass3 = 1;
            return;
        }
        else if (ch == 'p' && pass3 == 1)
        {
            charlink[3] = ch;
            charlink[4] = '\0';
            //stringlink = (string)charlink;
            pass3 = 0;
            pass4 = 1;
            return;
        }
        else if (ch == ':' && pass4 == 1)
        {
            charlink[4] = ch;
            charlink[5] = '\0';
            //stringlink = (string)charlink;
            pass4 = 0;
            pass5 = 1;
            return;
        }
        else if (ch == '/' && pass5 == 1)
        {
            charlink[5] = ch;
            charlink[6] = '\0';
            pass5 = 0;
            pass6 = 1;
            return;
        }
        else if (ch == '/' && pass6 == 1)
        {
            charlink[6] = ch;
            charlink[7] = '\0';
            //stringlink = (string)charlink;
            pass6 = 0;
            pass7 = 1;
        }
        else if (pass7 == 1 && ch != '/' && ch != ' ' && ch != '"' && ch != '\0' && ch != '\'')
        {
            charlink[looplink] = ch;
            ++looplink;
            return;
        }

        else if (pass7 == 1 && (ch == '/' || ch == ' ' || ch == '"' || ch == '\0' || ch == '\''))
        {
            charlink[looplink] = '\0';
            //stringlink = string(charlink);
            linkstore(charlink);
            pass7 = 0;
            looplink = 7;
            return;
        }
        else
        {
            pass1 = pass2 = pass3 = pass4 = pass5 = pass6 = pass7 = 0;
            return;
        }
}

/********************************FUNTION DEFINATIONS*******************************************/

#endif	/* _WORDBREAK_H */

