#pragma once

// �����

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Pigeon {

	// ��Sanbox��ʹ�ô��࣬���ӹ�ȥ
	class PIGEON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

	private:
		std::unique_ptr<Window> m_Window; // ����Ψһָ�룬����Window��һ��ʵ��
		bool m_Running = true;
	};

	// �ڿͻ��˶��崴�������ڷ���һ��app�Ķ���
	Application* CreateApplication();
}


