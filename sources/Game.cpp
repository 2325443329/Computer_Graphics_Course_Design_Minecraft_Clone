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

// ��ʼ����Ϸ
void Game::init()
{
	// ��ʼ��
	Shader::init();
	Texture::init();
	FrameBuffer::init();
	LensFlare::init();

	// ���
	matrices.push(glm::mat4(1.f));
	player = Player(glm::vec3(0.f, Chunk::height + 3.f, 0.f));

	// ����
	world.init(std::time(NULL), player.get_position());
	sun.init();
	moon.init();
	sky.init();
}

// �����¼�
void Game::checks_events(const SDL_Event& my_event)
{
	if (my_event.type == SDL_KEYUP)
	{
		// �������ģʽ
		if (my_event.key.keysym.sym == SDLK_p)
			debug = !debug;

		// ����ģʽ
		if (my_event.key.keysym.sym == SDLK_m)
			player.fly = !player.fly;

		// �л��ӽ�
		if (my_event.key.keysym.sym == SDLK_F5)
			player.first_person = !player.first_person;

		// �̶�����ͷ
		if (my_event.key.keysym.sym == SDLK_o)
		{
			fix_cam = !fix_cam;
			fixed_cam = player.camera;
		}

		// ��Ұ��¼���"-"��"="�������л���ɫƤ��
		if (my_event.key.keysym.sym == SDLK_MINUS) // "-"���л�����һ��Ƥ��
		{
			player.switch_skin(false);  // �л�����һ��Ƥ��
		}
		else if (my_event.key.keysym.sym == SDLK_EQUALS) // "="���л�����һ��Ƥ��
		{
			player.switch_skin(true);  // �л�����һ��Ƥ��
		}

		// ��Ұ��¼���1-9����ѡ�񷽿�
		if (my_event.key.keysym.sym == SDLK_0) 
		{
			std::cout << "���ѡ��ݷ���" << std::endl;
			player.block_type = 0; // ѡ��ݷ���
		}
		else if (my_event.key.keysym.sym == SDLK_1) 
		{
			std::cout << "���ѡ����������" << std::endl;
			player.block_type = 1; // ѡ����������
		}
		else if (my_event.key.keysym.sym == SDLK_2) 
		{
			std::cout << "���ѡ��ʯ����" << std::endl;
			player.block_type = 2; // ѡ��ʯ����
		}
		else if (my_event.key.keysym.sym == SDLK_3) 
		{
			std::cout << "���ѡ��ɳ�ӷ���" << std::endl;
			player.block_type = 3; // ѡ��ɳ�ӷ���
		}
		else if (my_event.key.keysym.sym == SDLK_4) 
		{
			std::cout << "���ѡ��ľ�鷽��" << std::endl;
			player.block_type = 4; // ѡ��ľ�鷽��
		}
		else if (my_event.key.keysym.sym == SDLK_5) 
		{
			std::cout << "���ѡ����Ҷ����" << std::endl;
			player.block_type = 5; // ѡ����Ҷ����
		}
		else if (my_event.key.keysym.sym == SDLK_6) 
		{
			std::cout << "���ѡ��ѩ����" << std::endl;
			player.block_type = 6; // ѡ��ѩ����
		}
		else if (my_event.key.keysym.sym == SDLK_7) 
		{
			std::cout << "���ѡ���Ӳݷ���" << std::endl;
			player.block_type = 7; // ѡ���Ӳݷ���
		}
		else if (my_event.key.keysym.sym == SDLK_8)  
		{
			std::cout << "���ѡ�������㷽��" << std::endl;
			player.block_type = 8; // ѡ�������㷽��
		}
		else if (my_event.key.keysym.sym == SDLK_9)  
		{
			std::cout << "���ѡ����������" << std::endl;
			player.block_type = 9; // ѡ����������
		}
		else if (my_event.key.keysym.sym == SDLK_F1)  // ����ӣ�F1��ѡ���ѹ�Ӣ����
		{
			std::cout << "���ѡ���ѹ�Ӣ����" << std::endl;
			player.block_type = 10; // ѡ���ѹ�Ӣ����
		}


	}

	// �˳�����
	if ((my_event.type == SDL_KEYUP && my_event.key.keysym.sym == SDLK_ESCAPE) || (stop_moving && my_event.type == SDL_MOUSEBUTTONUP))
	{
		stop_moving = !stop_moving;
		SDL_ShowCursor(stop_moving);
		SDL_WarpMouseInWindow(Window::window, Window::center.x, Window::center.y);
		glm::ivec2 mouse_pos = Window::center;
		SDL_Delay(100);
	}
	

	// �������ƻ�����
	else if (my_event.type == SDL_MOUSEBUTTONUP)
	{
		// �ƻ�һ������
		if (my_event.button.button == SDL_BUTTON_LEFT) // ��������ƻ�����
		{
			player.break_block();
		}
		// ���÷���
		else if (my_event.button.button == SDL_BUTTON_RIGHT) // �����Ҽ����÷���
		{
			player.place_block();
		}
	}		
}

// ������Ϸ
void Game::update(glm::ivec2& mouse_pos)
{
	time += frame_duration;

	// �ƶ�
	player.move(SDL_GetKeyboardState(NULL), world);

	// ����ͷ
	if (!stop_moving)
	{
		SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
		player.look(mouse_pos);
		SDL_WarpMouseInWindow(Window::window, Window::center.x, Window::center.y);
	}

	player.update_head();
	in_water = player.camera.get_position().y < water_level;

	// ������������
	world.send_meshes();

	// ���¹���
	world.update_mobs(player.get_position());

	// ����̫�������������
	sun.update(player.get_position());
	moon.update(player.get_position());
	sky.update(player.get_position(), sun.get_position().y - player.get_position().y);
}

// ��Ⱦ��Ϸ����
void Game::draw()
{
	Light test_1(Light::Type::Point, glm::vec3(0., 40., 0.), Color(1., 1., 1., 1.), 100.f);
	Light test_2(Light::Type::Point, glm::vec3(0., 40., 100.), Color(1., 1., 1., 1.), 100.f);
	Light test_3(Light::Type::Point, glm::vec3(100., 40., 0.), Color(1., 1., 1., 1.), 100.f);

	std::vector<const Light*> lights = { sun.get_light(), moon.get_light(), sky.get_light() };

	Camera render_camera = fix_cam ? fixed_cam : player.camera;

	// ��Ⱦ����Ч��
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

	//��Ⱦ����Ч��
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

	// ��Ⱦ��Ϸ����
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
		// ��Ⱦ����Ч��
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

		// ��Ⱦ��Ϸ����
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
		// ��Ⱦ����Ч��
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

		// ��Ⱦ����Ч��
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

		// ��Ⱦ��Ϸ����
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

	//��ͷ����Ч��
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

	// ��Ⱦ����Ч��
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
