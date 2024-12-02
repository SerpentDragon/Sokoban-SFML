#include "Localizer.hpp"

loc::generator Localizer::gen_ = loc::generator();

std::locale Localizer::locale_ = std::locale();

void Localizer::initLocalizer(const std::string& domain) noexcept
{
    gen_.clear_domains();
    gen_.add_messages_path("app_data/locale/");
    gen_.add_messages_domain(domain);

    locale_ = std::locale();
    locale_ = gen_(domain + ".UTF-8");
}

std::wstring Localizer::translate(std::wstring_view str) noexcept
{
    return loc::translate(std::wstring(str)).str(locale_);
}
