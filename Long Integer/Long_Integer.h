#ifndef LONG_INTEGER
#define LONG_INTEGER
class Long_Integer
{
private:
	unsigned int* arr;
	int mostSigDigits;
	int sign;
public:
	Long_Integer(int s, int* A);
	Long_Integer(int s, unsigned int* A,int size);
	Long_Integer(const Long_Integer &long_integer);
	Long_Integer& operator=(const Long_Integer &long_integer);
	Long_Integer operator+(const Long_Integer &long_integer);
	Long_Integer operator-(const Long_Integer &long_integer);
	bool operator<(const Long_Integer& long_integer);
	bool operator>(const Long_Integer& long_integer);
	bool operator==(const Long_Integer& long_integer);

	void test(Long_Integer other);
	
	Long_Integer(void);
	~Long_Integer();
	void print();
	void print_math (Long_Integer other,Long_Integer sum,char sign);
	bool equal_to    (Long_Integer other);
	bool less_than   (Long_Integer other);
	bool greater_than(Long_Integer other);
	Long_Integer add (Long_Integer other);
	Long_Integer subtract(Long_Integer other);
	unsigned int* getArrayAt(int index);
	int getSign();
	Long_Integer setSign(int sign);
	unsigned int* getLongInteger();
	int getMostSignificant();
	void print_math_scientific(Long_Integer other, Long_Integer sum, char sign,int prec);
	void print_scientific(int prec);
};
/*
LongInt(int sign, int [] array) – Initializes a LongInt via an array of integers and an integer containing
									1 or -1, indicating the sign of the overall LongInteger
void print() – Prints the String representation of the LongInt to standard output
boolean equalTo(LongInt other) – Determines if the LongInt is equal to the LongInt other
boolean lessThan(LongInt other) – Determines if the LongInt is less than the LongInt other
boolean greaterThan(LongInt other) – Determines if the LongInt is greater than the LongInt other
LongInt add(LongInt other) – Adds the LongInt and returns the result as a new LongInt
LongInt subtract(LongInt other) – Subtracts the LongInt and returns the result as a new LongInt

*/
#endif