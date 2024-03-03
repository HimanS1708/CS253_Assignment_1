<h1>How to run?</h1>

- Save the files in a directory, say `x`.
- Open your terminal and go to directory `x`.
- Type the following commands in the terminal:
  
  ```
  g++ solution.cpp -o solution.exe
  ./solution.exe
  ```
- You will have successfully started the program.

<h1>How are the Databases setup?</h1>

- There are three databases, namely - `car_database.txt` (for Cars) , `cust_database.txt` (for Customers) and `emp_database.txt` (for Employees)
- The attributes in a database are separated by `-`.
- The database for Cars stores the attributes: `Car ID` , `Model Name` , `Car Condition` , `Availability` , `Rent Price` , `Role of owner` , `Owner Name` and `Time at which it was rented` (in order)
- The database for Customers stores the attributes: `Customer ID` , `Customer Name` , `Password` , `Customer Record` , `Number of cars rented` , `Fine due` and `IDs of the cars rented` (in order)
- The database for Employees stores the attributes: `Employee ID` , `Employee Name` , `Password` , `Employee Record` , `Number of cars rented` , `Fine due` and `IDs of the cars rented` (in order)
- The attribute `IDs of the cars rented` is dynamic, i.e. if a customer/employee has no cars rented then this attribute is not present. If a customer/employee has ***x*** cars then there are ***x*** attributes.

<h1>Dummy Data for Databases</h1>

<h2>1. Car Database</h2>

```
0-Model 1-Good-Available-20000-NA-NA-0
1-Model 2-Good-Available-30000-NA-NA-0
2-Model 3-Good-Available-40000-NA-NA-0
3-Model 4-Good-Available-50000-NA-NA-0
4-Model 5-Good-Available-60000-NA-NA-0
```

<h2>2. Customer Database</h2>

```
0-Customer 1-@1-5-0-0
1-Customer 2-@2-5-0-0
2-Customer 3-@3-5-0-0
3-Customer 4-@4-5-0-0
4-Customer 5-@5-5-0-0
```

<h2>3. Employee Database</h2>

```
0-Employee 1-@e1-5-0-0
1-Employee 2-@e2-5-0-0
2-Employee 3-@e3-5-0-0
3-Employee 4-@e4-5-0-0
4-Employee 5-@e5-5-0-0
```

<h1>Working</h1>

- The program starts and loads data from databases so that it can be used easily for the working of the program.
- The program stores this loaded data using STL of C++ for easy manipulation.
- The databases are update dynamically as the program runs, for e.g., if some car has been rented then its attributes will be updated dynamically in the database as well in real time.
- There is only one Manager with username `Manager` and password `admin@123`.
- The number of Cars, Customers and Employees can vary.
- The IDs for Cars, Customers and Employees are unique.
- Throughout the program, only Username and Password is provided as input.
- Two entities cannot have the same name.
- Manager can add/update/delete/search Cars, Customers and Employees.
- Manager can view status of Cars, Customers and Employees.
- Customers/Employees can view all Cars and Cars rented by them.
- Customers/Employees can view and clear dues.
- Customers/Employees can rent and return Cars.
- Time is stored and checked using `time_t`.
- Customer/Employee record is initially "0.5".
- Customer record decreases by "0.1" per day after 7 days.
- Employee record decreases by "0.05" per day after 7 days.
- Customer is fined $500 per day after 7 days.
- Employee is fined $250 per day after 7 days.

<h1>Structure of Program</h1>

- There is Parent class User which has three derived classes - Customer, Employee and Manager.
- There is a class for Car.
- There is a login page which asks for the role of user.
- The type of role decides the options shown on the screen.
- Vector of objects cust, emp and car are used for easy access to data.
- Unique ID for all objects are created using static int values.
- `friend functions` are used for a function that needs to access the private/protected members of a class.

<h1>Assumptions</h1>

- The user does not enter unnecessary whitespaces whenever he enters a value.
- A customer does not register himself. Only the manager can register a Customer.
- Whenever the user is asked for a single character, if he enters a string then it is considered as a multiple character input so the string will act as a stream of characters.
- Customer/Employee can clear their own dues.
- Manager cannot delete a Car if it is currently rented.
- Manager cannot delete a Customer/Employee if they currently own a Car.
- Manager can delete a Customer/Employee if they currently have some dues.
