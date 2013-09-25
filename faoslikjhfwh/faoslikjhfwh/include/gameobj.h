
#ifndef _GAMEOBJ_H_
#define _GAMEOBJ_H_



struct vector2d{
float x;
float y;
};
struct moveableobject{
vector2d position;
vector2d speed;
int sprite;
int height;
int width;

};
//bool gameOver;
void initGame();
void updateGame(bool &gameOver);
void drawGame();
void testOnScreen(moveableobject &obj);
void destroyGame();
void movePlayer(moveableobject &player);
void menu();
#endif  //_GAMEOBJ_H_