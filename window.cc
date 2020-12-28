#include "window.h"

sf::Event Window::event;
/**
 * Tile defined as an enum where each type is defined as:
 *      W: Wall
 *      G: Ghost Pen Gate
 *      P: Portal
 *      u: Empty path
 *      o: Pill
 *      O: Big Pill
 *
 */
 
Window::Window()
{
    load_and_bind_textures();
    new (&_window) sf::RenderWindow(sf::VideoMode(8*28*2, 8*36*2), "Pac-Man");

    _window.setKeyRepeatEnabled(false);
		_view.reset(sf::FloatRect(0, 0, 8*28, 8*36));
		_window.setView(_view);
		pacsprite = 0;
		ghostsprite = 0;
		drawMaze();
		drawScores();
}

void Window::KeyboardInput(){
	//std::cout << "keyboard input inicio" << std::endl;
	while (_window.pollEvent(event)){
		switch (event.type) {
			case sf::Event::Closed:
				_window.close();
				break;
			// key pressed
			case sf::Event::KeyPressed:
				if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
						_key.SetKey(L_KEY);
						_key.SetHandled(false);
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
						_key.SetKey(R_KEY);
						_key.SetHandled(false);
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
						_key.SetKey(D_KEY);
						_key.SetHandled(false);
				} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
						_key.SetKey(U_KEY);
						_key.SetHandled(false);
				} else if(event.key.code == 15) {
						_key.SetKey(P_KEY);
						_key.SetHandled(false);
				} else if(event.key.code == 16) {
						_key.SetKey(Q_KEY);
						_window.close();
						//_key.SetHandled(false);
				}
				break;
			}
	}
	//std::cout << "Keyboard input fim" << std::endl;
}

void Window::drawScores(){
		//std::cout << "Draw score inicio" << std::endl;
	int i,num;
	int score_pos[2] = {6*8,1*8+4}; // posicao ultimo digito - score
	int highscore_pos[2] = {16*8,1*8+4}; // posicao ultimo digito - high score
	int _points = _tilemap.GetScore();
	int _high_score = _tilemap.GetHighScore();

	for(i=0;_high_score%(int)pow(10,i) != _high_score;i++){
		num = (_points%(int)pow(10,i+1) - _points%(int)pow(10,i))/pow(10,i);
		numbers[num].setPosition(score_pos[0],score_pos[1]);
		_window.draw(numbers[num]);
		score_pos[0] -= 8;
		
		num = (_high_score%(int)pow(10,i+1) - _high_score%(int)pow(10,i))/pow(10,i);
		numbers[num].setPosition(highscore_pos[0],highscore_pos[1]);
		_window.draw(numbers[num]);
		highscore_pos[0] -= 8;
			//std::cout << "Draw score fim" << std::endl;
	}
}

void Window::draw_texture(unsigned int texture, int length, int height, float angle)
{
}

void Window::drawMaze(){
	//std::cout << "Draw maze inicio" << std::endl;
	int i, j;
	Tile aux;

	_window.clear();
	maze_sprite.setPosition(0, 24);
	_window.draw(maze_sprite);
	high_sprite.setPosition(75,2);
	_window.draw(high_sprite);
	score_sprite.setPosition(112,2);
	_window.draw(score_sprite);
	life_sprite.setPosition(8*2,8*34);
	_window.draw(life_sprite);
	life_sprite.setPosition(8*4,8*34);
	_window.draw(life_sprite);
	cherry_sprite.setPosition(8*24,8*34);
	_window.draw(cherry_sprite);

	for(i=0;i<31;i++){
		for(j=0;j<28;j++){
			aux = _tilemap.GetMaze(i,j);
			if(aux == o){
				pill_sprite.setPosition(8*j,24 + 8*i);
				_window.draw(pill_sprite);
			}else if(aux == O){
				bigPill_sprite.setPosition(8*j,8*i+24);
				_window.draw(bigPill_sprite);
			}else if(aux == f){
				cherry_sprite.setPosition(8*j-3,8*i+24-3);
				_window.draw(cherry_sprite);
			}
		}
	}
		//std::cout << "Draw maze fim" << std::endl;
}

void Window::drawPacman(){
	//std::cout << "Draw pacman inicio" << std::endl;
	sf::Sprite sprite;
	sprite = pacman[(int)(pacsprite/4)][(int)_tilemap.GetDirection((int)PACMAN)];
	pacsprite == 11? pacsprite = 0 : pacsprite++;
	sprite.setPosition(_tilemap.GetPosition_px((int)PACMAN,1) - 7, 24 + _tilemap.GetPosition_px((int)PACMAN,0) - 7);
	_window.draw(sprite);
	//std::cout << "Drawpacman fim" << std::endl;
}

void Window::drawGhost(CharacterName name){
	//std::cout << "Draw Ghost inicio" << std::endl;
	if(_tilemap.GetMode((int)name) == FRIGHTENED && !_tilemap.GetEaten((int)name)){
		frightened_b[(int)(ghostsprite/4)].setPosition(_tilemap.GetPosition_px((int)name,1) - 7, 24 + _tilemap.GetPosition_px((int)name,0) - 7);
		_window.draw(frightened_b[(int)(ghostsprite/4)]);
	}else{
		if(!_tilemap.GetEaten((int)name)){
			ghosts[(int)name-1][(int)(ghostsprite/4)].setPosition(_tilemap.GetPosition_px((int)name,1) - 7, 24 + _tilemap.GetPosition_px((int)name,0) - 7);
			_window.draw(ghosts[(int)name-1][0]);
		}
		
		eyes[(int)_tilemap.GetDirection((int)name)].setPosition(_tilemap.GetPosition_px((int)name,1) - 7, 24 + _tilemap.GetPosition_px((int)name,0) - 7);

		_window.draw(eyes[(int)_tilemap.GetDirection((int)name)]);
	}
	ghostsprite == 7 ? ghostsprite = 0: ghostsprite++;
	//std::cout << "Draw ghost fim" << std::endl;
}

void Window::start(){
		//std::cout << "Start inicio" << std::endl;
		drawGhost(BLINKY);
		drawGhost(PINKY);
		drawGhost(INKY);
		drawGhost(CLYDE);
		drawPacman();
		ready_sprite.setPosition(11*8,20*8);
		_window.draw(ready_sprite);
		_window.display();
		//std::cout << "Start fim" << std::endl;
}

void Window::death(int i){
	sf::Sprite sprite;
		drawMaze();	
		sprite = dying[i];
		sprite.setPosition(_tilemap.GetPosition_px((int)PACMAN,1) - 7, 24 + _tilemap.GetPosition_px((int)PACMAN,0) - 7);
		_window.draw(sprite);
		_window.display();
}

void Window::victory(){
	_window.close();
}

void Window::game_over(){
	_window.close();
}

bool Window::run(){
	//std::cout << "run inicio" << std::endl;

	drawMaze();
	drawScores();

	drawPacman();

	drawGhost(BLINKY);
	drawGhost(PINKY);
	drawGhost(INKY);
	drawGhost(CLYDE);

	_window.display();

	//usleep(200000);
	
	return _window.isOpen();
}


void Window::load_and_bind_textures()
{
    // Bind map textures    
    maze_tex.loadFromFile("sprites/maze/maze.png");
    maze_sprite.setTexture(maze_tex);
    //maze_sprite.scale(2, 2);
    pill_tex.loadFromFile("sprites/maze/p-0.png");
    pill_sprite.setTexture(pill_tex);
    bigPill_tex.loadFromFile("sprites/maze/p-1.png");
    bigPill_sprite.setTexture(bigPill_tex);

    // Bind Pacman textures
    pac_0u_tex.loadFromFile("sprites/pacman/0u.png");
		pac_0_tex.loadFromFile("sprites/pacman/0.png");
		pac_0d_tex.loadFromFile("sprites/pacman/0d.png");
		pac_0r_tex.loadFromFile("sprites/pacman/0r.png");

    pacman[0][0].setTexture(pac_0u_tex);
		pacman[0][1].setTexture(pac_0_tex);
		pacman[0][2].setTexture(pac_0d_tex);
		pacman[0][3].setTexture(pac_0r_tex);
    
    pac_1u_tex.loadFromFile("sprites/pacman/1u.png");
		pac_1_tex.loadFromFile("sprites/pacman/1.png");
		pac_1d_tex.loadFromFile("sprites/pacman/1d.png");
		pac_1r_tex.loadFromFile("sprites/pacman/1r.png");

    pacman[1][0].setTexture(pac_1u_tex);
		pacman[1][1].setTexture(pac_1_tex);
		pacman[1][2].setTexture(pac_1d_tex);
		pacman[1][3].setTexture(pac_1r_tex);
    
    pac_2u_tex.loadFromFile("sprites/pacman/2u.png");
		pac_2_tex.loadFromFile("sprites/pacman/2.png");
		pac_2d_tex.loadFromFile("sprites/pacman/2d.png");
		pac_2r_tex.loadFromFile("sprites/pacman/2r.png");

    pacman[2][0].setTexture(pac_2u_tex);
		pacman[2][1].setTexture(pac_2_tex);
		pacman[2][2].setTexture(pac_2d_tex);
		pacman[2][3].setTexture(pac_2r_tex);
    
    dead_0_tex.loadFromFile("sprites/pacman/d-0.png");
		dead_1_tex.loadFromFile("sprites/pacman/d-1.png");
		dead_2_tex.loadFromFile("sprites/pacman/d-2.png");
		dead_3_tex.loadFromFile("sprites/pacman/d-3.png");
		dead_4_tex.loadFromFile("sprites/pacman/d-4.png");
		dead_5_tex.loadFromFile("sprites/pacman/d-5.png");
		dead_6_tex.loadFromFile("sprites/pacman/d-6.png");
		dead_7_tex.loadFromFile("sprites/pacman/d-7.png");
		dead_8_tex.loadFromFile("sprites/pacman/d-8.png");
		dead_9_tex.loadFromFile("sprites/pacman/d-9.png");
		dead_10_tex.loadFromFile("sprites/pacman/d-10.png");

    dying[0].setTexture(dead_0_tex);
    dying[1].setTexture(dead_1_tex);
    dying[2].setTexture(dead_2_tex);
    dying[3].setTexture(dead_3_tex);
    dying[4].setTexture(dead_4_tex);
    dying[5].setTexture(dead_5_tex);
    dying[6].setTexture(dead_6_tex);
    dying[7].setTexture(dead_7_tex);
    dying[8].setTexture(dead_8_tex);
    dying[9].setTexture(dead_9_tex);
    dying[10].setTexture(dead_10_tex);
  

    // Bind ghost textures
    ghost_r_0_tex.loadFromFile("sprites/ghosts/r-0.png");
    ghosts[0][0].setTexture(ghost_r_0_tex);

    ghost_r_1_tex.loadFromFile("sprites/ghosts/r-1.png");
    ghosts[0][1].setTexture(ghost_r_1_tex);

    ghost_p_0_tex.loadFromFile("sprites/ghosts/p-0.png");
    ghosts[1][0].setTexture(ghost_p_0_tex);
     
    ghost_p_1_tex.loadFromFile("sprites/ghosts/p-1.png");
    ghosts[1][1].setTexture(ghost_p_1_tex);
     
    ghost_b_0_tex.loadFromFile("sprites/ghosts/b-0.png");
    ghosts[2][0].setTexture(ghost_b_0_tex);

    ghost_b_1_tex.loadFromFile("sprites/ghosts/b-1.png");
    ghosts[2][1].setTexture(ghost_b_1_tex);

    ghost_y_0_tex.loadFromFile("sprites/ghosts/y-0.png");
    ghosts[3][0].setTexture(ghost_y_0_tex);
    
    ghost_y_1_tex.loadFromFile("sprites/ghosts/y-1.png");
    ghosts[3][1].setTexture(ghost_y_1_tex);
    

    ghost_scared_0_tex.loadFromFile("sprites/ghosts/s-0.png");
    frightened_b[0].setTexture(ghost_scared_0_tex);
    ghost_scared_1_tex.loadFromFile("sprites/ghosts/s-1.png");
    frightened_b[1].setTexture(ghost_scared_1_tex);

    ghost_scared_2_tex.loadFromFile("sprites/ghosts/s-2.png");
    frightened_w[0].setTexture(ghost_scared_2_tex);
    
    ghost_scared_3_tex.loadFromFile("sprites/ghosts/s-3.png");
    frightened_w[1].setTexture(ghost_scared_3_tex);

     // Bind ghost eye textures
    eye_up_tex.loadFromFile("sprites/eyes/up.png");
    eyes[0].setTexture(eye_up_tex);
    
    eye_left_tex.loadFromFile("sprites/eyes/left.png");
    eyes[1].setTexture(eye_left_tex);
    
    eye_down_tex.loadFromFile("sprites/eyes/down.png");
    eyes[2].setTexture(eye_down_tex);
    
    eye_right_tex.loadFromFile("sprites/eyes/right.png");
    eyes[3].setTexture(eye_right_tex);
    

    // Bind UI textures
    num_0_tex.loadFromFile("sprites/ui/0.png");
    num_1_tex.loadFromFile("sprites/ui/1.png");
    num_2_tex.loadFromFile("sprites/ui/2.png");
    num_3_tex.loadFromFile("sprites/ui/3.png");
    num_4_tex.loadFromFile("sprites/ui/4.png");
    num_5_tex.loadFromFile("sprites/ui/5.png");
    num_6_tex.loadFromFile("sprites/ui/6.png");
    num_7_tex.loadFromFile("sprites/ui/7.png");
    num_8_tex.loadFromFile("sprites/ui/8.png");
    num_9_tex.loadFromFile("sprites/ui/9.png");

		numbers[0].setTexture(num_0_tex);
    numbers[1].setTexture(num_1_tex);
		numbers[2].setTexture(num_2_tex);
		numbers[3].setTexture(num_3_tex);
		numbers[4].setTexture(num_4_tex);
		numbers[5].setTexture(num_5_tex);
		numbers[6].setTexture(num_6_tex);
		numbers[7].setTexture(num_7_tex);
		numbers[8].setTexture(num_8_tex);
    numbers[9].setTexture(num_9_tex);

    score_200_tex.loadFromFile("sprites/ui/200.png");
    score_200_sprite.setTexture(score_200_tex);
    //score_200_sprite.scale(2, 2);
    score_400_tex.loadFromFile("sprites/ui/400.png");
    score_400_sprite.setTexture(score_400_tex);
    //score_400_sprite.scale(2, 2);
    score_800_tex.loadFromFile("sprites/ui/800.png");
    score_800_sprite.setTexture(score_800_tex);
    //score_800_sprite.scale(2, 2);
    score_1600_tex.loadFromFile("sprites/ui/1600.png");
    score_1600_sprite.setTexture(score_1600_tex);
    //score_1600_sprite.scale(2, 2);
    ready_tex.loadFromFile("sprites/ui/ready.png");
    ready_sprite.setTexture(ready_tex);
    //ready_sprite.scale(2, 2);
    gameover_tex.loadFromFile("sprites/ui/gameover.png");
    gameover_sprite.setTexture(gameover_tex);
    //gameover_sprite.scale(2, 2);
    life_tex.loadFromFile("sprites/ui/life.png");
    life_sprite.setTexture(life_tex);
    //life_sprite.scale(2, 2);
    score_tex.loadFromFile("sprites/ui/score_tex.png");
    score_sprite.setTexture(score_tex);
    //score_sprite.scale(2, 2);
    high_tex.loadFromFile("sprites/ui/high.png");
    high_sprite.setTexture(high_tex);
    //high_sprite.scale(2, 2);
    score_100_tex.loadFromFile("sprites/ui/100.png");
    score_100_sprite.setTexture(score_100_tex);
    //score_100_sprite.scale(2, 2);
    score_300_tex.loadFromFile("sprites/ui/300.png");
    score_300_sprite.setTexture(score_300_tex);
    //score_300_sprite.scale(2, 2);

    // Fruit textures
    cherry_tex.loadFromFile("sprites/fruits/cherry.png");
    cherry_sprite.setTexture(cherry_tex);
    cherry_sprite.scale(0.5f, 0.5f);
    strawberry_tex.loadFromFile("sprites/fruits/strawberry.png");
    strawberry_sprite.setTexture(strawberry_tex);
    //strawberry_sprite.scale(2, 2);
}
