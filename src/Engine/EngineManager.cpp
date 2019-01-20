#include "Main.h"

EngineManager::EngineManager( std::vector<std::unique_ptr<Client>>* clients , std::vector<Bullet *>* bullets )
{


    this->clients = clients;
    this->bullets = bullets;
    this->bulletIdCounter = 1;
    this->walls = Map::getColliders();
}

void EngineManager::move( double stepTime )
{
    for (auto &client: *clients )
    {
            client->move(stepTime);

            CurrentPositionPacket currentPositionPacket;
            currentPositionPacket.setFromClient(dynamic_cast<Client *>(client.get()) );
            UdpConnection::udpSendAll(currentPositionPacket,*clients);

            if (client->getKeys(6) && client->isReadyToShoot())
            {
                client->setUnableToShoot();

                Bullet * bullet = new Bullet(client->shootPosition(),client->getITowerDirection(),bulletIdCounter++,client->getId());
                bullets->push_back(bullet);

                BulletInfoPacket bulletInfoPacket;
                bulletInfoPacket.setX(static_cast<Uint16>(bullet->getPosition().x));
                bulletInfoPacket.setY(static_cast<Uint16>(bullet->getPosition().y));
                bulletInfoPacket.setPlayerId(static_cast<Uint8>(bullet->getClientId()));
                bulletInfoPacket.setAngle(static_cast<Uint16>(bullet->getDirection()));
                bulletInfoPacket.setBulletId(static_cast<Uint8>(bullet->getId()));
                UdpConnection::udpSendAll(bulletInfoPacket, *clients );


        }
    }

    for (auto& bullet: *bullets )
        bullet->move(stepTime);
}


void EngineManager::checkColliders()
{
    for (auto &client: *clients)
    {
        for (auto &bullet: *bullets)
        {
            Collider *col1 = client->getCollider();
            Collider *col2 = bullet->getCollider();

            Vector2D col = Collider::areColliding(col1, col2);

            if (col.x != 0 || col.y != 0)
            {
                client->doDamage( 10 );
                if (client->getActHp() < 1) {
                    for (auto &cli: *clients) {
                        if (cli->getId() == bullet->getClientId()) {
                            cli->setScore(cli->getScore() + 1);
                        }
                    }
                    // Wysylanie pakietu
                    client->setIsPlayerReady(false);
                    PlayerDeadPacket pdp;
                    pdp.setKillerId(bullet->getClientId());
                    pdp.setPlayerId(client->getId());
                    UdpConnection::udpSendAll(pdp,*clients);
                }
                bullet->todestroy = true;
            }
        }
    }

    for (auto &bullet: *bullets)
    {
        for (auto &wall: walls)
        {
            Collider *col1 = bullet->getCollider();
            Collider *col2 = wall->getCollider();

            Vector2D col = Collider::areColliding(col1, col2);

            if (col.x != 0 || col.y != 0)
            {
                bullet->todestroy = true;
            }
        }
    }

    for (auto &client: *clients)
    {
        for (auto &wall: walls)
        {
            Collider *col1 = client->getCollider();
            Collider *col2 = wall->getCollider();

            Vector2D col = Collider::areColliding(col1, col2);

            if (col.x != 0 || col.y != 0)
            {
                client->setX(client->getX()+col.x*3);
                client->setY(client->getY()+col.y*3);

                int speed = client->getTankSpeed();
                if (speed>0)
                    client->setTankSpeed(speed-20);
                if (speed<0)
                    client->setTankSpeed(speed+20);
                if (speed>-20 && speed<20)
                    client->setTankSpeed(0);
            }
        }
    }

    if (clients->size() > 1)
        for (auto &client1: *clients)
        {
            for (auto &client2: *clients)
            {
                if (client1 != client2) {
                    Collider *col1 = client1->getCollider();
                    Collider *col2 = client2->getCollider();
                    Vector2D col = Collider::areColliding(col1, col2);

                    if (col.x != 0 || col.y != 0) {
                        client1->setX(client1->getX() + col.x);
                        client1->setY(client1->getY() + col.y);
                        client1->setTankSpeed(client1->getTankSpeed()-20);

                        client2->setX(client2->getX() - col.x);
                        client2->setY(client2->getY() - col.y);
                        //client2->setTankSpeed(client2->getTankSpeed()-20);
                    }
                }


            }
        }

    auto bullet_iterator = bullets->begin();
    while(bullet_iterator != bullets->end())
    {
        if ((*bullet_iterator)->todestroy)
        {
            BulletInfoPacket bulletInfoPacket;
            bulletInfoPacket.setX(static_cast<Uint16>(0));
            bulletInfoPacket.setY(static_cast<Uint16>(0));
            bulletInfoPacket.setPlayerId(static_cast<Uint8>((*bullet_iterator)->getClientId()));
            bulletInfoPacket.setAngle(static_cast<Uint16>((*bullet_iterator)->getDirection()));
            bulletInfoPacket.setBulletId(static_cast<Uint8>((*bullet_iterator)->getId()));
            UdpConnection::udpSendAll(bulletInfoPacket, *clients );


            delete *bullet_iterator;
            bullet_iterator = bullets->erase(bullet_iterator);
        }
        else
            ++bullet_iterator;
    }
}



//    Collider * col1 = nullptr;
//    Collider * col2 = nullptr;
//
//    for (int i = 0; i < gameObjects.size(); i++)
//    {
//        for (int j = i+1; j < gameObjects.size(); j++)
//        {
//            if (!(gameObjects[i]->getType()==STATIC && gameObjects[j]->getType()==STATIC))
//            {
//                double diagonal1 = sqrt( pow(gameObjects[i]->getW()/2,2) + pow(gameObjects[i]->getH()/2,2) );
//                double diagonal2 = sqrt( pow(gameObjects[j]->getW()/2,2) + pow(gameObjects[j]->getH()/2,2) );
//                double distance = sqrt( pow(gameObjects[j]->getX()-gameObjects[i]->getX(),2) + pow(gameObjects[j]->getY()-gameObjects[i]->getY(),2) );
//
//                if ( (distance < diagonal1 + diagonal2) )
//                {
//                    col1 = gameObjects[i]->getCollider();
//                    col2 = gameObjects[j]->getCollider();
//
//                    Vector2D col = Collider::areColliding(col1, col2);
//                    if (col.x != 0 || col.y != 0) {
//
//                        if (auto *p = dynamic_cast<Player *>(gameObjects[i])) {
//                            if (auto *b = dynamic_cast<Bullet *>(gameObjects[j])) {
//
//                            } else{
//                                p->PushOut(col * 2);
//                            }
//                        } else if (auto *p = dynamic_cast<Player *>(gameObjects[j])) {
//                            if (auto *b = dynamic_cast<Bullet *>(gameObjects[i])) {
//
//                            } else{
//                                p->PushOut(col * 2);
//
//                            }
//                        } else if (auto *b = dynamic_cast<Bullet *>(gameObjects[i])) {
//                            b->setToBeDestroyed();
//                        } else if (auto *b = dynamic_cast<Bullet *>(gameObjects[j])) {
//                            b->setToBeDestroyed();
//                        }
//                    }
//                }
//            }
//        }
//    }

