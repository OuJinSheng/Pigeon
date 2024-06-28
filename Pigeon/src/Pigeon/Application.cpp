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

	Application* Application::s_Instance = nullptr;

	Application::Application()
	{
		PG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application()
	{

	}

	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}

	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		//PG_CORE_TRACE("{0}", e.ToString());

		// ������
		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
		{
			(*--it)->OnEvent(e);
			if (e.Handled)
				break;
		}
	}
	
	void Application::Run()
	{
		while (m_Running)
		{
			glClearColor(0, 0, 0, 1);

			// �õ�ǰ���������ֵ��GL_COLOR_BUFFER_BITָ�����ɫ����
			glClear(GL_COLOR_BUFFER_BIT);

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}

}
