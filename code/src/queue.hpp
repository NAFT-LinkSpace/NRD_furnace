#if !defined(QUEUE_HEADER_FILE)
#define QUEUE_HEADER_FILE

#include <Arduino.h>
class StringQueue {
   private:
    String load;
    String header_;
    bool isfilted;

   public:
    StringQueue() {
        header_ = "";
    }
    StringQueue(const String& header) {
        header_ = header;
    }
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
    void println() {
        if (isfilted && load.length() != 0) {
            Serial.println(header_ + load);
        }
    }
};
extern StringQueue error_queue;
extern StringQueue prompt_queue;
extern StringQueue normal_queue;

#endif  // QUEUE_HEADER_FILE
