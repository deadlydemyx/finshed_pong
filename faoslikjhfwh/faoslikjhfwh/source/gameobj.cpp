#include <iostream>
#include "gameobj.h"
#include "AIE.h"
#include <cmath>

using namespace std;

const int SCREEN_X = 1280;
const int SCREEN_Y = 780;
const int PLAYER1_X = 50;
const int PLAYER1_W = 50;
const int PLAYER1_H = 175;

const int PLAYER2_X = 1225;
const int PLAYER2_W = 50;
const int PLAYER2_H = 175;

const int BALL_W = 32;
const int BALL_H = 32;

unsigned int bgImage = -1;
moveableobject player1 = {PLAYER1_X, 100, 0, 0, -1 , PLAYER1_H, PLAYER1_W};
moveableobject player2 = {PLAYER2_X, 100, 0, 0, -1, PLAYER2_H, PLAYER2_W};
moveableobject ball = {500, 500, 1, 1, -1, BALL_W, BALL_H};

int player1Score = 0;
int player2Score = 0;


 //

void initGame(){
	bgImage = CreateSprite( "./images/PBG.png", SCREEN_X, SCREEN_Y, true );
	MoveSprite(bgImage, SCREEN_X>>1, SCREEN_Y>>1);
	ball.sprite = CreateSprite( "./images/ball.png", BALL_W, BALL_H, true );
	MoveSprite(ball.sprite, ball.position.x ,ball.position.y);
	player1.sprite = CreateSprite( "./images/OnixP1.png", PLAYER1_W, PLAYER1_H, true );
	MoveSprite(player1.sprite, player1.position.x, player1.position.y);
	player2.sprite = CreateSprite( "./images/OnixP2.png", PLAYER2_W, PLAYER2_H, true );
	MoveSprite(player2.sprite, player2.position.x, player2.position.y);
}




bool checkPaddleCollision(moveableobject& ball, moveableobject& player) {
	int speed = ball.speed.x;
	
	int ballHalfW = ball.width>>1;
	int playerHalfW = player.width>>1;
	int playerHalfH = player.height>>1;
	
	if(speed == 0)
		return false;

	if(speed < 0){
		if(ball.position.x - ballHalfW < player.position.x + playerHalfW && 
			ball.position.y > player.position.y - playerHalfH &&
			ball.position.y < player.position.y + player.height){
				return true;
		}
	}
	else {
		if(ball.position.x + ballHalfW > player.position.x - playerHalfW && 
			ball.position.y > player.position.y - playerHalfH &&
			ball.position.y < player.position.y + player.height){
				return true;
		}
	}
	return false;
}


void seek(moveableobject &player, moveableobject& ball){
	float speed = sqrt(ball.speed.x*ball.speed.x + ball.speed.y*ball.speed.y);

	if (player.position.y < ball.position.y)
		player.position.y = ball.position.y;
	else if (player.position.y > ball.position.y)
		player.position.y = ball.position.y;
	else if (player.position.x > ball.position.x)
		player.position.y = ball.position.y;
}


void movePlayer(moveableobject &player)
{
float speed = sqrt (ball.speed.x*ball.speed.x + ball.speed.y*ball.speed.y - 30);

if(IsKeyDown('S'))
{
	//int diff = player.position.y;
	player.speed.y = 1;
}
else if(IsKeyDown('W'))
{
	//int diff = player.position.y;
	player.speed.y = -1;
}else
{
	player.speed.y = 0;
}
}


	void updateGame(bool &gameOver){

		movePlayer(player1);
		//if(ball.speed.x < 0)
		seek(player2, ball);
		
		ball.position.x += ball.speed.x;
		ball.position.y += ball.speed.y;

		player1.position.y += player1.speed.y;
		//(checkPaddleCollision(ball, player1) || checkPaddleCollision(ball, player2))
		
			if(ball.speed.x <0){
				if(checkPaddleCollision(ball, player1) == true)
				{
				ball.speed.x *= -1;
				}
			}
			else {
				if(checkPaddleCollision(ball, player2) == true)
				ball.speed.x *= -1;
			}
			if(ball.position.x <= 0)
			{
				++player2Score;
				ball.position.x = 640;
				ball.position.y = 340;//vector2d{300,300};
			}
			if(ball.position.x >= 1280)
				++player1Score;

			if (player1Score == 1 || player2Score == 1) {
				gameOver = true;
				player1Score = 0;
				player2Score = 0;
			}
		testOnScreen(ball);
		MoveSprite(ball.sprite, ball.position.x ,ball.position.y);
		RotateSprite(player1.sprite, 0);
		MoveSprite(player1.sprite, player1.position.x ,player1.position.y);
		RotateSprite(player2.sprite, 0);
		MoveSprite(player2.sprite, player2.position.x ,player2.position.y);

	}


	void drawGame()
	{

	static char outScore1[15] = {'\n'};
	static char outScore2[15] = {'\n'};
	
	sprintf(outScore1, "Player 1: %d", player1Score);
	sprintf(outScore2, "Player 2: %d", player2Score);

	DrawSprite(bgImage);
	DrawSprite(ball.sprite);
	DrawSprite(player1.sprite);
	DrawSprite(player2.sprite);
	DrawString(outScore1, 50, 50, SColour(255,0,0,255));
	DrawString(outScore2, 1000, 50, SColour(0,255,0,255));
	}


	void menu()
{
	bool menu = false;
	int choice;
	cout << "Welcome to game hell. Please select an option. Make sure your pick the right one...." << endl;
	// loop to keep player in menu state until an option is selected.
	while (menu == false)
	{
		cout << "1. WOULD YOU LIKE TO PLAY A GAME?" << endl;
		cout << "2. OR RUN LIKE A BITCH." << endl;
		cin >> choice;
		choice = choice - 1;
		switch (choice)
		{
		case 0: menu = true;
				break;
		case 1: exit(EXIT_SUCCESS);
				break;
		};
	}
}// allows the player to chose if they would like to play or exit.


	void testOnScreen(moveableobject &obj)
	{
	if(obj.position.x > SCREEN_X) {
		obj.speed.x *= -1;
		return ;
	}
	if(obj.position.x < 0) {
		obj.speed.x *= -1;
		return;
	}
	if(obj.position.y > SCREEN_Y) {
		obj.speed.y *= -1;
		return;
	}
	if(obj.position.y < 0) {
		obj.speed.y *= -1;
	
	}
}

	//removes all the sprites and objects.
	void destroyGame() {
	DestroySprite(bgImage);
	DestroySprite(ball.sprite);
	DestroySprite(player1.sprite);
	DestroySprite(player2.sprite);
	}
