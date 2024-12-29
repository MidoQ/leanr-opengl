#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

const int renderWidth = 800;
const int renderHeight = 600;

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
    GLFWwindow* window = initWindow();
    if (!window) {
        std::cout << "Fail to init window!" << std::endl;
        return -1;
    }

    // 渲染循环，在窗口关闭前一直渲染
    while(!glfwWindowShouldClose(window))
    {
        // 检测键盘输入
        processInput(window);

        // 使用特定颜色清屏
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        
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

void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
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
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
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
