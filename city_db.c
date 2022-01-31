/* Implementation of city database using Doubly Linked List*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct node  // doubly LL node defintion
{
    char name[50];  // name of city
    float x;        // x-latitude
    float y;        // y-longitude
    float dist;     // distance between city in node and capital city
    struct node* prev;  //pointer to previous node
    struct node* next;  //pointer to next node
};

float toRadians(const float degree) //function to convert city coordinates to radians 
{
    float one_deg=(M_PI)/180;
    return (one_deg*degree);
}

float distance(float lat2,float long2) //function to calculate distance b/w two points using their coordinates 
{
    float lat1=12.97, long1=77.59;
    
    //Convert the latitudes and longitudes from degree to radians. 
    lat1=toRadians(lat1);
    long1=toRadians(long1);
    lat2=toRadians(lat2);
    long2=toRadians(long2);

    float dlat=lat2-lat1;
    float dlong=long2-long1;

    float ans= pow(sin(dlat / 2), 2) +  cos(lat1) * cos(lat2) * pow(sin(dlong / 2), 2); 
    ans = 2 * asin(sqrt(ans));
    float r=6371;
    ans= ans*r;

    return ans;
}

void print(struct node* head_ref) //Function to print city records within given distance from capital city  
{
    struct node* curr=NULL;
    curr=head_ref;
    int flag=1,search=1;
    float d;
    printf("\n  Enter distance(in Kms): ");
    scanf("%f",&d);
    printf("\n  City records within %.2f kms of capital city Bengaluru:\n",d);
    while(flag!=0) //loop to 
    {
        if(curr->next==NULL && curr->prev==NULL)
        {
            printf("\n  City records database is empty");
            flag=0;
        }
        else if(curr->next==NULL && curr->prev!=NULL)
        {
            if(search==1)
            {
                printf("\n   No city records found within the given distance\n");
            }
            flag=0;
        }
        else
        {
            curr=curr->next;
            if(d>=(curr->dist)) //prints record if dist is less than or equal to user specified distance
            {
                printf("\n=>| Name: %s \n  | Coordinate X: %.2f (Latitude) \n  | Coordinate Y: %.2f(Longitude) \n  | Distance from Capital: %f kms\n",curr->name,curr->x,curr->y,curr->dist);
                search=0;
            }    
        }
    }
    
    while(curr->prev!=NULL) //loop to bring current node pointer back to head node
    {
        curr=curr->prev; 
    }
    flag=1;
    return;
}

void append(struct node** head_ref) //Function to insert a new city record into the database(LL)
{ 
    /* 1. allocate node */
    struct node* new_node = (struct node*)malloc(sizeof(struct node)); 
  
    struct node* last = *head_ref; /* used in step 5*/
  
    /* 2. put in the data  */
    printf("\n\nEnter city name:");
    scanf("%s",(new_node->name));

    printf("\nEnter Latitude(X):");
    scanf("%f",&(new_node->x));

    printf("\nEnter Longitude(Y):");
    scanf("%f",&(new_node->y));

    new_node->dist=distance(new_node->x,new_node->y);
  
    /* 3. This new node is going to be the last node, so 
          make next of it as NULL*/
    new_node->next = NULL; 
  
    /* 4. If the Linked List is empty, then make the new 
          node as head */
    if (*head_ref == NULL) { 
        new_node->prev = NULL; 
        *head_ref = new_node; 
        return; 
    } 
  
    /* 5. Else traverse till the last node */
    while (last->next != NULL) 
        last = last->next; 
  
    /* 6. Change the next of last node */
    last->next = new_node; 
  
    /* 7. Make last node as previous of new node */
    new_node->prev = last; 
  
    return; 
}

void display(struct node* head_ref) //function to display all records from database(LL)
{
    struct node* curr=NULL;
    curr=head_ref;
    int flag=1;
    while(flag!=0) //loop to print data in the list
    {
        if(curr->next==NULL && curr->prev==NULL)
        {
            printf("\n  No records in database");
            flag=0;
        }
        else if(curr->next==NULL && curr->prev!=NULL)
        {
            printf("\n  end\n");
            flag=0;
        }
        else
        {
            curr=curr->next;
            printf("\n=>| Name: %s \n  | Coordinate X: %.2f (Latitiude) \n  | Coordinate Y: %.2f(Longitude) \n  | Distance from Capital: %f kms\n",curr->name,curr->x,curr->y,curr->dist);
        }
        
            
    }
    
    while(curr->prev!=NULL) //loop to bring current node pointer back to head node
    {
        curr=curr->prev; 
    }
    flag=1;
    return;
}

void searchName(struct node* head_ref,char k_name[]) //Function to search record by name of the city
{
   struct node* curr=NULL;
   curr=head_ref;
   int flag=1,search=1;
    while(flag!=0 && search==1) 
    {
        if(curr->next==NULL && curr->prev==NULL)
        {
            printf("\n  Database is empty");
            flag=0;
        }
        else if(curr->next==NULL && curr->prev!=NULL)
        {
            printf("\n  Record not found in the database\n");
            flag=0;
        }
        else
        {
            curr=curr->next;
            if(strcmp(k_name,curr->name)==0)
            {
                search=0;
                printf("\nRecord found!");
                printf("\n=>| Name: %s \n  | Coordinate X: %.2f (Latitiude) \n  | Coordinate Y: %.2f(Longitude) \n  | Distance from Capital: %f kms\n",curr->name,curr->x,curr->y,curr->dist);
                break;
            }    
        }
        
            
    }
    
    while(curr->prev!=NULL) //loop to bring current node pointer back to head node
    {
        curr=curr->prev; 
    }
    flag=1;
    return;

}

void searchCord(struct node* head_ref,float X, float Y) //Function to search record by coordinates of the city
{
   struct node* curr=NULL;
   curr=head_ref;
   int flag=1,search=1;
    while(flag!=0 && search==1) //loop to print data in the list
    {
        if(curr->next==NULL && curr->prev==NULL)
        {
            printf("\n  Database is empty");
            flag=0;
        }
        else if(curr->next==NULL && curr->prev!=NULL)
        {
            printf("\n  Record not found in the database\n");
            flag=0;
        }
        else
        {
            curr=curr->next;
            if(X==curr->x && Y==curr->y)
            {
                search=0;
                printf("\n  Record found!");
                printf("\n=>| Name: %s \n  | Coordinate X: %.2f (Latitiude) \n  | Coordinate Y: %.2f(Longitude) \n  | Distance from Capital: %f kms\n",curr->name,curr->x,curr->y,curr->dist);
                break;
            }    
        }
    }
    
    while(curr->prev!=NULL) //loop to bring current node pointer back to head node
    {
        curr=curr->prev; 
    }
    flag=1;
    return;
}

void delNode(struct node** h_ref,struct node* del) //function to delete node
{
    if(*h_ref==NULL||del==NULL) //to check if list address or node to be
    return;                     //deleted exists or is it null
    
    if (*h_ref == del)   //when head node is to be deleted
        *h_ref = del->next; 
  
    if (del->next != NULL) //when last node is to be deleted
        del->next->prev = del->prev; 
  
    if (del->prev != NULL) 
        del->prev->next = del->next; 
  
    free(del); 
}

void delName(struct node* head_ref,char k_name[]) //function to delete a record(node) w.r.t. city name
{
   struct node* curr=NULL;
   curr=head_ref;
   int flag=1,search=1;
    while(flag!=0 && search==1) //loop to print data in the list
    {
        if(curr->next==NULL && curr->prev==NULL)
        {
            printf("\n  Database is empty");
            flag=0;
        }
        else if(curr->next==NULL && curr->prev!=NULL)
        {
            printf("\n  Record not found in the database\n");
            flag=0;
        }
        else
        {
            curr=curr->next;
            if(strcmp(k_name,curr->name)==0)
            {
                search=0;
                printf("\n  Record found!");
                delNode(&head_ref,curr);
                printf("\n  Record Deleted!");
                break;
            }    
        }
        
            
    }
    while(curr->prev!=NULL) //loop to bring current node pointer back to head node
    {
        curr=curr->prev; 
    }
    flag=1;
    return;

}

void delCord(struct node* head_ref,float X, float Y) //function to delete a record(node) w.r.t. city coordinates
{
   struct node* curr=NULL;
   curr=head_ref;
   int flag=1,search=1;
    while(flag!=0 && search==1) //loop to print data in the list
    {
        if(curr->next==NULL && curr->prev==NULL)
        {
            printf("\n  Database is empty");
            flag=0;
        }
        else if(curr->next==NULL && curr->prev!=NULL)
        {
            printf("\n  Record not found in the database\n");
            flag=0;
        }
        else
        {
            curr=curr->next;
            if(X==curr->x && Y==curr->y)
            {
                search=0;
                printf("\n  Record found!");
                delNode(&head_ref,curr);
                printf("\n  Record Deleted!");
                break;
            }    
        }
    }
    
    while(curr->prev!=NULL) //loop to bring current node pointer back to head node
    {
        curr=curr->prev; 
    }
    flag=1;
    return;
}


int main()
{
    struct node* head=NULL; // node pointer declaration, pointing to Null
    head=(struct node*)malloc(sizeof(struct node));  //allocating memory and returning a pointer to it
    struct node* curr=NULL;
    curr=head;
    
    head->prev=NULL;
    head->next=NULL;

    int o; // variable to store option number

    printf("\nWelcome to City Database!\n (Capital City: Bengaluru)");
    
    while(o!=6)  // while loop keeps running until user enters 6
    {
        printf("\n________________________________________________________________\n"
        "\nChoose any option[1-6]:\n"
        " 1. Enter new records\n"
        " 2. Delete records\n"
        " 3. Display all records\n"
        " 4. Search for a record\n"
        " 5. Display records within a distance from a given city\n"
        " 6. Quit\n");
        printf("\nEntered Option:");
        scanf("%d",&o);

        if(o==1)  //function to enter new records
        {
            char ch='y';
            while(ch=='y'||ch=='Y')
            {
                append(&head);
                printf("\n  Enter more records? [y/n]: ");
                scanf(" %c",&ch);
            }
        }

        else if(o==2)  //function to delete records
        {
            char city[50];
            float x1,y1;
            char ch='y';
            int p;
            while(ch=='y'||ch=='Y')
            {
             printf("\n Search record to be deleted by: \n"
             "  1. City Name\n"
             "  2. City Coordinates\n"
             "  Your choice[1 or 2]:");
             scanf(" %d",&p);
             if(p==1)
             {
                 printf("\n   Enter name of the city to be deleted:");
                 scanf("%s",city);
                 delName(head,city);
             }
            
             else if(p==2)
             {
                 printf("\n   Enter coordinates of the city to be deleted:");
                 printf("\n    Enter Latitude(X):");
                 scanf(" %f",&x1);
                 printf(" \n    Enter Longitude(Y): ");
                 scanf("%f",&y1); 
                 delCord(head,x1,y1);
             }
             
             else
             {
                 printf("\nInvalid option!");
             }
             
             printf("\nContinue Deleting? [y/n]: ");
             scanf(" %c",&ch);
            }
        }

        else if(o==3) //funtion to Display all records
        {
            display(head);
        }

        else if(o==4) //Search for a record
        {
            char city[50];
            float x1,y1;
            char ch='y';
            int p;
            while(ch=='y'||ch=='Y')
            {
             printf("\n Search by: \n"
             "  1. City Name\n"
             "  2. City Coordinates\n"
             "  Your choice[1 or 2]:");
             scanf(" %d",&p);
             if(p==1)
             {
                 printf("\n   Enter name of the city to be searched:");
                 scanf(" %s",city);
                 searchName(head,city);
             }
            
             else if(p==2)
             {
                 printf("\n   Enter Latitude(X):");
                 scanf(" %f",&x1);
                 printf(" \n   Enter Longitude(Y): ");
                 scanf("%f",&y1); 
                 searchCord(head,x1,y1);
             }
             
             else
             {
                 printf("\n  Invalid option!");
             }
             
             printf("\n  Continue Searching? [y/n]\n");
             scanf(" %c",&ch);
            }
        }

        else if(o==5) // Display records within a distance from a given city
        {
            char ch='y';
            while(ch=='y'||ch=='Y')
            {
                print(head);
                printf("\n Enter another distance? [y/n]: ");
                scanf(" %c",&ch);
            }
            
        }

        else if(o==6) //funtion to exit the program
        {
            break;
        }

        else
        {
            printf("Invalid Input! Enter again");
        }
        
    }
    
    

    return 0;
}