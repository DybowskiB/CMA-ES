class MyRandomEngine {
public:
    int _seed = 5;

    // Metoda seed
    void seed(int s) {
        _seed = s;
    }

    // Operator ()
    double operator()() {
        return static_cast<double>(1);
    }

    // Metoda discard
    void discard(int n) {
        return;
    }

    // Statyczne pola min i max
    static constexpr double min() {
        return static_cast<double>(0);
    }

    static constexpr double max() {
        return static_cast<double>(5);
    }
};