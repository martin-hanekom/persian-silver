#include <algorithm>
#include <functional>
#include "game.hpp"
#include "asset.hpp"

namespace silver
{

Game::Game(): screen(Screen::get()), board(tileDepth) 
{
    players.reserve(Player::maxPlayers);
}

Game::~Game()
{
}

Game& Game::get()
{
    static Game game;
    return game;
}

void Game::run(size_t playerCount)
{
    restart(playerCount);
    auto& window = screen.getWindow();

    while (window.isOpen())
    {
        window.handleEvents(
            [this](sf::Event::Closed const&) { onClosed(); },
            [this](sf::Event::KeyPressed const& keyPressed) { onKeyPressed(keyPressed); },
            [this](sf::Event::MouseButtonPressed const& mouseButton) { onMouseButtonPressed(mouseButton); },
            [this](sf::Event::MouseMoved const& mouseMove) { onMouseMoved(mouseMove); },
            [this](sf::Event::MouseWheelScrolled const& mouseScroll) { onMouseWheelScrolled(mouseScroll); }
        );

        window.clear();
        drawMain();
        drawUI();
        screen.setMainView();
        window.display();
    }
}

void Game::restart(size_t playerCount)
{
    assert(playerCount >= Player::minPlayers && playerCount <= Player::maxPlayers);
    players.clear();
    for (size_t i = 0; i < playerCount; ++i)
    {
        auto startIndex = Player::maxPlayers / playerCount * i;
        players.emplace_back("Player " + std::to_string(i + 1), i, board.getStartPos(startIndex));
    }

    info.setPlayer(players[currentPlayer]);
}

void Game::drawMain() const
{
    screen.setMainView();
    board.draw();
    std::for_each(players.cbegin(), players.cend(), std::bind(&Player::draw, std::placeholders::_1));
}

void Game::drawUI() const
{
    screen.setUIView();
    info.draw();
}

void Game::onClosed()
{
    Screen::getWindow().close();
}

void Game::onKeyPressed(sf::Event::KeyPressed const& keyPressed)
{
    switch (keyPressed.scancode)
    {
        case sf::Keyboard::Scancode::Escape:
            onClosed();
            break;
        default:
            break;
    }
}

void Game::onMouseMoved(sf::Event::MouseMoved const& mouseMove)
{
    auto& screen = Screen::get();
    auto mouseMainPosition = screen.mainViewCoords(mouseMove.position);
    auto mouseUIPosition = screen.uiViewCoords(mouseMove.position);

    if (mouseDragging && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {
        screen.pan(mouseClickPosition - mouseMainPosition);
    }
    else
    {
        mouseDragging = false;
        info.onMouseMoved(mouseUIPosition) || board.onMouseMoved(mouseMainPosition);
    }
}

void Game::onMouseButtonPressed(sf::Event::MouseButtonPressed const& mouseButton)
{
    auto& screen = Screen::get();
    mouseClickPosition = screen.mainViewCoords(mouseButton.position);
    mouseDragging = true;

    switch (mouseButton.button)
    {
        case sf::Mouse::Button::Left:
            info.onLeftClick() || board.onLeftClick();
            break;
        case sf::Mouse::Button::Right:
            board.onRightClick();
            break;
        default:
            break;
    }
}

void Game::onMouseWheelScrolled(sf::Event::MouseWheelScrolled const& mouseScroll)
{
    auto& window = Screen::getWindow();
    if (mouseScroll.wheel == sf::Mouse::Wheel::Vertical)
    {
        Screen::get().zoom(1.f - mouseScroll.delta * 0.1f);
    }
}

void Game::submit(BoardSelectAction&& action)
{
    auto& game = Game::get();
    game.info.setPiece(action.valid(game.getPlayer()) ? action.getPiece() : nullptr);
}

void Game::submit(MenuSelectAction&& action)
{
    auto& game = Game::get();
    if (action.valid(game.getPlayer()))
    {
        auto const buildTile = game.board.selected;
        auto const builder = buildTile->getPiece();
        switch (builder->getBuildType())
        {
            case BuildType::Consume:
                Game::submit(ConsumeBuildAction(buildTile, action.tile));
                break;
            case BuildType::Expand:
                game.board.menuSelected = action.tile;
                break;
            default:
                break;
        }
    }
    else
    {
        if (nullptr != game.board.menuSelected)
        {
            game.board.menuSelected->offSelect();
            game.board.menuSelected = nullptr;
        }
    }
}

void Game::submit(MoveAction&& action)
{
    auto& game = Game::get();
    if (action.valid(game.getPlayer()))
    {
        action.getPiece()->move(action.to);
    }
    game.info.setPiece(nullptr);
}

void Game::submit(ExpandBuildAction&& action)
{
    auto& game = Game::get();
    auto& player = game.getPlayer();
    if (action.valid(player))
    {
        player.expand(action.getPieceType(), action.getPiece(), action.location);
        game.info.setPlayer(player);
    }
    game.info.setPiece(nullptr);
}

void Game::submit(ConsumeBuildAction&& action)
{
    auto& game = Game::get();
    auto& player = game.getPlayer();
    if (action.valid(player))
    {
        player.consume(action.getPieceType(), action.getPiece());
        game.info.setPlayer(player);
    }
    game.info.setPiece(nullptr);
}

bool Game::isCurrentPlayerPiece(Piece const* const piece) const
{
    return nullptr != piece && piece->isPlayer(players[currentPlayer]);
}

void Game::nextPlayerCallback()
{
    Game::get().nextPlayer();
}

void Game::nextPlayer()
{
    auto& oldPlayer = players[currentPlayer];
    oldPlayer.reset();

    currentPlayer = (currentPlayer + 1) % players.size();
    info.setPlayer(players[currentPlayer]);
    info.setPiece(nullptr);
}

Player const& Game::getPlayer() const
{
    return players[currentPlayer];
}

Player& Game::getPlayer()
{
    return players[currentPlayer];
}

}