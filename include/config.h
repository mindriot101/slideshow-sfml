#ifndef CONFIG_H_
#define CONFIG_H_

#include <string>

struct Config {

    struct Resolution {
        int width;
        int height;
    };

    Resolution res;

    static Config parse(const std::string &filename);
};

#endif // CONFIG_H_
