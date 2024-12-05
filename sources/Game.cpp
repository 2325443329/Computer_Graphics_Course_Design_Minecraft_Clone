#include "Game.h"
#include "LensFlare.h"

World					Game::world;
Sun						Game::sun;
Moon					Game::moon;
Sky						Game::sky;
std::stack<glm::mat4>	Game::matrices = {};
Player					Game::player;
Camera					Game::fixed_cam;
bool					Game::fix_cam = false;
bool					Game::fake_cam = false;
bool					Game::in_water = false;
bool					Game::stop_moving = false;
bool					Game::debug = false;
float					Game::time = 0.f;

// 初始化游戏
void Game::init()
{
	// 初始化
	Shader::init();
	Texture::init();
	FrameBuffer::init();
	LensFlare::init();

	// 玩家
	matrices.push(glm::mat4(1.f));
	player = Player(glm::vec3(0.f, Chunk::height + 3.f, 0.f));

	// 世界
	world.init(std::time(NULL), player.get_position());
	sun.init();
	moon.init();
	sky.init();
}

// 处理事件
void Game::checks_events(const SDL_Event& my_event)
{
	if (my_event.type == SDL_KEYUP)
	{
		// 激活调试模式
		if (my_event.key.keysym.sym == SDLK_p)
			debug = !debug;

		// 飞行模式
		if (my_event.key.keysym.sym == SDLK_m)
			player.fly = !player.fly;

		// 切换视角
		if (my_event.key.keysym.sym == SDLK_F5)
			player.first_person = !player.first_person;

		// 固定摄像头
		if (my_event.key.keysym.sym == SDLK_o)
		{
			fix_cam = !fix_cam;
			fixed_cam = player.camera;
		}

		// 玩家按下键盘"-"和"="键进行切换角色皮肤
		if (my_event.key.keysym.sym == SDLK_MINUS) // "-"键切换到上一个皮肤
		{
			player.switch_skin(false);  // 切换到上一个皮肤
		}
		else if (my_event.key.keysym.sym == SDLK_EQUALS) // "="键切换到下一个皮肤
		{
			player.switch_skin(true);  // 切换到下一个皮肤
		}

		// 玩家按下键盘1-9键来选择方块
		if (my_event.key.keysym.sym == SDLK_0) 
		{
			std::cout << "玩家选择草方块" << std::endl;
			player.block_type = 0; // 选择草方块
		}
		else if (my_event.key.keysym.sym == SDLK_1) 
		{
			std::cout << "玩家选择泥土方块" << std::endl;
			player.block_type = 1; // 选择泥土方块
		}
		else if (my_event.key.keysym.sym == SDLK_2) 
		{
			std::cout << "玩家选择石方块" << std::endl;
			player.block_type = 2; // 选择石方块
		}
		else if (my_event.key.keysym.sym == SDLK_3) 
		{
			std::cout << "玩家选择沙子方块" << std::endl;
			player.block_type = 3; // 选择沙子方块
		}
		else if (my_event.key.keysym.sym == SDLK_4) 
		{
			std::cout << "玩家选择木块方块" << std::endl;
			player.block_type = 4; // 选择木块方块
		}
		else if (my_event.key.keysym.sym == SDLK_5) 
		{
			std::cout << "玩家选择树叶方块" << std::endl;
			player.block_type = 5; // 选择树叶方块
		}
		else if (my_event.key.keysym.sym == SDLK_6) 
		{
			std::cout << "玩家选择雪方块" << std::endl;
			player.block_type = 6; // 选择雪方块
		}
		else if (my_event.key.keysym.sym == SDLK_7) 
		{
			std::cout << "玩家选择杂草方块" << std::endl;
			player.block_type = 7; // 选择杂草方块
		}
		else if (my_event.key.keysym.sym == SDLK_8)  
		{
			std::cout << "玩家选择郁金香方块" << std::endl;
			player.block_type = 8; // 选择郁金香方块
		}
		else if (my_event.key.keysym.sym == SDLK_9)  
		{
			std::cout << "玩家选择兰花方块" << std::endl;
			player.block_type = 9; // 选择兰花方块
		}
		else if (my_event.key.keysym.sym == SDLK_F1)  // 新添加：F1键选择蒲公英方块
		{
			std::cout << "玩家选择蒲公英方块" << std::endl;
			player.block_type = 10; // 选择蒲公英方块
		}


	}

	// 退出窗口
	if ((my_event.type == SDL_KEYUP && my_event.key.keysym.sym == SDLK_ESCAPE) || (stop_moving && my_event.type == SDL_MOUSEBUTTONUP))
	{
		stop_moving = !stop_moving;
		SDL_ShowCursor(stop_moving);
		SDL_WarpMouseInWindow(Window::window, Window::center.x, Window::center.y);
		glm::ivec2 mouse_pos = Window::center;
		SDL_Delay(100);
	}
	

	// 放置与破坏方块
	else if (my_event.type == SDL_MOUSEBUTTONUP)
	{
		// 破坏一个方块
		if (my_event.button.button == SDL_BUTTON_LEFT) // 假设左键破坏方块
		{
			player.break_block();
		}
		// 放置方块
		else if (my_event.button.button == SDL_BUTTON_RIGHT) // 假设右键放置方块
		{
			player.place_block();
		}
	}		
}

// 更新游戏
void Game::update(glm::ivec2& mouse_pos)
{
	time += frame_duration;

	// 移动
	player.move(SDL_GetKeyboardState(NULL), world);

	// 摄像头
	if (!stop_moving)
	{
		SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
		player.look(mouse_pos);
		SDL_WarpMouseInWindow(Window::window, Window::center.x, Window::center.y);
	}

	player.update_head();
	in_water = player.camera.get_position().y < water_level;

	// 生成世界网格
	world.send_meshes();

	// 更新怪物
	world.update_mobs(player.get_position());

	// 更新太阳、月亮和天空
	sun.update(player.get_position());
	moon.update(player.get_position());
	sky.update(player.get_position(), sun.get_position().y - player.get_position().y);
}

// 渲染游戏场景
void Game::draw()
{
	Light test_1(Light::Type::Point, glm::vec3(0., 40., 0.), Color(1., 1., 1., 1.), 100.f);
	Light test_2(Light::Type::Point, glm::vec3(0., 40., 100.), Color(1., 1., 1., 1.), 100.f);
	Light test_3(Light::Type::Point, glm::vec3(100., 40., 0.), Color(1., 1., 1., 1.), 100.f);

	std::vector<const Light*> lights = { sun.get_light(), moon.get_light(), sky.get_light() };

	Camera render_camera = fix_cam ? fixed_cam : player.camera;

	// 渲染反射效果
	render_camera.invert(water_level);
	render_camera.change_resolution(Window::size.x * reflection_quality, Window::size.y * reflection_quality);
	fake_cam = true;

	FrameBuffer::reflection.bind();
	{
		FrameBuffer::clear();

		player.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
		world.draw_mobs(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
		world.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level + 0.4f));
		sun.draw(render_camera, lights);
		moon.draw(render_camera, lights);
		sky.draw(render_camera, lights);
	}
	FrameBuffer::unbind();

	//渲染折射效果
	render_camera = fix_cam ? fixed_cam : player.camera;
	render_camera.change_resolution(Window::size.x, Window::size.y);
	fake_cam = false;

	FrameBuffer::refraction.bind();
	{
		FrameBuffer::clear();

		player.draw(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level));
		world.draw_mobs(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level));
		world.draw(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level + 0.6f));

		if (debug)
			world.draw_debug(render_camera);
	}
	FrameBuffer::unbind();

	// 渲染游戏场景
	FrameBuffer::game.bind();
	{
		FrameBuffer::clear();

		player.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
		world.draw_mobs(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
		world.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
		sun.draw(render_camera, lights);
		moon.draw(render_camera, lights);
		sky.draw(render_camera, lights);

		if (debug)
			world.draw_debug(render_camera);

		FrameBuffer::reflection.get_texture().bind(0);
		FrameBuffer::refraction.get_texture().bind(1);
		{
			world.draw_water(render_camera, lights);
		}
		Texture::unbind();
		Texture::unbind();
	}
	FrameBuffer::unbind();

	if (in_water)
	{
		// 渲染折射效果
		FrameBuffer::refraction.bind();
		{
			FrameBuffer::clear();

			player.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
			world.draw_mobs(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
			world.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level + 0.4f));
			sun.draw(render_camera, lights);
			moon.draw(render_camera, lights);
			sky.draw(render_camera, lights);

			if (debug)
				world.draw_debug(render_camera);
		}
		FrameBuffer::unbind();

		// 渲染游戏场景
		FrameBuffer::game.bind();
		{
			FrameBuffer::clear();

			player.draw(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level));
			world.draw_mobs(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level));
			world.draw(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level));
			sky.draw(render_camera, lights);

			if (debug)
				world.draw_debug(render_camera);

			FrameBuffer::refraction.get_texture().bind(1);
			{
				world.draw_water(render_camera, lights);
			}
			Texture::unbind();
		}
		FrameBuffer::unbind();
	}

	else
	{
		// 渲染反射效果
		render_camera.invert(water_level);
		render_camera.change_resolution(Window::size.x * reflection_quality, Window::size.y * reflection_quality);
		fake_cam = true;

		FrameBuffer::reflection.bind();
		{
			FrameBuffer::clear();

			player.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
			world.draw_mobs(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
			world.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level + 0.4f));
			sun.draw(render_camera, lights);
			moon.draw(render_camera, lights);
			sky.draw(render_camera, lights);
		}
		FrameBuffer::unbind();

		// 渲染折射效果
		render_camera = fix_cam ? fixed_cam : player.camera;
		render_camera.change_resolution(Window::size.x, Window::size.y);
		fake_cam = false;

		FrameBuffer::refraction.bind();
		{
			FrameBuffer::clear();

			player.draw(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level));
			world.draw_mobs(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level));
			world.draw(render_camera, lights, Plane(0.f, -1.f, 0.f, water_level + 0.6f));

			if (debug)
				world.draw_debug(render_camera);
		}
		FrameBuffer::unbind();

		// 渲染游戏场景
		FrameBuffer::game.bind();
		{
			FrameBuffer::clear();

			player.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
			world.draw_mobs(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
			world.draw(render_camera, lights, Plane(0.f, 1.f, 0.f, -water_level));
			sun.draw(render_camera, lights);
			moon.draw(render_camera, lights);
			sky.draw(render_camera, lights);

			if (debug)
				world.draw_debug(render_camera);

			FrameBuffer::reflection.get_texture().bind(0);
			FrameBuffer::refraction.get_texture().bind(1);
			{
				world.draw_water(render_camera, lights);
			}
			Texture::unbind();
			Texture::unbind();
		}
		FrameBuffer::unbind();
	}

	//镜头光晕效果
	FrameBuffer::lens_flare.bind();
	{
		FrameBuffer::clear();

		if (!in_water)
		{
			LensFlare::draw(render_camera, sun.get_position(), sun.get_light()->get_intensity() / 2.f, sun.get_light()->get_color());
			LensFlare::draw(render_camera, moon.get_position(), moon.get_light()->get_intensity() / 5.f, moon.get_light()->get_color());
		}
	}
	FrameBuffer::unbind();

	// 渲染最终效果
	VertexBuffer game(Shader::screen, Mesh::screen, DataType::Positions | DataType::TexCoords);

	Shader::screen.bind();
	FrameBuffer::game.get_texture().bind(0);
	FrameBuffer::lens_flare.get_texture().bind(1);
	Texture::cursor.bind(2);
	game.bind();
	{
		game.send_uniform("u_draw_cursor", int(!Game::fix_cam && player.first_person));
		game.send_texture("u_texture", 0);
		game.send_texture("u_lens_flare", 1);
		game.send_texture("u_cursor", 2);
		game.draw();
	}
	VertexBuffer::unbind();
	Texture::unbind();
	Texture::unbind();
	Shader::unbind();
}
