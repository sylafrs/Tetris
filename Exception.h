#ifndef EXCEPTION_H_
#define EXCEPTION_H_

    #include <string>

    class Exception {
        private:
            std::string message;

        public:
            Exception(std::string message);
            virtual ~Exception();

            const std::string & getMessage() const;

    };

    std::ostream & operator<<(std::ostream & out, const Exception & e);

#endif//EXCEPTION_H_
