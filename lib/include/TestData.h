//
// Created by elvircrn on 12/24/2017.
//

#ifndef BOMPILER_TEST_DATA_H
#define BOMPILER_TEST_DATA_H

#include <string>
#include <tuple>

const std::string test1Code = R"(
/* First things first... */

main() {
	printf("Hello world!*n");
}
)";


const std::string test2Code = R"(

eql(a, b) a == b;
neq(a, b) a != b;
_lt(a, b) a < b;
leq(a, b) a <= b;
_gt(a, b) a > b;
geq(a, b) a >= b;

test(a, b, c, d, e, f) {
	printf("%d, %d, %d*n", eql(a, b), eql(c, d), eql(e, f));
	printf("%d, %d, %d*n", neq(a, b), neq(c, d), neq(e, f));
	printf("%d, %d, %d*n", _lt(a, b), _lt(c, d), _lt(e, f));
	printf("%d, %d, %d*n", leq(a, b), leq(c, d), leq(e, f));
	printf("%d, %d, %d*n", _gt(a, b), _gt(c, d), _gt(e, f));
	printf("%d, %d, %d*n", geq(a, b), geq(c, d), geq(e, f));
}

main() {
	test(5, 10, 10, 5, 6, 6);
}

)";


const std::string &test3Code = R"(

v[20];
n 10;
q n;

main() {
	extrn v, q, n;

	v[0] = 12;
	*q = 13;
	printf("%d*n", v[0]);
	printf("%d*n", n);
	printf("%d*n", *q);
	printf("%d*n", v);
	v = 17;
	printf("%d*n", v);

	v = &n; *v = 47;
	printf("%d*n", n);
}

)";


const std::string &test4Code = R"(

main() {
	extrn printf;
	auto f; f = &printf;
	f("pointer call*n");
}

)";

const std::string &printfTestCode = R"(
main() {
	printf("Hello world!*n");
}
)";


std::tuple<const unsigned char*, int> test1Params = std::make_tuple<const unsigned char*, int>((const unsigned char*)(test1Code.c_str()), (int)strlen(test1Code.c_str()));
std::tuple<const unsigned char*, int> test2Params = std::make_tuple<const unsigned char*, int>((const unsigned char*)(test2Code.c_str()), (int)strlen(test2Code.c_str()));
std::tuple<const unsigned char*, int> test3Params = std::make_tuple<const unsigned char*, int>((const unsigned char*)(test3Code.c_str()), (int)strlen(test3Code.c_str()));
std::tuple<const unsigned char*, int> test4Params = std::make_tuple<const unsigned char*, int>((const unsigned char*)(test4Code.c_str()), (int)strlen(test4Code.c_str()));
std::tuple<const unsigned char*, int> printfTestParams = std::make_tuple<const unsigned char*, int>((const unsigned char*)(printfTestCode.c_str()), (int)strlen(printfTestCode.c_str()));


#endif //BOMPILER_TEST_DATA_H
