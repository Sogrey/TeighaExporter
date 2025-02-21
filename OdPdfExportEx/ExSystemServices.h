/////////////////////////////////////////////////////////////////////////////// 
// Copyright (C) 2002-2017, Open Design Alliance (the "Alliance"). 
// All rights reserved. 
// 
// This software and its documentation and related materials are owned by 
// the Alliance. The software may only be incorporated into application 
// programs owned by members of the Alliance, subject to a signed 
// Membership Agreement and Supplemental Software License Agreement with the
// Alliance. The structure and organization of this software are the valuable  
// trade secrets of the Alliance and its suppliers. The software is also 
// protected by copyright law and international treaty provisions. Application  
// programs incorporating this software must include the following statement 
// with their copyright notices:
//   
//   This application incorporates Teigha(R) software pursuant to a license 
//   agreement with Open Design Alliance.
//   Teigha(R) Copyright (C) 2002-2017 by Open Design Alliance. 
//   All rights reserved.
//
// By use of this software, its documentation or related materials, you 
// acknowledge and accept the above terms.
///////////////////////////////////////////////////////////////////////////////

#ifndef EXSYSTEMSERVICES_DEFINED
#define EXSYSTEMSERVICES_DEFINED

#include "TD_PackPush.h"

#include "RxSystemServicesImpl.h"
#include "ExHostAppServices.h"
#include "ExDgnHostAppServices.h"

#include "RxInit.h"

class ExSystemServices : public RxSystemServicesImpl
{
public:
	ExSystemServices()
	{
		static const char* ActInfo[] = {
#ifdef TEIGHA_TRIAL
			"", ""
#else
		//"UserInfo", "UserSignature" 

		// Before compiling, a Teigha activation file should be placed in a location that a compiler can access, 
		// otherwise you get a compiler error such as "Kernel/Extensions/ExServices/ExSystemServices.h:43:10: fatal error: 'OdActivationInfo' file not found". 
		// To learn about Teigha activation, see the activation guide at https://docs.opendesign.com/tkernel/oda_activation.html    
#include "OdActivationInfo"
#endif
		};

		odActivate(ActInfo[0], ActInfo[1]);
	}

	virtual ~ExSystemServices()
	{
		odCleanUpStaticData();
	}
};

class MyDwgServices : public ExHostAppServices
{
private:
	/************************************************************************/
	/* Compile password support for R18 Drawings                            */
	/************************************************************************/
#if defined(_MSC_VER) && !(defined(_WINRT))
	bool getPassword(const OdString& dwgName, bool isXref, OdPassword& password)
	{
		char buff[_MAX_PATH] = { 0 };
		STD(cout) << "Enter password to open drawing: " << STD(endl);
		::CharToOemA((const char*)dwgName, buff);
		STD(cout) << "    " << buff << STD(endl);

		STD(cin).get(buff, '\n').get();

		wchar_t pwdBuff[_MAX_PATH] = { 0 };
		// convert to upper case unicode:
		::OemToCharW(buff, pwdBuff);
		::CharUpperW(pwdBuff);
		password = pwdBuff;
		return !password.isEmpty();
	}
#endif
};

class MyDgnServices : public OdExDgnHostAppServices
{

};

#include "TD_PackPop.h"

#endif// EXSYSTEMSERVICES_DEFINED
