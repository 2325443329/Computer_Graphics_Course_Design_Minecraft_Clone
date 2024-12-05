#include "Game.h"
#include <iostream>  // 用于输出到控制台

int main(int argc, char* argv[])
{
    bool running = true;

    // 初始化库
    if (!Window::init())
        return EXIT_FAILURE;

    // 初始化游戏
    Game::init();
    std::thread generation_thread([&running]() { while (running) Game::world.generate(Game::player.get_position()); });

    // 设置鼠标
    glm::ivec2 mouse_pos = Window::center;
    SDL_WarpMouseInWindow(Window::window, Window::center.x, Window::center.y);
    SDL_ShowCursor(SDL_DISABLE);  // 禁用鼠标光标
    SDL_Delay(100);  // 延迟100ms，确保鼠标已隐藏

    // FPS 计数器初始化
    uint32_t last_time = SDL_GetTicks();  // 上一次更新时间
    int frame_count = 0;  // 帧计数器

    // 程序主循环
    while (running)
    {
        uint32_t time_begin = SDL_GetTicks();  // 获取当前时间（毫秒）

        // 处理事件
        SDL_Event sdl_event;

        while (SDL_PollEvent(&sdl_event))  // 轮询事件
        {
            switch (sdl_event.type)
            {
            case SDL_WINDOWEVENT:
                switch (sdl_event.window.event)
                {
                case SDL_WINDOWEVENT_CLOSE:  // 处理窗口关闭事件
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
                Game::checks_events(sdl_event);  // 检查游戏中的事件
                lock.unlock();
            }
        }

        // 更新游戏状态
        lock.lock();
        Game::update(mouse_pos);
        lock.unlock();

        // 渲染场景
        FrameBuffer::clear();  // 清空缓冲区

        lock.lock();
        Game::draw();  // 绘制游戏内容
        lock.unlock();

        SDL_GL_SwapWindow(Window::window);  // 刷新窗口内容

        // 计算帧率
        uint32_t time_end = SDL_GetTicks();  // 获取结束时间

        // 更新帧计数器
        frame_count++;
        uint32_t elapsed = time_end - last_time;  // 计算已过去的时间（毫秒）

        if (elapsed >= 1000)  // 每秒更新一次
        {
            // 每秒输出一次 FPS 到控制台
            std::cout << "FPS: " << frame_count << std::endl;

            frame_count = 0;  // 重置帧计数器
            last_time = time_end;  // 更新上次更新时间
        }
        
        // 限制帧率，保持每帧时间稳定
        if (time_end - time_begin < frame_duration_ms)
            SDL_Delay(frame_duration_ms - (time_end - time_begin));  // 延迟剩余的时间，确保每帧的持续时间一致
    }

    generation_thread.join();  // 等待生成线程完成
    Window::clear();  // 清理窗口资源

    return 0;
}
