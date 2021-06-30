#include <sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>
#include<stdio.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<stdlib.h>

void mainMenu(int);
void displayMenu(int);
void admin_functions(int);
void jointAccountLogin(int);
void jointDisplayMenu(int);


void deleteAccount(int sd)
{
	char uname[20],buffer[38];

	printf("Enter the username to be deleted: ");
	scanf(" %s", uname);

	write(sd, uname, sizeof(uname));
	read(sd, buffer, sizeof(buffer));
	
	printf("%s",buffer);
	admin_functions(sd);
}

void deleteJointAccount(int sd)
{
	char uname1[20], uname2[20], buffer[38];
	memset(buffer,0,sizeof(buffer));

	printf("Enter Username 1 to delete: ");
	scanf(" %s",uname1);
	printf("Enter Username 2 to delete: ");
	scanf(" %s",uname2);

	write(sd, uname1, sizeof(uname1));
	write(sd, uname2, sizeof(uname2));

	read(sd, buffer, sizeof(buffer));

	printf("%s",buffer);
	admin_functions(sd);
}

void newJointAccount(int sd)
{
	char uname1[20], pass[20], uname2[20], buffer[30];
	memset(buffer,0,sizeof(buffer));
	printf("Enter first username: ");
	scanf(" %s", uname1);
	printf("Enter second username: ");
	scanf(" %s", uname2);
	printf("Enter password: ");
	scanf(" %s", pass);

	write(sd, uname1, sizeof(uname1));
	//write(sd, pass1, sizeof(pass1));
	write(sd, uname2, sizeof(uname2));
	write(sd, pass, sizeof(pass));

	read(sd, buffer, sizeof(buffer));
	printf("%s\n", buffer);
        admin_functions(sd);
}

void signUp(int sd)
{
	int account_id;
	char uname[20],pass[20], buffer[30];
        
	printf("Enter username: ");
	scanf(" %s",uname);
	printf("Enter password: ");
	scanf(" %s",pass);

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));
        
        memset(buffer,0,sizeof(buffer));
	read(sd, buffer, sizeof(buffer));
	printf("%s", buffer);
        admin_functions(sd);
}
void login(int sd)
{
	char buffer[30];
	char uname[20],pass[20];
	int flag;

	printf("Enter username: ");
	scanf(" %s",uname);
	//printf("Enter password: ");
	//scanf(" %s",pass);
	strcpy(pass,getpass("Enter password: "));

	write(sd, uname,sizeof(uname));
	write(sd, pass, sizeof(pass));

	read(sd, &flag, sizeof(flag));
	memset(buffer,0,sizeof(buffer));
	read(sd, buffer, sizeof(buffer));
	printf("%s\n",buffer);

	if(flag==1)
		displayMenu(sd);
	else
		mainMenu(sd);


}

void jointAccountLogin(int sd)
{
	char buffer[30];
	char uname1[20],pass[20],uname2[20];
	int flag;

	printf("Enter first username: ");
	scanf(" %s",uname1);
	
	printf("Enter second username: ");
	scanf(" %s",uname2);
	
	printf("Enter the password : ");
	scanf(" %s",pass);

	write(sd, uname1,sizeof(uname1));
	write(sd, uname2,sizeof(uname2));
	write(sd, pass, sizeof(pass));

	read(sd, &flag, sizeof(flag));
	memset(buffer,0,sizeof(buffer));
	read(sd, buffer, sizeof(buffer));
	printf("%s",buffer);

	if(flag==1)
	{
		jointDisplayMenu(sd);
	}
	else
		mainMenu(sd);

}

void viewDetails(int sd)
{
	char uname[20];
	int acc_id, balance;

	read(sd,uname, sizeof(uname));
	read(sd,&acc_id, sizeof(acc_id));
	read(sd,&balance, sizeof(balance));

	printf("\nUsername : %s  , Account ID : %d  , Balance : %d  \n",uname,acc_id,balance);
	displayMenu(sd);
}

void viewJointDetails(int sd)
{
	char uname1[20], uname2[20];
	int acc_id, balance;

	read(sd,uname1, sizeof(uname1));
	read(sd,uname2, sizeof(uname2));
	read(sd,&acc_id, sizeof(acc_id));
	read(sd,&balance, sizeof(balance));

	printf("\nUsername1 : %s  ,Username2 : %s  , Account ID : %d  , Balance : %d  \n",uname1,uname2,acc_id,balance);
	jointDisplayMenu(sd);
}

void deposit(int sd)
{
	int amount;
	char buffer[37];
	printf("\nEnter amount to deposit: ");
	scanf("%d",&amount);
	
	write(sd, &amount, sizeof(amount));
	read(sd, &amount, sizeof(amount));
	printf("Account Balance: %d\n",amount);
	memset(buffer,0,sizeof(buffer));
	read(sd,&buffer,sizeof(buffer));
	printf("%s\n",buffer);
	
	displayMenu(sd);
}

void jointDeposit(int sd)
{
	int amount;
	char buffer[37];
	printf("\nEnter amount to deposit: ");
	scanf("%d",&amount);
	
	write(sd, &amount, sizeof(amount));
	read(sd, &amount, sizeof(amount));
	printf("Acccount Balance: %d\n",amount);
	memset(buffer,0,sizeof(buffer));
	read(sd,&buffer,sizeof(buffer));
	printf("%s\n",buffer);
	
	jointDisplayMenu(sd);
}

void jointWithdraw(int sd)
{
	int amount,flag;
	printf("\nEnter amount to withdraw: ");
	scanf("%d",&amount);

	write(sd, &amount, sizeof(amount));
	read(sd, &flag, sizeof(flag));
	
	if(flag==0)
	{
		printf("*****Insufficient Balance*****\n");
		read(sd, &amount, sizeof(amount));
		printf("Balance: %d",amount);
	}
	else if(flag==1)
	{
	        printf("*****please provide valid amount*****\n");
	        read(sd, &amount, sizeof(amount));
		printf("Account Balance : %d\n",amount);
	}
	else
	{
		read(sd, &amount, sizeof(amount));
		printf("Modified Balance: %d",amount);

	}
	
	jointDisplayMenu(sd);
}





void withdraw(int sd)
{
	int amount,flag;
	printf("\nEnter amount to withdraw: ");
	scanf("%d",&amount);

	write(sd, &amount, sizeof(amount));
	read(sd, &flag, sizeof(flag));
	
	if(flag==0)
	{
		printf("*****Insufficient Balance*****\n");
		read(sd, &amount, sizeof(amount));
		printf("Account Balance : %d\n",amount);
	}
	else if(flag==1)
	{
	        printf("*****please provide valid amount*****\n");
	        read(sd, &amount, sizeof(amount));
		printf("Account Balance : %d\n",amount);
	}
	else
	{
		read(sd, &amount, sizeof(amount));
		printf("Modified Acoount Balance : %d\n",amount);

	}
	
	displayMenu(sd);
}

void jointPassChange(int sd)
{
	char pass[20];
	
	printf("\nEnter the new Password : ");
	scanf("%s",pass);
    

	write(sd,pass,sizeof(pass));
	mainMenu(sd);
	
}



void passChange(int sd)
{
	char pass[20];
	
	printf("Enter the new Password : ");
	scanf(" %s",pass);

	write(sd,pass,sizeof(pass));
	printf("*****Password changed successfully*****\n");
	mainMenu(sd);
	
}

void displayMenu(int sd)
{
	int choice;
	printf("\n     1.View Details\n     2.Deposit\n     3.Withdraw\n     4.Password Change\n     5.EXIT\n");
	printf("Enter your choice: "); 
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: system("clear");viewDetails(sd);
				break;
		case 2: system("clear");deposit(sd);
				break;
		case 3: system("clear");withdraw(sd);
				break;
		case 4: system("clear");passChange(sd);
				break;
		case 5: system("clear");mainMenu(sd);
				break;
		default: printf("Enter proper choice");
		         displayMenu(sd);
				break;

	}
}

void jointDisplayMenu(int sd)
{
	int choice;
	printf("\n  1.View Details\n  2.Deposit\n  3.Withdraw\n  4.Password Change\n  5.EXIT\n");
	printf("Enter your choice : ");
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: system("clear");viewJointDetails(sd);
				break;
		case 2: system("clear");jointDeposit(sd);
				break;
		case 3: system("clear");jointWithdraw(sd);
				break;
		case 4: system("clear");jointPassChange(sd);
				break;
		case 5: system("clear");mainMenu(sd);
				break;
	

	}

}

void admin_functions(int sd)
{
	int choice;
	
	printf("\n     1.Add Account\n     2.Delete Account\n     3.Search Account\n     4.Add Joint Account\n     5.Delete Joint Account\n     6.Search Joint Account\n     7.Exit\nEnter your choice : ");
	scanf("%d", &choice);
	
	char buffer[56], uname[20], pass[20], uname1[20], uname2[20];
	write(sd, &choice, sizeof(choice));
	
	switch(choice)
	{
		case 1:system("clear");signUp(sd);
			break;
		case 2:system("clear");deleteAccount(sd);
			break;
		case 3:system("clear");printf("Enter username to search : ");
			scanf(" %s", uname);
			write(sd, uname, sizeof(uname));
			memset(buffer,0,sizeof(buffer));
			read(sd, &buffer, sizeof(buffer));
			printf(" %s", buffer);
			admin_functions(sd);
			break;
		case 4:system("clear");newJointAccount(sd);
			break;
		case 5:system("clear");deleteJointAccount(sd);
			break;
		case 6:system("clear");printf("Enter username 1 to search: ");
			scanf("%s", uname1);
			printf("Enter username 2 to search: ");
			scanf("%s", uname2);
			write(sd, uname1, sizeof(uname1));
			write(sd, uname2, sizeof(uname2));
			memset(buffer,0,sizeof(buffer));
			read(sd, &buffer, sizeof(buffer));
			printf("%s\n", buffer);
			admin_functions(sd);
			break;
		case 7:system("clear");mainMenu(sd);
	}
}

void adminLogin(int sd)
{
	char uname[20], pass[20], buffer[37];
	int flag;
	
	printf("Enter the admin username: ");
	scanf(" %s",uname);
	//printf("Enter admin password: ");
	//scanf(" %s",pass);
	strcpy(pass,getpass("Enter admin password : "));
	
	write(sd, uname, sizeof(uname));
	write(sd, pass, sizeof(pass));
	read(sd, &flag, sizeof(flag));
	memset(buffer,0,sizeof(buffer));
	read(sd, buffer, sizeof(buffer));
	
	printf("%s\n",buffer);
	if(flag == 1)
		admin_functions(sd);
	else
		mainMenu(sd);
}

void mainMenu(int sd)
{
	int choice;

	printf("     1.LOGIN\n     2.ADMIN LOGIN\n     3.JOINT ACCOUNT LOGIN\n     4.EXIT\n");
	printf("Enter your choice: ");
	scanf("%d",&choice);

	write(sd, &choice, sizeof(choice));

	switch(choice)
	{
		case 1: system("clear");login(sd);
				break;
		case 2: system("clear");adminLogin(sd);
				break;
		case 3: system("clear");jointAccountLogin(sd);
				break;
		case 4: system("clear");exit(0);
				break;
		default: printf("Please provide valid choice\n");mainMenu(sd);break;		

	}
}

int main(int argc,char *argv[])
{
	
	struct sockaddr_in server;
	int sd;
	char buffer[80];
	sd = socket(AF_INET, SOCK_STREAM,0);

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(atoi(argv[1]));

	connect(sd, (struct sockaddr *)(&server), sizeof(server));
	
	mainMenu(sd);
	close(sd);
	return 0;
}

