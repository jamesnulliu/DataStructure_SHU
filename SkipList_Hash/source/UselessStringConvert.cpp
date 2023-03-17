#include <string>
long threeToLong(std::string s) {
	long answer = s.at(0);
	answer = (answer << 8) + s.at(1);
	return (answer << 8) + s.at(2);
}
std::string longToThree(long h) {
	std::string answer;
	long h1 = h >> 8 >> 8;
	long h2 = (h1 << 8 << 8) ^ h >> 8;
	long h3 = h << 8 << 8 << 8 >> 8 >> 8 >> 8;
	answer.push_back(h1);
	answer.push_back(h2);
	answer.push_back(h3);
	return answer;
}