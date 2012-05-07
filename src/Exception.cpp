#include "../include/Exception.h"
#include <string>

using namespace std;

Exception::Exception(string message) {
    this->message = message;
}

Exception::~Exception() {

}

const string & Exception::getMessage() const {
    return this->message;
}

ostream & operator<<(ostream & out, const Exception & e) {
    out << e;
    return out;
}
