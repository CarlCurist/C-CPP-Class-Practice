#include "Game.h"
Game::Game()
: mWindow(sf::VideoMode(screenX, screenY), "Come on Boys!")
//, mPlayer()
{
	//mPlayer.setRadius(40.f);
	//mPlayer.setPosition(screenX-300, screenY-300);
	//mPlayer.setFillColor(sf::Color::Cyan);
	backgroundText.loadFromFile("resources/image/background.png");
	gameover.loadFromFile("resources/image/gameover.png");
    background.setTexture(backgroundText);
    srand((unsigned) time(NULL));
    PlayerHP=3;
    Score=29;
    mPlayer=new Hero;
    fail=victory=haveBoss=false;
    //mWindow.setFramerateLimit(120);

//加载字体相关信息
    font.loadFromFile("resources/font/STHeiti Light.ttc");
    mScore.setFont(font);
    mHP.setFont(font);
    mScore.setPosition(0,0);
    mHP.setPosition(0,25);

//加载声音资源
    BGM1.openFromFile("resources/sound/game_music.ogg");
    BGM1.setLoop(true);
    BGM1.play();
}
void Game::enemyAction()
{
    //创建敌机
    if(Score==30&&!haveBoss)
        {
            allEnemy.push_back(new Enemy(boss));//击落50架敌机后放boss
            haveBoss=true;
        }
    if(rand()%3000==1)
    {
        allEnemy.push_back(new Enemy(normal));
    }

    if(rand()%6000==1)
    {
        allEnemy.push_back(new Enemy(elite));
    }

    //敌机开火
    for (std::vector<Enemy*>::iterator it = allEnemy.begin(); it != allEnemy.end(); ++it)
    {
        if((*it)->getType()==boss)
        {
            if(rand()%300==1)
                (*it)->fire();
        }
        if(rand()%2000==1)
        {
            (*it)->fire();
        }
    }
}

void Game::run()
{
	sf::Clock clock;
	while (mWindow.isOpen())
	{
	    if(fail)
        {
            processEvents();
            background.setTexture(gameover);

            char s[20],s2[20]="You Score: ";
            snprintf(s,9,"%d",Score);
            strcat(s2,s);
            mScore.setPosition(200,600);
            mScore.setString(s2);

            mWindow.clear();
            mWindow.draw(background);
            mWindow.draw(mScore);
            mWindow.display();
            continue;
        }
		sf::Time deltaTime = clock.restart();
		if(mPlayer->checkAlive()>0)
            processEvents();
		else
            if(mPlayer->ruin())
            {
                delete mPlayer;
                PlayerHP--;
                if(PlayerHP>0)
                    mPlayer=new Hero;
                else
                {
                    fail=true;
                    continue;
                }
            }
		update(deltaTime);
		enemyAction();
		checkCollide();
		render();
		deleteCrash();
		mPlayer->deleteDie();
	}
}
void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			if(PlayerHP)handlePlayerInput(event.key.code, true);
			break;
		case sf::Event::KeyReleased:
			if(PlayerHP)handlePlayerInput(event.key.code, false);
			break;
		case sf::Event::Closed:
			mWindow.close();
			break;
		}
	}
}
void Game::update(sf::Time deltaTime)
{
    mPlayer->moveNode(deltaTime);
    for (std::vector<Enemy*>::iterator it = allEnemy.begin(); it != allEnemy.end(); ++it)
    {
        Enemy *temp=*it;
        temp->moveNode(deltaTime);
    }

}
void Game::render()
{
    std::vector<Bullet*> p=mPlayer->getBulletVector();
	mWindow.clear();
	mWindow.draw(background);
	mWindow.draw(*mPlayer);
	//»­×Óµ¯
    for (std::vector<Bullet*>::iterator it = p.begin(); it != p.end(); ++it)
    {
        Bullet *temp=*it;
        mWindow.draw(*temp);
    }
    //
    for (std::vector<Enemy*>::iterator it = allEnemy.begin(); it != allEnemy.end(); ++it)
    {
        Enemy *temp=*it;
        mWindow.draw(*temp);

        //渲染每台敌机的子弹
        p=(*it)->getBulletVector();
        for (std::vector<Bullet*>::iterator it2 = p.begin(); it2 != p.end(); ++it2)
        {
            Bullet *temp=*it2;
            mWindow.draw(*temp);
        }
    }

//显示字符串
    char s[20],s2[20]="Score: ";
    snprintf(s,9,"%d",Score);
    strcat(s2,s);
    mScore.setString(s2);
    mWindow.draw(mScore);

    strcpy(s2,"HP: ");
    snprintf(s,9,"%d",PlayerHP);
    strcat(s2,s);
    mHP.setString(s2);
    mWindow.draw(mHP);
/////////////
	mWindow.display();
}
void Game::handlePlayerInput(sf::Keyboard::Key key,
	bool isPressed)
{
	if (key == sf::Keyboard::W)
		mPlayer->isMovingUp(isPressed);
	else if (key == sf::Keyboard::S)
		mPlayer->isMovingDown(isPressed);
	else if (key == sf::Keyboard::A)
		mPlayer->isMovingLeft(isPressed);
	else if (key == sf::Keyboard::D)
		mPlayer->isMovingRight(isPressed);
    if(key==sf::Keyboard::J)
    {
        mPlayer->fire();
    }
}

void Game::checkCollide()
{
    //检查玩家子弹
    Bullet *tempPlayer;
    std::vector<Bullet*> p=mPlayer->getBulletVector();
    for (std::vector<Bullet*>::iterator it = p.begin(); it != p.end(); ++it)
    {
        tempPlayer=*it;
        for (std::vector<Enemy*>::iterator it2 = allEnemy.begin(); it2 != allEnemy.end(); ++it2)
        {
            if((*it2)->checkHit(tempPlayer->getPosition().x+4,tempPlayer->getPosition().y))
                tempPlayer->die();
        }
    }

    //检查敌人子弹
    int myx=mPlayer->getPosition().x+51;
    int myy=mPlayer->getPosition().y;
    int otherx,othery;
    for (std::vector<Enemy*>::iterator it = allEnemy.begin(); it != allEnemy.end(); ++it)
    {
        //检查飞机有没有碰撞
        otherx=(*it)->getPosition().x;
        othery=(*it)->getPosition().y;
        if((*it)->getType()==normal)
        {
            if(myx<=otherx+57&&
                myx>=otherx&&
                myy<=othery+51&&
                myy>=othery)
            {
                mPlayer->crash();
            }
        }
        else
        {
            if(myx<=otherx+69&&
                myx>=otherx&&
                myy<=othery+95&&
                myy>=othery)
            {
                mPlayer->crash();
            }
        }

        //检查子弹碰撞
        p=(*it)->getBulletVector();
        for (std::vector<Bullet*>::iterator it2 = p.begin(); it2 != p.end(); ++it2)
        {
            otherx=(*it2)->getPosition().x;
            othery=(*it2)->getPosition().y;
            if(myx<=otherx+9&&
               myx>=otherx&&
               myy<=othery+21&&
               myy>=othery)
            {
                mPlayer->crash();
            }
        }
    }
    /*
    //检查玩家子弹
    Bullet *tempPlayer;
    std::vector<Bullet*> p=mPlayer->getBulletVector();
    for (std::vector<Bullet*>::iterator it = p.begin(); it != p.end(); ++it)
    {
        tempPlayer=*it;
        for (std::vector<Enemy*>::iterator it2 = allEnemy.begin(); it2 != allEnemy.end(); ++it2)
        {
            if(tempPlayer->getPosition().x<(*it2)->getPosition().x+69&&
               (*it2)->getPosition().x<tempPlayer->getPosition().x&&
               tempPlayer->getPosition().y<(*it2)->getPosition().y+95&&
               (*it2)->getPosition().y<tempPlayer->getPosition().y)
            {
                (*it2)->die();
                (*it)->die();
            }
        }
    }
    //检查敌机与敌机子弹
    for (std::vector<Enemy*>::iterator it = allEnemy.begin(); it != allEnemy.end(); ++it)
    {
        if((mPlayer.getPosition().x+102<(*it)->getPosition().x+69&&
            mPlayer.getPosition().x+102>(*it)->getPosition().x&&
            mPlayer.getPosition().y>(*it)->getPosition().y)||
           (mPlayer.getPosition().x<(*it)->getPosition().x+69&&
            mPlayer.getPosition().x>(*it)->getPosition().x&&
            mPlayer.getPosition().y>(*it)->getPosition().y))
                mPlayer.die();
        p=(*it)->getBulletVector();
        for (std::vector<Bullet*>::iterator it2 = p.begin(); it2 != p.end(); ++it2)
        {
            Bullet *temp=*it2;
            if(temp->getPosition().x<mPlayer.getPosition().x+102&&
               temp->getPosition().x>mPlayer.getPosition().x&&
               temp->getPosition().y>mPlayer.getPosition().y&&
               temp->getPosition().y<mPlayer.getPosition().y+126)
               mPlayer.die();
        }
    }
    */
}

void Game::deleteCrash()
{
    for (std::vector<Enemy*>::iterator it = allEnemy.begin(); it != allEnemy.end(); ++it)
    {
        if((*it)->checkAlive()<=0||(*it)->getPosition().y>=screenY)
        {
            if((*it)->canDelete())
            {
                delete *it;
                allEnemy.erase(it);
                it--;
                Score++;
            }
        }

    }

    //mPlayer.deleteDie();
}
