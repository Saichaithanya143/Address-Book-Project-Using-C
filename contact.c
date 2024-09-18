#include <stdio.h>
#include<ctype.h>
#include <stdlib.h>
#include <string.h>
#include<stdio_ext.h>
#include "contact.h"
#include "file.h"
#include "populate.h"

// Define a comparison function for sorting contacts by name
int compareByName(const void *a, const void *b) {
	return strcmp(((Contact *)a)->name, ((Contact *)b)->name);
}

// Define a comparison function for sorting contacts by phone number
int compareByPhone(const void *a, const void *b) {
	return strcmp(((Contact *)a)->phone, ((Contact *)b)->phone);
}

// Define a comparison function for sorting contacts by email
int compareByEmail(const void *a, const void *b) {
	return strcmp(((Contact *)a)->email, ((Contact *)b)->email);
}

void listContacts(AddressBook *addressBook) 
{
	// Sort contacts based on the chosen criteria

	int i;
	printf("<---------- The Data of All Contacts ----------->\n");
	printf("S.NO\t\tNAME\t\tCONTACT_NO\t\tEMAIL_TD\n");
	for(i=0;i<addressBook->contactCount;i++)
	{
		printf("%d\t\t%-20s%-20s%-20s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	}



}

void initialize(AddressBook *addressBook) {
	addressBook->contacts = malloc(100 * sizeof(Contact));
        addressBook->contactCount=0;
	populateAddressBook(addressBook);

	// Load contacts from file during initialization (After files)
	//loadContactsFromFile(addressBook);
}
void saveContactsToFile(AddressBook *addressBook)
{
	FILE *fptr;
	if((fptr=fopen("addressbook.csv","w"))==NULL)
	{ 
		fprintf(stderr,"The file doesn't exist");
	}

	int i;
	fprintf(fptr,"#%d#\n",addressBook->contactCount);
	for(i=0;i<addressBook->contactCount;i++)
	{
		fprintf(fptr,"%s,%s,%s\n",addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
	} 
	fclose(fptr);

}

void saveAndExit(AddressBook *addressBook) {
	saveContactsToFile(addressBook); // Save contacts to file
	exit(EXIT_SUCCESS); // Exit the program
}


void createContact(AddressBook *addressBook)
{
	/* Define the logic to create a Contacts */

	//Data for Name


	__fpurge(stdin);

	printf("Enter the name : \n");

	scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].name);


	//Data for Mobile Number

	int flag=0;
	int phonedigit=0;
	int res=0;
	do
	{
		__fpurge(stdin);

		printf("Please Enter the valid Phone number with 10 digits : \n");

		scanf("%[^\n]",addressBook->contacts[addressBook->contactCount].phone);


		while(addressBook->contacts[addressBook->contactCount].phone[phonedigit]!='\0')
		{
			flag=0;
			if(!(addressBook->contacts[addressBook->contactCount].phone[phonedigit]>='0' && addressBook->contacts[addressBook->contactCount].phone[phonedigit]<='9'))
			{ 
                                printf("Phone Number must contain 10 digits from '0' to '9' only\n");
				flag=1;
				break; 
			}
			phonedigit++;
		}

		if(flag==0 || phonedigit==10)
		{                   
			for(int i=0;i<addressBook->contactCount;i++)
			{ 
				res=strcmp(addressBook->contacts[addressBook->contactCount].phone,addressBook->contacts[i].phone); 
				if(res==0)
				{
					res=0;
					printf("The contact is already registred\n");
					break;
				} 
				else if(res!=0)
				{ 
					phonedigit=0;
					while(addressBook->contacts[addressBook->contactCount].phone[phonedigit]!='\0') 
					{ 
						flag=0;
						if(!(addressBook->contacts[addressBook->contactCount].phone[phonedigit]>='0' && addressBook->contacts[addressBook->contactCount].phone[phonedigit]<='9')) 
						{ 
							flag=1;
							break;
						} 
						phonedigit++;
					} 
				}

			} 
		}
	}while(flag==1 || phonedigit!=10 || res==0);



	//Data for Email_id


	char strvalid[10]=".com";
	char ch='@';
	int atrate=0;
	int dot=0;
	int email_check=0;
	char email[100];
	int ind=0;
	int at_ind=0;
	int dot_ind=0;
	int email_flag=0;
	int at_flag=0;

	do
	{
		printf("Please Enter the valid Email_id (e.g.abc@example.com): \n");
		__fpurge(stdin);

		scanf("%[^\n]",email);
		ind=0;
		at_ind=0;
		dot_ind=0; 

		for(int i=0;i<3;i++)
		{ 
			email_flag=0;
			if((email[i]>='0' && email[i]<='9') || (email[i]>='a' && email[i]<='z') || (email[i]>='A' && email[i]<='Z'))
			{
				email_flag=1;
			}
			else if(email_flag==0)
			{
				email_flag=0;
                                printf("Email id must contain atleast 3 characters before '@' \n");
				break;
			}

		}

		if(email_flag==1)
		{
			while(email[ind]!='\0')
			{  
				if(email[ind]=='@')
				{ 
					at_flag=0;
					at_ind=ind;
					if((email[at_ind+1]>='0' && email[at_ind+1]<='9') || (email[at_ind+1]>='a' && email[at_ind+1]<='z') || (email[at_ind+1]>='A' && email[at_ind+1]<='Z'))
					{
						at_flag=1;
					}
					else
					{
						at_flag=0;
                                                printf("Email id must contain atleast 1 character after '@' \n");
					} 
				}
				if(email[ind]=='.')
				{ 
					dot_ind=ind;
				}        
				ind++;
			}

			if(at_ind<dot_ind)
			{
				atrate=0;
				dot=0;

				char *at=strchr(email,ch);

				if(at)
				{
					atrate++;

				}

				char *dotcom=strstr(email,strvalid);

				if(dotcom)
				{
					dot++;
				} 

			}

			strcpy(addressBook->contacts[addressBook->contactCount].email,email);

			if(atrate!=0 || dot!=0 || at_ind<dot_ind)
			{ 
				for(int i=0;i<addressBook->contactCount;i++)
				{
					email_check=strcmp(addressBook->contacts[addressBook->contactCount].email,addressBook->contacts[i].email);
					if(email_check==0)
					{
						email_check=0;
						printf("The Email id is already registered\n");
						break;
					}
					else if(email_check!=0)
					{ 
						atrate=0;
						dot=0;
						char *at=strchr(email,ch);
						if(at)
						{
							atrate++;
						}
						char *dotcom=strstr(email,strvalid);
						if(dotcom)
						{ 
							dot++;
						}
					}
				}
			}
		}
	}while(email_flag==0 || at_flag==0 || atrate==0 || dot==0 || email_check==0 || at_ind>dot_ind);


	addressBook->contactCount++;
}
void searchContact(AddressBook *addressBook) 
{
	/* Define the logic for search */
	printf("Search Contact by through\n");
	printf("1.Name\n2.phone number\n3.Email_id\n");
	int option;
	printf("Choose the option : ");

	__fpurge(stdin);
	scanf("%d",&option);

	char search_read[100];
	int search_found=0;
	int i;
        int res=0;

	switch(option)
	{ 

		case 1:

			printf("Enter Name to Search : \n");

			__fpurge(stdin);
			scanf("%[^\n]",search_read);

			printf("<-----The Details Matching with above Search are----->\n");
			printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
			for(i=0;i<addressBook->contactCount;i++)
			{    

				if((strstr(addressBook->contacts[i].name,search_read)!=NULL))
				{ 
					search_found=1;
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(search_found!=1)
			{
				printf("<-----NO DATA FOUND----->\n");
			}

			break; 
		case 2:

			printf("Enter Phone Number to Search : \n");

			__fpurge(stdin);
			scanf("%[^\n]",search_read);

			for(i=0;i<addressBook->contactCount;i++)
			{    

				res=strcmp(addressBook->contacts[i].phone,search_read);
				if(res==0)
				{ 
					search_found=1;

					printf("<-----The Details Matching with above Search are----->\n");
					printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(search_found!=1)
			{
				printf("<-----NO DATA FOUND----->\n");
			} 
			break;


		case 3:

			printf("Enter Email id to Search : \n");

			__fpurge(stdin);
			scanf("%[^\n]",search_read);

			for(i=0;i<addressBook->contactCount;i++)
			{    

				res=strcmp(addressBook->contacts[i].email,search_read);
				if(res==0)
				{ 
					search_found=1;

					printf("<-----The Details Matching with above Search are----->\n");
					printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(search_found!=1)
			{
				printf("<-----NO DATA FOUND----->\n");
			}
			break;
	}

}

void editContact(AddressBook *addressBook)
{
	/* Define the logic for Editcontact */
	int edit_data=0;
	printf("Edit Contact by through\n");
	printf("1.Name\n2.Phone Number\n3.Email id\n");
	printf("Pleae Select the option : ");
	scanf("%d",&edit_data);

	int editoption=0;
	int edit_choice=0;
	char edit_name[100];
	char edit_phone[100];
	char edit_email[100];
	int res=0;
	int flag=0;
	int phonedigit=0;
	char edit_read[100];
	int i;
	int edit_found=0;

	char strvalid[10]=".com";
	char ch='@';
	int atrate=0;
	int dot=0;
	int email_check=0;
	int ind=0;
	int email_flag=0;
	int at_ind=0;
	int dot_ind=0;
	int at_flag=0;
	int edit_store=0;

	switch(edit_data)
	{
		case 1:

			printf("Enter Name to Search for edit the details : \n");

			__fpurge(stdin);
			scanf("%[^\n]",edit_read);

			printf("<-----The Details Matching with above Search are----->\n");
			printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
			for(i=0;i<addressBook->contactCount;i++)
			{    

				if((strstr(addressBook->contacts[i].name,edit_read)!=NULL))
				{ 
					edit_found=1;
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}

			if(edit_found==1)
			{

				printf("Please select the serial number to edit the details : ");  						                                       __fpurge(stdin); 						
				scanf("%d",&editoption);

				printf("Enter the Name to Edit : \n");

				__fpurge(stdin);
				scanf("%[^\n]",edit_name);

				strcpy(addressBook->contacts[editoption].name,edit_name);

				printf("The Name of Contact %d is Edited Successfully\n",editoption);
				printf("The details of Contact %d after edit is\n",editoption);
				printf("Name\t\t\tPhone Number\t\tEmail id\n");
				printf("%s\t\t%s\t\t%s\n",addressBook->contacts[editoption].name,addressBook->contacts[editoption].phone,addressBook->contacts[editoption].email);
				break;

			}
			else
			{ 
				printf("<-----NO DATA FOUND---->\n");
			}

			break;
		case 2:
			printf("Enter Phone Number to search for edit the details : \n");

			__fpurge(stdin);
			scanf("%[^\n]",edit_read);

			for(i=0;i<addressBook->contactCount;i++)
			{    

				res=strcmp(addressBook->contacts[i].phone,edit_read);
				if(res==0)
				{
					edit_store=i;
					edit_found=1;
					printf("<-----The Details Matching with above Search are----->\n");
					printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(edit_found==1)
			{

				do
				{

					printf("Enter the New Valid Phone Number with 10 digits : \n");

					__fpurge(stdin);
					scanf("%[^\n]",edit_phone);

					while(edit_phone[phonedigit]!='\0')
					{
						flag=0;
						if(!(edit_phone[phonedigit]>='0' && edit_phone[phonedigit]<='9'))
						{
							flag=1;
                                                        printf("The Phone Number must contain 10 digits from '0' to '9' only");
							break;
						}
						phonedigit++;
					}

					if(flag==0 || phonedigit==10)
					{
						for(int i=0;i<addressBook->contactCount;i++)
						{
							res=strcmp(edit_phone,addressBook->contacts[i].phone);
							if(res==0)
							{
								res=0;
								printf("The contact is already registred\n");
								break;
							}
							else if(res!=0)
							{
								phonedigit=0;
								while(edit_phone[phonedigit]!='\0')
								{
									flag=0;
									if(!(edit_phone[phonedigit]>='0' && edit_phone[phonedigit]<='9'))
									{
										flag=1;
										break;
									}
									phonedigit++;
								}
							}

						}
					}
				}while(flag==1 || phonedigit!=10 || res==0);


				strcpy(addressBook->contacts[edit_store].phone,edit_phone);

				printf("The Phone Number of Contact %d is Edited Successfully\n",edit_store);
				printf("The details of Contact %d after edit is\n",edit_store);
				printf("Name\t\t\tPhone Number\t\tEmail id\n");
				printf("%s\t\t%s\t\t%s\n",addressBook->contacts[edit_store].name,addressBook->contacts[edit_store].phone,addressBook->contacts[edit_store].email);
				break;


			}
			else
			{
				printf("<-----NO DATA FOUND------>\n");
			}
			break;

		case 3:
			printf("Enter Email id to Search for edit the details : \n");

			__fpurge(stdin);
			scanf("%[^\n]",edit_read);

			for(i=0;i<addressBook->contactCount;i++)
			{     
				res=strcmp(addressBook->contacts[i].email,edit_read);
				if(res==0)
				{
					edit_store=i;
					edit_found=1;
					printf("<-----The Details Matching with above Search are----->\n");
					printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				} 
			}

			if(edit_found==1)
			{
				do
				{
					printf("Enter the New valid Email_id (e.g.abc@example.com): \n");
					__fpurge(stdin);

					scanf("%[^\n]",edit_email);
					ind=0;
					at_ind=0;
					dot_ind=0; 

					for(int i=0;i<3;i++)
					{ 
						email_flag=0;
						if((edit_email[i]>='0' && edit_email[i]<='9') || (edit_email[i]>='a' && edit_email[i]<='z') || (edit_email[i]>='A' && edit_email[i]<='Z'))
						{
							email_flag=1;
						}
						else if(email_flag==0)
						{
							email_flag=0;
                                                        printf("Please Enter atleast 3 characters before '@' ");
							break;
						}

					}

					if(email_flag==1)
					{
						while(edit_email[ind]!='\0')
						{  
							if(edit_email[ind]=='@')
							{ 
								at_flag=0;
								at_ind=ind;
								if((edit_email[at_ind+1]>='0' && edit_email[at_ind+1]<='9') || (edit_email[at_ind+1]>='a' && edit_email[at_ind+1]<='z') || (edit_email[at_ind+1]>='A' && edit_email[at_ind+1]<='Z'))
								{
									at_flag=1;
								}
								else
								{
									at_flag=0;
                                                                        printf("Please Enter atleast 1 character after '@' ");
								} 
							}
							if(edit_email[ind]=='.')
							{ 
								dot_ind=ind;
							}        
							ind++;
						}
					}

					if(at_ind<dot_ind)
					{
						atrate=0;
						dot=0;
						char *at=strchr(edit_email,ch);

						if(at)
						{
							atrate++;

						}

						char *dotcom=strstr(edit_email,strvalid);

						if(dotcom)
						{
							dot++;
						}

					}
					if(atrate!=0 || dot!=0 || at_ind<dot_ind)
					{
						for(int i=0;i<addressBook->contactCount;i++)
						{
							email_check=strcmp(edit_email,addressBook->contacts[i].email);
							if(email_check==0)
							{
								email_check=0;
								printf("The Email id is already registered\n");
								break;
							}
							else if(email_check!=0)
							{
								atrate=0;
								dot=0;
								char *at=strchr(edit_email,ch);
								if(at)
								{
									atrate++;
								}
								char *dotcom=strstr(edit_email,strvalid);
								if(dotcom)
								{
									dot++;
								}
							}
						}
					}
				}while(email_flag==0 || at_flag==0 || atrate==0 || dot==0 || email_check==0 || at_ind>dot_ind);


				strcpy(addressBook->contacts[edit_store].email,edit_email);

				printf("The Email id of Contact %d is Edited Successfully\n",edit_store);
				printf("The details of Contact %d after edit is\n",edit_store);
				printf("Name\t\t\tPhone Number\t\tEmail id\n");
				printf("%s\t\t%s\t\t%s\n",addressBook->contacts[edit_store].name,addressBook->contacts[edit_store].phone,addressBook->contacts[edit_store].email);
				break;
			}
			else
			{ 
				printf("<-----NO DATA FOUND----->\n");
			}
			break;


	}

}
void deleteContact(AddressBook *addressBook)
{
	/* Define the logic for deletecontact */

	printf("Delete a Contact by using through\n");
	printf("1.Name\n2.Phone number\n3.Email id\n");

	int delete_option=0;
	printf("Enter the option : ");
	scanf("%d",&delete_option);

	int delete_found=0;
	char delete_read[100];
	int delete_choice=0;
	int delete_store=0;
	int i;
        int res=0;

	switch(delete_option)
	{

		case 1:

			printf("Enter Name to Search for delete the details : \n");

			__fpurge(stdin);
			scanf("%[^\n]",delete_read);

			printf("<-----The Details Matching with above Search are----->\n");
			printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
			for(i=0;i<addressBook->contactCount;i++)
			{    

				if((strstr(addressBook->contacts[i].name,delete_read)!=NULL))
				{ 
					delete_found=1;
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(delete_found==1)
			{
				printf("Please Enter the serial number to delete the details : ");

				__fpurge(stdin);
				scanf("%d",&delete_choice);


				for(int i=delete_choice;i<addressBook->contactCount;i++)
				{
					strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
					strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
					strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email); 
				}
                                 addressBook->contactCount--;
				printf("So the details of the Contact %d Name is deleted successfully\n",delete_choice);
			}
			else
			{ 
				printf("<-----NO DATA FOUND----->");
			}
			break;


		case 2:

			printf("Enter Phone Number to Search for delete the details : \n");

			__fpurge(stdin);
			scanf("%[^\n]",delete_read);

			for(i=0;i<addressBook->contactCount;i++)
			{    

				res=strcmp(addressBook->contacts[i].phone,delete_read);
				if(res==0)
				{ 
					delete_store=i;
					delete_found=1;
					printf("<-----The Details Matching with above Search are-----> : \n");
					printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(delete_found==1)
			{

				for(int i=delete_store;i<addressBook->contactCount;i++)
				{
					strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
					strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
					strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email); 
				}
                                addressBook->contactCount--;
				printf("So the details of the Contact %d Phone Number is deleted successfully\n",delete_store);
			}
			else
			{ 
				printf("<-----NO DATA FOUND----->");
			}
			break;


		case 3:

			printf("Enter Email id to Search for delete the details : \n");

			__fpurge(stdin);
			scanf("%[^\n]",delete_read);


			for(i=0;i<addressBook->contactCount;i++)
			{    

				res=strcmp(addressBook->contacts[i].email,delete_read);
				if(res==0)
				{ 
					delete_store=i;
						delete_found=1;

					printf("<-----The Details Matching with above Search are----->\n");
					printf("S.no\t\t\tName\t\t\tContact_No\t\tEmail_id\n");
					printf("%d\t\t\t%s\t\t%s\t\t%s\n",i,addressBook->contacts[i].name,addressBook->contacts[i].phone,addressBook->contacts[i].email);
				}
			}
			if(delete_found==1)
			{

				for(int i=delete_store;i<addressBook->contactCount;i++)
				{
					strcpy(addressBook->contacts[i].name,addressBook->contacts[i+1].name);
					strcpy(addressBook->contacts[i].phone,addressBook->contacts[i+1].phone);
					strcpy(addressBook->contacts[i].email,addressBook->contacts[i+1].email); 
				}
                                 addressBook->contactCount--;
				printf("So the details of the Contact %d Name is deleted successfully\n",delete_store);
			}
			else
			{ 
				printf("<-----NO DATA FOUND----->");
			}
			break;

	}
}

