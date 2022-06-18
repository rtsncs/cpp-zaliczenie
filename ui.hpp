#pragma once
#include "entity.hpp"
#include <cmath>
#include <sstream>

enum Alignment { TopLeft, Center };

class Text : public Entity {
  protected:
    sf::Text text;
    std::string label;
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    Alignment alignment;

  public:
    Text(Game *game, std::string label,
         Alignment alignment = Alignment::TopLeft);
    virtual void teleport(sf::Vector2f position);
    virtual unsigned move(sf::Vector2f offset);
    virtual void rotate(sf::Vector2f direction);
    virtual void update(float delta_time);
    virtual sf::FloatRect get_bounding_box() const;
};

template <typename T> class DataText : public Text {
  private:
    T *data;

  public:
    DataText(Game *_game, std::string _label, T *_data)
        : Text(_game, _label), data{_data} {}

    void set_data(T *new_data) { data = new_data; }

    void update([[maybe_unused]] float delta_time) {
        if (data) {
            std::stringstream ss;
            ss << label << *data;
            text.setString(ss.str());
        } else {
            text.setString(label + "0");
        }
    }
};

class Button : public Text {
  private:
    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    sf::RectangleShape background;

  public:
    Button(Game *game, std::string label,
           Alignment alignment = Alignment::TopLeft);
    bool clicked();
    std::string get_label();
    virtual void teleport(sf::Vector2f position);
    virtual unsigned move(sf::Vector2f offset);
    virtual void rotate(sf::Vector2f direction);
};
