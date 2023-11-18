#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <variant>
#include <cstdint>
#include <fmt/core.h>

using i64 = int64_t;
using f64 = double_t;

using value_t = std::variant<std::monostate, bool, i64, f64, std::string>;

class Arg {
    std::string short_{};
    std::string long_{};
    value_t value_{};
    value_t default_{};
    std::string description_{};
    int index_{-1};
public:
    Arg() = default;
    ~Arg() = default;
    Arg(Arg const&) = default;
    Arg(Arg&&) = default;
    Arg& operator=(Arg const&) = default;
    Arg& operator=(Arg&&) = default;

    // np. -i for ignore case
    Arg& marker(std::string v) noexcept {
        short_ = std::move(v);
        return *this;
    }
    std::string const marker() const noexcept {
        return short_;
    }
    // np. --icase for ignore case
    Arg& promarker(std::string v) noexcept {
        long_ = std::move(v);
        return *this;
    }
    std::string const& promarker() const noexcept {
        return long_;
    }
    Arg& value(value_t v) noexcept {
        value_ = std::move(v);
        return *this;
    }
    Arg& ordef(value_t v) noexcept {
        default_ = std::move(v);
        return *this;
    }
    Arg& index(int idx) noexcept {
        index_ = idx;
        return *this;
    }

    // std::variant<std::monostate, bool, i64, f64, std::string>;
    [[nodiscard]]
    std::string vstr(value_t const& v) const noexcept {
        switch (v.index()) {
            case 0: return "none";
            case 1: return (std::get<1>(v) ? "true" : "false");
            case 2: return fmt::format("{}", std::get<2>(v));
            case 3: return fmt::format("{}", std::get<3>(v));
            case 4: return fmt::format("{}", std::get<4>(v));
            default: return "?";
        }
    }
    [[nodiscard]]
    std::string as_str() const noexcept {
        return fmt::format("short: {}, long: {}, value: {}, default: {}, help: {}"
                , short_
                , long_
                , vstr(value_)
                , vstr(default_)
                , description_);
    }

    friend std::ostream& operator<<(std::ostream& s, Arg const& a) noexcept;
};

