#pragma once

#include "score.hpp"
#include <SFML/Graphics.hpp>
#include <vector>

enum CollisionLayer : int {
    PlayerLayer = 2,
    EnemyLayer = 4,
    BulletLayer = 8,
    MobLayer = 16,
    ItemLayer = 32,
    UILayer = 64,
};

enum GameState {
    Menu,
    Running,
    GameOver,
};

class Entity;
class Player;

class Game {
  private:
    sf::RenderWindow *window;
    std::vector<Entity *> entity_list;
    std::vector<Entity *> new_entities;
    Player *player;
    sf::Texture *player_texture;
    sf::Texture *enemy_texture;
    sf::Texture *bullet_texture;
    sf::Font *font;

    sf::Vector2f world_size;
    bool debug;
    unsigned entity_id_counter;
    unsigned score;
    int kills;
    std::vector<Score> scores;
    void start();
    void game_over();
    GameState state;
    void remove_entities();
    unsigned health_counter_id;
    void show_scores();
    void spawn_enemies();
    int enemies_left;

  public:
    Game(int size_x = 960, int size_y = 960);
    ~Game();
    void run();
    void spawn(Entity *entity);
    sf::Texture *get_player_texture() const;
    sf::Texture *get_enemy_texture() const;
    sf::Texture *get_bullet_texture() const;
    sf::Font *get_font() const;
    const sf::RenderWindow *get_window() const;
    sf::Vector2f get_world_size() const;
    bool get_debug_mode() const;
    unsigned new_entity_id();
    Entity *get_entity(unsigned id) const;
    unsigned collision_check(sf::FloatRect collider, unsigned id,
                             int layer) const;
    void add_score(unsigned amount);
    Player *get_player() const;
    void add_kill();
    GameState get_state() const;
};
