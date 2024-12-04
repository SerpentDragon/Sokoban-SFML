#pragma once

#include <memory>
#include <SFML/Graphics.hpp>
#include "../Player/settings.h"
#include "../Widgets/Button.hpp"

using namespace sf;
namespace vcsw = VCSWIN;

class VCSWindow
{
public:

    VCSWindow(std::shared_ptr<RenderWindow>) noexcept;

    VCSWindow(const VCSWindow&) noexcept = default;

    VCSWindow(VCSWindow&&) noexcept = default;
    
    VCSWindow& operator=(const VCSWindow&) noexcept = default;

    VCSWindow& operator=(VCSWindow&&) noexcept = default;

    ~VCSWindow() noexcept = default;

public:

    void displayVCSWIndow() noexcept;

private:

    std::shared_ptr<RenderWindow> window_;

    RectangleShape windowRect_;

    Button closeButton_;
};
