#include"enemy.h"
#include <stdlib.h>
#include <time.h>


class Game
{
public:
	Game();
	void run();

private:
	void processEvents();
	void update(sf::Time deltaTime);
	void render();
	void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void enemyAction();
	void checkCollide();
	void deleteCrash();
	sf::RenderWindow mWindow;
	Hero* mPlayer;

    //std::vector<Entity*> allEntity;
    std::vector<Enemy*>allEnemy;
	sf::Texture backgroundText;
	sf::Texture gameover;
	//sf::Texture congratulaton;
	sf::Sprite background;
	sf::Music BGM1;
	int PlayerHP,Score;
	sf::Font font;
	sf::Text mScore,mHP;
	bool haveBoss,victory,fail;
};
