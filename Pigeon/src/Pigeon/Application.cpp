#include "pgpch.h"
#include "Application.h"

#include "Pigeon/Log.h"

#include <GLFW/glfw3.h>

/*
* std::bind
* ����������������һ���ɵ��ö���callable object��������һ���µĿɵ��ö���������Ӧ��ԭ����Ĳ����б�
* �ɰ󶨲�����ԭ������Ҫ�����ò���ʱ������ref()
* ����Ҫ���õķ�ʽ�Ѳ������ݸ�ģ�庯��ʱ������ref(), ref()���ð�װ����reference_wrapper������ԭ���ᱻʶ���ֵ���ͣ���reference_wrapper����ʽת��Ϊ�����õ�ֵ����������
*/
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

namespace Pigeon {


	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		PG_CORE_TRACE("{0}", e.ToString());
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 0, 1, 1);

			// �õ�ǰ���������ֵ��GL_COLOR_BUFFER_BITָ�����ɫ����
			glClear(GL_COLOR_BUFFER_BIT);
			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
