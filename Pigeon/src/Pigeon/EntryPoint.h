#pragma once

// �����ͻ���Ӧ�ó���

#ifdef PG_PLATFORM_WINDOWS

// exturn���������ļ��ı���
extern Pigeon::Application* Pigeon::CreateApplication();

void main()
{
	auto app = Pigeon::CreateApplication();
	app->Run();
	delete app;
}

#endif // PG_PLATFORM_WINDOWS
