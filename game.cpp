#include "game.hpp"
#include "enemy.hpp"
#include "entity.hpp"
#include "gun.hpp"
#include "player.hpp"
#include "projectile.hpp"
#include "score.hpp"
#include "ui.hpp"
#include "utils.hpp"
#include <iostream>
#include <sstream>

Game::Game(int size_x, int size_y)
    : window{new sf::RenderWindow(sf::VideoMode(size_x, size_y), "Game",
                                  sf::Style::Titlebar | sf::Style::Close)},
      entity_list{}, new_entities{}, player{}, player_texture{load_texture(
                                                   "assets/player.png")},
      enemy_texture{load_texture("assets/enemy.png")},
      bullet_texture{load_texture("assets/bullet.png")},
      font{load_font("assets/font.ttf")}, world_size{sf::Vector2f(size_x,
                                                                  size_y)},
      debug{false}, entity_id_counter{0}, score{0}, kills{0},
      scores{Score::load()}, state{GameState::Menu} {
    window->setVerticalSyncEnabled(true);

    auto start_button = new Button(this, "START", Alignment::Center);
    start_button->teleport(sf::Vector2f(size_x / 2.0f, size_y / 2.0f));
    spawn(start_button);

    show_scores();
}

Game::~Game() {
    remove_entities();
    delete window;
    delete player_texture;
    delete enemy_texture;
    delete bullet_texture;
}

void Game::remove_entities() {
    for (auto entity : entity_list)
        delete entity;
    for (auto entity : new_entities)
        delete entity;
    entity_list.clear();
    new_entities.clear();
}

void Game::spawn(Entity *entity) { new_entities.push_back(entity); }

void Game::run() {
    sf::Clock last_frame;
    while (window->isOpen()) {
        float delta_time = last_frame.getElapsedTime().asSeconds();
        last_frame.restart();

        if (state == GameState::Running) {
            if (enemies_left == 0)
                spawn_enemies();
        }

        entity_list.insert(entity_list.end(), new_entities.begin(),
                           new_entities.end());
        new_entities.clear();

        sf::Event event;
        while (window->pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window->close();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::F1)
                    debug = !debug;
            }
        }

        for (auto entity = entity_list.begin(); entity != entity_list.end();) {
            if ((*entity)->is_dead()) {
                if (*entity == player) {
                    game_over();
                    delete *entity;
                    entity = entity_list.erase(entity);
                    if (auto counter = dynamic_cast<DataText<int> *>(
                            get_entity(health_counter_id)))
                        counter->set_data(nullptr);
                    break;
                }
                delete *entity;
                entity = entity_list.erase(entity);
            } else {
                if (auto button = dynamic_cast<Button *>(*entity)) {
                    if (button->clicked()) {
                        auto label = button->get_label();
                        if (label == "START" || label == "RETRY") {
                            start();
                            break;
                        }
                    }
                }
                (*entity)->update(delta_time);
                ++entity;
            }
        }

        window->clear(sf::Color(50, 100, 50));

        for (auto entity : entity_list)
            window->draw(*entity);

        window->display();
    }
}

sf::Texture *Game::get_player_texture() const { return player_texture; }
sf::Texture *Game::get_enemy_texture() const { return enemy_texture; }
sf::Texture *Game::get_bullet_texture() const { return bullet_texture; }
sf::Font *Game::get_font() const { return font; }

const sf::RenderWindow *Game::get_window() const { return window; }

sf::Vector2f Game::get_world_size() const { return world_size; }
bool Game::get_debug_mode() const { return debug; }

unsigned Game::new_entity_id() { return ++entity_id_counter; }
unsigned Game::collision_check(sf::FloatRect collider, unsigned id,
                               int layer) const {
    for (auto entity : entity_list) {
        if ((entity->get_collision_layer() &
             (CollisionLayer::BulletLayer | CollisionLayer::UILayer)))
            continue;
        if (entity->get_id() == id ||
            (entity->get_collision_layer() & layer) == 0)
            continue;
        if (collider.intersects(entity->get_bounding_box()))
            return entity->get_id();
    }
    return 0;
}

Entity *Game::get_entity(unsigned id) const {
    for (auto entity : entity_list)
        if (entity->get_id() == id)
            return entity;

    return nullptr;
}

Player *Game::get_player() const { return player; }

void Game::add_score(unsigned amount) { score += amount; }
void Game::add_kill() {
    kills++;
    enemies_left--;
    if (kills != 0 && kills % 12 == 0)
        player->set_health(100);
    if (kills == 24) {
        auto smg = Gun::SMG(this);
        spawn(smg);
        player->pickup_item(smg);
    }
}

void Game::start() {
    remove_entities();
    score = 0;
    kills = 0;
    enemies_left = 0;

    player = new Player(this);
    player->teleport(sf::Vector2f(480.0f, 480.0f));
    player->rotate(sf::Vector2f(0.0f, 1.0f));
    spawn(player);

    auto pistol = Gun::Pistol(this);
    spawn(pistol);
    player->pickup_item(pistol);

    auto health_counter = new DataText<int>(this, "HEALTH: ", &player->health);
    health_counter->teleport(sf::Vector2f(10.0f, 2.0f));
    spawn(health_counter);
    health_counter_id = health_counter->get_id();

    auto score_counter = new DataText<unsigned>(this, "SCORE: ", &score);
    score_counter->teleport(sf::Vector2f(10.0f, 35.0f));
    spawn(score_counter);

    auto kill_counter = new DataText<int>(this, "KILLS: ", &kills);
    kill_counter->teleport(sf::Vector2f(10.0f, 68.0f));
    spawn(kill_counter);

    state = GameState::Running;
}

void Game::game_over() {
    state = GameState::GameOver;
    Score new_score(score);
    new_score.save();
    scores = Score::load();

    auto retry_button = new Button(this, "RETRY", Alignment::Center);
    retry_button->teleport(
        sf::Vector2f(world_size.x / 2.0f, world_size.y / 2.0f));
    spawn(retry_button);

    show_scores();
}

GameState Game::get_state() const { return state; }

void Game::show_scores() {
    if (scores.empty())
        return;

    auto score_text = new Text(this, "HIGHSCORES:", Alignment::Center);
    score_text->teleport(sf::Vector2f(world_size.x / 2.0f, 15.0f));
    spawn(score_text);

    int i = 1;
    for (auto score : scores) {
        if (i > 10)
            break;
        std::stringstream ss;
        ss << i << ". " << score;
        auto score_text = new Text(this, ss.str(), Alignment::Center);
        score_text->teleport(
            sf::Vector2f(world_size.x / 2.0f, 15.0f + 30.f * i));
        i++;
        spawn(score_text);
    }
}

void Game::spawn_enemies() {
    for (int i = 0; i < 2; i++) {
        auto enemy = Enemy::Pistol(this);
        enemy->teleport(sf::Vector2f(50.0f, world_size.y / 2.0f - i * 100.0f));
        spawn(enemy);
        enemy = Enemy::Pistol(this);
        enemy->teleport(sf::Vector2f(world_size.x / 2.0f + i * 100.0f, 50.0f));
        spawn(enemy);
        enemy = Enemy::Pistol(this);
        enemy->teleport(sf::Vector2f(world_size.x - 50.0f,
                                     world_size.y / 2.0f - i * 100.0f));
        spawn(enemy);
    }
    enemies_left += 6;
}
