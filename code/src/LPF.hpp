#if !defined(LPF_HEADER_FILE)
#define LPF_HEADER_FILE

template <int I>
class LPF {
   private:
    double buf[I];
    uint ind;

   public:
    double filter(double);
    LPF();
};

template <int I>
double LPF<I>::filter(double d) {
    if (ind >= I) {
        ind = 0;
    }
    buf[ind] = d;
    ind++;

    double ret = 0;
    for (int i = 0; i < I; i++) {
        ret += buf[i];
    }

    return ret / I
}

#endif  // LPF_HEADER_FILE
