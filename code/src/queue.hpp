#if !defined(QUEUE_HEADER_FILE)
#define QUEUE_HEADER_FILE

#include <Arduino.h>
class StringQueue {
   private:
    String load;

   public:
    void push(const String s) {
        load += s;
    }
    void clear() {
        load = "";
    }
    const String read() {
        return load;
    }
};
extern StringQueue error_queue;
extern StringQueue prompt_queue;
extern StringQueue normal_queue;

#endif  // QUEUE_HEADER_FILE
