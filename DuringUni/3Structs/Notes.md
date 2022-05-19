Structs are duplicated into a function

like in primitive types if you pass in an int into the function, the int is duplicated and you use that

Its not a reference to a struct, if you change the struct passed into the parameters it doesnt change the struct

its a local copy of the struct

Its only when you pass in the pointer, you change the struct directly

unlike java, if you changed the object inside the function. it would change the object outside. You will need to replace the parameters with pointers to the struct. 

In memory, the struct is treated like it is an array. its treated like one contigious piece of memory. 

it is not a field. there are no operators that work with structs, apart from &

```c
struct date m;

char * ptr = &m;

ptr[0]
ptr[1]

```

```c

struct item {
	char barcode[6];
	const char *name;
	float price;
}


int main(){
	struct item items[2];

	strncpy(items[0].barcode, "DFH291", 6)'; //copys ths string
}

```

it is an array of contigious memory, but of different data types
first being chars, then a string, then a price. being 18 bytes of data total

creating an array of structs is making one large array. with both

memory allignment.

# UNION
UNIONS ARE STRUCTS THAT USE THE SAME MEMORY. ITS LIKE OVERLOADING THE ATTRIBUTES AND DECIDING WHICH ONE YOU WANT TO USE

in the below example it is trying to create a struct object, called catalog. 

the catalog will hold either a book or a film, it has the title and the type

```c 
enum holding_type {book, film};

struct catalog
{
	char * title;
	enum holding_type type;
	struct /*book*/
	{
		char * author
		char * ISBN;
	} book_info;

	struct /*film*/
	{
		char * director;
		char * producer;
	}film_info;
}
```

only one of the structure book_info or film_info is used at any one tim. this can be a major waste of memory

it is 44 bytes


the union, is this or this one

```c 
enum holding_type {book, film};

struct catalog
{
	char * title;
	enum holding_type type;
	union 
	{
		struct /*book*/
		{
			char * author
			char * ISBN;
		} book_info;

		struct /*film*/
		{
			char * director;
			char * producer;
		}film_info;
	} info;
}
```

it makes it so the info refers to the book OR the film. 

the maximum of all fiels of the union, 16 bytes. 

UNION is like shared memory. makes 16 bytes avaliable, and either the book or the film can use it

`x.info.book_info.author`

you cant know which part of the union is being used, thats why there is an enum added to it. so the programmer can tell which part of the information is being accessed

# Bitfields

can specify a size in bits for elements of a structure. its like a struct but you assign EXACTLY how many bits something needs to work, it gets around padding issues that structs might have