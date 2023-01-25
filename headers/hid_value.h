#pragma once

#include "..\headers\custom_types.h"
#include "..\headers\text_d2d.h"

#include <hidpi.h>

namespace hid
{
    class hid_device;

    class hid_value : public _HIDP_VALUE_CAPS
    {
        private:
            
            text information;

            //ulong value_unsigned { 0 };
            long value_signed { 0 };

            hid_device * device { nullptr };

        public:

            hid_value( hid_device * const in_device , const _HIDP_VALUE_CAPS & construct_value );

            void  set_information_text();
            void  set_text_position( const vertex & in_position ) { information.set_position_top_left( in_position ); }
            void  append_information_text( std::wstring in_text ) { information.add_content( in_text ); }

            float get_text_right() const { return information.get_right(); }
            float get_text_top()   const { return information.get_top(); }

            void  update( RAWINPUT & in_raw_data );

            //hid_device * get_device() const { return device; }
            long         get_value() const { return value_signed; }

            void  draw() const { information.draw(); }
    };
}