#include <iostream>
using namespace std;
#include "obj_import.h"
#include "camera.h"

/**
 * @brief callback function that's triggered whenever the window framebuffer size is changed
 * @param window current active GLFW window
 * @param width width of the buffer
 * @param height height of the buffer
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processUserInput(GLFWwindow* window);
void cube(GLfloat center_position_X, GLfloat center_position_Y, GLfloat center_position_Z, GLfloat edgeLength);

Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float deltaTime = 0.0f;
float lastFrame = 0.0f;

const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

float X_limit = SCREEN_WIDTH / 2.0f;
float Y_limit = SCREEN_HEIGHT / 2.0f;
bool first_mouse_action = true; //< keeps track of whether a mouse movement has happened so far.

/**
 * @brief driver code to draw the scene and interact with it
 * @return execution status (integer) - zero indicating success.
 */
int main()
{
    glfwInit();
    // use OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "IS F311 Assignment 2", NULL, NULL);
    if (window == NULL)
    {
        cout << "Could not create to create GLFW window" << endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); 
    // glMatrixMode(GL_PROJECTION); 
    // glLoadIdentity(); 
    // glOrtho(0, SCREEN_WIDTH, 0, SCREEN_HEIGHT, 0, 1000); 
    // glMatrixMode(GL_MODELVIEW); 
    // glLoadIdentity();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Could not initialize GLAD." << std::endl;
        return -1;
    }

    glEnable(GL_DEPTH_TEST); 

    Shader blender_shader("vertex_shader.glsl", "fragment_shader.glsl");

    char blender_data_path[45] = "resources/bed.obj"; // blender model containing a bed and a 
    ObjImport blender_object(blender_data_path);
    while (!glfwWindowShouldClose(window))
    {
    	// cout << "Inside the loop now"; // debug
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processUserInput(window);
        // draw a cube
        // glTranslatef(X_limit, Y_limit, -500 );
        // glTranslatef(X_limit, Y_limit, 500 );
        
        // cube(X_limit, Y_limit, -500, 200);
        // glPopMatrix();

        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        blender_shader.use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        blender_shader.setMat4("projection", projection);
        blender_shader.setMat4("view", view);

        // render the loaded model
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); 
        model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));
        blender_shader.setMat4("model", model);
        blender_object.Draw(blender_shader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

/**
 * @brief process mouse movement
 * @param window active GLFW window
 */
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (first_mouse_action)
    {
        X_limit = xpos;
        Y_limit = ypos;
        first_mouse_action = false;
    }

    float xoffset = xpos - X_limit;
    float yoffset = Y_limit - ypos; // reversed since y-coordinates go from bottom to top

    X_limit = xpos;
    Y_limit = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

/*
 * @brief handle user scrolling the mouse scroll wheel
 * @xoffset  
 */
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}


/**
 * @brief draws a cube centred at given coordinate
 * @param center_position_X centre of the cube: x-coordinate
 * @param center_position_Y centre of the cube: y-coordinate
 * @param center_position_Z centre of the cube: z-coordinate
 * @param edgeLength length of side of cube
 */
void cube(GLfloat center_position_X, GLfloat center_position_Y, GLfloat center_position_Z, GLfloat edgeLength )
{
    GLfloat half_edge = edgeLength * 0.5f; //< half the length of the edge
    
    GLfloat vertices[] =
    {
        // front side
        center_position_X - half_edge, center_position_Y + half_edge, center_position_Z + half_edge, // top left
        center_position_X + half_edge, center_position_Y + half_edge, center_position_Z + half_edge, // top right
        center_position_X + half_edge, center_position_Y - half_edge, center_position_Z + half_edge, // bottom right
        center_position_X - half_edge, center_position_Y - half_edge, center_position_Z + half_edge, // bottom left
        
        // left side
        center_position_X - half_edge, center_position_Y + half_edge, center_position_Z + half_edge, // top left
        center_position_X - half_edge, center_position_Y + half_edge, center_position_Z - half_edge, // top right
        center_position_X - half_edge, center_position_Y - half_edge, center_position_Z - half_edge, // bottom right
        center_position_X - half_edge, center_position_Y - half_edge, center_position_Z + half_edge, // bottom left

        // right side
		center_position_X + half_edge, center_position_Y + half_edge, center_position_Z + half_edge, // top left
		center_position_X + half_edge, center_position_Y + half_edge, center_position_Z - half_edge, // top right
		center_position_X + half_edge, center_position_Y - half_edge, center_position_Z - half_edge, // bottom right
		center_position_X + half_edge, center_position_Y - half_edge, center_position_Z + half_edge, // bottom left


        // back side
        center_position_X - half_edge, center_position_Y + half_edge, center_position_Z - half_edge, // top left
        center_position_X + half_edge, center_position_Y + half_edge, center_position_Z - half_edge, // top right
        center_position_X + half_edge, center_position_Y - half_edge, center_position_Z - half_edge, // bottom right
        center_position_X - half_edge, center_position_Y - half_edge, center_position_Z - half_edge, // bottom left
                
        // top of cube
        center_position_X - half_edge, center_position_Y + half_edge, center_position_Z + half_edge, // top left
        center_position_X - half_edge, center_position_Y + half_edge, center_position_Z - half_edge, // top right
        center_position_X + half_edge, center_position_Y + half_edge, center_position_Z - half_edge, // bottom right
        center_position_X + half_edge, center_position_Y + half_edge, center_position_Z + half_edge, // bottom left
        
        // bottom of cube
        center_position_X - half_edge, center_position_Y - half_edge, center_position_Z + half_edge, // top left
        center_position_X - half_edge, center_position_Y - half_edge, center_position_Z - half_edge, // top right
        center_position_X + half_edge, center_position_Y - half_edge, center_position_Z - half_edge, // bottom right
        center_position_X + half_edge, center_position_Y - half_edge, center_position_Z + half_edge  // bottom left
    };
    
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glColor3f(1, 1, 0);
    glEnableClientState(GL_VERTEX_ARRAY);
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glDrawArrays(GL_QUADS, 0, 24);
    glDisableClientState(GL_VERTEX_ARRAY);
}

/**
 * @brief process user input via keyboard
 * @param window active GLFW window
 */
void processUserInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}