#include "Main.h"

EngineManager::EngineManager( std::vector<std::unique_ptr<Client>>* clients , std::vector<Bullet *>* bullets , std::vector<PowerUp*>* powerUps )
{
    this->clients = clients;
    this->bullets = bullets;
    this->powerUps = powerUps;
    this->bulletIdCounter = 1;
    this->powerUpIdCounter = 1;
    this->powerUpTimer = 0;
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

    powerUpTimer += stepTime;

    if (powerUpTimer>5)
    {
        if (powerUps->size()<20)
        {
            auto* powerUp = new PowerUp( powerUpIdCounter++ , getSpawnPoint() , Uint8(random()%5) );
            powerUps->push_back(powerUp);

            PowerUpPacket powerUpPacket;
            powerUpPacket.setFromPowerUp(powerUp);
            powerUpPacket.setToShow(true);
            UdpConnection::udpSendAll(powerUpPacket,*clients);

            powerUpTimer=0;
        }
    }
    else
    {
        powerUpTimer += stepTime;
    }

    if (bulletIdCounter>250) bulletIdCounter=0;
    if (powerUpIdCounter>250) powerUpIdCounter=0;
}


void EngineManager::checkColliders()
{
    for (auto &client: *clients)
    {
        for (auto &bullet: *bullets)
        {
            if (client->getId() == bullet->getClientId())
            {
                break;
            }

            double distance = sqrt((bullet->getPosition().x-client->getPosition().x)*(bullet->getPosition().x-client->getPosition().x)
                                   + (bullet->getPosition().y-client->getPosition().y)*(bullet->getPosition().y-client->getPosition().y));
            if (distance < FIELD_SIZE*2) {
                Collider *col1 = client->getCollider();
                Collider *col2 = bullet->getCollider();
                Vector2D col = Collider::areColliding(col1, col2);


                if (col.x != 0 || col.y != 0) {
                    for(auto &killer : *clients){
                        if(killer->getId() == bullet->getClientId())
                        {
                            client->doDamage(static_cast<int>(10 * killer->getAttackRatio()));
                            if (client->getActHp() < 1 && client->isIsPlayerReady()) {
                                client->setIsPlayerReady(false);
                                client->setDeaths(client->getDeaths() + 1);
                                //clear all input
                                for (int i = 0; i < 7; i++) {
                                    client->setKeys(i, false);
                                }
                                // Wysylanie pakietu
                                killer->setScore(killer->getScore() + 1);
                                PlayerDeadPacket pdp;
                                pdp.setKillerId(killer->getId());
                                pdp.setPlayerId(client->getId());
                                TcpConnection::tcpSendAll(pdp, *clients);
                            }
                        }

                    }

                    bullet->todestroy = true;
                }
            }
        }
    }

    for (auto &bullet: *bullets)
    {
        for (auto &wall: walls)
        {
            double distance = sqrt((bullet->getPosition().x-wall->getPosition().x)*(bullet->getPosition().x-wall->getPosition().x)
                    + (bullet->getPosition().y-wall->getPosition().y)*(bullet->getPosition().y-wall->getPosition().y));
            if (distance < FIELD_SIZE*2)
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
    }

    for (auto &client: *clients)
    {
        for (auto &powerUp: *powerUps)
        {
            double distance = sqrt((client->getPosition().x-powerUp->getPosition().x)*(client->getPosition().x-powerUp->getPosition().x)
                                   + (client->getPosition().y-powerUp->getPosition().y)*(client->getPosition().y-powerUp->getPosition().y));
            if (distance < FIELD_SIZE*2)
            {
                Collider *col1 = client->getCollider();
                Collider *col2 = powerUp->getCollider();

                Vector2D col = Collider::areColliding(col1, col2);

                if (col.x != 0 || col.y != 0)
                {
                    client->applyPowerUp(powerUp->getPowerUpType());
                    powerUp->todestroy = true;
                }
            }
        }
    }

    for (auto &client: *clients)
    {
        for (auto &wall: walls)
        {
            double distance = sqrt((client->getPosition().x-wall->getPosition().x)*(client->getPosition().x-wall->getPosition().x)
                                   + (client->getPosition().y-wall->getPosition().y)*(client->getPosition().y-wall->getPosition().y));
            if (distance < FIELD_SIZE*2 || wall->getHeight() > FIELD_SIZE || wall->getWidth() > FIELD_SIZE)
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
    }

    if (clients->size() > 1)
        for (auto &client1: *clients)
        {
            for (auto &client2: *clients)
            {
                double distance = sqrt((client1->getPosition().x-client2->getPosition().x)*(client1->getPosition().x-client2->getPosition().x)
                                       + (client1->getPosition().y-client2->getPosition().y)*(client1->getPosition().y-client2->getPosition().y));
                if (distance < FIELD_SIZE*2) {
                    if (client1 != client2) {
                        Collider *col1 = client1->getCollider();
                        Collider *col2 = client2->getCollider();
                        Vector2D col = Collider::areColliding(col1, col2);

                        if (col.x != 0 || col.y != 0) {
                            client1->setX(client1->getX() + col.x);
                            client1->setY(client1->getY() + col.y);

                            client2->setX(client2->getX() - col.x);
                            client2->setY(client2->getY() - col.y);
                        }
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

    auto powerUp_iterator = powerUps->begin();
    while(powerUp_iterator != powerUps->end())
    {
        if ((*powerUp_iterator)->todestroy)
        {
            PowerUpPacket powerUpPacket;
            powerUpPacket.setFromPowerUp((*powerUp_iterator));
            powerUpPacket.setToShow(false);
            UdpConnection::udpSendAll(powerUpPacket,*clients);

            delete *powerUp_iterator;
            powerUp_iterator = powerUps->erase(powerUp_iterator);
        }
        else
            ++powerUp_iterator;
    }
}

SDL_Point EngineManager::getSpawnPoint()
{
    float sum = 1;
    while(sum != 0)
    {
        auto* spawn = Map::getSpawnPoints()[random()%int(Map::getSpawnPoints().size())];
        sum=0;
        for (auto &other: *clients)
        {
            Collider *col1 = other->getCollider();
            Vector2D col = Collider::areColliding(col1, spawn);

            if (col.x != 0 || col.y != 0)
            {
                sum+=abs(col.x);
                sum+=abs(col.y);
            }
        }
        for (auto &powerUp: *powerUps)
        {
            Collider *col1 = powerUp->getCollider();
            Vector2D col = Collider::areColliding(col1, spawn);

            if (col.x != 0 || col.y != 0)
            {
                sum+=abs(col.x);
                sum+=abs(col.y);
            }
        }
        if (sum == 0)
        {
            return { int(spawn->center->x) , int(spawn->center->y) };
        }
    }
}