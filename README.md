# PA1 READ ME
* Library which deals with only undergraduate and also only contains books as their resources. In this project, undergraduate can only borrow resources, in this case books, for 14 days and can borrow up to one resource. Class that saves data or does operations for undergraduate -named Under- inherited the class, Member. On the other hand, class for books named Book, has a parent class named Resource.
### Development Environment
- - - 
> OS: Ubuntu 18.04.1 64bit
> Language: C++
> How to Compile: $ make

### Code Explanation
- - -
1. library.h
* class Library
	* Library(): gets line-by-line information from resource.dat and input.dat
	* do operation(): make resource part and member part do their operation with given information. In this project, all resource type is book and all member type is Undergraduate, so we call B.do_op and U.do_op. Get each return values(ret1 and ret2) and call right result function for them.
	* print result(): write right result on output.dat
2. member.h
* class Under
	* This class is inherited by class Member. 
	* do_op(): 

### Link
- - -
[Redis](https://redis.io)
- - - 
