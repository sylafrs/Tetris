#ifndef AUDIO_H_
#define AUDIO_H_

    #include "Exception.h"

    class Audio {
        private:
            unsigned int cChannels;

        public:
            Audio() throw(Exception);
            virtual ~Audio();

            unsigned int createChannel() throw(Exception);
            void haltSounds();

    };

#endif//AUDIO_H_
