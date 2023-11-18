#pragma once
#include "argument.h"
#include <vector>
#include <any>
#include <fmt/core.h>

class Clap final {
    std::string progname_;
    std::vector<Arg> data_{};
public:
    Clap() = default;
    template<typename... T>
    explicit Clap(std::string progname, T... args) : progname_{std::move(progname)}{
        (..., data_.push_back(args));
    }

    Clap& add(Arg arg) noexcept {
        data_.push_back(std::move(arg));
        return *this;
    }

    int parse(int argn, char const* const argv[]) noexcept;

private:
    void add(std::string key, std::string value) noexcept;

    friend std::ostream& operator<<(std::ostream& s, Clap const& c) noexcept;
};
