#include <windows.h>
#include <iostream>

#include "duski/duski.h"
#include "duski/tools.h"

using namespace Duski;

int main() {
    DuskiWindow duski_window(800, 600);
    DuskiAPI duski(API::OPENGL, duski_window);
    
    MSG msg;
    bool running = true;
    while (running) {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE)) {
            if (msg.message == WM_QUIT) running = false;
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        
        duski.set_background_color(Tools::ColorRGBA(35, 35, 35, 255));
        duski.fill_rect(
            0, 0,
            Tools::Decuple(50), Tools::Decuple(50),
            Tools::ColorRGBA(120, 250, 57, 255)
        );

        duski.render();
    }

    duski.shutdown();

    return 0;
}
