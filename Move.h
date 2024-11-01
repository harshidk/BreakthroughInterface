#include <utility>
#include <string>

class Move{
    private:
        struct m{
            std::pair<int, int> startSq;
            std::pair<int, int> endSq;
        };
        m move;
    public:
        Move(int r0, int c0, int r1, int c1);
        Move();
        void setMove(int r0, int c0, int r1, int c1);
        Move::m getMove();
        friend bool operator== (const Move& m1, const Move& m2);
        std::string toString();
};