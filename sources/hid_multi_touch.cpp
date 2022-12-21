#include "..\headers\hid_multi_touch.h"
#include "..\headers\hid_device.h"

#include "..\headers\locate.h"

namespace hid
{
    using namespace std;

    hid_multi_touch::hid_multi_touch( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
    //: gui_microsoft::gui_microsoft( instance , parameters , show_flags )
    {

        OutputDebugString( L"\n hid_multi_touch::constructor" );

        //graphics.initialise( get_window() );
        ////grid.initialise();
        //write.initialise();
        //usages.initialise();

        //input.initialise();

        //message_loop();
    }

    hid_multi_touch::~hid_multi_touch()
    {
        OutputDebugString( L"\n hid_multi_touch::de-constructor" );
    }

} // namespace hid


// touchpad HID - mouse + keyboard
// one finger/point = context
// two finger = navigation - mouse window_ptr | context | direct touch 
// three = move window
// 
// five = keyboard
// ten finger 

/* references:
*    windows/driver samples/hid/hclient
*    www-user.tu-chemnitz.de/~heha/hsn/free.var , hidparse
*    stackoverflow.com
*    quuxplusone.github.io/blog/2021/03/03/push-back-emplace-back/
*    C++ How to program 10th edition , Deitel & Associates, Inc , ISBN-10: 0-13-444823-5 , ISBN-13: 978-0-13-444823-7
*/

// input_modifiers  ( buttons , values , features ) 
                  // output_modifiers
                  // 
                  // press over force threshold for capital letter
                  // delay after press for context 
                  // combined movement is mouse // 
                  // 
