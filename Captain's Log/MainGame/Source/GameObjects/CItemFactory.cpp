#include "precompiled_header.h"
#include "CItemFactory.h"

CItemFactory::CItemFactory()
{

}

CItemFactory::~CItemFactory()
{

}

CItemFactory* CItemFactory::GetInstance()
{
	static CItemFactory instance;
	return &instance;
}
