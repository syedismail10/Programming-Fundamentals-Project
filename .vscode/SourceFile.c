#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
int main(){
	int Schoice,SiD,Mchoice,choice=1,MiD,supp_id;
	printf("\t\t\tWelcome to Medical Store Management System\n");
	while(choice != -1){
		printf("1-Customer\n2-Medicines\n3-Suppliers");
		printf("\nEnter where do you want to go: ");
		scanf("%d",&Mchoice);
		while (Mchoice != 1 && Mchoice != 2 && Mchoice !=3 && Mchoice !=-1){
			printf("Enter the correct choice again:\n1-Customer\n2-Medicines\n3-Suppliers");
			scanf("%d",&Mchoice);
			}
		switch(Mchoice){
			case 1:
				printf("\n1-Add a record\n2-Search a record\n3-Modify a current record\n4-Display all records");
				printf("\nEnter your desired choice : ");
				scanf("%d",&Schoice);
				switch(Schoice){
					case 1:
						AddNewRecord();
						break;
					case 2:
						printf("Enter the unique id of customer");
						scanf("%d",&SiD);
						SearchByID(SiD);
						break;
					case 3:
						printf("Enter the unique id of customer");
						scanf("%d",&SiD);
						Modify(SiD);
						break;
					case 4:
						Display();
						break;
					default:
						printf("Wrong choice please select again!");
				}
				break;
			case 2:
				printf("\n1-Add a Medicine\n2-Search a Medicine\n3-Modify a current medicine\n4-Display all Medicines\n5-Display Expired Medicines");
				printf("\nEnter your desired choice : ");
				scanf("%d",&Schoice);
				switch(Schoice){
					case 1:
						AddNewMed();
						break;
					case 2:
						printf("Enter the unique id of medicine");
						scanf("%d",&MiD);
						SearchByMID(MiD);
						break;
					case 3:
						printf("Enter the unique id of medicine");
						scanf("%d",&MiD);
						ModifyMeds(MiD);
						break;
					case 4:
						DisplayMedicines();
						break;
					case 5:
						GetExpMedicines();
						break;
					default:
						printf("Wrong choice please select again!");	
				}
				break;
			case 3:
				printf("\n1-Add suppliers record\n2-Modify current suppliers record\n3-Display all suppliers records");
				printf("\nEnter your desired choice: ");
				scanf("%d",&Schoice);
				switch(Schoice){
					case 1:
						addsupp();
						break;
					case 2:
						printf("\nEnter the unique id of supplier");
						scanf("%d",&supp_id);
						modifysupp(supp_id);
						break;
					case 3:
						displaysupp();
						break;	
					default:
						printf("Wrong choice please select again!");
				}
				break;
			default:
					printf("Wrong choice Please select again!");		
		}
		printf("\nDo you want to exit? Enter -1 to do so\n");
		scanf("%d",&choice);
	}
	return 0;
}
int AddNewRecord(){
	struct customerinfo{
		char Name[20],Pnum[12];
		int ID;
	};
	struct customerinfo customer;
	char buffer_out[256];
	int NumOfRecords,length,i,res;
	FILE *outfile;
	outfile = fopen("Customers.txt","a");
	if (outfile == NULL){
		printf("\nError opened file\n");
		exit (1);
	}
	printf("Enter how many records you want to add : ");
	scanf("%d",&NumOfRecords);
	for (i = 1;i<=NumOfRecords;i++) {
		printf("Enter Customer Name:\n");
		fflush(stdin);
		gets(customer.Name);
		printf("Enter unique ID of Customer : ");
		scanf("%d",&customer.ID);
		res = UniqueID(customer.ID);
		while (res == 1){
			printf("ID already exists, Enter a new one: ");
			scanf("%d",&customer.ID);
			res = UniqueID(customer.ID);
		}
		printf("Enter phone number of customer : ");
		scanf("%s",&customer.Pnum);
		sprintf_s(buffer_out,256, "%s %d %s\n",customer.Name,customer.ID,customer.Pnum);
		fwrite(buffer_out,sizeof(char),strlen(buffer_out),outfile);
	}
	fclose (outfile);
}
int SearchByID(int SiD){
	FILE * Fptr;
	Fptr = fopen("Customers.txt","r");
	char singleLine[150],name[20],num[12];
	int id;
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %d %s\n",name,&id,&num);
		if (id == SiD){
			printf("Record found!\n");
			printf("Customer Name : %s\nCustomer ID : %d\nCuStomer Number : %s",name,id,num);
			return 1;
			break;
		}
	}
	fclose(Fptr);
	return 0;
}
int Modify(int SiD){
	struct customerinfo{
		char Name[20],Pnum[12];
		int ID;
	};
	struct customerinfo customer;
	FILE * Fptr;
	FILE * Ftemp;
	Fptr = fopen("Customers.txt","r");
	Ftemp = fopen("replace.txt","w");
	char singleLine[150],newline[150],name[20],num[12];
	int id,c=0;
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %d %s\n",name,&id,&num);
		if (id == SiD){
				printf("Enter Customer Name:\n");
				fflush(stdin);
				gets(customer.Name);
				printf("Enter unique ID of Customer : ");
				scanf("%d",&customer.ID);
				printf("Enter phone number of customer : ");
				scanf("%s",&customer.Pnum);
				sprintf_s(newline,150, "%s %d %s\n",customer.Name,customer.ID,customer.Pnum);
				fputs(newline,Ftemp);
		} else {
			fputs(singleLine,Ftemp);
		}
	}
	fclose(Fptr);
	fclose(Ftemp);
	remove("Customers.txt");
	rename("replace.txt","Customers.txt");
	return 0;
}
int Display(){
	FILE * Fptr;
	Fptr = fopen("Customers.txt","r");
	char singleLine[150],name[20],num[12];
	int id;
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %d %s\n",name,&id,&num);
		printf("\nCustomer Name : %s\nCustomer ID : %d\nCuStomer Number : %s",name,id,num);
	}
	fclose(Fptr);
	return 0;
}
int UniqueID(int SiD){
	FILE * Fptr;
	Fptr = fopen("Customers.txt","r");
	char singleLine[150],name[20],num[12];
	int id;
	while (!feof(Fptr)){
		fgets(singleLine,150,Fptr);
		sscanf(singleLine,"%s %d %s\n",name,&id,&num);
		if (id == SiD){
			return 1;
			break;
		}
	}
	fclose(Fptr);
	return 0;
}
int AddNewMed(){
	struct Medicineinfo{
		char Name[20],CompanyN[30],Category[20];
		int ID,SaleCost,Quantity,emonth,edate,eyear;
	};
	struct Medicineinfo medicine;
	char buffer_out[256];
	int NumOfRecords,i,res;
	FILE *outfile;
	outfile = fopen("Medicines.txt","a");
	if (outfile == NULL){
		printf("\nError opened file\n");
		exit (1);
	}
	printf("Enter how many records you want to add : ");
	scanf("%d",&NumOfRecords);
	for (i = 1;i<=NumOfRecords;i++){
		printf("Enter Medicine Name:\n");
		fflush(stdin);
		gets(medicine.Name);
		printf("Enter unique ID of medicine : ");
		scanf("%d",&medicine.ID);
		res = UniqueMID(medicine.ID);
		while (res == 1){
			printf("ID already exists, Enter a new one: ");
			scanf("%d",&medicine.ID);
			res = UniqueMID(medicine.ID);
		}
		printf("Enter Company Name of Medicine : ");
		scanf("%s",&medicine.CompanyN);
		printf("Enter Category of medicine : Anti-Biotic, Syrup, Diabetic, Capsule, Inhaler, Injections");
		scanf("%s",&medicine.Category);
		printf("Enter Sale Cost in Rs: ");
		scanf("%d",&medicine.SaleCost);
		printf("Enter the quantity of medicine : ");
		scanf("%d",&medicine.Quantity);
		printf("Enter expiry date of medicine : Month,Day,year respectively in 2 integers");
		scanf("%d%d%d",&medicine.emonth,&medicine.edate,&medicine.eyear);
		sprintf_s(buffer_out,256, "%s %d %s %s %d %d %d/%d/%d\n",medicine.Name,medicine.ID,medicine.CompanyN,medicine.Category,medicine.SaleCost,medicine.Quantity,medicine.emonth,medicine.edate,medicine.eyear);
		fwrite(buffer_out,sizeof(char),strlen(buffer_out),outfile);
	}
	fclose (outfile);
}
int SearchByMID(int MiD){
	FILE * Fptr;
	Fptr = fopen("Medicines.txt","r");
	char singleLine[150],name[20],CompanyN[30],Category[20];
	int id,SaleCost,Quantity,emonth,edate,eyear;
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %d %s %s %d %d %d/%d/%d\n",name,&id,CompanyN,Category,&SaleCost,&Quantity,&emonth,&edate,&eyear);
		if (id == MiD){
			printf("Medicine found!");
			printf("\nMedicine Name : %s\nMedicine ID : %d\nCompany Name : %s\nCategory : %s\nSale Cost: %d\nQuantity : %d\nDateOfExpiry : %d/%d/%d",name,id,CompanyN,Category,SaleCost,Quantity,emonth,edate,eyear);
			fclose(Fptr);
			return 1;
		}
	}
	fclose(Fptr);
	return 0;
}
int UniqueMID(int MiD){
	FILE * Fptr;
	Fptr = fopen("Medicines.txt","r");
	char singleLine[150],name[20],CompanyN[30],Category[20];
	int ID,SaleCost,Quantity,emonth,edate,eyear;
		while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %d %s %s %d %d %d/%d/%d\n",name,&ID,CompanyN,Category,&SaleCost,&Quantity,&emonth,&edate,&eyear);
		if (ID == MiD){
			return 1;
			break;
		}
	}
	fclose(Fptr);
	return 0;}
int DisplayMedicines(){
	FILE * Fptr;
	Fptr = fopen("Medicines.txt","r");
	char singleLine[150],name[20],CompanyN[30],Category[20];
	int ID,SaleCost,Quantity,emonth,edate,eyear;
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %d %s %s %d %d %d/%d/%d\n",name,&ID,CompanyN,Category,&SaleCost,&Quantity,&emonth,&edate,&eyear);
		printf("\nMedicine Name : %s\nMedicine ID : %d\nCompany Name : %s\nCategory : %s\nSale Cost: %d\nQuantity : %d\nDateOfExpiry : %d/%d/%d",name,ID,CompanyN,Category,SaleCost,Quantity,emonth,edate,eyear);
	}
	fclose(Fptr);
	return 0;
}
int GetExpMedicines(){
	FILE *Fptr;
	Fptr = fopen("Medicines.txt","r");
	char singleLine[150],name[20],CompanyN[30],Category[20];
	int ID,SaleCost,Quantity,emonth,edate,eyear,DayN,h,m,year;
	time_t t = time(NULL);
    struct tm *tm = localtime(&t);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", tm));
    sscanf(s,"%d/%d/%d ",&DayN,&m,&year);
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %d %s %s %d %d %d/%d/%d\n",name,&ID,CompanyN,Category,&SaleCost,&Quantity,&emonth,&edate,&eyear);
		if (year > eyear){
			printf("\nMedicine expired ! ");
			printf("\nMedicine Name : %s\nMedicine ID : %d\nCompany Name : %s\nCategory : %s\nSale Cost: %d\nQuantity : %d\nDateOfExpiry : %d/%d/%d",name,ID,CompanyN,Category,SaleCost,Quantity,emonth,edate,eyear);
		}else if (year == eyear){
			if (m > emonth){
				printf("Medicine expired ! ");
			printf("\nMedicine Name : %s\nMedicine ID : %d\nCompany Name : %s\nCategory : %s\nSale Cost: %d\nQuantity : %d\nDateOfExpiry : %d/%d/%d",name,ID,CompanyN,Category,SaleCost,Quantity,emonth,edate,eyear);
			}else if (m == emonth){
				if (DayN>edate){
					printf("Medicine expired ! ");
			printf("\nMedicine Name : %s\nMedicine ID : %d\nCompany Name : %s\nCategory : %s\nSale Cost: %d\nQuantity : %d\nDateOfExpiry : %d/%d/%d",name,ID,CompanyN,Category,SaleCost,Quantity,emonth,edate,eyear);
				}else if(DayN==edate){
					printf("Medicine expired today ! ");
			printf("\nMedicine Name : %s\nMedicine ID : %d\nCompany Name : %s\nCategory : %s\nSale Cost: %d\nQuantity : %d\nDateOfExpiry : %d/%d/%d",name,ID,CompanyN,Category,SaleCost,Quantity,emonth,edate,eyear);
				}
			}
		}
		}
	fclose(Fptr);
	return 0;
}
int ModifyMeds(int MiD){
		char singleLine[150],name[20],CompanyN[30],Category[20];
	int ID,SaleCost,Quantity,emonth,edate,eyear,DayN,h,m,year;
	FILE * Fptr;
	FILE * Ftemp;
	Fptr = fopen("Medicines.txt","r");
	Ftemp = fopen("replace3.txt","w");
	char newline[150];
	int id,c=0,res;
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %d %s %s %d %d %d/%d/%d\n",name,&ID,CompanyN,Category,&SaleCost,&Quantity,&emonth,&edate,&eyear);
		if (ID == MiD){
				printf("Enter Medicine Name:\n");
				fflush(stdin);
				gets(name);
				printf("Enter unique ID of medicine : ");
				scanf("%d",&ID);
				res = UniqueMID(ID);
				while (res == 1){
				printf("ID already exists, Enter a new one: ");
				scanf("%d",&ID);
				res = UniqueMID(ID);
				}
				printf("Enter Company Name of Medicine : ");
				scanf("%s",&CompanyN);
				printf("Enter Category of medicine : Anti-Biotic, Syrup, Diabetic, Capsule, Inhaler, Injections");
				scanf("%s",&Category);
				printf("EnterSale Cost in Rs: ");
				scanf("%d",&SaleCost);
				printf("Enter the quantity of medicine : ");
				scanf("%d",&Quantity);
				printf("Enter expiry date of medicine : Month,Day,year respectively in 2 integers");
				scanf("%d%d%d",&emonth,&edate,&eyear);
				sprintf_s(newline,150, "%s %d %s %s %d %d %d/%d/%d\n", name, ID, CompanyN, Category, SaleCost, Quantity, emonth, edate, eyear);
				fputs(newline,Ftemp);
		} else {
			fputs(singleLine,Ftemp);
		}
	}
	fclose(Fptr);
	fclose(Ftemp);
	remove("Medicines.txt");
	rename("replace3.txt","Medicines.txt");
	return 0;
}
int addsupp() { // suppliers function starts from here
	struct supplierinfo {
		char name[30],email[50],phone[12];
		int s_id;
	};
	struct supplierinfo supplier;
	char bufferout[256];
	int n_suppliers,j,result,length;
	FILE *suppfile;
	suppfile = fopen("Supplier.txt","a");
	if(suppfile==NULL) {
		printf("\nError\n");
		exit(1);
	}
	printf("Enter how many suppliers records you want to add :");
	scanf("%d",&n_suppliers);
	for(j=1;j<=n_suppliers;j++) {
		printf("Enter Suppliers name:\n");
		fflush(stdin);
		gets(supplier.name);
		printf("Enter unique id of supplier: ");
		scanf("%d",&supplier.s_id);
		result=UniqueSID(supplier.s_id);
		while(result==1) {
			printf("Supplier id already exists,please enter a new one:");
			scanf("%d",&supplier.s_id);
			result=UniqueSID(supplier.s_id);
		}
	   printf("Enter phone number of the supplier: ");
	   scanf("%s",&supplier.phone);
	   printf("Enter email address of the supplier: ");
	   scanf("%s",&supplier.email);
	   sprintf_s(bufferout,256, "%s %s %d %s\n",supplier.name,supplier.email,supplier.s_id,supplier.phone);
	   fwrite(bufferout,sizeof(char),strlen(bufferout),suppfile);
	}
	fclose(suppfile);
}
modifysupp(int supp_id){
	struct supplierinfo{
		
		char name[20],phone[12],email[50];
		int s_id;
	};
	struct supplierinfo supplier;
	FILE * Fptr;
	FILE * Ftemp;
	Fptr = fopen("Supplier.txt","r");
	Ftemp = fopen("replace2.txt","w");
	char singleLine[150],newline[150],name[20],num[12],email[50];
	int id,c=0;
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine," %s %s %d %s\n",name,email,&id,&num);
		if (id == supp_id){
				
				printf("Enter supplier's Name:\n");
			    fflush(stdin);
				gets(supplier.name);
				printf("Enter unique ID of supplier : ");
				scanf("%d",&supplier.s_id);
				printf("Enter phone number of supplier: ");
				scanf("%s",&supplier.phone);
				printf("Enter email address of supplier: ");
				scanf("%s",&supplier.email);
				sprintf_s(newline,150, "%s %s %d %s\n",supplier.name,supplier.email,supplier.s_id,supplier.phone);
				fputs(newline,Ftemp);
		} else {
			fputs(singleLine,Ftemp);
		}
	}
	fclose(Fptr);
	fclose(Ftemp);
	remove("Supplier.txt");
	rename("replace2.txt","Supplier.txt");
	return 0;
}
 displaysupp(){
	FILE * Fptr;
	Fptr = fopen("Supplier.txt","r");
	char singleLine[150],name[20],phone[12],email[50];
	int s_id;
	while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %s %d %s\n",name,email,&s_id,phone);
		printf("\nSupplier Name : %s\nSupplier Email : %s\nSupplier ID : %d\nSupplier Number : %s",name,email,s_id,phone);
	}
	fclose(Fptr);
}
int UniqueSID(int MiD){
	FILE * Fptr;
	Fptr = fopen("Supplier.txt","r");
	char singleLine[150],name[20],phone[12],email[50];
	int s_id;
		while (fgets(singleLine,150,Fptr) != NULL){
		sscanf(singleLine,"%s %s %d %s\n",name,email,&s_id,phone);
		if (s_id == MiD){
			return 1;
			break;
		}
	}
	fclose(Fptr);
	return 0;}
