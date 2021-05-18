#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;


class OndLine {
public:
	OndLine(){}
	OndLine(vector<string_view> oneline) {
		data = oneline;
	}
	operator vector<string_view>() const {
		return data;
	}
private:
	vector<string_view> data;
};
std::ostream& operator<<(std::ostream& out, const OndLine& v) {
	for (auto&& i : (vector<string_view>)v) {out << i;}
	return out;
}

//¡@¤À³Î¦r¦ê
OndLine splitSV(string_view strv, string_view delims = " ") {
	vector<string_view> output;
	size_t first = 0;
	while (first < strv.size()) {
		const auto second = strv.find_first_of(delims, first);
		if (first != second) {
			auto&& sv = strv.substr(first, second - first);
			//cout << sv;
			output.emplace_back(sv);
		}
		if (second == string_view::npos) {break;}
		first = second + 1;
	} //cout << endl;
	return output;
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


//====================================================================================
int main(int argc, char const* argv[]) {
	auto&& v1 = ReadFile_line("in.txt");

	vector<OndLine> v2(v1.size());
	for (auto&& i : v1) {
		OndLine sv;
		sv = splitSV(string_view(i), " ");
		cout << sv << endl;
		v2.emplace_back(sv);
	}

	return 0;
}
//====================================================================================
