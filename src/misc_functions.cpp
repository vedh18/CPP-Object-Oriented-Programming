#include "misc_functions.h"

int printMenu(vector<string> menu){
    for (int i = 0; i < (int)menu.size(); i++){
        cout << i+1 << ". " << menu[i] << ::endl;
    }
    cout << "Enter your choice: ";
    int x;
    ::cin >> x;
    return x;
}

time_t convertDateString(string dateStr) {
    tm tm = {};
    istringstream ss(dateStr);
    ss >> get_time(&tm, "%d %b %Y %H:%M:%S");
    if (ss.fail()) {
        return -1;
    }
    return mktime(&tm);
}

vector<string> split(string s, char delimiter) {
    vector<string> tokens;
    istringstream iss(s);
    string token;
    while (getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

string timeToDateString(time_t t) {
    tm* tm_ptr = localtime(&t);
    ostringstream oss;
    oss << put_time(tm_ptr, "%d %b %Y %H:%M:%S");
    return oss.str();
}
