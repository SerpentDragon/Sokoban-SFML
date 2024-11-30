#pragma once

#include <string_view>
#include <boost/locale.hpp>

namespace loc = boost::locale;

class Localizer
{
public:

    static void initLocalizer(const std::string&);

    static std::wstring translate(std::wstring_view);

private:

    Localizer(const Localizer&) = delete;

    Localizer& operator=(const Localizer&) = delete;

private:

    static loc::generator gen_;

    static std::locale locale_;
};
