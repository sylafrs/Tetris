#include "Exception.h"
#include <string>

using namespace std;

Exception::Exception(string message) {
    this->message = message;
}

Exception::~Exception() {

}

const std::string & Exception::getMessage() {
    return this->message;
}

ostream & operator<<(ostream & out, const Exception & e) {
    out << e << endl;
    return out;
}
