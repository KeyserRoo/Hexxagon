#ifndef HEXX_BACKGROUND_H
#define HEXX_BACKGROUND_H

class Background {
public:
    Background(const Background &) = delete;

    static Background &get();

private:
    Background();

    ~Background();

    static Background s_Instance;
};


#endif //HEXX_BACKGROUND_H
