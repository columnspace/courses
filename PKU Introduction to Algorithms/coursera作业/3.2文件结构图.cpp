/*
http://bailian.openjudge.cn/practice/2775/
*/
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Folder {
	vector<Folder*> subfolders;
	vector<string> files;
	string name;

public:
	Folder(string name):name(name){}
	~Folder() {
		for (int i = 0; i < subfolders.size(); i++) {
			delete subfolders[i];
		}
	}
	void input(string & line) {

		while (cin >> line) {
			if (line == "*" || line == "#" || line == "]") {
				sort(files.begin(), files.end());
				return;
			}
			if (line[0] == 'd') {
				subfolders.push_back(new Folder(line));
				subfolders.back()->input(line);
			}
			if (line[0] == 'f') {
				files.push_back(line);
			}
		}
	}

	void print(int depth = 0) {
		for (int j = 0; j < depth; j++) {
			cout << "|     ";
		}
		cout << name << endl;
		for (int i = 0; i < subfolders.size(); i++) {
			subfolders[i]->print(depth+1);
		}
		for (int i = 0; i < files.size(); i++) {
			for (int j = 0; j < depth; j++) {
				cout << "|     ";
			}
			cout << files[i] << endl;
		}
	}
};
int main() {
	int num_dataset = 0;
	while (true) {
		Folder root("ROOT");
		string line;
		root.input(line);
		if (line == "#") {
			break;
		}
		cout << "DATA SET " << ++num_dataset << ":" << endl;
		root.print();
		cout << endl;
	}
	return 0;
}