#pragma
#include <vector>
#include <fstream>
#include <string>
#include <string_view>
using namespace std;

class OneLine {
public:
	OneLine() {}
	OneLine(vector<string_view> oneline) {
		data = oneline;
	}
	OneLine(const string_view strv, string_view delims = " ") {
		splitSV(strv, delims);
	}
	operator vector<string_view>() const {
		return data;
	}

	vector<string_view> splitSV(string_view strv, string_view delims = " ") {
		vector<string_view> output;
		for (size_t first = 0; first < strv.size();) {
			const auto second = strv.find_first_of(delims, first);
			if (first != second)
				output.emplace_back(strv.substr(first, second - first));
			if (second == string_view::npos)
				break;
			first = second + 1;
		}
		if (output.size() == 0)
			output.emplace_back("");
		data = std::move(output);
		return data;
	}
	std::istream& getline(string_view delims = " ") {
		std::istream& is = std::getline(fs, str);
		if (is) {
			splitSV(str, delims);
		}
		return is;
	}
	void openFile(const string file_name) {
		if (name != file_name) {
			name = file_name;
			fs.close();
			fs.open(file_name, ios::in);
			if (!fs.is_open())
				throw runtime_error("Reading error.");
		}
	}

private:
	vector<string_view> data;
	string str;
private:
	string name;
	fstream fs;
};

std::ostream& operator<<(std::ostream& out, OneLine& v) {
	auto&& data = (vector<string_view>)v;
	cout << "[";
	for (size_t i = 0; i < data.size(); i++) {
		out << data[i];
		if (i < data.size() - 1) { cout << ", "; }
	}
	cout << "]";
	return out;
}
std::ostream& operator<<(std::ostream& out, vector<string_view>& v) {
	auto&& data = (vector<string_view>)v;
	cout << "[";
	for (size_t i = 0; i < data.size(); i++) {
		out << data[i];
		if (i < data.size() - 1) { cout << ", "; }
	}
	cout << "]";
	return out;
}
std::ostream& operator<<(std::ostream& out, vector<OneLine>& v) {
	for (auto&& i : v) {
		out << i << endl;
	}
	return out;
}

//=============================================================================
// ³v¦æÅª¨ú
vector<string> ReadFile_line(const string file_name) {
	vector<string> v;
	fstream fs(file_name, ios::in);
	if (!fs.is_open())
		throw runtime_error("Reading error.");

	for (string str; getline(fs, str);) {
		//cout << str << endl;
		v.emplace_back(str);
	} fs.seekg(0, fs.beg);
	fs.close();
	return v;
}

// ¤Á³ÎÀÉ®×
void rf_test1() {
	auto&& v1 = ReadFile_line("in.txt");
	vector<OneLine> v2;
	for (auto&& i : v1) {
		v2.emplace_back(OneLine(i, " "));
	}
	cout << v2 << endl;
}
// ¤Á³ÎÀÉ®× (Ãi¥[¸ü)
void rf_test2() {
	OneLine line;
	line.openFile("a.txt");
	while (line.getline()) {
		vector<string_view>&& tokenList = line;
		cout << tokenList << endl;
	}
}
// ¤Á³Î¦r¦ê
void rf_test3() {
	string str = "123 | 321";
	OneLine line(str, " | ");
	cout << line << endl;

	vector<string_view>&& tokenList = line;
	for (size_t i = 0; i < tokenList.size(); i++)
		cout << tokenList[i] << endl;
}

void rf_test() {
	rf_test1();
	rf_test2();
	rf_test3();
}