#include "..\headers\gui_windows_ms.h"

#include < cassert >
//#include < windows.h >
//#include < string >

//#include "..\headers\globals.h"
//#include "..\headers\locate.h"

namespace hid
{
    void gui_windows_ms::initialise( const HINSTANCE in_instance , const LPWSTR in_parameters , const int in_show_flags )
    {
        instance = in_instance; parameters = in_parameters; show_flags = in_show_flags;

        window_class.cbSize = sizeof( WNDCLASSEX );

        window_class.style         = CS_HREDRAW | CS_VREDRAW;
        window_class.lpfnWndProc   = gui_windows_ms::main_window_process;
        window_class.hInstance     = in_instance;//instance;//GetModuleHandle( 0 ); //instance that contains the window procedure for the class.
        window_class.lpszClassName = L"Precision input";//class_name;

        window_class.cbClsExtra    = 0; // extra bytes after structure
        window_class.cbWndExtra    = 0; // extra bytes following the window instance.
        window_class.hbrBackground = ( HBRUSH ) ( COLOR_WINDOW + 1 ); //( HBRUSH ) ( COLOR_GRAYTEXT + 1 );		//brush_background;
        window_class.hCursor       = LoadCursor( nullptr , IDC_ARROW );
        window_class.hIcon         = 0;
        window_class.hIconSm       = 0;
        window_class.lpszMenuName  = 0;

        ATOM atom{};

        atom = RegisterClassEx( &window_class );

        //error( L"register class ex" );

        window_principle = CreateWindowEx( WS_EX_COMPOSITED | WS_EX_TRANSPARENT ,//style_extra ,
                                           L"Precision input" ,//class_name ,
                                           L"application" ,//title_text ,
                                           WS_OVERLAPPEDWINDOW | WS_VISIBLE | WS_MAXIMIZE ,//style ,
                                           0 , 0 ,//x , y , 
                                           200 , 200 ,//CW_USEDEFAULT, CW_USEDEFAULT,//width , height ,
                                           0 ,//parent_window , 
                                           0 ,//menu ,
                                           in_instance ,//instance ,
                                           this );

        assert( window_principle != nullptr );

        locate::provide_window( window_principle );

        //if( window_principle == nullptr ) error( L"create window ex" );

        //UpdateWindow( hWnd );
    }

    int gui_windows_ms::message_loop()
    {
        while( GetMessage( &message , 0 , 0 , 0 ) )
        {
            TranslateMessage( &message );
            DispatchMessage( &message );
        }

        return message.message;
    }

    // This is just used to forward Windows messages from a global window
    // procedure to our member function window procedure because we cannot
    // assign a member function to WNDCLASS::lpfnWndProc.

    LRESULT CALLBACK gui_windows_ms::main_window_process( HWND in_window , UINT message , WPARAM w_param , LPARAM l_param )
    {
        // If we are creating the window, set the window_ptr to the instance of CAppWindow associated with the window as the HWND's user data.
        // That way when we get messages besides WM_CREATE we can call the instance's WndProc and reference non-static member variables.

        if( message == WM_NCCREATE )
        {
            CREATESTRUCT * create_ptr = reinterpret_cast< CREATESTRUCT * >( l_param );

            this_pointer = static_cast< gui_windows_ms * >( create_ptr->lpCreateParams );

            SetWindowLongPtr( in_window , GWLP_USERDATA , reinterpret_cast< LONG_PTR >( this_pointer ) );

            //this_ptr->window_ptr = window_ptr;   
        }
        else
        {
            this_pointer = reinterpret_cast< gui_windows_ms * >( GetWindowLongPtr( in_window , GWLP_USERDATA ) );
        }

        if( this_pointer )
            return this_pointer->message_handler( in_window , message , w_param , l_param );

        return DefWindowProc( in_window , message , w_param , l_param );
    }

    //window::~window()

    LRESULT gui_windows_ms::message_handler( HWND in_window , UINT message , WPARAM wParam , LPARAM lParam )
    {
        switch( message )
        {
            case WM_CREATE:
            {
            } break;

            case WM_DESTROY:
            {
                PostQuitMessage( 0 );
            } break;

            case WM_PAINT:
            {
               //paint.draw();
            } break;

            case WM_SIZE:
            {
               //paint.resize();
            } break;

            case WM_KEYDOWN:
            {
                switch( wParam )
                {
                    case VK_ESCAPE:
                    {
                        PostQuitMessage( 0 );
                        //DestroyWindow( in_window );
                    } break;

                }
            }

        } // switch( message )

        return DefWindowProc( in_window , message , wParam , lParam );

    } // message_handler

} // namespace hid

//GetClassInfo( hInst , thisClassName , &wincl ))

//SetWindowPos
      //HMONITOR monitor = MonitorFromWindow( GetModuleHandle(0) , MONITOR_DEFAULTTONEAREST);
      //MONITORINFO monitor_info {};
      //GetMonitorInfo( monitor , & monitor_info );
      //S_OK