#include "gamepad.h"
#include "global.h"
#include <dinput.h>

#pragma comment( lib, "dinput8.lib" )
#pragma comment( lib, "dxguid.lib" )

namespace input
{
	namespace joystick
	{

		BOOL initialize_joystick()
		{
			return TRUE;
		}


		LPDIRECTINPUT8 p_dinput = nullptr;
		LPDIRECTINPUTDEVICE8 p_dinput_device = nullptr;
		bool joypad_available = false;
		bool right = false;
		BOOL CALLBACK enum_direction_callback( const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext );


		bool is_joypad_available()
		{
			return joypad_available;
		}

		BOOL CALLBACK enum_direction_callback( const DIDEVICEOBJECTINSTANCE *pdidoi, VOID *pContext )
		{
			HRESULT     hr;
			DIPROPRANGE diprg;

			diprg.diph.dwSize = sizeof( DIPROPRANGE );
			diprg.diph.dwHeaderSize = sizeof( DIPROPHEADER );
			diprg.diph.dwHow = DIPH_BYID;
			diprg.diph.dwObj = pdidoi->dwType;
			diprg.lMin = 0 - 1000;
			diprg.lMax = 0 + 1000;
			hr = p_dinput_device->SetProperty( DIPROP_RANGE, &diprg.diph );

			if( FAILED( hr ) ) return DIENUM_STOP;

			return DIENUM_CONTINUE;
		}

		//Direct Input‚Ì‰Šú‰»‚ðs‚¤
		BOOL CALLBACK get_joystick_callback( LPDIDEVICEINSTANCE lpddi, LPVOID pvRef )
		{
			HRESULT ret;
			LPDIRECTINPUTDEVICE8 p_dev;

			ret = p_dinput->CreateDevice( lpddi->guidInstance, &p_dinput_device, NULL );

			if( ret != DI_OK )
			{
				return DIENUM_CONTINUE;
			}

			p_dinput_device->QueryInterface( IID_IDirectInputDevice8, ( LPVOID * )&p_dinput_device );

			return DIENUM_STOP;
		}

		int initialize_dinput( HWND hwnd )
		{

			HINSTANCE hinst = GetModuleHandle( NULL ); //–‚–@
			HRESULT ret = 0;

			ret = DirectInput8Create( hinst, DIRECTINPUT_VERSION, IID_IDirectInput8, ( void ** )& p_dinput, NULL );

			auto release_dinput =
				[]()
			{
				p_dinput_device->Release();
				p_dinput_device = nullptr;
				p_dinput->Release();
				p_dinput = nullptr;
				return FALSE;
			};

			//p_dinput_device = nullptr;

			//find joystick
			ret = p_dinput->EnumDevices( DI8DEVCLASS_GAMECTRL, ( LPDIENUMDEVICESCALLBACK )get_joystick_callback, NULL, DIEDFL_ATTACHEDONLY );

			if( p_dinput_device == nullptr )
			{
				p_dinput->Release();
				p_dinput = nullptr;
				return TRUE;
			}

			//set dataformat

			ret = p_dinput_device->SetDataFormat( std::addressof( c_dfDIJoystick ) );

			if( ret != DI_OK )
			{
				release_dinput();
				return FALSE;
			}

			//set mode
			//‹¦’²ƒ‚[ƒh‚ðÝ’è
			ret = p_dinput_device->SetCooperativeLevel( hwnd, DISCL_NONEXCLUSIVE | DISCL_FOREGROUND );

			if( ret != DI_OK )
			{
				release_dinput();
				return FALSE;
			}

			DIPROPRANGE diprg;


			//set range of axis
			ret = p_dinput_device->EnumObjects( enum_direction_callback, ( VOID* )hwnd, DIDFT_AXIS );
			p_dinput_device->Acquire();

			joypad_available = true;

			return TRUE;
		}

		void joystick::update()
		{
			//initialize
			std::fill( direction_, direction_ + DIRECTION_NUM, false );
			std::fill( button_, button_ + BUTTON_NUM, false );

			if( joypad_available )
			{
				DIJOYSTATE di_joystate;
				p_dinput_device->Poll();
				HRESULT ret = p_dinput_device->GetDeviceState( sizeof DIJOYSTATE, std::addressof( di_joystate ) );

				enum
				{
					E_BUTTON_R,
					E_BUTTON_L,
					E_BUTTON_U,
					E_BUTTON_D
				};

				if( ret == DI_OK )
				{
					//“ü—Í‚ÌŠi”[
					if( di_joystate.lX > 100 )
					{
						//game_main::global
						direction_[ E_BUTTON_R ] = true;
					}
					if( di_joystate.lX < -100 )
					{
						direction_[ E_BUTTON_L ] = true;
					}
					if( di_joystate.lY > 100 )
					{
						direction_[ E_BUTTON_U ] = true;
					}
					if( di_joystate.lY < -100 )
					{
						direction_[ E_BUTTON_D ] = true;
					}

				}

			}

		}
	}
}