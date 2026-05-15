#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

constexpr int DISPLAY_WIDTH { 800 };
constexpr int DISPLAY_HEIGHT { 600 };

// Variables to check for shader compilation success
GLint success;
GLchar infoLog[512];

// Vertex data of a triangle
constexpr GLfloat vertices[]{
     0.5f,  0.5f, 0.0f,  // top right
     0.5f, -0.5f, 0.0f,  // bottom right
    -0.5f, -0.5f, 0.0f,  // bottom left
    -0.5f,  0.5f, 0.0f   // top left
};

constexpr GLuint indices[] = {  // note that we start from 0!
    0, 1, 3,   // first triangle
    1, 2, 3    // second triangle
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
void framebuffer_size_callback(GLFWwindow*, int width, int height);

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
    // VERTEX DATA (VBO)
    // VERTEX ATTRIBUTES (VAO)
    // VERTEX INDECES (EBO)
    // ********************************

    // Create a Vertex Buffer Object (VBO), Vertex Attribute Object (VAO) and Element Buffer Object (EBO)
    // The VBO is a buffer ("array") used to send data to the GPU
    // The VAO stores the info on how to interpret the VBO data
    // The EBO stores indeces that OpenGL uses to decide which vertices to draw
    // The EBO helps us render a square with only 4 vertices instead of 6 (3 vertices per triangle that makes up the square)
    // A reference/id to each object is stored in a GLuint variable
    GLuint VAO, VBO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    // 1) Bind our VAO
    // We dont need to specify a target since there are no different VAO types
    glBindVertexArray(VAO);

    // 2) Bind our buffer (VBO) to the ARRAY_BUFFER target
    // A target is a binding point (a slot in OpenGL's state) for a specific type of buffer, it holds no data
    // We need to bind an object to the target so OpenGL known on which object to operate
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // 2.5) Copy our vertex data into the currently bound buffer's memory
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 3) Bind the EBO to the ELEMENT_ARRAY_BUFFER
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    // 3.5) Similar to the VBO, we copy the data into the bound buffer
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 4) Tell OpenGL how to interpret our vertex data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

    // Now we can enable the vertex attribute (vertex id is 0 as specified in the shader)
    glEnableVertexAttribArray(0);

    // The call to glVertexAttribPointer "saved" a reference to the VBO, we can unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // Unbind the VAO so future calls cant accidentally modify it
    glBindVertexArray(0);

    // Draw in wireframe mode
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // Future drawing calls will still use wireframe
    // We need to set it back to default
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

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

        // Draw a triangle with the VBO vertex data (before)
        // glDrawArrays(GL_TRIANGLES, 0, 3);
        // With the EBO, we can draw from the indeces instead
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Check and call events and swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // Deallocate the resources we've used (optional)
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteProgram(shaderProgram);

    // Terminate GLFW library and free resources
    glfwTerminate();
    return 0;
}

// Keep the screen filled in after resizing the window
void framebuffer_size_callback(GLFWwindow*, int width, int height)
{
    glViewport(0, 0, width, height);
}

// Check if user presses ESC to quit program
void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}
