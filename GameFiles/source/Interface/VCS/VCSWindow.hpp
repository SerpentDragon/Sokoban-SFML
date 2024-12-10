#pragma once

#include <memory>
#include "GraphicsTree.hpp"
#include <SFML/Graphics.hpp>
#include "../../Widgets/Button.hpp"
#include "../../settings/settings.h"

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

    void setCommits(const std::vector<Commit>&) noexcept;

    void displayVCSWIndow() noexcept;

    void setupTree() noexcept;

private:

    std::shared_ptr<RenderWindow> window_;

    RectangleShape windowRect_;

    GraphicsTree tree_;
};
