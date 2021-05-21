#pragma
#include <vector>
#include <fstream>
#include <string>
//#include <string_view>
#include <charconv>
using namespace std;

class OneLine {
public:
	using _type = string;
	using _typev = vector<_type>;
public:
	OneLine() {}
	OneLine(_typev oneline) {
		_data = oneline;
	}
	OneLine(const _type strv, _type delims = " ") {
		split(strv, delims);
	}
	operator _typev() const {
		return _data;
	}
	/*operator vector<string>() const {
		vector<string> str(_data.size());
		for (size_t i = 0; i < _data.size(); i++)
			str[i] = _data[i];
		return str;
	}*/
	operator vector<int>() const {
		vector<int> v(_data.size());
		for (size_t i = 1; i < _data.size(); i++) {
			auto&& sv = _data[i];
			int result = -1;
			if (auto [p, ec] = std::from_chars(std::data(sv),
				std::data(sv) + std::size(sv), result); ec == std::errc()) {
				v[i] = result;
				// std::cout << result << "\n" "p -> \"" << p << "\"\n";
			} else {
				v[i] = -1;
				// throw runtime_error("data is not int.");
			}
		}
		return v;
	}
	const _type& operator[](size_t idx) const {
		return _data[idx];
	}

	string& getCurrLine() {
		return str;
	}
	string getStringIdx(size_t idx) const {
		string s = "";
		if (idx < _data.size()) {
			s = string(_data[idx]);
		} else {
			throw runtime_error("range Error.");
		}
		return s;
	}
	long long getIntIdx(size_t idx) const {
		return stoll(getStringIdx(idx));
	}

	size_t size() {
		return _data.size();
	}
	vector<string_view>
	split(string_view strv, string_view delims = " ") {
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
		return output;
	}
	vector<string>
	split(const string& str, const string& delims = " "){
		vector<string> tokens;
		string::size_type lastPos = str.find_first_not_of(delims, 0);
		string::size_type pos = str.find_first_of(delims, lastPos);
		while (string::npos != pos || string::npos != lastPos) {
			tokens.push_back(str.substr(lastPos, pos - lastPos));//use emplace_back after C++11
			lastPos = str.find_first_not_of(delims, pos);
			pos = str.find_first_of(delims, lastPos);
		}
		return tokens;
	}
	std::istream& readNextLine(_type delims = " ") {
		std::istream& is = std::getline(fs, str);
		if (is) {
			_data = split(str, delims);
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
	_typev _data;
	string str;
private:
	string name;
	fstream fs;
};
std::ostream& operator<<(std::ostream& out, OneLine::_typev& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) {
		out << v[i];
		if (i < v.size() - 1) { cout << ", "; }
	}
	cout << "]";
	return out;
}
std::ostream& operator<<(std::ostream& out, OneLine& v) {
	return out << (OneLine::_typev&)v;
}

//=============================================================================
// 逐行讀取
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

// 切割檔案
void rf_test1() {
	auto&& v1 = ReadFile_line("data_test.txt");
	vector<OneLine> v2;
	for (auto&& i : v1) {
		v2.emplace_back(OneLine(i, " "));
	}
	for (auto&& i : v2) {
		cout << i << endl;
	}
}
// 切割檔案 (懶加載)
void rf_test2() {
	OneLine line;
	line.openFile("data_test.txt");
	while (line.readNextLine()) {
		OneLine::_typev&& tokenList = line;
		cout << tokenList << endl;
	}
}
// 切割字串
void rf_test3() {
	string str = "123 | 321";
	OneLine line(str, " | ");
	cout << line << endl;

	OneLine::_typev&& tokenList = line;
	for (size_t i = 0; i < tokenList.size(); i++)
		cout << tokenList[i] << endl;
}

// 返回字串
void rf_test_getIdx() {
	string str = "123 | 321";
	OneLine line(str, " | ");

	cout << line.getStringIdx(2) << endl;
}

void rf_test() {
	rf_test1();
	rf_test2();
	rf_test3();
}

