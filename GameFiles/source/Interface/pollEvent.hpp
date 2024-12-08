#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Widgets/Button.hpp"
#include "../settings/settings.h"
#include "../Managers/Localizer.hpp"

using namespace sf;

bool showWarning(std::shared_ptr<RenderWindow>, const String&) noexcept;

void pollEvents(std::shared_ptr<RenderWindow>) noexcept;
