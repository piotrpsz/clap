#include "clap.h"
#include <numeric>
#include <iostream>
#include <sstream>
#include <fmt/core.h>

/// Sprawdzenie czy przysłany znak nie(!) jest białym znakiem.
/// \param c - znak do sprawdzenia
/// \return True jeśli NIE jest białym znakiem, False w przeciwnym przypadku.
bool
is_not_space(char c) noexcept {
    return !std::isspace(c);
}

/// Obcięcie wiodących (z początku) białych znaków.
/// \param s - string z którego należy usunąć białe znaki
/// \return string bez wiodących białych znaków.
std::string
trim_left(std::string s) noexcept {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), is_not_space));
    return s;
}

/// Usunięcie zamykającyh (końcowych) białych znaków (z prawej strony).
/// \param s - string z którego należy usunąć białe znaki
/// \return string bez zamykających białych znaków.
std::string
trim_right(std::string s) noexcept {
    s.erase(std::find_if(s.rbegin(), s.rend(), is_not_space).base(), s.end());
    return s;
}

/// Usunięcie wiodących i zamykających białych znaków (z obu stron).
/// \param s - string z którego należy usunąć białe znaki
/// \return string bez wiodących i zamykających białych znaków.
std::string
trim(std::string s) noexcept {
    return trim_left(trim_right(std::move(s)));
}


/// Podział przysłanego stringa na wektor stringów. \n
/// Wyodrębnianie stringów składowych odbywa się po napotkaniu delimiter'a.
/// \param text - string do podziału,
/// \param delimiter - znak sygnalizujący podział,
/// \return Wektor stringów.
std::vector<std::string>
split(std::string const &text, char const delimiter) noexcept {
    // Lepiej policzyć delimitery niż później realokować wektor.
    auto const n = std::accumulate(
            text.cbegin(),
            text.cend(),
            ssize_t {0},
            [delimiter](ssize_t const count, char const c) {
                return (c == delimiter) ? count + 1 : count;
            }
    );

    std::vector<std::string> tokens{};
    tokens.reserve(n + 1);

    std::string token;
    std::istringstream stream(text);
    while (std::getline(stream, token, delimiter))
        if (auto str = trim(token); !str.empty())
            tokens.push_back(str);
    return tokens;
}

/// Przypisanie wartości argumentu na podstawie klucza.
/// \param key - klucz argumentu,
/// \param value - wartość argumentu
/// \remark Dopuszczalny jest brak wartości (wstawiany True - jako znak że jest). \n
///         Dopuszczalny jest klucz jako zestaw (po jednym myślniku).
void Clap::add(std::string key, std::string value) noexcept {
    auto is_long = key[0] == '-' && key[1] == '-';

    // Szukamy pełnego dopasowania.
    for (auto& arg: data_)
        if ((is_long && arg.promarker() == key) || (!is_long && arg.marker() == key)) {
            if (value.empty()) arg.value(true);
            else arg.value(value);
            return;
        }

    // Nie ma dokładnego dopasowania.
    // Może być, że mamy zestaw np. -ifr (jeśli nie ma wartości).
    // W zestawie każda literka to marker jakiegos argumentu.
    if (!is_long && value.empty()) {
        auto const subkey{key.substr(1)};
        for (auto const c : subkey) {
            auto ok{false};
            for (auto& arg: data_) {
                if (arg.marker().substr(1)[0] == c) {
                    arg.value(ok = true);
                    break;
                }
            }
            // Nie dopasowano tej literki.
            if (!ok)
                fmt::print(stderr, "unknown parameter: -{} (in {})\n", c, key);
        }
        return;
    }

    // Nie jest to zestaw lub jest wartość (nie dopuszczalna dla zestawu).
    fmt::print(stderr, "unknown parameter: {}\n", key);
}

int Clap::parse(int const argn, char const *const argv[]) noexcept {
    std::string key{}, value{};

    for (int i = 1; i < argn; i++) {
        auto const str{argv[i]};
        auto const is_key = str[0] == '-';
        if (!key.empty()) {
            if (!is_key)
                // Jeśli aktualny argument nie jest kluczem
                // to jest wartością dla zapamiętanego klucza.
                value = str;

            add(std::move(key), std::move(value));
            key.clear();
            value.clear();

            if (!is_key)
                // zużyliśmy aktualny argument jako wartość
                // więc nie ma już nic do roboty i przechodzimy
                // do następnego argumentu
                continue;
        }

        auto items = split(str, '=');
        switch (items.size()) {
            case 1:
                key = items[0];
                break;
            case 2:
                key = items[0];
                value = items[1];
                break;
            default:
                fmt::print(stderr, "invalid parameter: {}\n", str);
        }
    }

    if (!key.empty())
        add(std::move(key), std::move(value));
    return 0;
}

std::optional<Arg> Clap::
operator[](std::string const& name) const noexcept {
    for (auto const& arg: data_)
        if (arg.marker() == name || arg.promarker() == name)
            return arg;

    return {};
}

std::ostream& operator<<(std::ostream& s, Clap const& c) noexcept {
    fmt::print("{}\n", c.progname_);
    for (auto const& arg: c.data_)
        fmt::print("\t{}\n", arg.as_str());
    return s;
}
