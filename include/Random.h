#ifndef RANDOM_H_
#define RANDOM_H_

    class Random {
        private:
            int min;
            int max;
        public:
            Random();
            int next(int min, int max);
            int next(int max);
            int next();
            
            void setMin(int min);
            void setMax(int max);
    };

#endif//RANDOM_H_
