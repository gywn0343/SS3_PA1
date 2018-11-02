# PA1 READ ME
- - -
* Library which deals with only undergraduate and also only contains books as their resources. In this project, undergraduate can only borrow resources, in this case books, for 14 days and can borrow up to one resource. Class that saves data or does operations for undergraduate -named Under- inherited the class, Member. On the other hand, class for books named Book, has a parent class named Resource.
### Development Environment
- - - 
* OS: Ubuntu 18.04.1 64bit
* Language: C++
* How to Compile: $ make

### Code Explanation
- - -
1. library.h
* class Library
	* Library(): gets line-by-line information from resource.dat and input.dat
	* do_operation(): make resource part and member part do their operation with given information. In this project, all resource type is book and all member type is Undergraduate, so we call B.do_op and U.do_op. Get each return values(ret1 and ret2) and call right result function for them.
	* print_result(): write right result on output.dat
2. member.h
* class Under
	* This class is inherited by class Member. 
	* do_op(): This function checks if this action is valid utilizing information stored in undergraduate and member class. Usually the operation is same between other nenbers, so the functions called by do_op function are defined in parent class, Member.
* class Member
	* In this class, members' names, their restirct date, and their possible borrow counts are stored in vector. 
	* isExeed(): Checks if the number of borrows are more than possible number of them. 
	* isRestricted(): Checks if this member is restricted.
	* final_state(): This one is for updating information. For example, if the member succeeded on borrowing resources, then it has to increment the number of borrows with one. In addition, when the member returned resource late, then number of borrows are decremented, and the restrict date has to be set.
3. resource.h
* class Book
	* This class is inherited by class Resource.
	* do_op(): Same as do_op in class Under.
* class Resource
	* In this class, resources' names, borrowed member's name, borrowed date and return date is stored in vector.
	* isInLibrary(): Check is this kind of resource is in the library.
	* isAvailable(): Check if somebody else has already borrowed the resource.
	* isGoodReturn(): Check if the return was right in time.
	* final_state(): For updating information. If the resource is lended to anyone, it has to store the date and member's information.

