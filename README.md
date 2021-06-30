		***************************************** About The Project ************************************************

1. The project aims to develop a banking system that is user-friendly and multifunctional.

2. I have used two separate database files(.dat files) for storing the normal user's and joint account 
   user's data.Two more database files also have been used for deleting the particular account. 

3. Three types of login created: normal user, joint account user,administrator.

4. Once you login as administrator, you can be able to add, delete, search for a specific
   account (normal as well as joint).

5. Once the customer connect to the server, you get the login and password prompt.

6. After successful login, you get the menu for example:
   Do you want to: Deposit, Withdraw, Balance Enquiry, Password Change, View details, Exit.
  
7. once you login as a joint account holder, you get the menu for example:
   Do you want to: Deposit, Withdraw, Balance Enquiry, Password Change, View details, Exit.
  
8. socket programming and proper file locking is used for joint users.
   No IPC mechanism is used in this project.
   
		************************************* Instructions To Run The Project ***************************************
 
1. Compile the server.c file using gcc server.c -o server 

2. Compile the client.c file using gcc client.c -o client 

3. Run the server file using the ./server any port no.  EX:- ./server 55896 

4. Run the client file using the ./server the same port no. used in the server side.  EX:- ./client 55896
   (NOTE : There is no restriction on the port numbers used ,just make you use the same port
   number on client side that you've used on the server side.)
   
5. For admin login Purpose :-
   Username : 'admin'          Password : 'password' 
   
****************************************************************************************************************************************   
