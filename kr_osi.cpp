#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <thread>
#include <atomic>
#include <algorithm>
#include <mutex>
#include <chrono>

std::mutex potok;
class MyBank {
public:
      MyBank (int sum1) {
		  sum = sum1;
	}
	int getSum() {
		//std::lock_guard<std::mutex> lock(potok);
		return sum;
	}
	void changeSum(int update) {
		std::lock_guard<std::mutex> lock(potok);
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << "Your balance was: " << getSum()<<"\n";
		sum += update;
		std::cout << "Update is: " << update << " New balance: " << getSum() << "\n";
	
	}
	bool notNegative(int update) {
		std::lock_guard<std::mutex> lock(potok);
		if (getSum() + update >= 0) {
			return true;
		}
		else {
			return false;
		}
	}
private:
	int sum;
	

};
void changes(MyBank& mybank, std::vector<int> changes) {
	std::vector<int> negativeOperations;
	for (int i = 0; i < changes.size(); i++) {
		if (mybank.notNegative(changes[i])) {
			mybank.changeSum(changes[i]);
		}
		else {
			std::cout << "This update: " << changes[i] << " is to small, we will try again\n";
			negativeOperations.push_back(changes[i]);
		}
	}
	for (int i = 0; i < negativeOperations.size(); i++) {

		if (mybank.notNegative(negativeOperations[i])) {
			mybank.changeSum(negativeOperations[i]);
		}
		else {
			std::cout << "Update: " << negativeOperations[i] << " is to small\n";
		}
	}
	
}
int main() {
		int a;
		std::cin >> a;
		MyBank balance(a);
		std::vector<int> v1 = { 120, -300, 40 };
		std::vector<int> v2 = { 100, -300, 20 };
		std::thread t1 (changes, std::ref(balance), v1);
		std::thread t2 (changes, std::ref(balance), v2);
		t1.join();
		t2.join();
		std::cout << balance.getSum();

	}