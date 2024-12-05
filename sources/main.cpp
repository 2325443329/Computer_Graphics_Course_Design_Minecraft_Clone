#include "Game.h"
#include <iostream>  // �������������̨

int main(int argc, char* argv[])
{
    bool running = true;

    // ��ʼ����
    if (!Window::init())
        return EXIT_FAILURE;

    // ��ʼ����Ϸ
    Game::init();
    std::thread generation_thread([&running]() { while (running) Game::world.generate(Game::player.get_position()); });

    // �������
    glm::ivec2 mouse_pos = Window::center;
    SDL_WarpMouseInWindow(Window::window, Window::center.x, Window::center.y);
    SDL_ShowCursor(SDL_DISABLE);  // ���������
    SDL_Delay(100);  // �ӳ�100ms��ȷ�����������

    // FPS ��������ʼ��
    uint32_t last_time = SDL_GetTicks();  // ��һ�θ���ʱ��
    int frame_count = 0;  // ֡������

    // ������ѭ��
    while (running)
    {
        uint32_t time_begin = SDL_GetTicks();  // ��ȡ��ǰʱ�䣨���룩

        // �����¼�
        SDL_Event sdl_event;

        while (SDL_PollEvent(&sdl_event))  // ��ѯ�¼�
        {
            switch (sdl_event.type)
            {
            case SDL_WINDOWEVENT:
                switch (sdl_event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:  // �����ڹر��¼�
                    lock.lock();
                    running = false;
                    lock.unlock();
                    break;

                default:
                    break;
                }
                break;

            default:
                lock.lock();
                Game::checks_events(sdl_event);  // �����Ϸ�е��¼�
                lock.unlock();
            }
        }

        // ������Ϸ״̬
        lock.lock();
        Game::update(mouse_pos);
        lock.unlock();

        // ��Ⱦ����
        FrameBuffer::clear();  // ��ջ�����

        lock.lock();
        Game::draw();  // ������Ϸ����
        lock.unlock();

        SDL_GL_SwapWindow(Window::window);  // ˢ�´�������

        // ����֡��
        uint32_t time_end = SDL_GetTicks();  // ��ȡ����ʱ��

        // ����֡������
        frame_count++;
        uint32_t elapsed = time_end - last_time;  // �����ѹ�ȥ��ʱ�䣨���룩

        if (elapsed >= 1000)  // ÿ�����һ��
        {
            // ÿ�����һ�� FPS ������̨
            std::cout << "FPS: " << frame_count << std::endl;

            frame_count = 0;  // ����֡������
            last_time = time_end;  // �����ϴθ���ʱ��
        }
        
        // ����֡�ʣ�����ÿ֡ʱ���ȶ�
        if (time_end - time_begin < frame_duration_ms)
            SDL_Delay(frame_duration_ms - (time_end - time_begin));  // �ӳ�ʣ���ʱ�䣬ȷ��ÿ֡�ĳ���ʱ��һ��
    }

    generation_thread.join();  // �ȴ������߳����
    Window::clear();  // ��������Դ

    return 0;
}
