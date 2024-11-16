#include <iostream>
#include <vector>
#include <string>
#include <random>

#include "rclcpp/rclcpp.hpp"

class secretholder{
	public:
	unsigned secret;

	secretholder(){
		std::random_device rd;
		secret = rd();
		std::cout << "[secretholder]" << "generated Secret: " << secret << std::endl;
	}

	void task(){
		using packet_t = struct{
			std::string name;
			unsigned secret;
		};

		packet_t * p = new packet_t;
		p->name = "secretholder";
		p->secret = secret;

		/* assume some task is performed */
		std::cout << "[secretholder]" << "task happed on pointer " << p << std::endl;

		delete p;
	}
};

/*
	database
	allocate data of fixed size
	read data 
	store data
*/
class database{
	public:
	std::vector<unsigned *> arrs;

	database(){
	}
	~database(){
		for(auto arr : arrs)
			delete[] arr;
	}

	void alloc(int sz){
		arrs.push_back(new unsigned[sz]);
	}

	void free(int index){
		arrs.erase(arrs.begin() + index);
	}
	
	unsigned read(int k, int i){
		return arrs[k][i];
	}

	void write(int k, int i, unsigned x){
		arrs[k][i] = x;
	}
};

using namespace std;

int main(){
	std::cout << "Server Up" << std::endl;

	secretholder SS;
	database DB;

	while(true){
		SS.task();

		cout << "Command 1: alloc" << endl;
		cout << "Command 2: free" << endl;
		cout << "Command 3: read" << endl;
		cout << "Command 4: write" << endl;
		cout << "Command 5: exit" << endl;

		cout << "Command: ";
		int cmd;
		cin >> cmd;

		switch(cmd){
			case 1: {
				cout << "input alloc size: ";
				int size;
				cin >> size;

				DB.alloc(size);
				cout << "allocated at index " << DB.arrs.size() - 1 << " : " << DB.arrs.back() << endl;
			} break;
			case 2: {
				cout << "input free index: ";
				int index;
				cin >> index;

				DB.free(index);
			} break;
			case 3: {
				cout << "input directory (k, i): ";
				int k, i;
				cin >> k >> i;

				cout << "value: " << DB.read(k, i) << endl;
			} break;
			case 4: {
				cout << "input directory (k, i): ";
				int k, i;
				cin >> k >> i;

				cout << "input value: ";
				unsigned x;
				cin >> x;

				DB.write(k, i, x);
			} break;
			case 5: { return 0; } break;
			default: break;
		}

	}
}
