#include "pch.hpp"
#include "Shaders.hpp"
#include "Callbacks.hpp"
#include "Input.hpp"

using std::string;

float Vertices[] = {
	0.5f,  0.5f,  0.0f,
	0.5f, -0.5f,  0.0f,
   -0.5f, -0.5f,  0.0f,
   -0.5f,  0.5f,  0.0f
};

unsigned int Indices[] = {
	0, 1, 3,
	1, 2, 3
};

int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(
		800,
		600,
		"learning opengl",
		nullptr,
		nullptr
	);

	if (!window)
	{
		std::cout << "failed to create glfw window";
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "failed to initialize glad";
		return -1;
	}

	glViewport(0, 0, 800, 600);

	glfwSetFramebufferSizeCallback(window, FrameBufferSizeCallback);

	unsigned int vao, vbo, ebo;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &ebo);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Indices), Indices, GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		3 * sizeof(float),
		static_cast<void*>(nullptr)
	);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	const string vertexShaderSource = LoadShaderSource("shaders/vertex.glsl");
	const string fragmentShaderSource = LoadShaderSource("shaders/fragment.glsl");

	const unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER, vertexShaderSource);
	const unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource);
	const unsigned int shaderProgram = CreateShaderProgram(vertexShader, fragmentShader);

	// wireframe mode:
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	float timeValue = static_cast<float>(glfwGetTime());
	float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
	int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

	while (!glfwWindowShouldClose(window))
	{
		ProcessInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);

		timeValue = static_cast<float>(glfwGetTime());
		greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");

		glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(vao);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(1, &vbo);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}