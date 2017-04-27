#include "Long_Integer.h"
#include <iostream>
#include <stdio.h>
#include <math.h>
#define LIMIT (unsigned int)99999999
#define NEGATIVE -1
#define POSITIVE 1
#define ENDARRAY -1111
using namespace std;
Long_Integer::Long_Integer(int sign, unsigned int* A, int size) : sign(sign){
	arr = new unsigned int[size];
	mostSigDigits = size - 1;
	for (int i = 0; i < size; i++)
		arr[i] = A[i];
}
Long_Integer::Long_Integer(void){
	arr = NULL;
	mostSigDigits = NULL;
	sign = NULL;
}
Long_Integer::~Long_Integer(){
	delete arr;
	arr = NULL;
}
Long_Integer::Long_Integer(const Long_Integer &long_integer){
	arr = new unsigned int[long_integer.mostSigDigits + 1];
	mostSigDigits = long_integer.mostSigDigits;
	sign = long_integer.sign;
	for (int i = 0; i <= long_integer.mostSigDigits; i++){
		arr[i] = long_integer.arr[i];
	}
}
Long_Integer& Long_Integer::operator=(const Long_Integer &long_integer){
	if (this != &long_integer){
		arr = new unsigned int[long_integer.mostSigDigits + 1];
		mostSigDigits = long_integer.mostSigDigits;
		sign = long_integer.sign;
		for (int i = 0; i <= long_integer.mostSigDigits; i++){
			arr[i] = long_integer.arr[i];
		}
	}
	return *this;
}
int Long_Integer::getMostSignificant(){
	return mostSigDigits;
}
void Long_Integer::print(){
	unsigned int big = arr[mostSigDigits] > 0 ? (int)log10(arr[mostSigDigits]) : 0;
	unsigned int size = mostSigDigits * 8 + 1 + big;
	unsigned short* A = new unsigned short[size];
	int value;
	for (int i = 0; i <= mostSigDigits; i++){
		value = arr[i];
		for (int j = 0; j < 8; j++){
			A[i * 8 + j] = value % 10;
			value /= 10;
			if (i * 8 + j >= size - 1)
				break;
		}
	}
	printf("%c", sign == POSITIVE ? ' ' : '-');
	for (int i = size - 1; i >= 0 && i < size; i--){
		printf("%u", A[i]);
		if (i % 3 == 0 && i != 0)
			printf(",");
	}
	printf("\n");
	delete[] A;
	A = NULL;
}
void Long_Integer::print_scientific(int prec){
	unsigned int big = arr[mostSigDigits] > 0 ? (int)log10(arr[mostSigDigits]) : 0;
	unsigned int size = mostSigDigits * 8 + 1 + big;
	unsigned short* A = new unsigned short[size];
	int value;
	for (int i = 0; i <= mostSigDigits; i++){
		value = arr[i];
		for (int j = 0; j < 8; j++){
			A[i * 8 + j] = value % 10;
			value /= 10;
			if (i * 8 + j >= size - 1)
				break;
		}
	}
	printf("%c", sign == POSITIVE ? ' ' : '-');
	int i = size - 1;
	while( i > size - prec - 2 && i < size){
		if (size - 1 > 0){
			printf("%u", A[i]);
			if (i == size - 1)
				printf(".");
		}
		else if (size - 1 == 0){
			printf("%u", A[0]);
		}
		else
			printf("0");
		i--;
	}
	printf("e+%u", size - 1);
	delete[] A;
	A = NULL;
}
bool Long_Integer::equal_to(Long_Integer other){
	if (arr[mostSigDigits] == *other.getArrayAt(other.getMostSignificant())
		&&  mostSigDigits  ==  other.getMostSignificant()
		&&  sign           ==  other.getSign())
		return true;
	else
		return false;
}
bool Long_Integer::less_than(Long_Integer other){
	return !greater_than(other) && !equal_to(other);
}
bool Long_Integer::greater_than(Long_Integer other){
	if (sign == NEGATIVE && other.getSign() == POSITIVE)
		return false;
	else if (sign == POSITIVE && other.getSign() == NEGATIVE)
		return true;
	else if (sign == other.getSign() && sign == NEGATIVE)
		return Long_Integer(*this).setSign(POSITIVE).less_than(other.setSign(POSITIVE));
	else if (sign == other.getSign() && sign == POSITIVE
		&& (mostSigDigits > other.getMostSignificant()
		|| (mostSigDigits == other.getMostSignificant()
		&& arr[mostSigDigits] > *(other.getArrayAt(other.getMostSignificant())))))
		return true;
	else
		return false;
}
unsigned int* Long_Integer::getArrayAt(int index){
	return arr + index;
}
Long_Integer Long_Integer::add(Long_Integer other){
	if (sign == other.getSign() && sign == POSITIVE){
		int max = mostSigDigits > other.getMostSignificant()
				? mostSigDigits : other.getMostSignificant();
		unsigned int* ptr = other.getLongInteger();
		unsigned int* A = new unsigned int[2 + max];
		unsigned int this_value;
		unsigned int othr_value;
		for (int i = 0; i < 2 + max; i++)
			A[i] = NULL;
		for (int cntr = 0; cntr < max + 1; cntr++){
			this_value = cntr <= mostSigDigits ? arr[cntr] : 0;
			othr_value = cntr <= other.getMostSignificant() ? ptr[cntr] : 0;
			if (this_value + othr_value + A[cntr] > LIMIT){
				A[cntr + 1]++;
				A[cntr] = this_value + othr_value + A[cntr] - (LIMIT + 1);
			}else{
				A[cntr] = this_value + othr_value + A[cntr];
			}

		}
		int sz = A[max + 1] == 0 ? max + 1: max + 2;
		Long_Integer sum = Long_Integer(POSITIVE, A, sz);
		delete [] A; 
		A = NULL;
		return sum;
	}
	else if (sign == NEGATIVE && other.getSign() == NEGATIVE){
		return Long_Integer(*this).setSign(POSITIVE).add(other.setSign(POSITIVE)).setSign(NEGATIVE);
	}
	else if (sign == NEGATIVE && other.getSign() == POSITIVE){
		return other.subtract(Long_Integer(*this).setSign(POSITIVE));
	}
	else if(sign == POSITIVE && other.getSign() == NEGATIVE){
		return Long_Integer(*this).subtract(other.setSign(POSITIVE));
	}
}
Long_Integer Long_Integer::subtract(Long_Integer other){
	if (sign == other.getSign() && sign == NEGATIVE){
		return other.setSign(POSITIVE).subtract(Long_Integer(*this).setSign(POSITIVE));
	}
	else if (sign == POSITIVE && other.getSign() == NEGATIVE){
		return Long_Integer(*this).add(other.setSign(POSITIVE));
	}
	else if (sign == NEGATIVE && other.getSign() == POSITIVE){
		return other.add(Long_Integer(*this).setSign(POSITIVE)).setSign(NEGATIVE);
	}
	else if (sign == other.getSign() && sign == POSITIVE && this->less_than(other)){
		return other.subtract(Long_Integer(*this)).setSign(NEGATIVE);
	}
	else if(sign == other.getSign() && sign == POSITIVE 
		&& (*this > other || *this == other)){
		int max = mostSigDigits > other.getMostSignificant() 
				? mostSigDigits : other.getMostSignificant();
		//size is 1 bigger than the largest index
		int* A = new int[max + 1];
		for (int i = 0; i < max + 1; i++){
			A[i] = NULL;
		}
		unsigned int* ptr = other.getLongInteger();
		int this_value;
		int othr_value;
		for (int cntr = 0; cntr <= max; cntr++){
			this_value = cntr <= mostSigDigits ? arr[cntr] : 0;
			othr_value = cntr <= other.getMostSignificant() ? ptr[cntr] : 0;
			if (this_value < othr_value){
				A[cntr] = LIMIT + 1 + this_value - othr_value + A[cntr];
				A[cntr + 1]--;
			}
			else if (othr_value <= this_value){
				A[cntr] = this_value - othr_value;
			}
		}
		unsigned int sz = 0;
		for (unsigned int i = max; i >= 0 && i <= max; i--){
			if (A[i] > 0){
				sz = i;
				break;
			}
		}
		unsigned int* AA = new unsigned int[max + 1];
		for (int i = 0; i < max + 1; i++){
			AA[i] = A[i];
		}
		Long_Integer diff = Long_Integer(POSITIVE,AA, sz + 1);
		delete [] A;
		delete[] AA;
		A = NULL;
		return diff;
	}
}

Long_Integer Long_Integer::setSign(int sign){
	this->sign = sign;
	return *this;
}
int Long_Integer::getSign(){
	return sign;
}
unsigned int* Long_Integer::getLongInteger(){
	return arr;
}
void Long_Integer::print_math(Long_Integer other,Long_Integer sum,char sign){
	//count the amount of digits in each number

	unsigned int big1 = arr[mostSigDigits] > 0 ? (int)log10(arr[mostSigDigits]) : 0;
	unsigned int big2 = other.getMostSignificant() > 0 ? (int)log10(*other.getArrayAt(other.getMostSignificant())) : 0;
	unsigned int big3 = sum.getMostSignificant() > 0 ? (int)log10(*sum.getArrayAt(sum.getMostSignificant())) : 0;

	unsigned int size1 = mostSigDigits * 8 + 1 + big1;
	unsigned int size2 = other.getMostSignificant() * 8 + 1 + big2;
	unsigned int size3 = sum.getMostSignificant() * 8 + 1 + big3;
	unsigned int maxsz = size1 >= size2 ? size1 >= size3 ? size1 : size3 : size2 >= size3 ? size2 : size3;
	// instantiate comma counts
	unsigned int comcnt1 = 0;
	unsigned int comcnt2 = 0;
	unsigned int comcnt3 = 0;
	unsigned int maxcomm = 0;
	//get comma count1 and count 2
	for (unsigned int i = 0; i < maxsz + 1; i++){
		if (i % 3 == 0 && i != 0 && i < size1)
			comcnt1++;
		if (i % 3 == 0 && i != 0 && i < size2)
			comcnt2++;
		if (i % 3 == 0 && i != 0 && i < size3)
			comcnt3++;
		if (i % 3 == 0 && i != 0 && i < maxsz)
			maxcomm++;
	}
	printf("   ");
	for (int i = 0; i < maxcomm - comcnt1; i++)
		printf(" ");
	for (int i = 0; i < maxsz - size1; i++)
		printf(" ");
	print();
	printf("%c  ",sign);
	for (int i = 0; i < maxcomm - comcnt2; i++)
		printf(" ");
	for (int i = 0; i < maxsz - size2; i++)
		printf(" ");
	other.print();
	printf("---");
	for (int i = 0; i < maxsz; i++){
		printf("-");
		if (i % 3 == 0){
			printf("-");
		}
	}
	printf("\n");
	printf("   ");
	for (int i = 0; i < maxcomm - comcnt3; i++)
		printf(" ");
	for (int i = 0; i < maxsz - size3; i++)
		printf(" ");
	sum.print();
	printf("\n\n");
}

void Long_Integer::print_math_scientific(Long_Integer other, Long_Integer sum, char sign,int prec){
		unsigned int big1 = arr[mostSigDigits] > 0 ? (int)log10(arr[mostSigDigits]) : 0;
		unsigned int big2 = other.getMostSignificant() > 0 ? (int)log10(*other.getArrayAt(other.getMostSignificant())) : 0;
		unsigned int big3 = sum.getMostSignificant() > 0 ? (int)log10(*sum.getArrayAt(sum.getMostSignificant())) : 0;

		unsigned int size1 = mostSigDigits * 8 + 1 + big1;
		unsigned int size2 = other.getMostSignificant() * 8 + 1 + big2;
		unsigned int size3 = sum.getMostSignificant() * 8 + 1 + big3;
		unsigned int maxsz = size1 >= size2 ? size1 >= size3 ? size1 : size3 : size2 >= size3 ? size2 : size3;

		printf("   ");
		print_scientific(prec);
		printf("%c  ", sign);
		other.print_scientific(prec);
		printf("---");
		for (int i = 0; i < 1 + log10(maxsz) + prec + 2; i++){
			printf("-");
			if (i % 3 == 0){
				printf("-");
			}
		}
		printf("\n");
		printf("   ");
		sum.print_scientific(prec);
		printf("\n\n");
}

Long_Integer::Long_Integer(int sign, int *A):sign(sign){
	int size = 0;
	while (A[size] != ENDARRAY)
		size++;
	mostSigDigits = size - 1;
	arr = new unsigned int[size];
	for (unsigned int i = 0; i < size; i++){
		arr[i] = A[i];
	}
}

void Long_Integer::test(Long_Integer other){

	int a = 1;
}

Long_Integer Long_Integer::operator+(const Long_Integer& long_integer){
	return (*this).add(long_integer);
}
Long_Integer Long_Integer::operator-(const Long_Integer& long_integer){
	return (*this).subtract(long_integer);
}
bool Long_Integer::operator<(const Long_Integer& long_integer){
	return (*this).less_than(long_integer);
}
bool Long_Integer::operator>(const Long_Integer& long_integer){
	return (*this).greater_than(long_integer);
}
bool Long_Integer::operator==(const Long_Integer& long_integer){
	return (*this).equal_to(long_integer);
}
/*
int main(){

	int A[] = { 11568359, 0, 142355, ENDARRAY};
	int B[] = { 34529077, ENDARRAY };

	Long_Integer AA = Long_Integer(POSITIVE, A);
	Long_Integer* BB = new Long_Integer(POSITIVE, B);
	
	Long_Integer CC = (AA + *BB);

	bool DD = AA > *BB;

	return 0;
}
*/

int main(){
	int positive = 1;
	int negative = -1;

	int A[] = { 11568359, 34529077, 5459, 10056810, 0, 142355,ENDARRAY};
	int B[] = { 54317890, 45948474, 35000327,ENDARRAY};
	int C[] = { 28937492, 87289347, 49872934, 72348723, 93742093, 20973420, 34209374, 97340297, 90234702, 293023,ENDARRAY };
	int D[] = { 23423423, 23423567, 66234234, 9928374, 82038942, 9823049, 87339234, 29873429, 34298374, 98534,ENDARRAY };
	int E[] = { 76527612, 62741230, 67216241,
					61276521, 32461745, 51651123, 42587561, 68486132,
					54351531, 41592654, 51515131, 45415451, 38435153,
					38131384, 84381351, 38413513, 38431351, 84681315,
					84684313, 46843153, 48435168, 43435168, 43518468,
					43489436, 84694835, 83513516, 16843861, 8436413,ENDARRAY };


	Long_Integer* long_int [5];
	long_int[0] = new Long_Integer(positive, A);
	long_int[1] = new Long_Integer(negative, B);
	long_int[2] = new Long_Integer(positive, C);
	long_int[3] = new Long_Integer(negative, D);
	long_int[4] = new Long_Integer(positive, E);
	//print test cases
	printf("\n\n");
	for (int i = 0; i < 5; i++){
		printf("Printing test case %c%s ",i + 65,":");
		long_int[i]->print();
		//printf("Printing test case %c%s ", i + 65, ":");
		//long_int[i]->print_scientific(5);
		//printf("\n");
	}
	printf("\n\n");
	printf("Printing all boolean comparisons ...\n");
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			printf("|%c greater than %c: %s|\n", i + 65, j + 65, *long_int[i] > *long_int[j] ? "true " : "false");
			printf("|%c less than    %c: %s|\n", i + 65, j + 65, *long_int[i] < *long_int[j] ? "true " : "false");
			printf("|%c equal to     %c: %s|\n", i + 65, j + 65, *long_int[i] == *long_int[j] ? "true " : "false");
			printf("+-----------------------+\n");
		}
	}
	printf("\n\n");
	Long_Integer this_value;
	Long_Integer othr_value;
	Long_Integer difference;
	Long_Integer sum;
	for (unsigned int i = 0; i < 4; i++){
		for (unsigned int j = 0; j < 4; j++){
			this_value = *long_int[i];
			othr_value = *long_int[j];
			difference = this_value - othr_value;
			printf("Printing %c - %c:",i + 65,j + 65);
			this_value.print_scientific(3);
			printf(" - ");
			othr_value.print_scientific(3);
			printf(" = ");
			difference.print_scientific(3);
			printf("\n\n");
			this_value.print_math(othr_value, difference, '-');
		}
	}
	for (unsigned int i = 0; i < 4; i++){
		for (unsigned int j = 0; j < 4; j++){
			this_value = *long_int[i];
			othr_value = *long_int[j];
			sum        = this_value + othr_value;
			printf("Printing %c + %c:", i + 65, j + 65);
			this_value.print_scientific(3);
			printf(" + ");
			othr_value.print_scientific(3);
			printf(" = ");
			sum.print_scientific(3);
			printf("\n\n");
			this_value.print_math(othr_value, sum, '+');
		}
	}
	this_value = *long_int[4];
	for (unsigned int i = 0; i < 5; i++){
		printf("Printing E + %c:", i + 65);
		othr_value = *long_int[i];
		sum		= this_value + othr_value;
		this_value.print_scientific(3);
		printf(" + ");
		othr_value.print_scientific(3);
		printf(" = ");
		sum.print_scientific(3);
		printf("\n\n");
		this_value.print_math(othr_value, sum, '+');
	}
	for(unsigned int i = 0; i < 5; i++){
		if (i != 2){}
			//continue;
		printf("Printing E - %c:", i + 65);
		othr_value = *long_int[i];
		difference = this_value - othr_value;
		this_value.print_scientific(3);
		printf(" + ");
		othr_value.print_scientific(3);
		printf(" = ");
		difference.print_scientific(3);
		printf("\n\n");
		this_value.print_math(othr_value, difference, '-');
	}

	for(int i = 0; i < 5; i++)
		delete long_int[i];
	return 0;
};

/*
int main(){
	int positive = 1;
	int negative = -1;

	int A[] = { 11568359, 34529077, 5459, 10056810, 0, 142355, ENDARRAY };
	int B[] = { 54317890, 45948474, 35000327, ENDARRAY };
	int C[] = { 28937492, 87289347, 49872934, 72348723, 93742093, 20973420, 34209374, 97340297, 90234702, 293023, ENDARRAY };
	int D[] = { 23423423, 23423567, 66234234, 9928374, 82038942, 9823049, 87339234, 29873429, 34298374, 98534, ENDARRAY };
	int E[] = { 76527612, 62741230, 67216241,
		61276521, 32461745, 51651123, 42587561, 68486132,
		54351531, 41592654, 51515131, 45415451, 38435153,
		38131384, 84381351, 38413513, 38431351, 84681315,
		84684313, 46843153, 48435168, 43435168, 43518468,
		43489436, 84694835, 83513516, 16843861, 8436413, ENDARRAY };

	Long_Integer* long_int[5];
	long_int[0] = new Long_Integer(positive, A);
	long_int[1] = new Long_Integer(negative, B);
	long_int[2] = new Long_Integer(positive, C);
	long_int[3] = new Long_Integer(negative, D);
	long_int[4] = new Long_Integer(positive, E);
	//print test cases
	printf("\n\n");
	for (int i = 0; i < 5; i++){
		printf("Printing test case %c%s ", i + 65, ":");
		long_int[i]->print_scientific(3);
	}
	printf("\n\n");
	printf("Printing all boolean comparisons ...\n");
	for (int i = 0; i < 5; i++){
		for (int j = 0; j < 5; j++){
			printf("|%c greater than %c: %s|\n", i + 65, j + 65, *long_int[i] > *long_int[j] ? "true " : "false");
			printf("|%c less than    %c: %s|\n", i + 65, j + 65, *long_int[i] < *long_int[j] ? "true " : "false");
			printf("|%c equal to     %c: %s|\n", i + 65, j + 65, *long_int[i] == *long_int[j] ? "true " : "false");
			printf("+-----------------------+\n");
		}
	}
	printf("\n\n");
	Long_Integer this_value;
	Long_Integer othr_value;
	Long_Integer difference;
	Long_Integer sum;
	for (unsigned int i = 0; i < 4; i++){
		for (unsigned int j = 0; j < 4; j++){
			printf("Printing %c - %c:\n", i + 65, j + 65);
			this_value = *long_int[i];
			othr_value = *long_int[j];
			difference = this_value - othr_value;
			this_value.print_math_scientific(othr_value, difference, '-',3);
		}
	}
	for (unsigned int i = 0; i < 4; i++){
		for (unsigned int j = 0; j < 4; j++){
			printf("Printing %c + %c:\n", i + 65, j + 65);
			this_value = *long_int[i];
			othr_value = *long_int[j];
			sum = this_value + othr_value;
			this_value.print_math_scientific(othr_value, sum, '+',3);
		}
	}
	this_value = *long_int[4];
	for (unsigned int i = 0; i < 5; i++){
		printf("Printing E + %c:\n", i + 65);
		othr_value = *long_int[i];
		sum = this_value + othr_value;
		this_value.print_math_scientific(othr_value, sum, '+',3);
	}
	for (unsigned int i = 0; i < 5; i++){
		if (i != 2){}
		//continue;
		printf("Printing E - %c:\n", i + 65);
		othr_value = *long_int[i];
		difference = this_value - othr_value;
		this_value.print_math_scientific(othr_value, difference, '-',3);
	}
	return 0;
};
*/