#include "stdafx.h"
#include "Projectile.h"

CProjectile::CProjectile()
{
}

CProjectile::~CProjectile()
{
}


void CProjectile::SetDamage(int value)
{
	m_iDamage = value;
}

int CProjectile::GetDamage() const
{
	return m_iDamage;
}
