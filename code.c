/*This project is part of DSPD2 assignemnt , 2024.
Submitted by: Nitesh Yadav (BT22CSE086): VNIT, nagpur
Database created using AVL Tree.*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 1000

typedef struct Duration
{
    int hours;
    int minutes;
} Duration;

typedef struct audiobooks
{
    int AudiobookID;
    char Title[SIZE];
    char Author[SIZE];
    char Narrator[SIZE];
    Duration time;
    Duration watched;
    char Genre[SIZE];
    float Rating;
    int no_of_rating;
    struct audiobooks *next;
} audiobooks;

typedef struct Preferences
{
    char genres[SIZE];
    char authors[SIZE];
    char narrators[SIZE];
} Preferences;

typedef struct users
{
    int UserID;
    char Name[SIZE];
    char Email[SIZE];
    struct Preferences prefer;
    struct audiobooks *library;
    struct users *next;
} users;

void Visitbook(audiobooks *term)
{
    if (term != NULL)
    {
        printf("Details about audiobook\n");
        printf("Id:%d\n", term->AudiobookID);
        printf("Title:%s\n", term->Title);
        printf("Author:%s\n", term->Author);
        printf("NArrator:%s\n", term->Narrator);
        printf("Length:%d:%d\n", term->time.hours, term->time.minutes);
        printf("Time watched:%d:%d\n", term->watched.hours, term->watched.minutes);
        printf("Genre:%s\n", term->Genre);
        printf("Rating:%f\n\n", term->Rating);
        printf("----------------------------------------------------------------------\n\n");
    }
}

void VisitUsers(users *term)
{

    if (term != NULL)
    {
        printf("Details about User\n");
        printf("Id:%d\n", term->UserID);
        printf("Name:%s\n", term->Name);
        printf("Email:%s\n", term->Email);
        printf("Prefered Author:%s\n", term->prefer.authors);
        printf("Prefered Narrator:%s\n", term->prefer.narrators);
        printf("Prefered Genre:%s\n\n", term->prefer.genres);
        audiobooks *temp;
        temp = term->library;
        while (temp != NULL)
        {
            Visitbook(temp);
            temp = temp->next;
        }
        printf("----------------------------------------------------------------------\n\n");
    }
}

users *CreateUsers(users *head)
{
    FILE *fp = fopen("users.txt", "r");
    char word[SIZE];
    users *tail = (users *)malloc(sizeof(users));
    head = tail;
    while (fscanf(fp, "%s", word) == 1)
    {
        users *temp = (users *)malloc(sizeof(users));
        tail->next = temp;
        int p;
        fscanf(fp, "%d", &p);
        temp->UserID = p;
        fscanf(fp, "%s", word);
        strcpy(temp->Name, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Email, word);
        fscanf(fp, "%s", word);
        strcpy(temp->prefer.authors, word);
        fscanf(fp, "%s", word);
        strcpy(temp->prefer.narrators, word);
        fscanf(fp, "%s", word);
        strcpy(temp->prefer.genres, word);
        temp->next = NULL;
        tail = tail->next;
    }
    tail = head;
    head = head->next;
    free(tail);
    fclose(fp);
    return head;
}

audiobooks *CreateAudio_Book(audiobooks *head)
{
    FILE *fp = fopen("audiobook.txt", "r");
    char word[SIZE];
    audiobooks *tail = (audiobooks *)malloc(sizeof(audiobooks));
    head = tail;
    while (fscanf(fp, " %s", word) == 1)
    {
        audiobooks *temp = (audiobooks *)malloc(sizeof(audiobooks));
        tail->next = temp;
        int p;
        fscanf(fp, "%d", &p);
        temp->AudiobookID = p;
        fscanf(fp, "%s", word);
        strcpy(temp->Title, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Author, word);
        fscanf(fp, "%s", word);
        strcpy(temp->Narrator, word);
        fscanf(fp, "%d", &p);
        temp->time.hours = p;
        fscanf(fp, "%d", &p);
        temp->time.minutes = p;
        fscanf(fp, "%d", &p);
        temp->watched.hours = p;
        fscanf(fp, "%d", &p);
        temp->watched.minutes = p;
        float q;
        fscanf(fp, "%s", word);
        strcpy(temp->Genre, word);
        fscanf(fp, "%f", &q);
        temp->Rating = q;
        temp->next = NULL;
        tail = tail->next;
        tail->no_of_rating = 100;
    }
    tail = head;
    head = head->next;
    free(tail);
    fclose(fp);
    return head;
}

audiobooks *add_audiobooks(audiobooks *head, int id, char title[], char author[], char narrator[], int hrs, int mins, char genres[])
{
    audiobooks *new = (audiobooks *)malloc(sizeof(audiobooks));
    new->AudiobookID = id;
    strcpy(new->Title, title);
    strcpy(new->Author, author);
    strcpy(new->Narrator, narrator);
    strcpy(new->Genre, genres);
    new->time.hours = hrs;
    new->time.minutes = mins;
    new->watched.hours = 0;
    new->watched.minutes = 0;
    new->Rating = 0;
    new->no_of_rating = 0;
    if (head == NULL)
    {
        new->next = NULL;
        head = new;
        printf("New audiobook is successfully added.\n");
    }
    else if (head->AudiobookID > new->AudiobookID)
    {
        new->next = head;
        head = new;
        printf("New audiobook is successfully added.\n");
    }
    else
    {
        audiobooks *curr = head;
        while (curr->next != NULL && curr->next->AudiobookID < new->AudiobookID)
        {
            curr = curr->next;
        }
        if (curr->next->AudiobookID == new->AudiobookID)
            printf("Duplicate ID.\n");
        else
        {
            new->next = curr->next;
            curr->next = new;
            printf("New audiobook is successfully added.\n");
        }
    }
    return head;
}

audiobooks *edit_audiobooks(audiobooks *head, int id, char title[], char author[], int hrs, int mins)
{
    audiobooks *curr = head;
    int i = 0;
    while (curr != NULL)
    {
        if (curr->AudiobookID == id)
        {
            strcpy(curr->Title, title);
            strcpy(curr->Author, author);
            curr->time.hours = hrs;
            curr->time.minutes = mins;
            i = 1;
        }
        curr = curr->next;
    }
    if (i == 1)
        printf("Audiobook has been updated.\n");
    return head;
}

audiobooks *delete_audiobooks(audiobooks *head, char title[], char author[])
{
    int i = 0;
    if (head == NULL)
    {
        printf("Audiobook not found.\n");
        i = 1;
    }
    else if (strcmp(head->Title, title) == 0 || strcmp(head->Author, author) == 0)
    {
        audiobooks *temp;
        temp = head;
        head = head->next;
        free(temp);
        i = 1;
        printf("Audiobook deleted successfully.\n");
    }
    else
    {
        audiobooks *curr;
        curr = head;
        while (curr != NULL && curr->next != NULL)
        {
            if (strcmp(curr->next->Title, title) == 0 || strcmp(curr->next->Author, author) == 0)
            {
                audiobooks *temp;
                temp = curr->next;
                curr->next = temp->next;
                free(temp);
                printf("Audiobook deleted successfully.\n");
                i = 1;
            }
            if (curr != NULL)
                curr = curr->next;
        }
    }
    if (i == 0)
        printf("Audiobook not found.\n");
    return head;
}

void search_audiobooks(audiobooks *head, char term[])
{
    int flag = 0;
    audiobooks *curr;
    if (head != NULL)
    {
        curr = head;
        while (curr != NULL && flag == 0)
        {
            if (strcmp(curr->Author, term) == 0 || strcmp(curr->Title, term) == 0 || strcmp(curr->Genre, term) == 0)
            {
                Visitbook(curr);
                flag = 1;
            }

            curr = curr->next;
        }
    }
    if (flag == 0)
    {
        printf("This audiobook does not exist. \n");
    }
}

users *add_users_profile(users *head, int id, char email[], char name[], char gen[], char aut[], char narr[])
{
    users *new = (users *)malloc(sizeof(users));
    new->UserID = id;
    strcpy(new->Name, name);
    strcpy(new->Email, email);
    strcpy(new->prefer.genres, gen);
    strcpy(new->prefer.authors, aut);
    strcpy(new->prefer.narrators, narr);
    new->library = NULL;
    int i;
    do
    {
        i = 1;
        users *curr = head;
        while (curr != NULL)
        {
            if (strcmp(curr->Email, email) == 0)
            {
                i = 0;
                printf("Email ID already present.\nTry again.\n");
            }
            curr = curr->next;
        }
        if (i == 0)
        {
            printf("Enter email:\n");
            scanf("%s", email);
            strcpy(new->Email, email);
        }
    } while (i == 0);
    if (head == NULL)
    {
        new->next = NULL;
        head = new;
        printf("New User is added successfully.\n");
    }
    else if (new->UserID > head->UserID)
    {
        new->next = head;
        head = new;
        printf("New User is added successfully.\n");
    }
    else
    {
        users *curr = head;
        while (curr->next != NULL || curr->next->UserID < new->UserID)
            curr = curr->next;
        if (curr->next->UserID == new->UserID)
            printf("Duplicate ID.\n");
        else
        {
            new->next = curr->next;
            curr->next = new;
            printf("New User is added successfully.\n");
        }
    }
    return head;
}

users *add_users_library(users *head, int id)
{
    if (head != NULL)
    {
        users *curr = head;
        while (curr != NULL && curr->UserID != id)
            curr = curr->next;
        int i, aid;
        printf("Press\n1. To add the audiobook.\n2. To remove the audiobook.\n");
        scanf("%d", &i);
        if (i == 1)
        {
            if (curr != NULL)
            {
                int iid, mins, hrs;
                char title[SIZE], author[SIZE], narrator[SIZE], genres[SIZE];
                printf("Enter audiobooks id:");
                scanf("%d", &iid);
                printf("Enter title of book:");
                scanf("%s", title);
                printf("Enter author of book:");
                scanf("%s", author);
                printf("Enter narrator of book:");
                scanf("%s", narrator);
                printf("Enter genre of book:");
                scanf("%s", genres);
                printf("Enter length of book in minutes:");
                scanf("%d", &mins);
                hrs = mins / 60;
                mins = mins % 60;
                curr->library = add_audiobooks(curr->library, iid, title, author, narrator, hrs, mins, genres);
            }
        }
        else if (i == 2)
        {
            printf("Enter id of the audiobook to be deleted:");
            scanf("%d", &aid);
            audiobooks *temp;
            temp = curr->library;
            while (temp != NULL && temp->AudiobookID != aid)
                temp = temp->next;
            char title[SIZE], author[SIZE];
            if (temp != NULL)
            {
                strcpy(title, temp->Title);
                strcpy(author, temp->Author);
            }
            curr->library = delete_audiobooks(curr->library, title, author);
        }
        else
            printf("Invalid input.\n");
    }
    return head;
}

users *listening_progress(users *head, int userID, int audiobookID, int hr, int min)
{
    users *temp = head;
    while (temp != NULL && temp->UserID != userID)
    {
        temp = temp->next;
    }
    audiobooks *curr = temp->library;
    while (curr != NULL && curr->AudiobookID != audiobookID)
    {
        curr = curr->next;
    }
    if (curr != NULL)
    {
        Duration T = curr->time;
        T.hours = hr;
        T.minutes = min;
        curr->time = T;
    }
    printf("Listening time is updated.\n");
    return head;
}

users *Display_user_libraries(users *start, int userID, char genre[], char author[], char narrator[])
{
    int x;
    users *temp = start;

    int flag = 0;
    audiobooks *curr;
    while (temp->UserID != userID)
        temp = temp->next;
    audiobooks *head = temp->library;
    printf("if you want to filter with respect to genre type 1 \n");
    printf("if you want to filter with respect to author type 2 \n");
    printf("if you want to filter with respect to narrator type 3 \n");
    scanf("%d", &x);

    if (x == 1)
    {

        if (head != NULL)
        {
            curr = head;
            while (curr != NULL && flag == 0)
            {
                if (strcmp(curr->Genre, genre) == 0)
                {
                    Visitbook(curr);
                    flag = 1;
                }

                curr = curr->next;
            }
        }
    }
    if (x == 2)
    {
        int flag = 0;
        audiobooks *curr;
        if (head != NULL)
        {
            curr = head;
            while (curr != NULL && flag == 0)
            {
                if (strcmp(curr->Author, author) == 0)
                {
                    Visitbook(curr);
                    flag = 1;
                }
                curr = curr->next;
            }
        }
        if (flag == 0)
        {
            printf("This audiobook does not exist. \n");
        }
    }
    if (x == 3)
    {
        int flag = 0;
        audiobooks *curr;
        if (head != NULL)
        {
            curr = head;
            while (curr != NULL && flag == 0)
            {
                if (strcmp(curr->Author, author) == 0)
                {
                    Visitbook(curr);
                    flag = 1;
                }
                curr = curr->next;
            }
        }
        if (flag == 0)
        {
            printf("This audiobook does not exist. \n");
        }
    }
}

audiobooks *rate_audiobooks(users *head, audiobooks *start, int userid, int abid, int rate)
{
    users *curr = head;
    while (curr != NULL && curr->UserID != userid)
    {
        curr = curr->next;
    }
    if (curr != NULL)
    {
        audiobooks *temp = start;
        while (temp != NULL && temp->AudiobookID != abid)
        {
            temp = temp->next;
        }
        if (temp != NULL && temp->AudiobookID == abid)
        {
            temp->Rating *= temp->no_of_rating;
            temp->no_of_rating++;
            temp->Rating += rate;
            temp->Rating /= temp->no_of_rating;
            printf("Audiobook rating has been updated.\n");
        }
    }
    return start;
}

void most_popular_rating(audiobooks *head)
{
    audiobooks *curr, *temp;
    float rate;
    curr = head;
    rate = 0.0;
    while (curr != NULL)
    {
        if (curr->Rating > rate)
        {
            rate = curr->Rating;
            temp = curr;
        }
        curr = curr->next;
    }
    if (rate == 0.0)
        printf("No rating are available to determine popularity.\n");
    else
        printf("Details of most popular audiobooks are:\nTitle:%s.\nAuthor:%s.\nRating:%f.\n", temp->Title, temp->Author, temp->Rating);
}

void listening_history_report_user(users *head, int id)
{
    users *curr;
    int flag = 0;
    curr = head;
    audiobooks *temp;
    temp = NULL;
    while (curr != NULL && flag == 0)
    {
        if (curr->UserID == id)
        {
            temp = curr->library;
            flag = 1;
        }
        curr = curr->next;
    }
    if (flag == 1)
    {
        while (temp != NULL)
        {
            if (temp->watched.hours != 0 || temp->watched.minutes != 0)
            {
                printf("ID:%d.\nTitle:%s.\nAuthor:%s.\nTime Listened:%d:%d", temp->AudiobookID, temp->Title, temp->Author, temp->watched.hours, temp->watched.minutes);
            }
        }
    }
    else
    {
        printf("User does not exist.\n");
    }
}

users *merge_users_libraries(users *head, int id1, int id2)
{
    users *curr, *first, *second;
    int flag1 = 0;
    int flag2 = 0;
    curr = head;
    first = NULL;
    second = NULL;
    while (curr != NULL)
    {
        if (curr->UserID == id1 || curr->UserID == id2)
        {
            if (first == NULL)
            {
                first = curr;
                flag1 = 1;
            }
            else
            {
                second = curr;
                flag2 = 1;
            }
        }
        curr = curr->next;
    }
    if (flag1 == 1 && flag2 == 1)
    {
        audiobooks *temp1 = first->library;
        audiobooks *temp2 = second->library;
        audiobooks *temp;
        if (temp1 != NULL && temp2 != NULL)
        {
            if (temp1->AudiobookID > temp2->AudiobookID)
            {
                temp = temp2;
                first->library = temp;
                temp2 = temp2->next;
            }
            else
            {
                temp = temp1;
                first->library = temp;
                temp1 = temp1->next;
            }
        }
        while (temp1 != NULL && temp2 != NULL)
        {
            if (temp1->AudiobookID > temp2->AudiobookID)
            {
                temp->next = temp2;
                temp = temp->next;
                temp2 = temp2->next;
            }
            else
            {
                temp->next = temp1;
                temp = temp->next;
                temp1 = temp1->next;
            }
        }
        if (temp1 != NULL)
            temp->next = temp1;
        if (temp2 != NULL)
            temp->next = temp2;
        curr = head;
        while (curr->next != second)
            curr = curr->next;
        curr->next = second->next;
        second = NULL;
        printf("USers have been merged.\n");
    }
    else
        printf("Invalid user id(s).\n");
    return head;
}

void Listening_history_report_audiobook(int audiobookID, audiobooks *head)
{

    while (head != NULL && head->AudiobookID != audiobookID)
    {
        head = head->next;
    }
    printf("audiobookID is %d.\n", head->AudiobookID);
    printf("title is %s.\n", head->Title);
    Duration temp;
    temp = head->watched;

    printf("total listening progress is %d hours and %d minutes.\n", temp.hours, temp.minutes);
}

void display_audiobooks(audiobooks *head)
{
    float i;
    float j = 6.0;
    audiobooks *curr, *temp, *loop;
    loop = head;
    while (loop != NULL)
    {
        curr = head;
        temp = NULL;
        i = 0.0;
        while (curr != NULL)
        {
            if (curr->Rating > i && curr->Rating < j)
            {
                temp = curr;
                i = curr->Rating;
            }
            curr = curr->next;
        }
        if (temp != NULL)
        {
            printf("ID:%d.\nTitle:%s.\nRating:%f.\n\n", temp->AudiobookID, temp->Title, temp->Rating);
            j = temp->Rating;
        }
        loop = loop->next;
    }
}

int main()
{

    int n;
    audiobooks *head;
    head = NULL;
    head = CreateAudio_Book(head);
    users *start;
    start = NULL;
    start = CreateUsers(start);
    audiobooks *temp = head;
    while (temp != NULL)
    {
        Visitbook(temp);
        temp = temp->next;
    }
    users *curr = start;
    while (curr != NULL)
    {
        VisitUsers(curr);
        curr = curr->next;
    }
    printf("To add audiobook type 1 \n");
    printf("To edit audiobook type 2 \n");
    printf("To delete audiobook type 3 \n");
    printf("To search audiobook type 4 \n");
    printf("To add user profile type 5 \n");
    printf("To add user library type 6 \n");
    printf("To get listening progress type 7 \n");
    printf("To display user libraries type 8 \n");
    printf("To rate an audiobook type 9 \n");
    printf("To know the most popular audiobook type 10 \n");
    printf("To get listening history of user type 11 \n");
    printf("To merge user libraries type 12 \n");
    printf("To get listening history of audiobook type 13 \n");
    printf("To diplay audiobook list according to ratings type 14 \n");
    printf("To print audiobooks list type 15 \n");
    printf("To print users list type 16 \n");

    int id, mins, hrs, uid, rate, flag, uid1, uid2;
    char title[SIZE], author[SIZE], narrator[SIZE], genres[SIZE];
    char term[SIZE], email[SIZE], name[SIZE];

    while (n != -1)
    {
        printf("enter the required value of function: \n");
        scanf("%d", &n);

        switch (n)
        {
        case 1:
            printf("Enter audiobooks id: \n");
            scanf("%d", &id);
            printf("Enter title of book: \n");
            scanf("%s", title);
            printf("Enter author of book: \n");
            scanf("%s", author);
            printf("Enter narrator of book: \n");
            scanf("%s", narrator);
            printf("Enter genre of book: \n");
            scanf("%s", genres);
            printf("Enter length of book in minutes: \n");
            scanf("%d", &mins);
            hrs = mins / 60;
            mins = mins % 60;
            head = add_audiobooks(head, id, title, author, narrator, hrs, mins, genres);
            break;
        case 2:
            printf("Enter audiobooks id: \n");
            scanf("%d", &id);
            printf("Enter new title of book: \n");
            scanf("%s", title);
            printf("Enter new author of book: \n");
            scanf("%s", author);
            printf("Enter new length of book in minutes: \n");
            scanf("%d", &mins);
            hrs = mins / 60;
            mins = mins % 60;
            head = edit_audiobooks(head, id, title, author, hrs, mins);
            break;
        case 3:
            printf("Enter title of book: \n");
            scanf("%s", title);
            printf("Enter author of book: \n");
            scanf("%s", author);
            head = delete_audiobooks(head, title, author);
            break;
        case 4:
            printf("Enter title or author or genre of book: \n");
            scanf("%s", term);
            search_audiobooks(head, term);
            break;
        case 5:
            printf("enter user ID: \n");
            scanf("%d", &uid);
            printf("enter user email: \n");
            scanf("%s", email);
            printf("Enter name of user: \n");
            scanf("%s", name);
            printf("Enter author of book: \n");
            scanf("%s", author);
            printf("Enter narrator of book: \n");
            scanf("%s", narrator);
            printf("Enter genre of book: \n");
            scanf("%s", genres);
            start = add_users_profile(start, uid, email, name, genres, author, narrator);
            break;
        case 6:
            do
            {
                printf("enter user ID: \n");
                scanf("%d", &uid);
                flag = 0;
                users *temp;
                temp = start;
                while (temp != NULL)
                {
                    if (temp->UserID == uid)
                    {
                        flag = 1;
                    }
                    temp = temp->next;
                }
                if (flag == 0)
                {
                    printf("User does not exist.\n");
                }
            } while (flag != 1);
            if (flag == 1)
                start = add_users_library(start, uid);
            break;
        case 7:
            printf("enter user ID: \n");
            scanf("%d", &uid);
            printf("Enter audiobooks id: \n");
            scanf("%d", &id);
            printf("Enter new listening time of book in minutes: \n");
            scanf("%d", &mins);
            hrs = mins / 60;
            mins = mins % 60;
            start = listening_progress(start, uid, id, hrs, mins);
            break;
        case 8:
            printf("enter user ID: \n");
            scanf("%d", &uid);
            printf("Enter author of book: \n");
            scanf("%s", author);
            printf("Enter narrator of book: \n");
            scanf("%s", narrator);
            printf("Enter genre of book: \n");
            scanf("%s", genres);
            Display_user_libraries(start, uid, author, narrator, genres);
            break;
        case 9:
            printf("enter user ID: \n");
            scanf("%d", &uid);
            printf("Enter audiobooks id: \n");
            scanf("%d", &id);
            printf("Enter rating (it should be between 1 to 5): \n");
            scanf("%d", &rate);
            head = rate_audiobooks(start, head, uid, id, rate);
            break;
        case 10:
            most_popular_rating(head);
            break;
        case 11:
            printf("Enter user id:\n");
            scanf("%d", &uid);
            listening_history_report_user(start, uid);
            break;
        case 12:
            printf("enter first user ID: \n");
            scanf("%d", &uid1);
            printf("enter second user ID: \n");
            scanf("%d", &uid2);
            start = merge_users_libraries(start, uid1, uid2);
            break;
        case 13:
            printf("Enter audiobooks id: \n");
            scanf("%d", &id);
            Listening_history_report_audiobook(id, head);
            break;
        case 14:
            display_audiobooks(head);
            break;
        case 15:
            temp = head;
            while (temp != NULL)
            {
                Visitbook(temp);
                temp = temp->next;
            }
            break;
        case 16:
            curr = start;
            while(curr!=NULL)
            {
                VisitUsers(curr);
                curr=curr->next;
            }
            break;
        default:
            printf("The program has terminated. ");
            n = -1;
        }
    }
}