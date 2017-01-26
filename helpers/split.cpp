#include <sstream>
#include <string>

//string split methods from http://stackoverflow.com/a/236803

void split(const string &s, char delim, vector<string> &elems) {
    stringstream ss; //include sstream
    ss.str(s);
    string item;
    while (getline(ss, item, delim)) {
        elems.push_back(item);
    }
}
vector<string> split(const string &s, char delim) {
    vector<string> elems;
	split(s, delim, elems);
    return elems;
}