// imaGL.cpp : Définit les fonctions de la bibliothèque statique.
//

#include "imaGL.h"


void CImaGL::computePixelSize()
{
	int nNbComp = 0;
	switch (m_PixelFormat)
	{
	default:
	case CImaGL::EPixelFormat::Undefined:
		m_nPixelSize = 0;
		break;
	case CImaGL::EPixelFormat::R:
		nNbComp = 1;
		break;
	case CImaGL::EPixelFormat::RG:
		nNbComp = 2;
		break;
	case CImaGL::EPixelFormat::RGB:
	case CImaGL::EPixelFormat::BGR:
		nNbComp = 3;
		break;
	case CImaGL::EPixelFormat::RGBA:
	case CImaGL::EPixelFormat::BGRA:
		nNbComp = 4;
		break;
	}
	switch (m_PixelType)
	{
	default:
	case CImaGL::EPixelType::Undefined:
		m_nPixelSize = 0;
		break;
	case CImaGL::EPixelType::UByte:
	case CImaGL::EPixelType::Byte:
		m_nPixelSize = nNbComp;
		break;
	case CImaGL::EPixelType::UShort:
	case CImaGL::EPixelType::Short:
		m_nPixelSize = nNbComp * 2;
		break;
	case CImaGL::EPixelType::UInt:
	case CImaGL::EPixelType::Int:
		m_nPixelSize = nNbComp * 4;
		break;
	case CImaGL::EPixelType::HFloat:
		m_nPixelSize = nNbComp * 2;
		break;
	case CImaGL::EPixelType::Float:
		m_nPixelSize = nNbComp * 4;
		break;
	case CImaGL::EPixelType::UByte_3_3_2:
	case CImaGL::EPixelType::UByte_2_3_3_Rev:
		m_nPixelSize = 1;
		break;
	case CImaGL::EPixelType::UShort_5_6_5:
	case CImaGL::EPixelType::UShort_5_6_5_Rev:
		m_nPixelSize = 2;
		break;
	case CImaGL::EPixelType::UShort_4_4_4_4:
	case CImaGL::EPixelType::UShort_4_4_4_4_Rev:
	case CImaGL::EPixelType::UShort_5_5_5_1:
	case CImaGL::EPixelType::UShort_1_5_5_5_Rev:
	case CImaGL::EPixelType::UInt_8_8_8_8:
	case CImaGL::EPixelType::UInt_8_8_8_8_Rev:
	case CImaGL::EPixelType::UInt_10_10_10_2:
	case CImaGL::EPixelType::UInt_2_10_10_10_Rev:
		m_nPixelSize = 4;
		break;
	}
}
