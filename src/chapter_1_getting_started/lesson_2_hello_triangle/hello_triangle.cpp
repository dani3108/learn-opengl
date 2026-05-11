#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

constexpr int DISPLAY_WIDTH { 800 };
constexpr int DISPLAY_HEIGHT { 600 };

// Variables to check for shader compilation success
GLint success;
GLchar infoLog[512];

// Vertex data of a triangle
constexpr GLfloat vertices[] {
    -0.5f, -0.5f, 0.0f,
    +0.5f, -0.5f, 0.0f,
    +0.0f, +0.5f, 0.0f
};

// Vertex shader
// We simply take the input data and forward to the shader output
// We could normalize the data here for instance
const GLchar* vertexShaderSource { 
    "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0"
};

// Fragment shader
// We define a vec4 to represent RGBA
// The purpose of this shader is to calculate the color of our pixels
const GLchar* fragmentShaderSource {
    "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "    FragColor = vec4(1.0f, 0.5f, 0.2f, 0.5f);\n"
    "}\0"
};

// Window resize callback function
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

// Function to process user input
void processInput(GLFWwindow* window);

int main() 
{
    // ********************************
    // INITIALIZATION
    // ********************************

    // Initialize GLFW
    glfwInit();

    // Specify OpenGL version 3.3 and CORE profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // If MacOS this line is also needed
    #ifdef __APPLE__
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif

    // Create window object and check for success
    GLFWwindow* window { glfwCreateWindow(DISPLAY_WIDTH, DISPLAY_HEIGHT, "Hello Triangle", NULL, NULL) };
    if(!window) {
        std::cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        return -1;
    }

    // Make context of the window the current context
    glfwMakeContextCurrent(window);

    // Init GLAD and check for success
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cerr << "Failed to initialize GLAD\n";
        return -1;
    }

    // Assign callback function for whenever we resize the window
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // ********************************
    // SHADER CREATION AND COMPILATION
    // ********************************

    // Create a vertex shader object
    GLuint vertexShader { glCreateShader(GL_VERTEX_SHADER) };

    // Attach the shader code to the shader object and compile the shader
    // The shader needs to be dinamically compiled during runtime for OpenGL to use it
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    // Check if the shader compiled successfully
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if(!success) 
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED // " << infoLog << '\n';
    }
    else
        std::cout << "Vertex shader compiled successfully.\n";

    // Create a fragment shader object
    GLuint fragmentShader { glCreateShader(GL_FRAGMENT_SHADER) };

    // Attach the code and compile
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    // Check if the shader compiled successfully
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if(!success) 
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED // " << infoLog << '\n';
    }
    else
        std::cout << "Fragment shader compiled successfully.\n";

    // Create our shader program
    // To use compiled shaders, we LINK them to the program
    // Then we activate the program when rendering stuff
    GLuint shaderProgram { glCreateProgram() };
        
    // Attach shaders to the shader program and link them
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);


    // Check if linking the shader program failed
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) 
    {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cerr << "ERROR::SHADER::PROGRAM::LINKING_FAILED // " << infoLog << '\n';
    }
    else 
        std::cout << "Shader program linking successful.\n";

    // Delete shader objects after linking, not needed after that
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // ********************************
    // VERTEX DATA AND ATTRIBUTES SETUP
    // ********************************

    // Create a Vertex Buffer Object (VBO) and Vertex Attribute Object (VAO)
    // The VBO is a buffer ("array") used to send data to the GPU
    // The VAO stores the info on how to interpret the VBO data
    // A reference/id to the buffer is stored in a GLuint variable
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    // 1) Bind our VAO
    // We dont need to specify a target since there are no different VAO types
    glBindVertexArray(VAO);

    // 2) Bind our buffer (VBO) to the ARRAY_BUFFER target
    // A target is a binding point (a slot in OpenGL's state) for a specific type of buffer, it holds no data
    // We need to bind an object to the target so OpenGL known on which object to operate
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 3) Copy our vertex data into the currently bound buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 4) Tell OpenGL how to interpret our vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Now we can enable the vertex attribute (vertex id is 0 as specified in the shader)
    glEnableVertexAttribArray(0);

    // The call to glVertexAttribPointer "saved" a reference to the VBO, we can unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO so future calls cant accidentally modify it
    glBindVertexArray(0); 

    // Render loop
    while(!glfwWindowShouldClose(window))
    {
        // Input processing
        processInput(window);

        // Background color
        glClearColor(0.2f, 0.3f, 0.4f, 0.5f);
        glClear(GL_COLOR_BUFFER_BIT);

        // Render triangle

        // Activate the newly created shader program (after linking the shaders)
        // Every shader and render call will now use this program
        glUseProgram(shaderProgram);

        // Bind VAO
        // We only have one so its not necessary to bind it every time
        glBindVertexArray(VAO);

        // Draw a triangle with the VBO vertex data
        glDrawArrays(GL_TRIANGLES, 0, 3);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Terminate GLFW library and free resources
    glfwTerminate();
    return 0;
}

// Keep the screen filled in after resizing the window
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Check if user presses ESC to quit program
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
