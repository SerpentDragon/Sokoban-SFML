#pragma once 

#include <string>
#include <memory>
#include "pollEvent.hpp"
#include <unordered_map>
#include <SFML/Audio.hpp>
#include "../Player/map.h"
#include <SFML/Graphics.hpp>
#include "VCS/VCSWindow.hpp"
#include "../Player/settings.h"
#include "../Player/Player.hpp"
#include "../Widgets/Button.hpp"
#include "../Managers/Localizer.hpp"
#include "../Managers/SoundManager.hpp"
#include "../Managers/TextureManager.hpp"
#include "../VersionControl/VersionControlSystem.hpp"

using namespace sf;

class Drawing
{
public:

    Drawing(std::shared_ptr<RenderWindow>) noexcept;

    Drawing(const Drawing&) = delete;
    
    Drawing(Drawing&&) noexcept = delete;

    Drawing& operator=(const Drawing&) = delete;

    Drawing& operator=(Drawing&&) noexcept = delete;

    ~Drawing() noexcept = default;

    void setLevel(const int) noexcept;

    int getLevel() const noexcept;

    bool drawWorld() noexcept;

    void setCoins(int) noexcept;

    const int getCoins() const noexcept;

private:

    void loadTextures() noexcept;

    void createButtons() noexcept;

    void updateLevelText(int) noexcept;

    void updateCoinsText() noexcept;

    void updateBackground(int) noexcept;

    void drawMap(size_t, size_t, 
        const std::vector<std::vector<int>>&, int, int) noexcept;

    void displayVCSWindow() noexcept;

private:

    std::shared_ptr<RenderWindow> window_;

    std::unordered_map<std::string_view, RectangleShape> world_;

    Button backButton_;
    Button restartButton_;
    Button levelsButton_;

    // version control system
    Button saveButton_;
    Button showCommitTreeButton_;

    unsigned int level_;

    Text levelText_;
    Text coinsText_;

    RectangleShape background_;

    int coins_; // coins amount you have 
    const int price_ = 10;  // coins amount you need to cancel your move

    Player player_;
};
