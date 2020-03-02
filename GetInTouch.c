#include<stdio.h>
#include<malloc.h>
#include<conio.h>
#define NODES 9
#define EDGES 15

typedef struct node
{
	char vertex;
	int wt;
	struct node * next;
}NODE;

typedef NODE * NODE_PTR;



NODE_PTR adjList[NODES], nn, tptr, prev;
NODE_PTR tptr1,tptr2;

typedef struct edge
{
	char v1;
	char v2;
} EDGE;

EDGE graph[EDGES] =  {
	{'A','B'},
	{'A','H'},
	{'B','H'},
	{'B','C'},
	{'C','D'},
	{'E','F'},
	{'F','G'},
	{'I','H'},
	{'I','G'},
	{'C','I'},
	{'G','H'},
	{'D','F'},
	{'D','E'},
	{'A','C'},
	{'C','F'}
};
int value[NODES]={10,10,10,10,10,10,10,10,10};
int adjMatrix[NODES][NODES];

//FUNCTIONS

void findFriends(int friends)
{
    int desiredNode;
    desiredNode=friends-65;

    printf("         %c -> ", friends);
    for(tptr = adjList[desiredNode]; tptr->next; tptr = tptr->next)
		    printf("%c-> ", tptr->vertex);
		    printf("%c", tptr->vertex);


}

void findMutualFriends(char mfriends1,char mfriends2)
{
    int desiredNode1,desiredNode2;
    int count=0;
        desiredNode1=mfriends1-65;
    desiredNode2=mfriends2-65;


    //printf("%d %d",desiredNode1,desiredNode2);
    printf("         ");
    for(tptr1 = adjList[desiredNode1]; tptr1; tptr1 = tptr1->next)
        for(tptr2 = adjList[desiredNode2]; tptr2; tptr2 = tptr2->next)
        {
            if(tptr1->vertex==tptr2->vertex)
            {
                printf("%c, ",tptr1->vertex);
                count++;
            }
        }
        if(count==0)
            printf("         There are no mutual connections");
        else
            printf("are the mutual connections of %c and %c",mfriends1,mfriends2);

}

void maxFriends()
{
    int number,index,max=0,ind;
    for(ind = 0,number=0; ind < NODES; ind++,number=0)
        {
			for(tptr = adjList[ind]; tptr->next; tptr = tptr->next)
            {
			   number++;
            }
            if(number>max)
            {
                max=number;
                index=ind;
            }
        }
        printf("         The Node with maximum connections is %c",index+65);
}

void secondLevelConnections(char connection)
{
     int connectionNode,desiredNode3,size1,ind;
     char secondCon[10];
     char real;
     real=connection;
        connectionNode=connection-65;
        //printf("%c",connection);

        //FINDING SECOND LEVEL CONNECTIONS
         for(tptr1 = adjList[connectionNode],ind=0,size1=0; tptr1; tptr1 = tptr1->next)
         {
            desiredNode3=(tptr1->vertex)-65;
            //printf("%d ",desiredNode3);
            for(tptr2=adjList[desiredNode3];tptr2;tptr2=tptr2->next,ind++,size1++)
            {
                //printf("%d ",adjList[desiredNode3]);
                //printf("%c ",tptr2->vertex);
                secondCon[ind]=tptr2->vertex;
            }
            //printf("\n");
            //printf("%d",size1);

         }
    //REMOVING THE DIRECT CONNECTIONS
         for(tptr1 = adjList[connectionNode]; tptr1; tptr1 = tptr1->next)
         for(int i=0;i<size1;i++)
         {
             if(secondCon[i]==tptr1->vertex)
             secondCon[i]='N';
         }

         /*for(int i=0;i<size1;i++)
         {
             if(secondCon[i]!='N')
             //printf("%c ",secondCon[i]);
         }*/

         //REMOVING DUPLICATIONS
         for(int i=0;i<size1;i++)
         {
             for(int j=i+1;j<size1;j++)
             {
                 if(secondCon[i]==secondCon[j])
                    secondCon[i]='N';

             }
         }

         printf("         The Secondary level connections are ");
         for(int i=0;i<size1;i++)
         {
             if(secondCon[i]!='N' && secondCon[i]!=real)
             printf("%c, ",secondCon[i]);
         }

}
int isConnection(int fromNode,char to)
{
    int flag=0;
    for(tptr = adjList[fromNode]; tptr->next; tptr = tptr->next)
        if(tptr->vertex == to)
        flag=1;
    return flag;
}

void transaction(char from,char to)
{
    int fromNode,flag,amount,toNode;
    fromNode=from-65;
    toNode=to-65;
    flag=isConnection(fromNode,to);
    if(flag==1)
    {
        printf("\n          TRANSACTION CAN BE DONE");
        printf("\n          Enter the amount to be transacted : ");
        scanf("%d",&amount);
        //printf("%d",amount);
        if(amount>value[fromNode])
        {
            printf("          TRANSACTION CANNOT BE COMPLETED DUE TO LOW BALANCE !!\n\n");
            exit;
        }
        else
        {
        value[fromNode]=value[fromNode]-amount;
        value[toNode]=value[toNode]+amount;
        printf("\n          TRANSCATION SUCCESSFUL");
        printf("\n          CURRENT VALUE : ");
        printf("\n          %c : %d",from,value[fromNode]);
        printf("\n          %c : %d\n\n",to,value[toNode]);
        }
    }

    else
        printf("\n          TRANSACTION IMPOSSIBLE\n\n");

}




int main()
{
    int choice;

    char friends;


    char mfriends1,mfriends2,whatever,whatever2;


    char connection;

    char from,to;


	int ind, size, v1Ind, v2Ind, in, out;
	size = sizeof(graph) / sizeof(EDGE);
	for(ind = 0; ind < size; ind++)
	{
		v1Ind = graph[ind].v1 - 65;
		v2Ind = graph[ind].v2 -65;
	//	adjMatrix[v1Ind][v2Ind]= 1;
	{
		nn = (NODE_PTR) malloc(sizeof(NODE));
		nn->vertex = graph[ind].v2;
		nn->next = NULL;
		for(tptr  = adjList[v1Ind], prev = NULL; tptr; prev = tptr, tptr=tptr->next);
		if(prev==NULL)
		   adjList[v1Ind] = nn;
		   else
		   prev->next = nn;
	}
	//	adjMatrix[v2Ind][v1Ind]= 1;
	{
		nn = (NODE_PTR) malloc(sizeof(NODE));
		nn->vertex = graph[ind].v1;
		nn->next = NULL;
		for(tptr  = adjList[v2Ind], prev = NULL; tptr; prev = tptr, tptr=tptr->next);
		if(prev==NULL)
		   adjList[v2Ind] = nn;
		   else
		   prev->next = nn;
	}
			}

            printf("----------THE GRAPH----------\n\n");
			for(ind = 0; ind < NODES; ind++, printf("\n"))
			{
				printf("        %c -> ", ind + 65);
			for(tptr = adjList[ind]; tptr->next; tptr = tptr->next)
			    printf("%c-> ", tptr->vertex);
			    printf("%c", tptr->vertex);
			}
printf("\n \n");
printf("          1.CONNECTIONS\n          2.MUTUAL CONNECTIONS\n          3.MAXIMUM CONNECTIONS\n          4.SECOND LEVEL CONNECTIONS\n          5.TRANSACTIONS\n\n");

printf("         Enter your choice : ");
scanf("%d",&choice);
switch (choice)
{
case 1:
    printf("\n         Enter the Node whose connections are to be shown : ");
    scanf("%c",&whatever);
    scanf("%c",&friends);
    findFriends(friends);
    printf("\n \n");
    break;

case 2:
    //MUTUAL FREINDS
    printf("\n         Enter the nodes whose mutual connections are to be found:");
    scanf("%c",&whatever);
    scanf("%c",&mfriends1);
    scanf(" %c",&mfriends2);
    findMutualFriends(mfriends1,mfriends2);
    printf("\n \n");
    break;

case 3:
    //MAX FRIENDS
    maxFriends();
    printf("\n \n");
    break;

case 4:
    //SECOND LEVEL CONNECTIONS
    printf("\n         Enter the node whose second level connections is to be found : ");
    scanf("%c",&whatever);
    scanf("%c",&connection);
    secondLevelConnections(connection);
    printf("\n \n");
    break;

case 5:
    //TRANSACTIONS
    printf("\n          Enter the node which wishes to perform the transaction: ");
    scanf("%c",&whatever);
    scanf("%c",&from);
    printf("\n          Enter the destination node:");
    scanf("%c",&whatever);
    scanf("%c",&to);
    //printf("%c %c",from,to);
    transaction(from,to);
    break;

default:
    printf("\n         INVALID CHOICE!!");

}










	return 0;
}






