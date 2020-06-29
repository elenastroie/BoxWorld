#pragma once
#include <SFML/Network.hpp>
#include "MatrixPosition.h"

class Packet : public sf::Packet
{
public:
    Packet(const MatrixPosition&, const MatrixPosition&);
    Packet(const MatrixPosition&, const MatrixPosition&, const MatrixPosition&);
};
