#include "Mesh.h"
#include "Model.h"
#include "Camera.h"
#include <iostream>
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void cube(GLfloat center_position_X, GLfloat center_position_Y, GLfloat center_position_Z, GLfloat edgeLength);

// settings
const unsigned int SCREEN_WIDTH = 800;
const unsigned int SCREEN_HEIGHT = 600;

// camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = SCREEN_WIDTH / 2.0f;
float lastY = SCREEN_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main()
{
    glfwInit();
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

    glViewport(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT); 
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

    Shader blenderShader("vertex_shader.glsl", "fragment_shader.glsl");

    char blenderModel[45] = "bed.obj"; // blender model containing a bed and a 
    Model blenderObject(blenderModel);
    while (!glfwWindowShouldClose(window))
    {
    	// cout << "Inside the loop now";
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // draw a cube
        processInput(window);
        glTranslatef(lastX, lastY, -500 );
        glTranslatef(lastX, lastY, 500 );
        
        cube(lastX, lastY, -500, 200);
        glPopMatrix();
        // render
        // ------
        glClearColor(0.05f, 0.05f, 0.05f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


        // glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCREEN_WIDTH / (float)SCREEN_HEIGHT, 0.1f, 100.0f);
        // glm::mat4 view = camera.GetViewMatrix();
        // blenderShader.setMat4("projection", projection);
        // blenderShader.setMat4("view", view);

        // // render the loaded model
        // glm::mat4 model = glm::mat4(1.0f);
        // model = glm::translate(model, glm::vec3(0.0f, -1.75f, 0.0f)); // translate it down so it's at the center of the scene
        // model = glm::scale(model, glm::vec3(0.2f, 0.2f, 0.2f));	// it's a bit too big for our scene, so scale it down
        // blenderShader.setMat4("model", model);
        // blenderObject.Draw(blenderShader);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
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

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}

void cube(GLfloat center_position_X, GLfloat center_position_Y, GLfloat center_position_Z, GLfloat edgeLength )
{
    GLfloat half_edge = edgeLength * 0.5f;
    
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