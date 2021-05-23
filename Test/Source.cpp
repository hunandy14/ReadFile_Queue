#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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
	OneLine(const _type strv, _type delims) {
		split(strv, delims);
	}
	operator _typev() const {
		return _data;
	}
	operator string() {
		return str;
	}
	const _type& operator[](size_t idx) const {
		return _data[idx];
	}
	size_t size() {
		return _data.size();
	}
public:
	const _typev& split(_type strv, _type delims = " ") {
		_typev output;
		for (size_t first = 0; first < strv.size();) {
			const auto second = strv.find_first_of(delims, first);
			if (first != second)
				output.emplace_back(strv.substr(first, second - first));
			if (second == _type::npos)
				break;
			first = second + 1;
		}
		if (output.size() == 0)
			output.emplace_back("");
		_data = std::move(output);
		return _data;
	}
	bool readNextLine(_type delims = " ") {
		bool notend=0;
		if (fs.is_open()) 	{
			std::istream& is = std::getline(fs, str);
			if (is) {
				split(str, delims);
				notend=1;
			}
		} else {
			std::istream& is = std::getline(std::cin, str);
			if (is) {
				split(str, delims);
				notend=1;
			}
		}

		return notend;
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
	void closeFile() {
		fs.close();
	}
private:
	_typev _data;
	string str;
private:
	string name;
	fstream fs;
};
std::ostream& operator<<(std::ostream& out, OneLine& v) {
	cout << "[";
	for (size_t i = 0; i < v.size(); i++) {
		out << v[i];
		if (i < v.size() - 1) { cout << ", "; }
	}
	cout << "]";
	return out;
}

//=============================================================================
// ±qÀÉ®×¸ü¤J¨Ã¤Á³Î
void OneLine_test1() {
	cout << "=====================±qÀÉ®×¸ü¤J¨Ã¤Á³Î=====================" << endl;
	OneLine line;
	line.openFile("data_test.txt");
	while (line.readNextLine(" ")) {
		cout << line << endl;
	}
	line.closeFile();
}
// ¤Á³Î¦r¦ê
void OneLine_test2() {
	cout << "=====================±q¿é¤J¸ü¤J¨Ã¤Á³Î=====================" << endl;
	OneLine line;
	line.readNextLine(" ");
	cout << line << endl;
}
// ¤Á³Î¦r¦ê
void OneLine_test3() {
	cout << "=====================¡@¡@¤Á³Î¦r¦ê¡@¡@=====================" << endl;
	string str = "123 | 321";
	OneLine line(str, " | ");
	cout << line << endl;
	for (size_t i = 0; i < line.size(); i++)
		cout << "line[" << i << "] = " << line[i] << endl;
}
//====================================================================================
int main(int argc, char const* argv[]) {
	OneLine_test1();
	OneLine_test2();
	OneLine_test3();
	return 0;
}
//====================================================================================
