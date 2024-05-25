#ifndef MICROSTARTER_H
#define MICROSTARTER_H

namespace Start_state {
    enum states {
        START,
        STOP
    };
}

class Microstarter {
    public:
        Microstarter(int uPin);
        int uPin;
        Start_state::states uState;
        void uUpdate();
}
#endif