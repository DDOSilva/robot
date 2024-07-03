#ifndef MICROSTARTER_H
#define MICROSTARTER_H

//creates integer constants 
namespace Start_state {
    enum states {
        START,              // 0
        STOP                // 1
    };
}

class Microstarter {
    public:
        Microstarter(int uPin); 

        int uPin;                        // pin that receives signal from IR module
        Start_state::states uState;      // stores received signal state
        void uUpdate();                  // read signal from pin and sends to states
};
#endif