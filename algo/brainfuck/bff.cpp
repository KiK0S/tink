#include <bits/stdc++.h>

using namespace std;

void fail(const string& message) {
	cerr << "ERROR: " << message << endl;
	exit(1);
}

string read_File(const string& fileName) {
	ifstream in(fileName.c_str());
	string s, nxt;
	while (in >> nxt) {
		s += nxt;
		if (s.length() > 5000000) {
			fail("Too long program");
		}
	}
	return s;
}

string s;

int main(int argc, char* argv[]) {
	if (argc < 2) {
		fail("Usage: bf <fileName> (<config>)\nPrints each step info if (config & 1 == 1)\nUses more detailed input if (config & 2 == 2)");
	}
	bool f = 0;
	bool input_type = 0;
	if (argc > 2) {
		f = atoi(argv[2]) & 1;
		input_type = (atoi(argv[2]) & 2) > 0;
	}

	if (argc)
	s = read_File(argv[1]);
	vector<unsigned char> data(1, 0);
	int cnt = 0;
	int curr = 0;
	int pt = 0;
	string outp = "";
	int itercnt;
	cin >> noskipws;
	while (curr < s.size()) {
		itercnt++;
		if (itercnt > 50000000) {
			fail("Too many operations");
		}
		switch (s[curr]) {
			case '<': {
				pt--;
				if (pt < 0) {
					fail("ptr less than zero");
				}
				break;
			}
			case '>': {
				pt++;
				if (pt >= (int)data.size()) {
					data.push_back(0);
				}
				break;
			}
			case '-': {
				data[pt]--;
				break;
			}
			case '+': {
				data[pt]++;
				break;
			}
			case ',': {
				if (input_type) {
					cout << "Insert your char and press enter" << endl;
					char c;
					cin >> data[pt] >> c;
					cout << "You have inserted \"" << data[pt] << "\"\n";
				}
				else {
					cin >> data[pt];
				}
				break;
			}
			case '.': {
				cout << "Printed \"" << data[pt] << "\"\n";
				outp += data[pt];
				break;
			}
			case '[': {
				if (data[pt] == 0) {
					if (f) {
						cout << "Command [ data[i] = 0\n";
					}
					int ccnt = cnt + 1;
					curr++;
					if (f) {
						cout << "Commands skiped: \"";
					}
					while (ccnt > cnt && curr < (int)s.size()) {
						if (s[curr] == '[') {
							ccnt++;
						}
						if (s[curr] == ']') {
							ccnt--;
						}
						if (ccnt == cnt) {
							break;
						}
						if (f) {
							cout << s[curr];
						}
						curr++;
					}
					if (f) {
						cout << "\"\n";
					}
					if (curr == (int)s.size()) {
						fail("Can not find closing ']'");
					}
				}
				else {
					cnt++;
				}
				break;
			}
			case ']': {
				int ccnt = cnt - 1;
				curr--;
				while (cnt > ccnt && curr >= 0) {
					if (s[curr] == '[') {
						cnt--;
					}
					if (s[curr] == ']') {
						cnt++;
					}
					curr--;
				}
				if (cnt != ccnt) {
					fail("Can not find opening '['");
				}
				if (f) {
					cout << "Command is ']', got back, ignore next outputed command\n";
				}
				break;
			}
			default: {
				break;
			}
		}
		if (f) {
			cout << "Command " << s[curr] << " pos is " << pt << " data is ";
			for (auto i : data) {
				cout << (int)i << ' ';
			}
			cout << '\n';
		}
		curr++;
	}
	cout << "Ended with data ";
	for (auto i : data) {
		cout << (int)i << ' ';
	}
	cout << '\n';
	cout << "Iterations made: " << itercnt << '\n';
	cout << "The output is \"" << outp << "\"\n";
}