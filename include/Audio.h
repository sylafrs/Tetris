#ifndef AUDIO_H_
#define AUDIO_H_

    #include "Exception.h"

    class Audio {
        public:
            Audio() throw(Exception);
            virtual ~Audio();
    
    };

#endif//AUDIO_H_
