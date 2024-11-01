#include "Move.h"
#include "iostream"

Move::Move(int r0, int c0, int r1, int c1){
    move.startSq = {r0, c0};
    move.endSq = {r1, c1};
}

Move::Move(){
    move.startSq = {0, 0};
    move.endSq = {0, 0};
}

void Move::setMove(int r0, int c0, int r1, int c1){
    move.startSq = {r0, c0};
    move.endSq = {r1, c1};
}

Move::m Move::getMove(){
    return move;
}

bool operator==(const Move &m1, const Move &m2){
    return ((m1.move.endSq == m2.move.endSq) && (m1.move.startSq == m2.move.startSq));
}

std::string Move::toString(){
    std::string res;
    res += char(move.startSq.second + 97);
    res += std::to_string(move.startSq.first + 1);
    res += char(move.endSq.second + 97);
    res += std::to_string(move.endSq.first + 1);
    return res;
}