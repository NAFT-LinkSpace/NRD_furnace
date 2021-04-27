#if !defined(QUEUE_HEADER_FILE)
#define QUEUE_HEADER_FILE

#include <Arduino.h>
class StringQueue {
   private:
    String load;
    bool isfilted;

   public:
    void push(const String s) {
        if (isfilted) {
            load += s;
        }
    }
    void clear() {
        load = "";
        isfilted = false;
    }
    const String& read() {
        return load;
    }
    void filter(const bool b) {
        isfilted = b;
    }
    const unsigned int strlen() {
        return load.length();
    }
    void println(const String& header) {
        if (isfilted) {
            Serial.println(header + load);
        }
    }
    void println() {
        println("");
    }
};
extern StringQueue error_queue;
extern StringQueue prompt_queue;
extern StringQueue normal_queue;

#endif  // QUEUE_HEADER_FILE
