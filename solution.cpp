#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

//Function declaration
void user_role();
void view_cars();
void view_rented_cars(fstream &Database,char role,int id);
int string_to_int(string s);
double string_to_double(string s);
long int string_to_long(string s);

//Create classes
class User{
	protected:
		string name;
		int id;
		string password;
		friend void view_rented_cars(char role,int id);
};

class Customer : public User{
	private:
		double customer_record;
		int cars_rented;
		map<int, bool> id_cars_rented;
		double fine_due;
		
	public:
		static int cust_count;
		
		friend int check_name_password(string name,string password,char role,int size);
		friend bool customer_func();
		friend void view_rented_cars(char role,int id);
		friend bool rent_car(char role,string name,int self_id);
		friend void update_database(char role,int id);
		friend void view_all(string type);
		friend void add(string type);
		friend void del(string type);
		friend void update(string type);
		friend void search(string type);
		friend void load_customers();
		
		Customer(string name,string password){
			this->name=name;
			this->password=password;
			this->id=cust_count;
			this->customer_record=5.0;
			this->cars_rented=0;
			this->fine_due=0.0;
		
			cust_count++;
		}
		
		//Shows the dues of a customer
		void show_due(){
			cout<<fine_due<<"\n";
		}
		
		//Clear dues
		void clear_due(){
			string amt;
			double amount=0;
			bool valid=0;
			while(!valid){
				cout<<"Enter the amount you want to clear...\n\n";
				cin>>amt;
				if(amt=="q") return;
				
				amount = string_to_double(amt);
				if(amount==-1){
					cout<<"Invalid amount! Try again...\n\n";
				}
				else if(amount<=0 || amount>fine_due){
					cout<<"Invalid amount! Try again...\n\n";
				}
				else{
					valid=1;
				}
			}
			fine_due-=amount;
			
			cout<<"\nSuccessfully cleared from due the given amount.\n\n";
		}
		
		//Return a car
		int return_request(){
			bool success=0,exit=0;
			
			int id=0;
			int days=0;
			while(!success || !exit){
				cout<<"Enter the ID of the car you want to return.\n\n";
			
				string sid;
				cin>>sid;
				if(sid=="q"){
					exit=1;
					return -1;
				}
				
				for(int i=0;i<sid.size();i++){
					id=(10*id)+(sid[i]-48);
				}
				
				if(this->id_cars_rented.find(id)==this->id_cars_rented.end()){
					cout<<"You do not have a car with this ID.\n\n";
					exit=1;
					continue;
				}
				
				time_t curr_time = time(NULL);
				time_t time_rented = 0;
				
				ifstream Database;
				Database.open("car_database.txt");
				
				if(Database.fail()){
					cout<<"Error opening Database. Returning...\n\n";
					return -1;
				}
				
				string line;
				vector<string> lines;
				while(Database){
					getline(Database,line);
					
					if(line.size()<2) continue;
					
					int ind1=line.find("-");
					
					int i;
					
					string lid="";
					string tmodel="";
					string tcondition="";
					string tavailability="Available";
					string tprice="";
					string ttype_of_owner="NA";
					string towner_name="NA";
					string ttime="";

					for(i=0;i<ind1;i++){
						lid+=line[i];
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
						tmodel+=line[i];
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
						tcondition+=line[i];
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
						tprice+=line[i];
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;i<line.size();i++){
						ttime+=line[i];
					}
					
					if(lid==sid){
						string tline="";
						time_rented = string_to_long(ttime);						
						tline+=lid+"-"+tmodel+"-"+tcondition+"-"+tavailability+"-"+tprice+"-"+ttype_of_owner+"-"+towner_name+"-0";
						lines.push_back(tline);
					}
					else{
						lines.push_back(line);
					}
				}
				
				Database.close();
				
				ofstream Database1;
				Database1.open("car_database.txt");
				
				if(Database1.fail()){
					cout<<"Error opening Database. Returning...\n\n";
					return -1;
				}
				
				for(int i=0;i<lines.size();i++)
					Database1 << lines[i] <<"\n";
				
				Database1.close();
				
				this->cars_rented--;
				this->id_cars_rented.erase(id);
				this->fine_due+=((curr_time-time_rented-604800)/604800)*500;
				this->customer_record-=((curr_time-time_rented-604800)/604800)*0.1;
				this->customer_record=max(this->customer_record,0.0);
				success = 1;
				
				return id;
			}
		}
};

class Employee : public User{
	private:
		double employee_record;
		int cars_rented;
		map<int,bool> id_cars_rented;
		double fine_due;
	
	public:
		static int emp_count;
		
		friend int check_name_password(string name,string password,char role,int size);
		friend bool employee_func();
		friend void view_rented_cars(char role,int id);
		friend bool rent_car(char role,string name,int self_id);
		friend void update_database(char role,int id);
		friend void view_all(string type);
		friend void add(string type);
		friend void del(string type);
		friend void update(string type);
		friend void search(string type);
		friend void load_employees();
		
		Employee(string name,string password){
			this->name=name;
			this->password=password;
			this->id=emp_count;
			this->employee_record=5.0;
			this->cars_rented=0;
			this->fine_due=0.0;
			
			emp_count++;
		}
		
		void show_due(){
			cout<<fine_due<<"\n";
		}
		
		//Clear dues
		void clear_due(){
			string amt;
			double amount=0;
			bool valid=0;
			while(!valid){
				cout<<"Enter the amount you want to clear...\n\n";
				cin>>amt;
				if(amt=="q") return;
				
				amount = string_to_double(amt);
				if(amount==-1){
					cout<<"Invalid amount! Try again...\n\n";
				}
				else if(amount<=0 || amount>fine_due){
					cout<<"Invalid amount! Try again...\n\n";
				}
				else{
					valid=1;
				}
			}
			fine_due-=amount;
			
			cout<<"\nSuccessfully cleared from due the given amount.\n\n";
		}
		
		//Return a car
		int return_request(){
			bool success=0,exit=0;
			
			int id=0;
			int days=0;
			while(!success || !exit){
				cout<<"Enter the ID of the car you want to return.\n\n";
			
				string sid;
				cin>>sid;
				if(sid=="q"){
					exit=1;
					return -1;
				}
				
				for(int i=0;i<sid.size();i++){
					id=(10*id)+(sid[i]-48);
				}
				
				if(this->id_cars_rented.find(id)==this->id_cars_rented.end()){
					cout<<"You do not have a car with this ID.\n\n";
					exit=1;
					continue;
				}
				
				time_t curr_time = time(NULL);
				time_t time_rented = 0;
				
				ifstream Database;
				Database.open("car_database.txt");
				
				if(Database.fail()){
					cout<<"Error opening Database. Returning...\n\n";
					return -1;
				}
				
				string line;
				vector<string> lines;
				while(Database){
					getline(Database,line);
					
					if(line.size()<2) continue;
					
					int ind1=line.find("-");
					
					int i;
					
					string lid="";
					string tmodel="";
					string tcondition="";
					string tavailability="Available";
					string tprice="";
					string ttype_of_owner="NA";
					string towner_name="NA";
					string ttime="";

					for(i=0;i<ind1;i++){
						lid+=line[i];
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
						tmodel+=line[i];
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
						tcondition+=line[i];
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
						tprice+=line[i];
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;line[i]!='-';i++){
					}
					
					i++;
					ind1=i;
					
					for(i=ind1;i<line.size();i++){
						ttime+=line[i];
					}
					
					if(lid==sid){
						time_rented=string_to_long(ttime);
						string tline="";						
						tline+=lid+"-"+tmodel+"-"+tcondition+"-"+tavailability+"-"+tprice+"-"+ttype_of_owner+"-"+towner_name+"-0";
						lines.push_back(tline);
					}
					else{
						lines.push_back(line);
					}
				}
				
				Database.close();
				
				ofstream Database1;
				Database1.open("car_database.txt");
				
				if(Database1.fail()){
					cout<<"Error opening Database. Returning...\n\n";
					return -1;
				}
				
				for(int i=0;i<lines.size();i++)
					Database1 << lines[i] <<"\n";
				
				Database1.close();
				
				this->cars_rented--;
				this->id_cars_rented.erase(id);
				this->fine_due+=((curr_time-time_rented-604800)/604800)*500;
				this->employee_record-=((curr_time-time_rented-604800)/604800)*0.1;
				this->employee_record=max(this->employee_record,0.0);
				success = 1;
				
				return id;
			}
		}
};

class Manager : public User{
	public:
		Manager(string name,string password){
			this->name=name;
			this->password=password;
			this->id=0;
		}
};

class Car{
	public:
		static int car_count;
		
		int id;
		string model;
		string condition;
		string availibity;
		string type_of_owner;
		string owner_name;
		double price;
		time_t time_rented;
		
		Car(string model,string condition,double price){
			this->model=model;
			this->id=car_count;
			this->condition=condition;
			this->availibity="Available";
			this->type_of_owner="NA";
			this->owner_name="NA";
			this->price=price;
			this->time_rented=0;
			
			car_count++;
		}
};

//Creating set for storing Objects
vector<Customer> cust;
vector<Employee> emp;
vector<Car> car;

//View rented Cars
void view_rented_cars(char role,int id){
	cout<<"\n\n\n--------------------------------------\n";
	cout<<"  | ID - Model - Price - Condition |  \n";
	
	ifstream Database;
	Database.open("car_database.txt");
	
	if(role=='c'){
		Customer curr_cust("","");
		for(int i=0;i<cust.size();i++){
			if(cust[i].id==id){
				curr_cust=cust[i];
				break;
			}
		}
		map<int,bool> ids=curr_cust.id_cars_rented;
		string line;
		
		Database.seekg(0, ios::beg);
		while(Database){
			//Read a line from Database
			getline(Database,line);
			
			//Extracting id from the line
			int ind1 = -1;
			ind1 = line.find("-");
			string sid="";
			for(int i=0;i<ind1;i++){
				sid+=line[i];
			}
			
			int id = 0;
			bool in=0;
			for(int i=0;i<sid.size();i++){
				if((int)sid[i]>=48 && (int)sid[i]<58){
					id = 10*id + sid[i] - 48;
					in=1;
				}
			}
			if(!in) continue;
			if(ids.find(id)!=ids.end()){
				int ind2;
				for(int i=0;i<car.size();i++){
					if(car[i].id==id){
						ind2=i;
						break;
					}
				}
				cout<<"  | "<<car[ind2].id<<" - "<<car[ind2].model<<" - $"<<car[ind2].price<<" - "<<car[ind2].condition<<" |  \n";
			}
		}
	}
	else if(role=='e'){
		Employee curr_emp("","");
		for(int i=0;i<emp.size();i++){
			if(emp[i].id==id){
				curr_emp=emp[i];
				break;
			}
		}
		map<int,bool> ids=curr_emp.id_cars_rented;
		string line;
		
		Database.seekg(0, ios::beg);
		while(Database){
			//Read a line from Database
			getline(Database,line);
			
			//Extracting id from the line
			int ind1=-1;
			ind1 = line.find("-");
			string sid="";
			for(int i=0;i<ind1;i++){
				sid+=line[i];
			}
			
			int id = 0;
			bool in=0;
			for(int i=0;i<sid.size();i++){
				if((int)sid[i]>=48 && (int)sid[i]<58){
					id = 10*id + sid[i] - 48;
					in=1;
				}
			}
			if(!in) continue;
			if(ids.find(id)!=ids.end()){
				int ind2;
				for(int i=0;i<car.size();i++){
					if(car[i].id==id){
						ind2=i;
						break;
					}
				}
				cout<<"  | "<<car[ind2].id<<" - "<<car[ind2].model<<" - $"<<car[ind2].price<<" - "<<car[ind2].condition<<" |  \n";
			}
		}
	}
	
	cout<<"--------------------------------------\n\n\n";
}

//Function for checking name and password
int check_name_password(string name,string password,char role,int size){
	bool found=0;
	ifstream Database;
	
	if(role=='c'){ //Checking if such a customer exists
		Database.open("cust_database.txt");
		
		for(int i=0;i<size;i++){
			if(cust[i].name==name){
				found=1;
				break;
			}
		}
	}
	else if(role=='e'){ //Checking if such an employee exists
		Database.open("emp_database.txt");
		
		for(int i=0;i<size;i++){
			if(emp[i].name==name){
				found=1;
				break;
			}
		}
	}
	
	if(!found){
		Database.close();
		return 2;
	}
	
	//If user exists, check if the password is correct
	Database.seekg(0, ios::beg);
	
	string line;
	while(Database){
		//Read a line from Database
		getline(Database,line);
		
		//Extracting names from the Database
		int ind1=-1,ind2=-1;
		string sname="",spassword="";
		ind1 = line.find("-");
		if(ind1==-1){
			return 1;
		}
		int i;
		for(i=ind1+1;line[i]!='-';i++){
			sname+=line[i];
		}
		
		if(sname!=name) continue;
		
		ind1=i;
		for(i=ind1+1;line[i]!='-';i++){
			spassword+=line[i];
		}
		
		if(spassword!=password){
			return 1;
		}
		else{
			return 0;
		}
	}
}

//Function for viewing all Cars for Customers and Employees
void view_cars(){
	bool f=0;
	for(int i=0;i<car.size();i++){
		if(car[i].availibity=="Available"){
			f=1;
			break;
		}
	}
	
	if(!f){
		cout<<"No cars are currently available... Sorry :(\n\n";
		return;
	}
	
	cout<<"\n\n\n--------------------------------------\n";
	cout<<"  | ID - Model - Price - Condition |\n";
	for(int i=0;i<car.size();i++){
		if(car[i].availibity=="Available") cout<<"  | "<<car[i].id<<" - "<<car[i].model<<" - $"<<car[i].price<<" - "<<car[i].condition<<" |\n";
	}
	cout<<"--------------------------------------\n\n\n";
}

//Checks if the id is valid
bool update_car_status(int id,char role,string name){
	ifstream Database;
	Database.open("car_database.txt");
	
	if(role=='x' || role=='y'){
		bool found=0;
		string line;
		vector<string> lines;
		int line_number=0,wanted_line_number=-1,ind_in_vector=-1;
		while(Database){
			getline(Database,line);
			lines.push_back(line);
			line_number++;
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			string sid;
			for(int i=0;i<ind1;i++){
				sid+=line[i];
			}
			
			int fid=0;
			bool in=0;
			for(int i=0;i<sid.size();i++){
				if((int)sid[i]>=48 && (int)sid[i]<58){
					fid = 10*fid + sid[i] - 48;
					in=1;
				}
			}
			
			if(!in) continue;
			if(fid==id){
				wanted_line_number=line_number;
				//Update car vector
				for(int i=0;i<car.size();i++){
					if(car[i].id==fid){
						ind_in_vector=i;
						car[i].availibity="Rented";
						car[i].type_of_owner= (role == 'x' ? "Customer":"Employee");
						car[i].owner_name=name;
						car[i].time_rented=time(NULL);
					}
				}
				
				found=1;
			}
		}
		
		Database.close();
		
		if(!found) return 0;
		else{
			ofstream write_file;
			write_file.open("car_database.txt");
			
			if(write_file.fail()){
				cout<<"Error opening database. Returning...\n\n";
				return 0;
			}
			
			wanted_line_number--;
			
			for(int i=0;i<line_number;i++){
				if(i!=wanted_line_number){
					write_file << lines[i] << "\n";
				}
				else{
					string temp="";
					temp = temp + to_string(car[ind_in_vector].id) + "-" + car[ind_in_vector].model + "-" + car[ind_in_vector].condition + "-" + car[ind_in_vector].availibity + "-" + to_string(car[ind_in_vector].price) + "-" + car[ind_in_vector].type_of_owner + "-" + car[ind_in_vector].owner_name + "-" + to_string(car[ind_in_vector].time_rented) + "\n";
					write_file << temp;
				}
			}
			
			write_file.close();
			
			return 1;
		}
		
		return 1;
	}
	
	for(int i=0;i<car.size();i++){
		if(car[i].id==id && car[i].availibity=="Rented"){
			return 0;
		}
	}
	
	bool found=0;
	string line;
	vector<string> lines;
	int line_number=0,wanted_line_number=-1,ind_in_vector=-1;
	while(Database){
		getline(Database,line);
		lines.push_back(line);
		line_number++;
		
		if(line.size()<2) continue;
		
		int ind1;
		ind1=line.find("-");
		string sid;
		for(int i=0;i<ind1;i++){
			sid+=line[i];
		}
		
		int fid=0;
		bool in=0;
		for(int i=0;i<sid.size();i++){
			if((int)sid[i]>=48 && (int)sid[i]<58){
				fid = 10*fid + sid[i] - 48;
				in=1;
			}
		}
		
		if(!in) continue;
		if(fid==id){
			wanted_line_number=line_number;
			//Update car vector
			for(int i=0;i<car.size();i++){
				if(car[i].id==fid){
					ind_in_vector=i;
					car[i].availibity="Rented";
					car[i].type_of_owner= (role == 'c' ? "Customer":"Employee");
					car[i].owner_name=name;
					car[i].time_rented=time(NULL);
				}
			}
			
			found=1;
		}
	}
	
	Database.close();
	
	if(!found) return 0;
	else{
		ofstream write_file;
		write_file.open("car_database.txt");
		
		if(write_file.fail()){
			cout<<"Error opening database. Returning...\n\n";
			return 0;
		}
		
		wanted_line_number--;
		
		for(int i=0;i<line_number;i++){
			if(i!=wanted_line_number){
				write_file << lines[i] << "\n";
			}
			else{
				string temp="";
				temp = temp + to_string(car[ind_in_vector].id) + "-" + car[ind_in_vector].model + "-" + car[ind_in_vector].condition + "-" + car[ind_in_vector].availibity + "-" + to_string(car[ind_in_vector].price) + "-" + car[ind_in_vector].type_of_owner + "-" + car[ind_in_vector].owner_name + "-" + to_string(car[ind_in_vector].time_rented) + "\n";
				write_file << temp;
			}
		}
		
		write_file.close();
		
		return 1;
	}
}

//Rent a car
bool rent_car(char role,string name,int self_id){
	bool success=0,exit=0;
	string tid;
	
	bool car_available=0;
	for(int i=0;i<car.size();i++){
		if(car[i].availibity=="Available"){
			car_available=1;
			break;
		}
	}
	if(!car_available){
		cout<<"No cars are available... Sorry :(\n\n";
		return 0;
	}
	
	while(!success || !exit){
		cout<<"Enter the id of the car you want to rent.\n";
		cout<<"(Press q) Exit.\n\n";
		cin>>tid;
		
		if(tid=="q"){
			exit=1;
			break;
		}
		
		int id = 0;
		for(int i=0;i<tid.size();i++){
			id=10*id+(tid[i]-48);
		}
		
		bool valid=0;
		
		valid = update_car_status(id,role,name);
		
		if(!valid){
			cout<<"\nInvalid car ID :(\n\n";
			return 0;
		}
		else{
			double price=0;
			for(int i=0;i<car.size();i++){
				if(car[i].id==id){
					price=car[i].price;
					break;
				}
			}
			
			if(role=='c'){
				for(int i=0;i<cust.size();i++){
					if(cust[i].id==self_id){
						cust[i].fine_due += price;
						cust[i].cars_rented++;
						cust[i].id_cars_rented[id]=1;
					}
				}
			}
			else if(role=='e'){
				for(int i=0;i<emp.size();i++){
					if(emp[i].id==self_id){
						emp[i].fine_due += (85.0/100)*price;
						emp[i].cars_rented++;
						emp[i].id_cars_rented[id]=1;
					}
				}
			}
			cout<<"\nSuccessfully rented car... Come back again :)\n\n";
			success=1;
			return 1;
		}
	}
	
	return 0;
}

//Update customer and employee database
void update_database(char role,int id){
	ifstream Database;
	ofstream Database1;
	
	if(role=='c'){
		Database.open("cust_database.txt");
		
		if(Database.fail()){
			cout<<"Error opening database. Returning...\n\n";
			return;
		}
		
		int ind;
		for(int i=0;i<cust.size();i++){
			if(cust[i].id==id){
				ind=i;
				break;
			}
		}
		
		string line;
		vector<string> lines;
		while(Database){
			getline(Database,line);
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			string sid="";
			for(int i=0;i<ind1;i++){
				sid+=line[i];
			}
			
			if(sid==to_string(id)){
				string tline="";
				tline+=to_string(cust[ind].id)+"-"+cust[ind].name+"-"+cust[ind].password+"-"+to_string(cust[ind].customer_record)+"-"+to_string(cust[ind].cars_rented)+"-"+to_string(cust[ind].fine_due);
				for(auto x:cust[ind].id_cars_rented) tline = tline + "-" + to_string(x.first);
				lines.push_back(tline);
			}
			else{
				lines.push_back(line);
			}
		}
		
		Database.close();
		
		Database1.open("cust_database.txt");
		
		for(int i=0;i<lines.size();i++){
			Database1 << lines[i] <<"\n";
		}
		
		Database1.close();
	}
	else if(role=='e'){
		Database.open("emp_database.txt");
		
		if(Database.fail()){
			cout<<"Error opening database. Returning...\n\n";
			return;
		}
		
		int ind;
		for(int i=0;i<emp.size();i++){
			if(emp[i].id==id){
				ind=i;
				break;
			}
		}
		
		string line;
		vector<string> lines;
		while(Database){
			getline(Database,line);
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			string sid="";
			for(int i=0;i<ind1;i++){
				sid+=line[i];
			}
			
			if(sid==to_string(id)){
				string tline="";
				tline+=to_string(emp[ind].id)+"-"+emp[ind].name+"-"+emp[ind].password+"-"+to_string(emp[ind].employee_record)+"-"+to_string(emp[ind].cars_rented)+"-"+to_string(emp[ind].fine_due);
				for(auto x:emp[ind].id_cars_rented) tline = tline + "-" + to_string(x.first);
				lines.push_back(tline);
			}
			else{
				lines.push_back(line);
			}
		}
		
		Database.close();
		
		Database1.open("emp_database.txt");
	
		for(int i=0;i<lines.size();i++){
			Database1 << lines[i] <<"\n";
		}
	}
}

//Function for handling customers
bool customer_func(){
	//Welcome Screen
	cout<<"\t\t----- Hello Customer! -----\n(Enter 'q' to exit)\n\n";
	
	string name="",password="";
	bool success=0;
	bool first=0;
	
	//Wait till correct input else exit
	while(!success){
		cout<<"Enter your name\n\n";
		if(!first){
			cin.ignore();
			first=1;
		}
		getline(cin,name,'\n');
		if(name=="q"){
			return 1;
		}
		cout<<"Enter your password\n\n";
		getline(cin,password,'\n');
		if(password=="q"){
			return 1;
		}
		
		int find=check_name_password(name,password,'c',Customer::cust_count);
		if(find==0) success=1;
		else if(find==1) cout<<"Wrong Password :( ! Try again...\n";
		else if(find==2) cout<<"Username not found :-O\n";
	}
	
	Customer curr_cust("","");
	for(int i=0;i<cust.size();i++){
		if(cust[i].name==name){
			curr_cust.name=cust[i].name;
			curr_cust.password=cust[i].password;
			curr_cust.id=cust[i].id;
			curr_cust.customer_record=cust[i].customer_record;
			curr_cust.cars_rented=cust[i].cars_rented;
			curr_cust.id_cars_rented=cust[i].id_cars_rented;
			curr_cust.fine_due=cust[i].fine_due;
			break;
		}
	}
	
	cout<<"\t\t----- Successful Login! -----\n\n\n";
	cout<<"Welcome, "<<name<<"!\n\n";
	bool exit=0;
	char input;
	while(!exit){
		cout<<"\n\nWhat would you like to do?\n\n";
		cout<<"(Press 1) View all available Cars.\n";
		cout<<"(Press 2) View rented Cars.\n";
		cout<<"(Press 3) View your current dues.\n";
		cout<<"(Press 4) Clear your dues.\n";
		cout<<"(Press 5) Rent an available Car.\n";
		cout<<"(Press 6) Return a Car.\n";
		cout<<"(Press q) Logout.\n\n";
		cin>>input;
		switch(input){
			case '1':
				//View available cars
				view_cars();
				break;
			case '2':
				//View rented cars
				if(curr_cust.cars_rented==0){
					cout<<"No cars rented.\n";
					break;
				}
				
				view_rented_cars('c',curr_cust.id);
				break;
			case '3':
				//Show current dues
				curr_cust.show_due();
				break;
			case '4':
				//Pay dues
				curr_cust.clear_due();
				break;
			case '5':
			{
				//Rent available Cars
				if(curr_cust.cars_rented >= curr_cust.customer_record/2){
					cout<<"Your record is not good enough to rent a car.\n";
					break;
				}
				
				bool success = 0;
				success = rent_car('c',curr_cust.name,curr_cust.id);
				if(success){
					for(int i=0;i<cust.size();i++){
						if(cust[i].id==curr_cust.id){
							curr_cust=cust[i];
							break;
						}
					}
					update_database('c',curr_cust.id);
				}
				break;
			}
			case '6':
			{
				//Return a Car
				int success = 0;
				success = curr_cust.return_request();
				if(success>=0){
					cout<<"\n\nSuccessfully returned Car.\n";
					
					for(int i=0;i<car.size();i++){
						if(car[i].id==success){
							car[i].availibity="Available";
							car[i].type_of_owner="NA";
							car[i].owner_name="NA";
							car[i].time_rented=0;
							break;
						}
					}
					
					for(int i=0;i<cust.size();i++){
						if(cust[i].id==curr_cust.id){
							cust[i]=curr_cust;
							break;
						}
					}
					update_database('c',curr_cust.id);
				}
				break;
			}
			case 'q':
				//Exit
				exit=1;
				break;
			default:
				cout<<"Invalid input :(\n\n";
				break;
		}
	}
	
	Sleep(500);
	system("cls");
	user_role();
}

//Function for handling employees
bool employee_func(){
	//Welcome Screen
	cout<<"\t\t----- Hello Employee! -----\n(Enter 'q' to exit)\n\n";
	
	string name="",password="";
	bool success=0;
	bool first=0;
	
	//Wait till correct input else exit
	while(!success){
		cout<<"Enter your name\n";
		if(!first){
			cin.ignore();
			first=1;
		}
		getline(cin,name,'\n');
		if(name=="q"){
			return 1;
		}
		cout<<"Enter your password\n";
		getline(cin,password,'\n');
		if(password=="q"){
			return 1;
		}
		
		int find=check_name_password(name,password,'e',Employee::emp_count);
		if(find==0) success=1;
		else if(find==1) cout<<"Wrong Password :( ! Try again...\n";
		else if(find==2) cout<<"Username not found :-O\n";
	}
	
	Employee curr_emp("","");
	for(int i=0;i<emp.size();i++){
		if(emp[i].name==name){
			curr_emp.name=emp[i].name;
			curr_emp.password=emp[i].password;
			curr_emp.id=emp[i].id;
			curr_emp.employee_record=emp[i].employee_record;
			curr_emp.cars_rented=emp[i].cars_rented;
			curr_emp.id_cars_rented=emp[i].id_cars_rented;
			curr_emp.fine_due=emp[i].fine_due;
			break;
		}
	}
	
	cout<<"\t\t----- Successful Login! -----\n\n\n";
	cout<<"Welcome, "<<name<<"!\n\n";
	bool exit=0;
	char input;
	while(!exit){
		cout<<"\n\nWhat would you like to do?\n\n";
		cout<<"(Press 1) View all available Cars.\n";
		cout<<"(Press 2) View rented Cars.\n";
		cout<<"(Press 3) View your current dues.\n";
		cout<<"(Press 4) Clear your dues.\n";
		cout<<"(Press 5) Rent an available Car.\n";
		cout<<"(Press 6) Return a Car.\n";
		cout<<"(Press q) Logout.\n";
		cin>>input;
		switch(input){
			case '1':
				//View available Cars
				view_cars();
				break;
			case '2':
				//View rented Cars
				if(curr_emp.id_cars_rented.size()==0){
					cout<<"No cars rented.\n";
					break;
				}
				view_rented_cars('e',curr_emp.id);
				break;
			case '3':
				//Show current dues
				curr_emp.show_due();
				break;
			case '4':
				//Pay dues
				curr_emp.clear_due();
				break;
			case '5':
			{
				//Rent available Cars
				if(curr_emp.cars_rented >= curr_emp.employee_record/2){
					cout<<"Your record is not good enough to rent a car.\n";
					break;
				}
				
				bool success = 0;
				success = rent_car('e',curr_emp.name,curr_emp.id);
				if(success){
					for(int i=0;i<emp.size();i++){
						if(emp[i].id==curr_emp.id){
							curr_emp=emp[i];
							break;
						}
					}
					update_database('e',curr_emp.id);
				}
				break;
			}
			case '6':
			{
				//Return a Car
				int success = 0;
				success = curr_emp.return_request();
				if(success>=0){
					cout<<"\n\nSuccessfully returned Car.\n";
					
					for(int i=0;i<car.size();i++){
						if(car[i].id==success){
							car[i].availibity="Available";
							car[i].type_of_owner="NA";
							car[i].owner_name="NA";
							car[i].time_rented=0;
							break;
						}
					}
					
					for(int i=0;i<emp.size();i++){
						if(emp[i].id==curr_emp.id){
							emp[i]=curr_emp;
							break;
						}
					}
					update_database('e',curr_emp.id);
				}
				break;
			}
			case 'q':
				//Exit
				exit=1;
				break;
			default:
				cout<<"Invalid input :(\n\n";
				break;
		}
	}
	
	Sleep(500);
	system("cls");
	user_role();
}

//View records
void view_all(string type){
	cout<<"\n\n\n------------------------------------------------------------------------\n";
	if(type=="car"){
		cout<<"| ID - Model - Condition - Availability - Price - Role of Owner - Name |\n";
		for(int i=0;i<car.size();i++){
			cout<<"| "<<car[i].id<<" - "<<car[i].model<<" - "<<car[i].condition<<" - "<<car[i].availibity<<" - $"<<car[i].price<<" - "<<car[i].type_of_owner<<" - "<<car[i].owner_name<<" |\n";
		}
	}
	else if(type=="customer"){
		cout<<"|ID - Name - Password - Customer Record - Cars rented - Fine due|\n";
		for(int i=0;i<cust.size();i++){
			cout<<"|"<<cust[i].id<<" - "<<cust[i].name<<" - "<<cust[i].password<<" - "<<cust[i].customer_record<<" - "<<cust[i].cars_rented<<" - $"<<cust[i].fine_due<<"|\n";
		}
	}
	else if(type=="employee"){
		cout<<"|ID - Name - Password - Employee Record - Cars rented - Fine due|\n";
		for(int i=0;i<emp.size();i++){
			cout<<"|"<<emp[i].id<<" - "<<emp[i].name<<" - "<<emp[i].password<<" - "<<emp[i].employee_record<<" - "<<emp[i].cars_rented<<" - $"<<emp[i].fine_due<<"|\n";
		}
	}
	else{
		cout<<"Something went wrong :-O\n\n";
		return;
	}
	cout<<"------------------------------------------------------------------------\n\n\n";
}

//Add records
void add(string type){
	ofstream Database;
	
	if(type=="car"){
		Database.open("car_database.txt", ios::app);
		
		string model,condition;
		string price;
		cout<<"Enter the model name.\n\n";
		cin.ignore();
		getline(cin,model);
		
		if(model=="q") return;
		
		bool valid = 0;
		while(!valid){
			cout<<"Enter condition.\n\n";
			cin>>condition;
			
			if(condition=="q") return;
			
			if(condition!="Good" && condition!="Mid" && condition!="Bad"){
				cout<<"Condition can only be Good, Mid or Bad. Retry.\n\n";
				continue;
			}
			
			valid = 1;
		}
		
		valid = 0;
		double dprice;
		while(!valid){
			cout<<"Enter price.\n";
			cin>>price;
			
			if(price=="q") return;
			
			dprice = string_to_double(price);
			if(dprice==-1){
				cout<<"Invalid format. Try again :(\n";
			}
			else{
				valid = 1;
				break;
			}
		}
		
		Car New_Car(model,condition,dprice);
		car.push_back(New_Car);
		
		int ind=car.size()-1;
		string line="";
		line+=to_string(car[ind].id)+"-"+car[ind].model+"-"+car[ind].condition+"-"+car[ind].availibity+"-"+to_string(car[ind].price)+"-"+car[ind].type_of_owner+"-"+car[ind].owner_name;
		Database << line <<"\n";
		
		Database.close();
	}
	else if(type=="customer"){
		Database.open("cust_database.txt", ios::app);
		
		string name,password;
		cout<<"Enter the name of the customer.\n\n";
		cin.ignore();
		getline(cin,name);
		
		for(int i=0;i<cust.size();i++){
			if(cust[i].name == name){
				cout<<"Name already taken. Try something else...\n";
				Database.close();
				return;
			}
		}
		
		if(name=="q") return;
		
		cout<<"Enter the password. (Make sure the password has no whitespaces)\n\n";
		cin>>password;
		
		Customer New_Customer(name,password);
		cust.push_back(New_Customer);
		
		int ind=cust.size()-1;
		string line="";
		line+=to_string(cust[ind].id)+"-"+cust[ind].name+"-"+cust[ind].password+"-"+to_string(cust[ind].customer_record)+"-"+to_string(cust[ind].cars_rented)+"-"+to_string(cust[ind].fine_due);
		Database << line <<"\n";
		
		Database.close();
	}
	else if(type=="employee"){
		Database.open("emp_database.txt", ios::app);
		
		string name,password;
		cout<<"Enter the name of the emp.\n\n";
		cin.ignore();
		getline(cin,name);
		
		for(int i=0;i<emp.size();i++){
			if(emp[i].name == name){
				cout<<"Name already taken. Try something else...\n";
				Database.close();
				return;
			}
		}
		
		if(name=="q") return;
		
		cout<<"Enter the password. (Make sure the password has no whitespaces)\n\n";
		cin>>password;
		
		Employee New_Employee(name,password);
		emp.push_back(New_Employee);
		
		int ind=emp.size()-1;
		string line="";
		line+=to_string(emp[ind].id)+"-"+emp[ind].name+"-"+emp[ind].password+"-"+to_string(emp[ind].employee_record)+"-"+to_string(emp[ind].cars_rented)+"-"+to_string(emp[ind].fine_due);
		Database << line <<"\n";
		
		Database.close();
	}
	else{
		cout<<"Something went wrong :-O\n\n";
		return;
	}
	
	cout<<"\n\nSuccessfully added.\n";
}

//Update records
void update(string type){
	ifstream iDatabase;
	ofstream oDatabase;
	
	string sid;
	bool valid=0;
	int id=0;
	while(!valid){
		cout<<"Enter ID of the tuple to be updated.\n\n";
		cin>>sid;
		
		if(sid=="q") return;
		
		bool f=0;
		for(int i=0;i<sid.size();i++){
			if((int)sid[i]<48 || (int)sid[i]>57){
				f=1;
				break;
			}
		}
		if(f) continue;
		else valid=1;
	}
	
	for(int i=0;i<sid.size();i++){
		id=(10*id)+(sid[i]-48);
	}
	
	if(type=="car"){
		bool exists = 0;
		for(int i=0;i<car.size();i++){
			if(car[i].id==id){
				exists=1;
				break;
			}
		}
		
		if(!exists){
			cout<<"Such an ID does not exist in the record.\n\n";
			return;
		}
		
		iDatabase.open("car_database.txt");
		
		string line;
		vector<string> lines;
		while(iDatabase){
			getline(iDatabase,line);
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			
			string sid="";
			for(int i=0;i<ind1;i++)
				sid+=line[i];
			
			if(sid==to_string(id)){
				int ind;
				for(int i=0;i<car.size();i++){
					if(car[i].id==id){
						ind=i;
						break;
					}
				}
				
				if(car[ind].availibity=="Rented"){
					cout<<"Cannot update this car, it is currently rented.\n\n";
					iDatabase.close();
					return;
				}
				
				string model,condition;
				string price;
				cout<<"Enter the model name.\n\n";
				cin.ignore();
				getline(cin,model);
				
				if(model=="q") return;
				
				bool valid = 0;
				while(!valid){
					cout<<"Enter condition.\n\n";
					cin>>condition;
					
					if(condition=="q") return;
					
					if(condition!="Good" && condition!="Mid" && condition!="Bad"){
						cout<<"Condition can only be Good, Mid or Bad. Retry. \n\n";
						continue;
					}
					
					valid = 1;
				}
				
				valid = 0;
				double dprice;
				while(!valid){
					cout<<"Enter price.\n\n";
					cin>>price;
					
					if(price=="q") return;
					
					dprice = string_to_double(price);
					if(dprice==-1){
						cout<<"Invalid format. Try again... :(\n";
					}
					else{
						valid = 1;
						break;
					}
				}
				
				Car New_Car(model,condition,dprice);
				
				car.push_back(New_Car);
				car[car.size()-1].id=car[ind].id;
				swap(car[car.size()-1],car[ind]);
				car.pop_back();
				string tline="";
				tline+=to_string(car[ind].id)+"-"+car[ind].model+"-"+car[ind].condition+"-"+car[ind].availibity+"-"+to_string(car[ind].price)+"-"+car[ind].type_of_owner+"-"+car[ind].owner_name;
				lines.push_back(tline);
			}
			else{
				lines.push_back(line);
			}
		}
		
		iDatabase.close();
		
		oDatabase.open("car_database.txt");
		
		for(int i=0;i<lines.size();i++)
			oDatabase << lines[i] << "\n";
			
		oDatabase.close();		
	}
	else if(type=="customer"){
		bool exists = 0;
		vector<int> car_ids;
		int wanted_ind = -1;
		for(int i=0;i<cust.size();i++){
			if(cust[i].id==id){
				for(auto x:cust[i].id_cars_rented) car_ids.push_back(x.first);
				exists=1;
				break;
			}
		}
		
		if(!exists){
			cout<<"Such an ID does not exist in the record.\n\n";
			return;
		}
		
		iDatabase.open("cust_database.txt");
		
		string line;
		vector<string> lines;
		while(iDatabase){
			getline(iDatabase,line);
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			
			string sid="";
			for(int i=0;i<ind1;i++)
				sid+=line[i];
			
			if(sid==to_string(id)){
				int ind;
				for(int i=0;i<cust.size();i++){
					if(cust[i].id==id){
						ind=i;
						break;
					}
				}
				
				string name,password;
				double customer_record;
				cout<<"Enter new name.\n\n";
				cin.ignore();
				getline(cin,name);
				
				if(name=="q") return;
				
				cout<<"Enter new password. (Make sure it does not have whitespace)\n\n";
				cin>>password;
				
				cout<<"Enter new customer record.\n\n";
				cin>>customer_record;
				Customer New_Customer(name,password);
				
				cust.push_back(New_Customer);
				cust[cust.size()-1].id=cust[ind].id;
				cust[cust.size()-1].customer_record=customer_record;
				cust[cust.size()-1].cars_rented=cust[ind].cars_rented;
				cust[cust.size()-1].id_cars_rented=cust[ind].id_cars_rented;
				cust[cust.size()-1].fine_due=cust[ind].fine_due;
				swap(cust[cust.size()-1],cust[ind]);
				wanted_ind = ind;
				cust.pop_back();
				string tline="";
				tline+=to_string(cust[ind].id)+"-"+cust[ind].name+"-"+cust[ind].password+"-"+to_string(cust[ind].customer_record)+"-"+to_string(cust[ind].cars_rented)+"-"+to_string(cust[ind].fine_due);
				lines.push_back(tline);
			}
			else{
				lines.push_back(line);
			}
		}
		
		iDatabase.close();
		
		oDatabase.open("cust_database.txt");
		
		for(int i=0;i<lines.size();i++)
			oDatabase << lines[i] << "\n";
			
		oDatabase.close();
		
		for(auto x:car_ids){
			update_car_status(x,'x',cust[wanted_ind].name);
		}
	}
	else if(type=="employee"){
		bool exists = 0;
		vector<int> car_ids;
		int wanted_ind = -1;
		for(int i=0;i<emp.size();i++){
			if(emp[i].id==id){
				for(auto x:emp[i].id_cars_rented) car_ids.push_back(x.first);
				exists=1;
				break;
			}
		}
		
		if(!exists){
			cout<<"Such an ID does not exist in the record.\n\n";
			return;
		}
		
		iDatabase.open("emp_database.txt");
		
		string line;
		vector<string> lines;
		while(iDatabase){
			getline(iDatabase,line);
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			
			string sid="";
			for(int i=0;i<ind1;i++)
				sid+=line[i];
			
			if(sid==to_string(id)){
				int ind;
				for(int i=0;i<emp.size();i++){
					if(emp[i].id==id){
						ind=i;
						break;
					}
				}
				
				string name,password;
				double employee_record;
				cout<<"Enter new name.\n\n";
				cin.ignore();
				getline(cin,name);
				
				if(name=="q") return;
				
				cout<<"Enter new password. (Make sure it does not have whitespace)\n\n";
				cin>>password;
				
				cout<<"Enter new customer record.\n\n";
				cin>>employee_record;
				Employee New_Employee(name,password);
				
				emp.push_back(New_Employee);
				emp[emp.size()-1].id=emp[ind].id;
				emp[emp.size()-1].employee_record=employee_record;
				emp[emp.size()-1].cars_rented=emp[ind].cars_rented;
				emp[emp.size()-1].id_cars_rented=emp[ind].id_cars_rented;
				emp[emp.size()-1].fine_due=emp[ind].fine_due;
				swap(emp[emp.size()-1],emp[ind]);
				wanted_ind = ind;
				emp.pop_back();
				string tline="";
				tline+=to_string(emp[ind].id)+"-"+emp[ind].name+"-"+emp[ind].password+"-"+to_string(emp[ind].employee_record)+"-"+to_string(emp[ind].cars_rented)+"-"+to_string(emp[ind].fine_due);
				lines.push_back(tline);
			}
			else{
				lines.push_back(line);
			}
		}
		
		iDatabase.close();
		
		oDatabase.open("emp_database.txt");
		
		for(int i=0;i<lines.size();i++)
			oDatabase << lines[i] << "\n";
			
		oDatabase.close();
		
		for(auto x:car_ids){
			update_car_status(x,'y',emp[wanted_ind].name);
		}
	}
	else{
		cout<<"Something went wrong :-O\n\n";
		return;
	}
	
	cout<<"\n\nSuccessfully updated.\n";
}

//Delete records
void del(string type){
	ifstream iDatabase;
	ofstream oDatabase;
	
	string sid;
	bool valid=0;
	int id=0;
	while(!valid){
		cout<<"Enter ID of the tuple to be removed.\n\n";
		cin>>sid;
		
		if(sid=="q") return;
		
		bool f=0;
		for(int i=0;i<sid.size();i++){
			if((int)sid[i]<48 || (int)sid[i]>57){
				f=1;
				break;
			}
		}
		if(f) continue;
		else valid=1;
	}
	
	for(int i=0;i<sid.size();i++){
		id=(10*id)+(sid[i]-48);
	}
	
	if(type=="car"){
		bool exists = 0;
		for(int i=0;i<car.size();i++){
			if(car[i].id==id){
				exists=1;
				break;
			}
		}
		if(!exists){
			cout<<"Such an ID does not exist in the record.\n\n";
			return;
		}
		
		iDatabase.open("car_database.txt");
		
		string line;
		vector<string> lines;
		while(iDatabase){
			getline(iDatabase,line);
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			
			string sid="";
			for(int i=0;i<ind1;i++)
				sid+=line[i];
			
			if(sid==to_string(id)){
				int ind;
				for(int i=0;i<car.size();i++){
					if(car[i].id==id){
						ind=i;
						break;
					}
				}
				
				if(car[ind].availibity=="Rented"){
					cout<<"Cannot remove this car, it is currently rented.\n\n";
					iDatabase.close();
					return;
				}
				
				swap(car[ind],car[car.size()-1]);
				car.pop_back();
			}
			else{
				lines.push_back(line);
			}
		}
		
		iDatabase.close();
		
		oDatabase.open("car_database.txt");
		
		for(int i=0;i<lines.size();i++)
			oDatabase << lines[i] <<"\n";
		
		oDatabase.close();
	}
	else if(type=="customer"){
		bool exists = 0;
		for(int i=0;i<cust.size();i++){
			if(cust[i].id==id){
				exists=1;
				break;
			}
		}
		if(!exists){
			cout<<"Such an ID does not exist in the record.\n\n";
			return;
		}
		
		iDatabase.open("cust_database.txt");
		
		string line;
		vector<string> lines;
		while(iDatabase){
			getline(iDatabase,line);
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			
			string sid="";
			for(int i=0;i<ind1;i++)
				sid+=line[i];
			
			if(sid==to_string(id)){
				int ind;
				for(int i=0;i<cust.size();i++){
					if(cust[i].id==id){
						ind=i;
						break;
					}
				}
				
				if(cust[ind].cars_rented>0){
					cout<<"Cannot remove this customer, he has not returned all cars.\n\n";
					iDatabase.close();
					return;
				}
				else if(cust[ind].fine_due>0){
					cout<<"Cannot remove this customer, he has dues left.\n\n";
					iDatabase.close();
					return;
				}
				
				swap(cust[ind],cust[cust.size()-1]);
				cust.pop_back();
			}
			else{
				lines.push_back(line);
			}
		}
		
		iDatabase.close();
		
		oDatabase.open("cust_database.txt");
		
		for(int i=0;i<lines.size();i++)
			oDatabase << lines[i] <<"\n";
		
		oDatabase.close();
	}
	else if(type=="employee"){
		bool exists = 0;
		for(int i=0;i<emp.size();i++){
			if(emp[i].id==id){
				exists=1;
				break;
			}
		}
		if(!exists){
			cout<<"Such an ID does not exist in the record.\n\n";
			return;
		}
		
		iDatabase.open("emp_database.txt");
		
		string line;
		vector<string> lines;
		while(iDatabase){
			getline(iDatabase,line);
			
			if(line.size()<2) continue;
			
			int ind1;
			ind1=line.find("-");
			
			string sid="";
			for(int i=0;i<ind1;i++)
				sid+=line[i];
			
			if(sid==to_string(id)){
				int ind;
				for(int i=0;i<emp.size();i++){
					if(emp[i].id==id){
						ind=i;
						break;
					}
				}
				
				if(emp[ind].cars_rented>0){
					cout<<"Cannot remove this customer, he has not returned all cars.\n";
					iDatabase.close();
					return;
				}
				
				swap(emp[ind],emp[emp.size()-1]);
				emp.pop_back();
			}
			else{
				lines.push_back(line);
			}
		}
		
		iDatabase.close();
		
		oDatabase.open("emp_database.txt");
		
		for(int i=0;i<lines.size();i++)
			oDatabase << lines[i] <<"\n";
		
		oDatabase.close();
	}
	else{
		cout<<"Something went wrong :-O\n";
		return;
	}
	
	cout<<"\n\nSuccessfully deleted.\n";
}

void search(string type){
	string sid;
	cout<<"Enter ID of the tuple to be searched.\n";
	cout<<"(Press q) Exit.\n";
	cin>>sid;
	
	if(sid=="q") return;
	
	if(type=="car"){
		int ind=-1;
		bool exists = 0;
		for(int i=0;i<car.size();i++){
			if(sid==to_string(car[i].id)){
				ind = i;
				exists = 1;
				break;
			}
		}
		
		if(!exists){
			cout<<"\nEntry with such an ID does not exist.\n";
			return;
		}
		
		cout<<"\n\n\n------------------------------------------------------------------------\n";
		cout<<"| ID - Model - Condition - Availability - Price - Role of Owner - Name |\n";
		for(int i=0;i<car.size();i++){
			if(i==ind) cout<<"| "<<car[i].id<<" - "<<car[i].model<<" - "<<car[i].condition<<" - "<<car[i].availibity<<" - "<<car[i].price<<" - "<<car[i].type_of_owner<<" - "<<car[i].owner_name<<" |\n";
		}
		cout<<"------------------------------------------------------------------------\n\n\n";
	}
	else if(type=="customer"){
		int ind=-1;
		bool exists = 0;
		for(int i=0;i<cust.size();i++){
			if(sid==to_string(cust[i].id)){
				ind = i;
				exists = 1;
				break;
			}
		}
		
		if(!exists){
			cout<<"\nEntry with such an ID does not exist.\n";
			return;
		}
		
		cout<<"\n\n\n------------------------------------------------------------------------\n";
		cout<<"|ID - Name - Password - Customer Record - Cars rented - Fine due|\n";
		for(int i=0;i<cust.size();i++){
			if(i==ind) cout<<"|"<<cust[i].id<<" - "<<cust[i].name<<" - "<<cust[i].password<<" - "<<cust[i].customer_record<<" - "<<cust[i].cars_rented<<" - "<<cust[i].fine_due<<"|\n";
		}
		cout<<"------------------------------------------------------------------------\n\n\n";
	}
	else if(type=="employee"){
		int ind=-1;
		bool exists = 0;
		for(int i=0;i<emp.size();i++){
			if(sid==to_string(emp[i].id)){
				ind = i;
				exists = 1;
				break;
			}
		}
		
		if(!exists){
			cout<<"\nEntry with such an ID does not exist.\n";
			return;
		}
		
		cout<<"\n\n\n------------------------------------------------------------------------\n";
		cout<<"|ID - Name - Password - Employee Record - Cars rented - Fine due|\n";
		for(int i=0;i<emp.size();i++){
			if(i==ind) cout<<"|"<<emp[i].id<<" - "<<emp[i].name<<" - "<<emp[i].password<<" - "<<emp[i].employee_record<<" - "<<emp[i].cars_rented<<" - "<<emp[i].fine_due<<"|\n";
		}
		cout<<"------------------------------------------------------------------------\n\n\n";
	}
	else{
		cout<<"Something went wrong :-O\n\n";
		return;
	}
}

//Function for handling manager
bool manager_func(){
	//Welcome Screen
	cout<<"\t\t----- Hello Manager! -----\n(Enter 'q' to exit)\n\n";
	
	string name="",password="";
	bool success=0;
	bool first=0;
	
	//Wait till correct input else exit
	while(!success){
		cout<<"Enter your name\n";
		if(!first){
			cin.ignore();
			first=1;
		}
		getline(cin,name,'\n');
		if(name=="q"){
			return 1;
		}
		cout<<"Enter your password\n";
		getline(cin,password,'\n');
		if(password=="q"){
			return 1;
		}
		
		int find;
		if(name!="Manager") find=2;
		else if(password!="admin@123") find=1;
		else find=0;
		
		if(find==0) success=1;
		else if(find==1) cout<<"Wrong Password :( ! Try again...\n";
		else if(find==2) cout<<"Username not found :-O\n";
	}
	
	cout<<"\t\t----- Successful Login! -----\n\n\n";
	cout<<"Welcome, "<<name<<"!\n\n";
	bool exit=0;
	char input;
	while(!exit){
		cout<<"\n\nWhat would you like to do?\n";
		cout<<"(Press 1) View status of all cars.\n";
		cout<<"(Press 2) Add Car.\n";
		cout<<"(Press 3) Update Car.\n";
		cout<<"(Press 4) Delete Car.\n";
		cout<<"(Press 5) Search Car.\n";
		cout<<"(Press 6) View all customers.\n";
		cout<<"(Press 7) Add customer.\n";
		cout<<"(Press 8) Update Customer.\n";
		cout<<"(Press 9) Delete Customer.\n";
		cout<<"(Press a) Search Customer.\n";
		cout<<"(Press b) View all employees.\n";
		cout<<"(Press c) Add Employee.\n";
		cout<<"(Press d) Update Employee.\n";
		cout<<"(Press e) Delete Employee.\n";
		cout<<"(Press f) Search Employee.\n";
		cout<<"(Press q) Logout.\n";
		cin>>input;
		
		switch(input){
			case '1':
				//View all cars
				view_all("car");
				break;
			case '2':
				//Add Car
				add("car");
				break;
			case '3':
				//Update Car
				update("car");
				break;
			case '4':
				//Delete Car
				del("car");
				break;
			case '5':
				//Search Car
				search("car");
				break;
			case '6':
				//View all customers
				view_all("customer");
				break;
			case '7':
				//Add Customer
				add("customer");
				break;
			case '8':
				//Update Customer
				update("customer");
				break;
			case '9':
				//Delete Customer
				del("customer");
				break;
			case 'a':
				//Search Customer
				search("customer");
				break;
			case 'b':
				//View all employees
				view_all("employee");
				break;
			case 'c':
				//Add Employee
				add("employee");
				break;
			case 'd':
				//Update Employee
				update("employee");
				break;
			case 'e':
				//Delete Employee
				del("employee");
				break;
			case 'f':
				//Search Employee
				search("employee");
				break;
			case 'q':
				exit=1;
				break;
			default:
				cout<<"Invalid input :(\n\n";
				break;
		}
	}
	
	Sleep(500);
	system("cls");
	user_role();
}

//Asks for the role of user else exit
char input(){
	char type;
	
	cout<<"Enter your role:\n\n";
	cout<<"1 for Customer\n2 for Employee\n3 for Manager\nq to exit\n\n\n";
	cin>>type;
	
	return type;
}

//Decides role
void role(char &type,bool &exit,bool &is_customer,bool &is_employee,bool &is_manager){
	bool f=1;
	
	//Wait for the role of user else exit
	while(f && !exit){
		switch(type){
			case 'q':
				exit=1;
				break;
			case '1':
				is_customer=1;
				f=0;
				break;
			case '2':
				is_employee=1;
				f=0;
				break;
			case '3':
				is_manager=1;
				f=0;
				break;
			default:
				cout<<"Invalid Input! Try again...\n";
				type=input();
		}
	}
}

//Asks user for role
void user_role(){
	char type;
	type=input();
	bool exit=0;
	bool is_customer=0,is_employee=0,is_manager=0;
	
	while(!exit){
		//Wait for the role of user else exit
		role(type,exit,is_customer,is_employee,is_manager);
		
		//Role of user
		if(is_customer){
			bool f=0;
			f=customer_func();
			if(f) exit=1;
		}
		else if(is_employee){
			bool f=0;
			f=employee_func();
			if(f) exit=1;
		}
		else if(is_manager){
			bool f=0;
			f=manager_func();
			if(f) exit=1;
		}
	}
}

//Converts string to integer
int string_to_int(string s){
	bool valid = 1;
	for(int i=0;i<s.size();i++){
		if((int)s[i]<48 || (int)s[i]>57){
			valid=0;
			break;
		}
	}
	
	if(!valid) return -1;
	
	int val = 0;
	for(int i=0;i<s.size();i++){
		val = (10*val) + (s[i]-48);
	}
	
	return val;
}

//Converts string to double
double string_to_double(string s){
	bool valid = 1;
	int cnt = 0;
	
	for(int i=0;i<s.size();i++){
		if((int)s[i]==46) cnt++;
		else if((int)s[i]<48 || (int)s[i]>57){
			valid = 0;
			break;
		}
		if(cnt>1) return -1;
	}
	
	if(!valid || cnt>1) return -1;
	
	double val=0.0;
	if(cnt==0){
		val = string_to_int(s);
		return val;
	}
	int ind = s.find('.');
	
	for(int i=0;i<ind;i++){
		val = (10*val) + (s[i]-48);
	}
	
	int pow=10;
	for(int i=ind+1;i<s.size();i++){
		val = val + (s[i]-48.0)/pow;
		pow*=10;
	}
	
	return val;
}

//Converts string to long
long int string_to_long(string s){
	bool valid = 1;
	for(int i=0;i<s.size();i++){
		if((int)s[i]<48 || (int)s[i]>57){
			valid=0;
			break;
		}
	}
	
	if(!valid) return -1;
	
	long int val = 0LL;
	for(int i=0;i<s.size();i++){
		val = (10*val) + (s[i]-48);
	}
	
	return val;
}

void load_cars(){
	ifstream Database;
	Database.open("car_database.txt");
	
	string line;
	vector<string> lines;
	while(Database){
		getline(Database,line);
		
		// cout<<line<<"\n";
		
		if(line.size()<2) continue;
		
		string sid="",smodel="",scondition="",savailibility="",sprice="",stype_of_owner="",sowner_name="",stime="";
		int i;
		int ind;
		ind=line.find("-");
		for(i=0;i<ind;i++){
			sid+=line[i];
		}
		
		i++;
		ind=i;
		for(i=ind;line[i]!='-';i++){
			smodel+=line[i];
		}
		
		i++;
		ind=i;
		for(i=ind;line[i]!='-';i++){
			scondition+=line[i];
		}
		
		i++;
		ind=i;
		for(i=ind;line[i]!='-';i++){
			savailibility+=line[i];
		}
		
		i++;
		ind=i;
		for(i=ind;line[i]!='-';i++){
			sprice+=line[i];
		}
		
		i++;
		ind=i;
		for(i=ind;line[i]!='-';i++){
			stype_of_owner+=line[i];
		}
		
		i++;
		ind=i;
		for(i=ind;;i++){
			if(line[i]=='-') break;
			sowner_name+=line[i];
		}
		
		i++;
		ind=i;
		for(i=ind;i<line.size();i++){
			stime+=line[i];
		}
		
		int id = string_to_int(sid);
		double price = string_to_double(sprice);
		long int litime = string_to_long(stime);
		
		Car New_Car(smodel,scondition,price);
		New_Car.id = id;
		New_Car.availibity = savailibility;
		New_Car.type_of_owner = stype_of_owner;
		New_Car.owner_name = sowner_name;
		New_Car.time_rented = litime;
		
		car.push_back(New_Car);
		
		lines.push_back(line);
	}
	
	string final_id="";
	string lline=lines[lines.size()-1];
	int lind=lline.find("-");
	for(int i=0;i<lind;i++){
		final_id+=lline[i];
	}
	
	Car::car_count = string_to_int(final_id)+1;
	
	Database.close();
}

void load_customers(){
	ifstream Database;
	Database.open("cust_database.txt");
	
	string line;
	vector<string> lines;
	while(Database){
		getline(Database,line);
		
		if(line.size()<2) continue;
		
		string sid="",sname="",spassword="",scustomer_record="",scars_rented="",sfine_due="";
		map<int, bool> id_cars_rented;
		int i;
		int ind;
		ind=line.find("-");
		for(i=0;i<ind;i++){
			sid+=line[i];
		}
		
		i++;
		for(;line[i]!='-';i++){
			sname+=line[i];
		}
		
		i++;
		for(;line[i]!='-';i++){
			spassword+=line[i];
		}
		
		i++;
		for(;line[i]!='-';i++){
			scustomer_record+=line[i];
		}
		
		i++;
		for(;line[i]!='-';i++){
			scars_rented+=line[i];
		}
		
		i++;
		bool no = 0;
		for(;line[i]!='-';i++){
			if(i==line.size() || line[i]==EOF){
				no = 1;
				break;
			}
			sfine_due+=line[i];
		}
		if(!no){
			i++;
			string car_id="";
			while(line[i]!='\n'){
				car_id+=line[i];
				i++;
				if(line[i]=='-'){
					id_cars_rented[string_to_int(car_id)]=1;
					i++;
					car_id="";
				}
				else if(line[i]=='\n' || i==line.size() || line[i]==EOF){
					id_cars_rented[string_to_int(car_id)]=1;
					break;
				}
			}
		}
		
		int id = string_to_int(sid);
		double customer_record = string_to_double(scustomer_record);
		int cars_rented = string_to_int(scars_rented);
		double fine_due = string_to_double(sfine_due);
		
		Customer New_Customer(sname,spassword);
		New_Customer.id = id;
		New_Customer.customer_record = customer_record;
		New_Customer.cars_rented = cars_rented;
		New_Customer.fine_due = fine_due;
		New_Customer.id_cars_rented = id_cars_rented;
		
		cust.push_back(New_Customer);
		
		lines.push_back(line);
	}
	
	string final_id="";
	string lline=lines[lines.size()-1];
	int lind=lline.find("-");
	for(int i=0;i<lind;i++){
		final_id+=lline[i];
	}
	
	Customer::cust_count = string_to_int(final_id)+1;
	
	Database.close();
}

void load_employees(){
	ifstream Database;
	Database.open("emp_database.txt");
	
	string line;
	vector<string> lines;
	while(Database){
		getline(Database,line);
		
		if(line.size()<2) continue;
		
		string sid="",sname="",spassword="",semployee_record="",scars_rented="",sfine_due="";
		map<int, bool> id_cars_rented;
		int i;
		int ind;
		ind=line.find("-");
		for(i=0;i<ind;i++){
			sid+=line[i];
		}
		
		i++;
		for(;line[i]!='-';i++){
			sname+=line[i];
		}
		
		i++;
		for(;line[i]!='-';i++){
			spassword+=line[i];
		}
		
		i++;
		for(;line[i]!='-';i++){
			semployee_record+=line[i];
		}
		
		i++;
		for(;line[i]!='-';i++){
			scars_rented+=line[i];
		}
		
		i++;
		bool no = 0;
		for(;line[i]!='-';i++){
			if(i==line.size()){
				no = 1;
				break;
			}
			sfine_due+=line[i];
		}
		if(!no){
			i++;
			string car_id="";
			while(line[i]!='\n'){
				car_id+=line[i];
				i++;
				if(line[i]=='-'){
					id_cars_rented[string_to_int(car_id)]=1;
					i++;
					car_id="";
				}
				else if(line[i]=='\n' || i==line.size() || line[i]==EOF){
					id_cars_rented[string_to_int(car_id)]=1;
					break;
				}
			}
		}
		
		int id = string_to_int(sid);
		double employee_record = string_to_double(semployee_record);
		int cars_rented = string_to_int(scars_rented);
		double fine_due = string_to_double(sfine_due);
		
		Employee New_Employee(sname,spassword);
		New_Employee.id = id;
		New_Employee.employee_record = employee_record;
		New_Employee.cars_rented = cars_rented;
		New_Employee.fine_due = fine_due;
		New_Employee.id_cars_rented = id_cars_rented;
		
		emp.push_back(New_Employee);
		
		lines.push_back(line);
	}
	
	string final_id="";
	string lline=lines[lines.size()-1];
	int lind=lline.find("-");
	for(int i=0;i<lind;i++){
		final_id+=lline[i];
	}
	
	Employee::emp_count = string_to_int(final_id)+1;
	
	Database.close();
}

int Car::car_count = 0;
int Customer::cust_count = 0;
int Employee::emp_count = 0;

int main(){
	//Loading Data from Car Database
	load_cars();
	
	//Loading Data from Customer Database
	load_customers();
	
	//Loading Data from Employee Database
	load_employees();
	
	//Creating Dummy Data for Manager Database
	Manager Manager_1("Manager","admin@123");
	
	//Welcome Screen
	cout<<"\t\t------ Welcome! ------\n\n\n";
	
	//Ask for user role
	user_role();
	
	return 0;
}
