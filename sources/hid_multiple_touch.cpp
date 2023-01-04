#include "..\headers\hid_multiple_touch.h"

#include "..\headers\locate.h"

namespace hid
{
    hid_multiple_touch::hid_multiple_touch( const HINSTANCE instance , const LPWSTR parameters , const int show_flags )
    {
        OutputDebugString( L"hid_multi_touch::paramatised constructor\n" );

        locate::set_application( this );

        window.initialise( instance , parameters , show_flags );
        graphics.initialise();
        write.initialise();
        //usages.initialise();
        input.initialise();

    }

    void hid_multiple_touch::start()
    {
        update();
    }

    void hid_multiple_touch::update()
    {
        while( state == states::running )
        {
            window.update();
            graphics.draw_begin();
            //input.update();
            input.draw();
            graphics.draw_end();
        }
    }

    hid_multiple_touch::~hid_multiple_touch()
    {
        OutputDebugString( L"hid_multi_touch::de-constructor\n" );
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