#pragma once

// �����

#include "Core.h"

namespace Pigeon {

	// ��Sanbox��ʹ�ô��࣬���ӹ�ȥ
	class PIGEON_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// �ڿͻ��˶��崴��
	Application* CreateApplication();
}


