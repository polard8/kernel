/*
 * Author:  Deep Aggarwal
 * Date:    -/-/2015
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define INITIALSIZE 1000 //initial size of the char array

/* A data structure is needed to store the content
 * of the file and some other metadata about the
 * input file.
 */
typedef struct _inputFileInfo
{
    int lineNumber;
    char *lineData;
    struct _inputFileInfo *next;
} ds;

//Number of lines in a file
int numOfLines = 0;
ds *head = NULL;
ds *tail = NULL;

int main(int argc, char *argv[])
{
    //Usage: ./textEditor <fileName>
    if(argc != 2)
    {
        printf("Error: File name is not specified.\n");
        printf("Usage: ./textEditor <textFileName>\n");
        exit(1);
    }

    //A file pointer to read a file
    FILE *fp;

    //Open a file for both reading and writing. The file must exist.
    fp = fopen(argv[argc-1], "r+");
    if(fp == NULL)
    {
        //File does not exist, so it will be created for reading and writing.
        fp = fopen(argv[argc-1], "w+");
    }
    else
    {
        //If file already exists and is not empty, then upload the
        //  contents of the file into the data structure.
        int c = 0;
        int i = 0;
        int lineNum = 0;
        char charArray[INITIALSIZE] = {0}; //Initializes the array

        while( (c=getc(fp)) != EOF)
        {
            if(c == '\n')
            {
                lineNum++;
                numOfLines++;
                charArray[i] = '\0';
                i = 0;

                if(head == NULL)
                {
                    ds *newNode = malloc(sizeof(ds));
                    newNode->lineNumber = lineNum;
                    newNode->lineData = malloc(strlen(charArray)+1); // 1 is added to make space for the terminating null character
                    strcpy(newNode->lineData, charArray);
                    newNode->next = NULL;
                    head = newNode;
                    tail = newNode;
                }
                else //iterate through the linked-list
                {
                    ds *curr = head;
                    while(curr->next != NULL)
                    {
                        curr = curr->next;
                    }
                    ds *newNode = malloc(sizeof(ds));
                    newNode->lineNumber = lineNum;
                    newNode->lineData = malloc(strlen(charArray)+1); // 1 is added to make space for the terminating null character
                    strcpy(newNode->lineData, charArray);
                    newNode->next = NULL;
                    curr->next = newNode;
                    tail = newNode;
                }

                memset(charArray, 0, INITIALSIZE);
                continue;
            }
            charArray[i++] = c;
        }
    }

    char *enteredCommand = NULL;
    size_t ec_size = 0;
    while(1)
    {
        //Print the command prompt for the text editor
        printf("textEditor-%s-$ ", argv[argc-1]);

        /*
         * Read the user input. The possible inputs are:
         *  p: Print the contents of the file.
         *  a 3 I like cats!: Append "I like cats!" to the text at line number 3.
         *  w: Write the changes back to the file (overwrites the file if it exists).
         *  q: Quit
         */
        getline(&enteredCommand, &ec_size, stdin);
        int ec_len = strlen(enteredCommand);
        enteredCommand[ec_len-1] = '\0';

        if(strcmp(enteredCommand, "p") == 0)
        {
            //Print the contents of the file
            ds *temp = head;
            while(temp != NULL)
            {
                printf("%s\n", temp->lineData);
                temp = temp->next;
            }
        }
        else if(enteredCommand[0] == 'a')
        {
            //Append the content to the text at line number mentioned in the command
            //First parse the line number
            char* dest = malloc(strlen(enteredCommand)+1);
            memset(dest, '\0', strlen(enteredCommand)+1);
            strcpy(dest, enteredCommand);
            const char delim = ' ';
            char *token;
            token = strtok(dest, &delim);
            token = strtok(NULL, &delim);
            if(token == NULL)
            {
                printf("Error: The format to append is: \"a <lineNumber> <textToAppend>\"\n");
                exit(1);
            }
            int lineN = atoi(token);

            //Now parse the text to be appended
            char *ret1, *ret2;
            ret1 = strchr(enteredCommand, delim);
            ret2 = strchr(ret1+1, delim);
            if(ret2 == NULL)
            {
                printf("Error: The format to append is: \"a <lineNumber> <textToAppend>\"\n");
                exit(1);
            }
            char *text = ret2 + 1;

            //Now update the datastore (ds) with the new append data
            ds *temp = head;
            if(lineN > numOfLines)
            {
                numOfLines++;
                ds *newNode = malloc(sizeof(ds));
                newNode->lineNumber = numOfLines;
                newNode->lineData = malloc(strlen(text)+1); // 1 is added to make space for the terminating null character
                strcpy(newNode->lineData, text);
                newNode->next = NULL;
                if(tail == NULL)
                {
                    head = newNode;
                    tail = newNode;
                }
                else
                {
                    tail->next = newNode;
                    tail = newNode;
                }
            }
            else
            {
                while(temp != NULL)
                {
                    if(temp->lineNumber == lineN)
                    {
                        char *dest = malloc(strlen(temp->lineData) + strlen(text) + 1);
                        strcat(dest, temp->lineData);
                        strcat(dest, text);
                        temp->lineData = dest;
                    }
                    temp = temp->next;
                }
            }
        }
        else if(strcmp(enteredCommand, "w") == 0)
        {
            //Write the changes back to the file (overwrites the file if it exists)
            fp = fopen(argv[argc-1], "w+");
            ds *temp = head;
            while(temp != NULL)
            {
                fprintf(fp, "%s\n", temp->lineData);
                temp = temp->next;
            }
        }
        else if(strcmp(enteredCommand, "q") == 0)
        {
            exit(0);
        }

        free(enteredCommand);
        enteredCommand = NULL;
    }

    //Close all the file descriptors and free the allocated memories
    fclose(fp);

    //We don't really need to free memory allocated for the linked-list, since the process is exiting now
    return 0;
}

