#include "../include/Exception.h"
#include <string>

using namespace std;

Exception::Exception(const string & message) : message(message) {
}

Exception::~Exception() {

}

const string & Exception::getMessage() const {
    return this->message;
}

ostream & operator<<(ostream & out, const Exception & e) {
    out << e.getMessage();
    return out;
}

