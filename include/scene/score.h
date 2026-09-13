#ifndef SCORE_H
#define SCORE_H

namespace game::scene
{

class score
{
public:
    void draw();

private:
    void process_key_press();

    static inline constexpr char top_text[] = "Top gamers";
};

} // namespace game::scene

#endif
