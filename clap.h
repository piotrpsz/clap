// MIT License
//
// Copyright (c) 2023 Piotr Pszczółkowski
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
#pragma once
#include "argument.h"
#include <optional>
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
    std::optional<Arg> operator[](std::string const&) const noexcept;
<<<<<<< HEAD

=======
>>>>>>> tmp_x
private:
    void add(std::string key, std::string value) noexcept;

    friend std::ostream& operator<<(std::ostream& s, Clap const& c) noexcept;
};
