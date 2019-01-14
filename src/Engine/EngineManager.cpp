#include "Main.h"

EngineManager::EngineManager( std::vector<std::unique_ptr<Client>>* clients , std::vector<Bullet *>* bullets )
{
    this->clients = clients;
    this->bullets = bullets;
}

void EngineManager::move( double stepTime )
{
    for (auto &client: *clients )
    {
        client->move(stepTime);
        CurrentPositionPacket currentPositionPacket;
        currentPositionPacket.setFromClient(dynamic_cast<Client *>(client.get()) );
        UdpConnection::udpSendAll(currentPositionPacket,*clients);
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
                client->setActHp( uint8_t(client->getActHp()-10) );
                bullet->todestroy = true;
            }
        }
    }

    auto bullet_iterator = bullets->begin();
    while(bullet_iterator != bullets->end())
    {
        if ((*bullet_iterator)->todestroy)
        {
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

