#include "stdafx.h"
#include "Packet.h"

Packet::Packet(const MatrixPosition& one, const MatrixPosition& two)
{
    *this << one.GetRowIndex() << one.GetColumnIndex() << two.GetRowIndex() << two.GetColumnIndex();
}

Packet::Packet(const MatrixPosition& one, const MatrixPosition& two, const MatrixPosition& three) : Packet(one, two)
{
    *this << three.GetRowIndex() << three.GetColumnIndex();
}
