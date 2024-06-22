#pragma once

// �����

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"
#include "Pigeon/Events/ApplicationEvent.h"
#include "Pigeon/LayerStack.h"

namespace Pigeon {

	// ��Sanbox��ʹ�ô��࣬���ӹ�ȥ
	class PIGEON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window; // ����Ψһָ�룬����Window��һ��ʵ��
		bool m_Running = true;
		LayerStack m_LayerStack;	// ��ջ�ϴ������̳�Application����������

	private:
		static Application* s_Instance;
	};

	// �ڿͻ��˶��崴�������ڷ���һ��app�Ķ���
	Application* CreateApplication();
}


