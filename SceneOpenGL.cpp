#include "SceneOpenGL.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <iostream>
#include <string>

SceneOpenGL::SceneOpenGL(const Options& options) :
    m_options(options), m_window(0), m_GLContext(0), m_input(), m_useJoysticks(false)
{
}

SceneOpenGL::~SceneOpenGL()
{
    m_input.closeJoysticks();
    SDL_GL_DeleteContext(m_GLContext);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool SceneOpenGL::initWindow(const std::string& windowTitle)
{
    if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) == -1)
    {
        std::cout << "Error while initializing SDL : " << SDL_GetError() << std::endl;
        SDL_Quit();

        return false;
    }

    if(SDL_NumJoysticks())
        m_useJoysticks = true;

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    if(m_options.fullscreen) m_window = SDL_CreateWindow(windowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_options.width, m_options.height,
        SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL|SDL_WINDOW_FULLSCREEN);
    else m_window = SDL_CreateWindow(windowTitle.c_str(),
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        m_options.width, m_options.height,
        SDL_WINDOW_SHOWN|SDL_WINDOW_OPENGL);

    if(m_window == 0)
    {
        std::cout << "Error while creating window : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }

    m_GLContext = SDL_GL_CreateContext(m_window);

    if(!m_GLContext)
    {
        std::cout << "Error while creating context : " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }

    {
        int width, height;
        SDL_GetWindowSize(m_window, &width, &height);
        glViewport(0, 0, width, height);
    }

    return true;
}

bool SceneOpenGL::initGL()
{
    #ifdef WIN32
    GLenum initGLEW( glewInit() );

    if(initGLEW != GLEW_OK)
    {
        std::cout << "Error while initializing GLEW : " << glewGetErrorString(initGLEW) << std::endl;
        SDL_GL_DeleteContext(m_GLContext);
        SDL_DestroyWindow(m_window);
        SDL_Quit();

        return false;
    }
    #endif // WIN32

    glEnable(GL_DEPTH_TEST);

    return true;
}

void SceneOpenGL::mainLoop()
{
    using namespace glm;

    Shader shader_default("Shaders/texture.vert", "Shaders/texture.frag");
    Shader shader_background("Shaders/background.vert", "Shaders/background.frag");
    Shader shader_track("Shaders/texture.vert", "Shaders/track.frag");
    Shader shader_map("Shaders/map.vert", "Shaders/map.frag");

    const unsigned int frameRate(1000/60);

  if(m_useJoysticks)
    {
        m_input.openJoysticks();
        SDL_JoystickEventState(SDL_ENABLE);
    }

    const mat4 modelview_base(1);

    Ship ship(shader_default, "Models/ship.png", vec3(0,1,0), 0.014, 2.0, 900.0);
    Box box(shader_default, "Textures/debug.png", 50);
    Skybox skybox(shader_background, "Textures/skybox.png", 300);

    Track track(shader_track, shader_map, "Textures/road.png");

    track.beginBuild( Track::TrackProfile::flatProfile(30) );
    track.appendFlatWidthChange(20,40.006776); //adjust xx
    track.appendStraight(25);
    track.appendFlatWidthChange(30,35);
    track.appendTurn(glm::radians(60.),100);
    track.appendPipeIn(30,10,glm::radians(45.),50);
    track.appendTurn(glm::radians(-150.),250,32);
    track.appendTwist(glm::radians(90.),150);
    track.appendPipeOut(30,75);
    track.appendPipeIn(55,0,glm::radians(-80.),175);
    track.appendQuarter(glm::radians(90.),200);
    track.appendTurn(glm::radians(-90.),150);
    track.appendQuarter(glm::radians(90.),200,64);
    track.appendPipeOut(35,150);
    track.appendQuarter(glm::radians(90.),200,64);
    track.appendStraight(31.745621); // adjust yy
    track.appendQuarter(glm::radians(-90.),150,32);
    track.appendStraight(50-18.132910); // adjust zz
    track.appendTurn(glm::radians(90.),109.3);
    track.appendQuarter(glm::radians(-25.),25);
    track.appendFlatWidthChange(30,49.85);
    track.appendQuarter(glm::radians(25.),25);
    track.appendTurn(glm::radians(180.),184.75,64);
    track.endBuild();

    Camera camera(12.0, 4.0, vec3(0,1,0), perspective(70.0f, static_cast<float>(m_options.width)/m_options.height, 5.f, 1000.0f));

    m_input.afficherPtr(true);
    m_input.capturePtr(false);

    Texture texture("Textures/metal029b.jpg");

    glClearColor(1,0,1,1);
    glLineWidth(20.);

    int frames = 0;
    const unsigned int startProgram = SDL_GetTicks();
    while(!m_input.terminate())
    {
        const unsigned int startLoop = SDL_GetTicks();

        m_input.updateEvents();

        if(m_input.getKey(SDL_SCANCODE_ESCAPE))
            break;

        //std::cout << "--------------------" << std::endl;

        ship.control(m_input);

        { // move camera
            if (m_input.getKey(SDL_SCANCODE_I)) camera.m_type = Camera::SHIP_VIEW;
            if (m_input.getKey(SDL_SCANCODE_O)) camera.m_type = Camera::REPLAY_VIEW;
            if (m_input.getKey(SDL_SCANCODE_P)) camera.m_type = Camera::TRACK_VIEW;

            const mat4 projection = camera.getCameraProjection(ship, track, startLoop/1000.);
            const mat4 projection_inv = glm::inverse(projection);
            shader_default.setUniform("projection", projection);
            shader_background.setUniform("projection", projection);
            shader_background.setUniform("time", startLoop/1000.);
            shader_background.setUniform("projection_inv", projection_inv);
            shader_track.setUniform("projection", projection);
            shader_track.setUniform("time", startLoop/1000.);
            shader_map.setUniform("projection", projection);
            shader_map.setUniform("time", startLoop/1000.);

            /*
            vec4 camera_pos = projection_inv * vec4(0,0,0,1);
            camera_pos /= camera_pos.w;
            std::cout << "camera pos " << glm::to_string(camera_pos) << std::endl;
            */
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        { // background
            glm::mat4 modelview_local = modelview_base;
            modelview_local = glm::translate(modelview_local, camera.m_position);
            skybox.draw(modelview_local);
        }

        glClear(GL_DEPTH_BUFFER_BIT);

        // track
        track.draw(modelview_base);

        { // floating box
            float angle = frames*2.;
            glm::mat4 modelview_local = modelview_base;
            modelview_local = glm::translate(modelview_local, glm::vec3(200, 150, 200));
            modelview_local = glm::rotate(modelview_local, glm::radians(angle), glm::vec3(1,.2,-.4));
            box.draw(modelview_local);
        }

        // ship
        ship.draw(modelview_base);

        // Actualization
        SDL_GL_SwapWindow(m_window);

        // Framerate
        const unsigned int elapsed = SDL_GetTicks() - startLoop;
        if (elapsed < frameRate) SDL_Delay(frameRate - elapsed);
        frames++;
    }
    const unsigned int stopProgram = SDL_GetTicks();

    { // FPS stat
        const double elapsed = static_cast<double>(stopProgram - startProgram) / 1000;
        const double frameRateAvg = frames/elapsed;
        std::cout << "Ran for " << elapsed << "s" << std::endl;
        std::cout << "Frames : " << frames << std::endl;
        std::cout << "Framerate : " << frameRateAvg << std::endl;
    }
}
