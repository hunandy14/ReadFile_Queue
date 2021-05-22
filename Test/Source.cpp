#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <string_view>
#include <charconv>
using namespace std;

class OneLine {
private:
	using _type = vector<string_view>;
public:
	OneLine() {}
	OneLine(_type oneline) {
		data = oneline;
	}
	OneLine(const string_view strv, string_view delims = " ") {
		splitSV(strv, delims);
	}
	operator _type() const {
		return data;
	}
	operator vector<string>() const {
		vector<string> str(data.size());
		for (size_t i = 0; i < data.size(); i++)
			str[i] = data[i];
		return str;
	}
	string getStringIdx(size_t idx) const {
		string s = "";
		if (idx < data.size()) {
			s = string(data[idx]);
		} else {
			throw runtime_error("range Error.");
		}
		return s;
	}
	long getIntIdx(size_t idx) const {
		return stoull(getStringIdx(idx));
	}
	size_t size() {
		return data.size();
	}
	_type splitSV(string_view strv, string_view delims = " ") {
		_type output;
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
	_type data;
	string str;
private:
	string name;
	fstream fs;
};
std::ostream& operator<<(std::ostream& out, vector<string_view>& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) {
		out << v[i];
		if (i < v.size() - 1) { cout << ", "; }
	}
	cout << "]";
	return out;
}
std::ostream& operator<<(std::ostream& out, OneLine& v) {
	return out << (vector<string_view>&)v;
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
	for (auto&& i : v2) {
		cout << i << endl;
	}
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

// ªð¦^¦r¦ê
void rf_test_getIdx() {
	string str = "123 | 321";
	OneLine line(str, " | ");

	cout << line.getStringIdx(2) << endl;
}


//====================================================================================
int main(int argc, char const* argv[]) {
	rf_test1();
	//rf_test2();
	//rf_test3();
	return 0;
}
//====================================================================================
