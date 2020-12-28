#ifndef tilemap_h
#define tilemap_h

#include <iostream>
#include "enum.h"
 
class Tilemap{
    public:
				Tile GetMaze(int x,int y);
				int GetPosition(int x,int y);
				int GetPosition_px(int x,int y);
				Direction GetDirection(int i);
				Mode GetMode(int name);
				int GetScore();
				int GetHighScore();
				bool GetEaten(int name);

				void SetMaze(Tile tile,int x, int y);
				void SetPosition(int i,int x, int y);
				void SetPosition_px(int i,int x, int y);
				void SetDirection(Direction direction,int i);
				void SetMode(int name, Mode mode);
				void SetEaten(bool eaten,int name);

				void AddPoints(int points);
				void LoseLife();
				int GetLives();
				
				void ResetMaze();
    private:
        static Tile _maze[31][28];
				static int _positions[5][2];
				static int _positions_px[5][2];
				static Direction _directions[5];
				static Mode _mode[5];
				static bool _eaten[5];
				static int _lives;
				static unsigned int _points;
        static unsigned int _high_score;
};

#endif
