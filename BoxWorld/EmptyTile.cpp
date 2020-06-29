#include "stdafx.h"
#include "EmptyTile.h"

bool EmptyTile::CanPlayerMoveThrough() const { return true; }

bool EmptyTile::CanBeMovedByPlayer() const { return false; }

void EmptyTile::LoadTexture(){}
