#pragma once

// �����ͻ���Ӧ�ó���

#ifdef PG_PLATFORM_WINDOWS

// exturn���������ļ��ı���
extern Pigeon::Application* Pigeon::CreateApplication();

void main()
{
	Pigeon::Log::Init();	// �ǵ���"Pigeon.h"�е�����ͷ�ļ�
	PG_CORE_WARN("Initialized log");
	int a = 5;
	PG_INFO("Hello Var={0}", a);

	auto app = Pigeon::CreateApplication();
	app->Run();
	delete app;
}

#endif // PG_PLATFORM_WINDOWS
