#include "pgpch.h"
#include "WindowsWindow.h"

#include "Pigeon/Events/ApplicationEvent.h"
#include "Pigeon/Events/KeyEvent.h"
#include "Pigeon/Events/MouseEvent.h"

//#include <glad/glad.h>	// glad.h������glfw3.hǰ����
//#include <GLFW/glfw3.h>

namespace Pigeon {

	static bool s_GLFWInitialized = false;

	// ����ص�
	static void GLFWErrorCallback(int error_code, const char* description)
	{
		PG_CORE_ERROR("GLFW Error ({0}): {1}", error_code, description);
	}

	Window* Window::Create(const WindowProps& props)
	{
		return new WindowsWindow(props);
	}

	WindowsWindow::WindowsWindow(const WindowProps& props)
	{
		Init(props);
	}

	WindowsWindow::~WindowsWindow()
	{
		Shutdown();
	}

	void WindowsWindow::Init(const WindowProps& props)
	{
		m_Data.Title = props.Title;
		m_Data.Width = props.Width;
		m_Data.Height = props.Height;

		PG_CORE_INFO("Creating window {0} ({1} {2})", props.Title, props.Width, props.Height);

		if (!s_GLFWInitialized)
		{
			int success = glfwInit();
			PG_CORE_ASSERT(success, "Could not initialize GLFW!");

			glfwSetErrorCallback(GLFWErrorCallback);
			s_GLFWInitialized = true;
		}

		// ��ʼ��GLFW
		m_Window = glfwCreateWindow((int)props.Width, (int)props.Height, m_Data.Title.c_str(), nullptr, nullptr);
		glfwMakeContextCurrent(m_Window);
		// ��ʼ��Glad
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PG_CORE_ASSERT(status, "Failed to initialize Glad!");

		glfwSetWindowUserPointer(m_Window, &m_Data);	// ����ָ�����ڵ��û�����ָ�롣��ǰֵ����ֱ�����ڱ�����
		SetVSync(true);

		// ����GLFW�ص�
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						KeyPressedEvent event(key, 0);
						data.EventCallback(event);
						break;
					}
					
					case GLFW_RELEASE:
					{
						KeyReleasedEvent event(key);
						data.EventCallback(event);
						break;
					}
					
					case GLFW_REPEAT:
					{
						KeyPressedEvent event(key, 1);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
					case GLFW_PRESS:
					{
						MouseButtonPressedEvent event(button);
						data.EventCallback(event);
						break;
					}

					case GLFW_RELEASE:
					{
						MouseButtonReleasedEvent event(button);
						data.EventCallback(event);
						break;
					}
				}
			});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
	}

	void WindowsWindow::Shutdown()
	{
		glfwDestroyWindow(m_Window);
	}

	void WindowsWindow::OnUpdate()
	{
		/* <����GLFW�¼��Ĵ���>
		* GLFW��Ҫ���ڵ��봰��ϵͳ���н�����������Ϊ�˽����¼�������Ϊ��������Ӧ�ÿ�����û�п�ס���������ſɼ��Ĵ���ʱ���¼�������붨��ִ�У����������������ÿ֡�Ļ���������֮�����
		* ���������ַ�ʽ�����������¼�����ѯ��polling���͵ȴ���waiting)����glfwPollEvents()��glfwWaitEvent()
		* 
		* glwWaitEvents()
		* ��������Ⱦʱ������õ�ѡ������������Ϸ�����������ֻ��Ҫ���յ��µ���������һ����Ⱦ��glfwWaitEvents ���Ǹ��õ�ѡ��
		* ����һֱ�ȴ�ֱ���յ�����һ���¼������ͬʱ���Ὣ�߳̽�������״̬�� Ȼ���������յ����¼����⽫���ʡ������CPU���ڣ��������һЩ�޸���������˵�Ƿǳ����õ�
		*/

		/* <����GLFW��������>
		* GLFWĬ��ʹ��˫���弼��
		*/

		// ��ѯ�¼�������������
		glfwSwapBuffers(m_Window);
		glfwPollEvents();	
	}

	void WindowsWindow::SetVSync(bool enabled)
	{
		if (enabled)
			// �ȴ�1֡������
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		// �����Ƿ�����
		m_Data.VSync = enabled;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_Data.VSync;
	}
}