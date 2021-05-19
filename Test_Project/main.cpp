#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string_view>
using namespace std;


class OndLine {
public:
	OndLine(){}
	OndLine(vector<string_view> oneline) {
		datav = oneline;
	}
	OndLine(const string_view strv, string_view delims = " ") {
		splitSV(strv, delims);
	}


	operator vector<string_view>() const {
		return datav;
	}


	vector<string_view> splitSV(string_view strv, string_view delims = " ") {
		vector<string_view> output;
		size_t first = 0;
		while (first < strv.size()) {
			const auto second = strv.find_first_of(delims, first);
			if (first != second) {
				output.emplace_back(strv.substr(first, second - first));
			} if (second == string_view::npos) {
				break;
			} first = second + 1;
		}
		datav = std::move(output);
		return datav;
	}
	void readFile_line(const string file_name) {
		vector<string> v;
		fstream fs(file_name, ios::in);
		if (!fs.is_open())
			throw runtime_error("Reading error.");
		for (string str; getline(fs, str);){
			//cout << str << endl;
			v.emplace_back(str);
		} fs.seekg(0, fs.beg);
		fs.close();
		data = std::move(v);
	}

private:
	vector<string_view> datav;
	vector<string> data;
};

std::ostream& operator<<(std::ostream& out, OndLine& v) {
	vector<string_view> data = v;
	cout << "[";
	for (size_t i = 0; i < data.size(); i++) {
		out << data[i];
		if (i < data.size()-1) { cout << ", ";}
	}
	cout << "]";
	return out;
}


// ³v¦æÅª¨ú
vector<string> ReadFile_line(const string file_name) {
	vector<string> v;
	fstream fs(file_name, ios::in);
	if (!fs.is_open())
		throw runtime_error("Reading error.");

	for (string str; getline(fs, str);){
		//cout << str << endl;
		v.emplace_back(str);
	} fs.seekg(0, fs.beg);
	fs.close();
	return v;
}

void test1() {
	auto&& v1 = ReadFile_line("in.txt");

	vector<OndLine> v2;
	for (auto&& i : v1) {
		v2.emplace_back(OndLine(i, " "));
	}

	for (auto&& i : v2) {
		cout << i << endl;
	}
}

//====================================================================================
int main(int argc, char const* argv[]) {
	test1();
	return 0;
}
//====================================================================================
