#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

const int renderWidth = 800;
const int renderHeight = 600;
char infoLog[512];

const char* vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "out vec4 vertexColor;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "   vertexColor = vec4(0.5, 0.0, 0.5, 1.0);\n"
                                 "}\0";

const char* fragmentShaderSource = "#version 330 core\n"
                                   "in vec4 vertexColor;\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "    FragColor = vertexColor;\n"
                                   "}\0";

/**
 * @brief 窗口大小改变时，同步改变viewport大小
 */
void framebuffer_size_callback(GLFWwindow* window, int width, int height);

/**
 * @brief 处理键盘输入
 */
void processInput(GLFWwindow* window);

/**
 * @brief 初始化窗口
 */
GLFWwindow* initWindow();

/**
 * 主函数
 */
int main()
{
    float vertices[] = {
        0.5f, 0.5f, 0.0f,   // 右上角
        0.5f, -0.5f, 0.0f,  // 右下角
        -0.5f, -0.5f, 0.0f, // 左下角
        -0.5f, 0.5f, 0.0f   // 左上角
    };
    unsigned int indices[] = {
        0, 1, 3,
        1, 2, 3
    };
    unsigned int VBO, VAO, EBO;

    unsigned int vertexShader;
    unsigned int fragmentShader;
    unsigned int shaderProgram;
    int shaderCompileSuccess;
    int shaderLinkSuccess;

    // 初始化窗口
    GLFWwindow* window = initWindow();
    if (!window) {
        std::cout << "Fail to init window!" << std::endl;
        return -1;
    }

    // 创建VAO，用于保存顶点属性
    glGenVertexArrays(1, &VAO);
    // 创建VBO和EBO，并使VAO与VBO关联
    glGenBuffers(1, &VBO);  // VBO里放顶点
    glGenBuffers(1, &EBO);  // EBO里放顶点索引
    glBindVertexArray(VAO);

    // 将顶点数据复制到VBO缓冲
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // 将顶点数据复制到EBO缓冲索引
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // 指定顶点数据格式并启用顶点属性
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // 解绑VBO和VAO
    // 注意EBO和VAO不能解绑，否则会丢失EBO的调用
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // 加载并编译顶点着色器
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if(!shaderCompileSuccess)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);      // 使用线框模式
    // glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);      // 使用填充模式（默认）

    // 加载并编译片段着色器
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &shaderCompileSuccess);
    if(!shaderCompileSuccess)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
        return -1;
    }

    // 创建着色器程序，并链接顶点着色器和片段着色器
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &shaderLinkSuccess);
    if(!shaderLinkSuccess) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::LINK_FAILED\n" << infoLog << std::endl;
        return -1;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // 渲染循环，在窗口关闭前一直渲染
    while (!glfwWindowShouldClose(window)) {
        // 检测键盘输入
        processInput(window);

        // 使用特定颜色清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // 检查是否发生事件
        glfwPollEvents();
        // 交换缓冲（将后台缓冲送显）
        glfwSwapBuffers(window);
    }

    // 释放资源，结束渲染
    glfwTerminate();

    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

GLFWwindow* initWindow()
{
    // 创建窗口
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(renderWidth, renderHeight, "LearnOpenGL", nullptr, nullptr);
    if (window == nullptr) {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    // 将窗口上下文设置为当前线程的上下文
    glfwMakeContextCurrent(window);

    // 加载GLAD，用于加载本机的OpenGL函数
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    // 设定viewport大小
    // viewport指的是渲染的范围，它未必需要和窗口一样大
    glViewport(0, 0, renderWidth, renderHeight);
    // 设置回调函数，在窗口大小改变时，同步改变viewport大小
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    return window;
}
